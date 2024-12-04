#include "minirt.h"

static void set_viewport_pixel_parameters(t_view *view, t_pixel_data *pixel_data) 
{
    t_vec3 viewport_u = {view->viewport_width, 0, 0};
    t_vec3 viewport_v = {0, -view->viewport_height, 0};
    pixel_data->pixel_delta_u = vec_mul(viewport_u, 1.0 / view->image_width);
    pixel_data->pixel_delta_v = vec_mul(viewport_v, 1.0 / view->image_height);
    t_vec3 viewport_upper_left = vec_sub(vec_sub(vec_sub(view->camera_center, view->focal_length),
		vec_mul(viewport_u, 0.5)),vec_mul(viewport_v, 0.5));
    pixel_data->pixel00_loc = vec_add(viewport_upper_left, vec_mul(vec_add(pixel_data->pixel_delta_u, pixel_data->pixel_delta_v), 0.5));
}

static int count_objects(t_object *obj_arr)
{
	int i;

	if (obj_arr == NULL)
		return (0);
	i = 0;
	while (obj_arr[i].object != NULL)
		i++;
	return (i);
}

static void calc_t_for_objects(float *t, t_object *obj_arr, size_t obj_cnt, t_ray ray)
{
	int i;

	i = 0;
	while (i < obj_cnt)
	{
		if (obj_arr[i].type == 0)
		{
			t_sphere *sphere = (t_sphere *)obj_arr[i].object;
			t[i] = hit_sphere(sphere->center, sphere->radius, ray);
		}
		else if (obj_arr[i].type == 1)
		{
			t_plane *plane = (t_plane *)obj_arr[i].object;
			t[i] = hit_plane(ray, plane);
		}
		else if (obj_arr[i].type == 2)
		{
			t_cylinder *cylinder = (t_cylinder *)obj_arr[i].object;
			t[i] = hit_cylinder(&ray, cylinder);
		}
		else if (obj_arr[i].type == 3)
		{
			t_cone *cone = (t_cone *)obj_arr[i].object;
			t[i] = hit_cone(&ray, cone);
		}
		i++;
	}
}


static unsigned int calc_color(t_data *data, t_color object_color, float *angles)
{
	int r, g, b;
	int i;

	r = data->amb_light->brightness * data->amb_light->color.r;
	g = data->amb_light->brightness * data->amb_light->color.g;
	b = data->amb_light->brightness * data->amb_light->color.b;
	i = 0;
	while (i < data->diff_lights_cnt)
	{
        r += object_color.r * angles[i] * data->diff_lights[i].brightness;
		r += data->diff_lights[i].brightness * angles[i] * data->diff_lights[i].color.r;
        g += object_color.g * angles[i] * data->diff_lights[i].brightness;
		g += data->diff_lights[i].brightness * angles[i] * data->diff_lights[i].color.g;
        b += object_color.b * angles[i] * data->diff_lights[i].brightness;
		b += data->diff_lights[i].brightness * angles[i] * data->diff_lights[i].color.b;
        i++;
	}
	r = r < 255 ? r : 255;
    g = g < 255 ? g : 255;
    b = b < 255 ? b : 255;
	return (rgb_to_hex(r, g, b));
}


unsigned int calc_color_for_object_pixel(t_data *data, t_pixel_data *pixel_data, float *angles)
{
	unsigned int	obj_type;
	unsigned int	color;
	void			*object;

	obj_type = data->objects[pixel_data->obj_index].type;
	object = data->objects[pixel_data->obj_index].object;
	if (obj_type == 0)
		color = calc_color(data, ((t_sphere *)object)->color, angles);
	else if (obj_type == 1)
		color = calc_color(data, ((t_plane *)object)->color, angles);
	else if (obj_type == 2)
		color = calc_color(data, ((t_cylinder *)object)->color, angles);
	else
		color = calc_color(data, ((t_cone *)object)->color, angles);

    return (color);
}
static float *calc_light_angles_for_object(t_data *data, t_pixel_data *pixel_data)
{
	t_light_calc_fn light_calc[4];
	t_point3 intersection;
	float *angles;
	void *object;
	unsigned int obj_type;
	int i;

	light_calc[0] = (t_light_calc_fn)calc_light_angle_sphere;
	light_calc[1] = (t_light_calc_fn)calc_light_angle_plane;
	light_calc[2] = (t_light_calc_fn)calc_light_angle_cylinder;
	light_calc[3] = (t_light_calc_fn)calc_light_angle_cone;
	angles = malloc(sizeof(float) * data->diff_lights_cnt);
	intersection = point_intersection(pixel_data->ray.orig, pixel_data->ray.dir, pixel_data->closest_t);
	obj_type = data->objects[pixel_data->obj_index].type;
	object = data->objects[pixel_data->obj_index].object;
	i = 0;
	while (i < data->diff_lights_cnt)
	{
		if (shaded_pixel(pixel_data->obj_index, intersection, data->diff_lights[i].origin, data))
			angles[i] = 0;
		else
			angles[i] = light_calc[obj_type](pixel_data->closest_t, pixel_data->ray, data->view, &(data->diff_lights[i]), object);
		i++;
	}
	return angles;
}

static float calc_closest_t(float *t_arr, int t_arr_size, int *obj_index)
{
	int i;
	float t_temp;

	t_temp = FLT_MAX;
	*obj_index = -1;
	i = 0;
	while (i < t_arr_size)
	{
		if (t_arr[i] > 0 && t_arr[i] < t_temp)
		{
			t_temp = t_arr[i];
			*obj_index = i;
		}
		i++;
	}
	if (*obj_index == -1)
		return (-1);
	return (t_temp);
}

void calc_params_for_pixel(t_data *data, t_pixel_data *pixel_data, int x, int y)
{
	float *t;
	t_point3 pixel_center;

	pixel_center = vec_add(pixel_data->pixel00_loc, 
		vec_add(vec_mul(pixel_data->pixel_delta_u, x),vec_mul(pixel_data->pixel_delta_v, y)));
	pixel_data->ray.orig = data->view->camera_center;
	pixel_data->ray.dir = unit_vector(vec_sub(pixel_center, data->view->camera_center));
	t = malloc(sizeof(float) * (data->objects_cnt + 1));
	calc_t_for_objects(t, data->objects, data->objects_cnt, pixel_data->ray);
	pixel_data->closest_t = calc_closest_t(t, data->objects_cnt, &pixel_data->obj_index);
	free(t);
}

unsigned int calc_color_for_pixel(t_data *data, t_pixel_data *pixel_data)
{
	float *angles;
	unsigned int color;

	angles = calc_light_angles_for_object(data, pixel_data);
	color = calc_color_for_object_pixel(data, pixel_data, angles);
	free(angles);
	return (color);
}

void create_image(t_img *img, t_data *data)
{
	t_pixel_data pixel_data;
	unsigned int color;
	int x;
	int y;

	set_viewport_pixel_parameters(data->view, &pixel_data);
    x = 0;
    while (x < IMAGE_WIDTH)
    {
        y = 0;
        while (y < IMAGE_HEIGHT)
        {
			calc_params_for_pixel(data, &pixel_data, x, y);
			if (pixel_data.closest_t < 0)
				my_mlx_pixel_put(img, x, y, 0xADD8E6);
			else
			{
				color = calc_color_for_pixel(data, &pixel_data);
				my_mlx_pixel_put(img, x, y, color);
			}
			y++;
        }
        x++;
    }
}
