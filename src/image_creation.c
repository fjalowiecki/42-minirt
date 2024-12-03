#include "minirt.h"

static void set_viewport_pixel_parameters(t_view *view, t_vec3 *pixel_delta_u, t_vec3 *pixel_delta_v, t_vec3 *pixel00_loc)
{
    t_vec3 viewport_u = {view->viewport_width, 0, 0};
    t_vec3 viewport_v = {0, -view->viewport_height, 0};
    *pixel_delta_u = vec_mul(viewport_u, 1.0 / view->image_width);
    *pixel_delta_v = vec_mul(viewport_v, 1.0 / view->image_height);
    t_vec3 viewport_upper_left = vec_sub(vec_sub(vec_sub(view->camera_center, view->focal_length),
		vec_mul(viewport_u, 0.5)),vec_mul(viewport_v, 0.5));
    *pixel00_loc = vec_add(viewport_upper_left, vec_mul(vec_add(*pixel_delta_u, *pixel_delta_v), 0.5));
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

static unsigned int calc_color(int obj_index, t_point3 intersection, t_data *data, t_color object_color, float *angles)
{
	int r, g, b;
	int i;

	r = data->amb_light->brightness * data->amb_light->color.r;
	g = data->amb_light->brightness * data->amb_light->color.g;
	b = data->amb_light->brightness * data->amb_light->color.b;
	i = 0;
	while (i < data->diff_lights_cnt)
	{
		if (shaded_pixel(obj_index, intersection, data->diff_lights[i].origin, data))
		{
			i++;
			continue;
		}
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

static unsigned int calc_parameters_for_object(int obj_index, float closest_t, t_ray ray, t_data *data)
{
	unsigned int pixel_color;
	int i;
	float *angles = malloc(sizeof(float) * data->diff_lights_cnt);

	i = 0;
	if (data->objects[obj_index].type == 0)
	{	
		t_sphere *sphere = data->objects[obj_index].object;
		while (i < data->diff_lights_cnt)
		{
			angles[i] = calc_light_angle_sphere(closest_t, ray.dir, data->view, &(data->diff_lights[i]), sphere);
			i++;
		}
		t_point3 intersection = point_intersection(ray.orig, ray.dir, closest_t);
		pixel_color = calc_color(obj_index, intersection, data, sphere->color, angles);
	}
	else if (data->objects[obj_index].type == 1)
	{
		t_plane *plane = data->objects[obj_index].object;
		while (i < data->diff_lights_cnt)
		{
			angles[i] = calc_light_angle_plane(closest_t, ray.dir, data->view, &(data->diff_lights[i]), plane);	
			i++;
		}
		t_point3 intersection = point_intersection(ray.orig, ray.dir, closest_t);
		pixel_color = calc_color(obj_index, intersection, data, plane->color, angles);
	}
	else if (data->objects[obj_index].type == 2)
	{
		t_cylinder *cylinder = data->objects[obj_index].object;
		while (i < data->diff_lights_cnt)
		{
			angles[i] = calc_light_angle_cylinder(closest_t, ray, data->view, &(data->diff_lights[i]), cylinder);
			i++;
		}
		t_point3 intersection = point_intersection(ray.orig, ray.dir, closest_t);
		pixel_color = calc_color(obj_index, intersection, data, cylinder->color, angles);
	}
	else if (data->objects[obj_index].type == 3)
	{
		t_cone *cone = data->objects[obj_index].object;
		while(i < data->diff_lights_cnt)
		{
			angles[i] = calc_light_angle_cone(closest_t, ray, data->view, &(data->diff_lights[i]), cone);
			i++;
		}	
		t_point3 intersection = point_intersection(ray.orig, ray.dir, closest_t);
		pixel_color = calc_color(obj_index, intersection, data, cone->color, angles);
	}
	free(angles);
	return pixel_color;
}

void create_image(t_img *img, t_data *data)
{
	t_ray ray;
	float *t;

	t_vec3 pixel_delta_u;
	t_vec3 pixel_delta_v;
	t_vec3 pixel00_loc;
	set_viewport_pixel_parameters(data->view, &pixel_delta_u, &pixel_delta_v, &pixel00_loc);

	ray.orig = data->view->camera_center;
    int x = 0;
    while (x < IMAGE_WIDTH)
    {
        int y = 0;
        while (y < IMAGE_HEIGHT)
        {
			t_point3 pixel_center = vec_add(pixel00_loc, vec_add(vec_mul(pixel_delta_u, x),vec_mul(pixel_delta_v, y)));
			ray.dir  = unit_vector(vec_sub(pixel_center, data->view->camera_center));

			t = malloc(sizeof(float) * (data->objects_cnt + 1));
			calc_t_for_objects(t, data->objects, data->objects_cnt, ray);
			float closest_t;
			int obj_index;
			closest_t = calc_closest_t(t, data->objects_cnt, &obj_index);
			if (closest_t < 0)
				my_mlx_pixel_put(img, x, y, 0xADD8E6);
			else
			{
				unsigned int pixel_color = calc_parameters_for_object(obj_index, closest_t, ray, data);
				my_mlx_pixel_put(img, x, y, pixel_color);
			}
			free(t);
			y++;
        }
        x++;
    }
}
