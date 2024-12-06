#include "minirt.h"

static float	pick_closest_t_and_its_obj(float *t_arr,
	int t_arr_size, int *obj_index)
{
	int		i;
	float	t_temp;

	if (t_arr_size == 0 || t_arr == NULL)
		return (-1);
	t_temp = T_MAX;
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

static void	calc_t_for_all_objects(float *t_arr,
	t_object *obj_arr, size_t obj_cnt, t_ray *ray)
{
	int	i;

	i = 0;
	if (obj_cnt == 0 || obj_arr == NULL)
		t_arr = NULL;
	while (i < obj_cnt)
	{
		if (obj_arr[i].type == 0)
			t_arr[i] = hit_sphere(ray, obj_arr[i].object);
		else if (obj_arr[i].type == 1)
			t_arr[i] = hit_plane(ray, obj_arr[i].object);
		else if (obj_arr[i].type == 2)
			t_arr[i] = hit_cylinder(ray, obj_arr[i].object);
		else if (obj_arr[i].type == 3)
			t_arr[i] = hit_cone(ray, obj_arr[i].object);
		i++;
	}
}

void	calc_ray_params_for_pixel(t_data *data,
	t_pixel_data *pixel_data, int x, int y)
{
	t_point3	pixel_center;

	pixel_center = vec_add(pixel_data->pixel00_loc,
			vec_add(vec_mul(pixel_data->pixel_delta_u, x),
				vec_mul(pixel_data->pixel_delta_v, y)));
	pixel_data->ray.orig = data->view->camera_center;
	pixel_data->ray.dir = unit_vector(vec_sub(pixel_center,
				data->view->camera_center));
}

void	calc_closest_t_for_ray(t_data *data,
	t_pixel_data *pixel_data)
{
	float		*t_arr;

	if (data->objects_cnt == 0)
		pixel_data->closest_t = -1;
	t_arr = malloc(sizeof(float) * data->objects_cnt);
	if (!t_arr)
	{
		free_resources(data);
		error_exit(MALL_ERR);
	}
	calc_t_for_all_objects(t_arr, data->objects,
		data->objects_cnt, &pixel_data->ray);
	pixel_data->closest_t = pick_closest_t_and_its_obj(t_arr, data->objects_cnt,
			&pixel_data->obj_index);
	free(t_arr);
}
