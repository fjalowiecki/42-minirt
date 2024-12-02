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

static void calc_t_for_objects(float *t, t_object *obj_arr, t_ray ray)
{
	int i;
	int obj_cnt;
	
	obj_cnt = count_objects(obj_arr);
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
		i++;
	}
}

static unsigned int calc_color(int brightness, t_color color, float angle)
{
	int r, g, b;

	r = color.r * angle * brightness;
	g = color.g * angle * brightness;
	b = color.b * angle * brightness;
	return (rgb_to_hex(r, g, b));
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

static unsigned int calc_parameters_for_object(int obj_index, float closest_t, t_ray ray, t_view *view, t_light *light, t_object *obj_arr)
{
	unsigned int pixel_color;

	if (obj_arr[obj_index].type == 0)
	{	
		t_sphere *sphere = obj_arr[obj_index].object;
		float angle = calc_light_angle_sphere(closest_t, ray.dir, view, light, sphere);	
		pixel_color = calc_color(light->brightness, sphere->color, angle);
	}
	else if (obj_arr[obj_index].type == 1)
	{
		t_plane *plane = obj_arr[obj_index].object;
		float angle = calc_light_angle_plane(closest_t, ray.dir, view, light, plane);	
		pixel_color = calc_color(light->brightness, plane->color, angle);
	}
	else if (obj_arr[obj_index].type == 2)
	{
		t_cylinder *cylinder = obj_arr[obj_index].object;
		float angle = calc_light_angle_cylinder(closest_t, ray, view, light, cylinder);	
		pixel_color = calc_color(light->brightness, cylinder->color, angle);
	}
	return pixel_color;
}

void create_image(t_img *img, t_view *view, t_light *light, t_object *obj_arr)
{
	t_ray ray;
	float *t;
	int obj_cnt;

	obj_cnt = count_objects(obj_arr);

	t_vec3 pixel_delta_u;
	t_vec3 pixel_delta_v;
	t_vec3 pixel00_loc;
	set_viewport_pixel_parameters(view, &pixel_delta_u, &pixel_delta_v, &pixel00_loc);

	ray.orig = view->camera_center;
    int x = 0;
    while (x < IMAGE_WIDTH)
    {
        int y = 0;
        while (y < IMAGE_HEIGHT)
        {
			t_point3 pixel_center = vec_add(pixel00_loc, vec_add(vec_mul(pixel_delta_u, x),vec_mul(pixel_delta_v, y)));
			ray.dir  = unit_vector(vec_sub(pixel_center, view->camera_center));

			t = malloc(sizeof(float) * (obj_cnt + 1));
			calc_t_for_objects(t, obj_arr, ray);
			float closest_t;
			int obj_index;
			closest_t = calc_closest_t(t, obj_cnt, &obj_index);
			if (closest_t < 0)
				my_mlx_pixel_put(img, x, y, 0xADD8E6);
			else
			{
				unsigned int pixel_color = calc_parameters_for_object(obj_index, closest_t, ray, view, light, obj_arr);
				my_mlx_pixel_put(img, x, y, pixel_color);
			}
			free(t);
			y++;
        }
        x++;
    }
}
