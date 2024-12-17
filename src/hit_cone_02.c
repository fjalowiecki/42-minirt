#include "minirt.h"

static t_vec3	calc_normal_side(t_point3 hit_point, t_cone *cone,
	t_vec3 unit_axis)
{
	t_vec3	hit_to_vertex;
	double	height_proj;
	t_vec3	normal;

	hit_to_vertex = vec_sub(hit_point, cone->vertex);
	height_proj = dot_product(hit_to_vertex, unit_axis);
	normal = vec_sub(hit_to_vertex, vec_mul(unit_axis, height_proj));
	return (unit_vector(normal));
}

static t_vec3	cone_normal(t_point3 hit_point, t_cone *cone)
{
	t_vec3	unit_axis;

	unit_axis = unit_vector(cone->axis);
	if (cone->inter_type == SIDE)
		return (calc_normal_side(hit_point, cone, unit_axis));
	else
		return (unit_vector(cone->axis));
}

double	calc_light_angle_cone(t_pixel_data *pixel_data,
	t_view *view, t_light *light, t_cone *cone)
{
	t_point3	intersection;
	t_vec3		norm_vec;
	t_vec3		intersec_light;
	double		angle;

	(void)view;
	intersection = vec_add(vec_mul(pixel_data->ray.dir,
				pixel_data->closest_t), pixel_data->ray.orig);
	norm_vec = cone_normal(intersection, cone);
	pixel_data->normal = norm_vec;
	intersec_light = unit_vector(vec_sub(light->origin, intersection));
	angle = dot_product(norm_vec, intersec_light);
	if (angle < 0.0)
		angle = 0.0;
	return (angle);
}
