#include "minirt.h"

static unsigned int	calc_color(t_data *data,
	t_color obj_c, double *angles, t_pixel_data *pd)
{
	double	r;
	double	g;
	double	b;
	size_t	i;
	t_light	*a;

	a = data->amb_light;
	r = (obj_c.r / 255.0f) * a->brightness * (a->color.r / 255.0f);
	g = (obj_c.g / 255.0f) * a->brightness * (a->color.g / 255.0f);
	b = (obj_c.b / 255.0f) * a->brightness * (a->color.b / 255.0f);
	i = 0;
	while (i < data->diff_lights_cnt)
	{
		r += (obj_c.r / 255.0f) * pd->angles_diff[i] * data->diff_lights[i]
			.brightness * (data->diff_lights[i].color.r / 255.0f)
			+ calc_spec(pd->angles_spec[i], data->diff_lights[i].color.r);
		g += (obj_c.g / 255.0f) * pd->angles_diff[i] * data->diff_lights[i]
			.brightness * (data->diff_lights[i].color.g / 255.0f)
			+ calc_spec(pd->angles_spec[i], data->diff_lights[i].color.g);
		b += (obj_c.b / 255.0f) * pd->angles_diff[i] * data->diff_lights[i]
			.brightness * (data->diff_lights[i].color.b / 255.0f)
			+ calc_spec(pd->angles_spec[i], data->diff_lights[i].color.g);
		i++;
	}
	return (rgb_to_hex(r * 255, g * 255, b * 255));
}

static unsigned int	calc_color_for_object_pixel(t_data *data,
	t_pixel_data *pixel_data)
{
	unsigned int	obj_type;
	unsigned int	color;
	void			*object;

	obj_type = data->objects[pixel_data->obj_index].type;
	object = data->objects[pixel_data->obj_index].object;
	if (obj_type == 0)
		color = calc_color(data, ((t_sphere *)object)->color,
				pixel_data->angles_diff, pixel_data);
	else if (obj_type == 1)
		color = calc_color(data, ((t_plane *)object)->color,
				pixel_data->angles_diff, pixel_data);
	else if (obj_type == 2)
		color = calc_color(data, ((t_cylinder *)object)->color,
				pixel_data->angles_diff, pixel_data);
	else
		color = calc_color(data, ((t_cone *)object)->color,
				pixel_data->angles_diff, pixel_data);
	return (color);
}

static double	calc_specular_angles(t_vec3 normal,
	t_data *data, int i, t_point3 intersection)
{
	t_vec3	light_dir;
	t_vec3	view_dir;
	t_vec3	reflect_dir;
	double	spec_angle;

	light_dir = unit_vector(vec_sub(data->diff_lights[i].origin, intersection));
	view_dir = unit_vector(vec_sub(data->view->camera_center,
				data->view->focal_length));
	reflect_dir = vec_sub(vec_mul(normal, 2.0 * dot_product(normal, light_dir)),
			light_dir);
	reflect_dir = unit_vector(reflect_dir);
	view_dir = unit_vector(view_dir);
	spec_angle = fmax(0.0, dot_product(reflect_dir, view_dir));
	return (spec_angle);
}

static void	calc_light_angles_for_object(t_data *data,
	t_pixel_data *pixel_data, t_light_calc_fn *light_calc)
{
	t_point3		intersection;
	void			*object;
	unsigned int	obj_type;
	size_t			i;

	intersection = point_intersection(pixel_data->ray.orig,
			pixel_data->ray.dir, pixel_data->closest_t);
	obj_type = data->objects[pixel_data->obj_index].type;
	object = data->objects[pixel_data->obj_index].object;
	i = 0;
	while (i < data->diff_lights_cnt)
	{
		if (shaded_pixel(intersection,
				data->diff_lights[i].origin, data))
		{
			pixel_data->angles_diff[i] = 0;
			pixel_data->angles_spec[i] = 0;
		}
		else
		{
			pixel_data->angles_diff[i] = light_calc[obj_type](pixel_data,
					data->view, &(data->diff_lights[i]), object);
			pixel_data->angles_spec[i] = calc_specular_angles(
					pixel_data->normal, data, i, intersection);
		}
		i++;
	}
}

unsigned int	calc_color_for_pixel(t_data *data, t_pixel_data *pixel_data)
{
	unsigned int			color;
	static t_light_calc_fn	light_calc[4];

	light_calc[0] = (t_light_calc_fn)calc_light_angle_sphere;
	light_calc[1] = (t_light_calc_fn)calc_light_angle_plane;
	light_calc[2] = (t_light_calc_fn)calc_light_angle_cylinder;
	light_calc[3] = (t_light_calc_fn)calc_light_angle_cone;
	pixel_data->angles_diff = malloc(sizeof(double) * data->diff_lights_cnt);
	if (!pixel_data->angles_diff)
	{
		free_all(data);
		error_exit(MALL_ERR);
	}
	pixel_data->angles_spec = malloc(sizeof(double) * data->diff_lights_cnt);
	if (!pixel_data->angles_spec)
	{
		free_all(data);
		error_exit(MALL_ERR);
	}
	calc_light_angles_for_object(data, pixel_data, light_calc);
	color = calc_color_for_object_pixel(data, pixel_data);
	free(pixel_data->angles_diff);
	free(pixel_data->angles_spec);
	return (color);
}
