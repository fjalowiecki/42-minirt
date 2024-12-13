#include "minirt.h"

static unsigned int	calc_color(t_data *data,
	t_color object_color, float *angles)
{
	float	r;
	float	g;
	float	b;
	int		i;

	r = (object_color.r / 255.0f) * data->amb_light->brightness
		* (data->amb_light->color.r / 255.0f);
	g = (object_color.g / 255.0f) * data->amb_light->brightness
		* (data->amb_light->color.g / 255.0f);
	b = (object_color.b / 255.0f) * data->amb_light->brightness
		* (data->amb_light->color.b / 255.0f);
	i = 0;
	while (i < data->diff_lights_cnt)
	{
		r += (object_color.r / 255.0f) * angles[i] * data->diff_lights[i]
			.brightness * (data->diff_lights[i].color.r / 255.0f);
		g += (object_color.g / 255.0f) * angles[i] * data->diff_lights[i]
			.brightness * (data->diff_lights[i].color.g / 255.0f);
		b += (object_color.b / 255.0f) * angles[i] * data->diff_lights[i]
			.brightness * (data->diff_lights[i].color.b / 255.0f);
		i++;
	}
	return (rgb_to_hex(r * 255, g * 255, b * 255));
}

static unsigned int	calc_color_for_object_pixel(t_data *data,
	t_pixel_data *pixel_data, float *angles)
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

static void	calc_light_angles_for_object(t_data *data,
	t_pixel_data *pixel_data, t_light_calc_fn *light_calc, float *angles)
{
	t_point3		intersection;
	void			*object;
	unsigned int	obj_type;
	int				i;

	intersection = point_intersection(pixel_data->ray.orig,
			pixel_data->ray.dir, pixel_data->closest_t);
	obj_type = data->objects[pixel_data->obj_index].type;
	object = data->objects[pixel_data->obj_index].object;
	i = 0;
	while (i < data->diff_lights_cnt)
	{
		if (shaded_pixel(pixel_data->obj_index, intersection,
				data->diff_lights[i].origin, data))
			angles[i] = 0;
		else
			angles[i] = light_calc[obj_type](pixel_data,
					data->view, &(data->diff_lights[i]), object);
		i++;
	}
}

unsigned int	calc_color_for_pixel(t_data *data, t_pixel_data *pixel_data)
{
	float					*angles;
	unsigned int			color;
	static t_light_calc_fn	light_calc[4];

	light_calc[0] = (t_light_calc_fn)calc_light_angle_sphere;
	light_calc[1] = (t_light_calc_fn)calc_light_angle_plane;
	light_calc[2] = (t_light_calc_fn)calc_light_angle_cylinder;
	light_calc[3] = (t_light_calc_fn)calc_light_angle_cone;
	angles = malloc(sizeof(float) * data->diff_lights_cnt);
	if (!angles)
	{
		free_all(data);
		error_exit(MALL_ERR);
	}
	calc_light_angles_for_object(data, pixel_data, light_calc, angles);
	color = calc_color_for_object_pixel(data, pixel_data, angles);
	free(angles);
	return (color);
}
