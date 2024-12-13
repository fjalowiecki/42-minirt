#include "minirt.h"

float	closest_cyl_t(float t_side, float t_bott,
	float t_top, t_cylinder *cylinder)
{
	float	t_closest;

	t_closest = -1;
	if (t_side >= 0)
	{
		t_closest = t_side;
		cylinder->inter_type = SIDE;
	}
	if (t_bott >= 0 && (t_closest < 0 || t_bott < t_closest))
	{
		t_closest = t_bott;
		cylinder->inter_type = BOTTOM;
	}
	if (t_top >= 0 && (t_closest < 0 || t_top < t_closest))
	{
		t_closest = t_top;
		cylinder->inter_type = TOP;
	}
	return (t_closest);
}

t_vec3	cylinder_normal(t_point3 intersect_to_center, t_cylinder *cyl)
{
	t_vec3	unit_vec;

	unit_vec = unit_vector(cyl->N_axis);
	if (cyl->inter_type == SIDE)
		return (unit_vector(vec_sub(intersect_to_center, vec_mul
					(unit_vec, dot_product(intersect_to_center, unit_vec)))));
	if (cyl->inter_type == BOTTOM)
		return (vec_mul(unit_vec, -1));
	else
		return (unit_vec);
}

float	calc_light_angle_cylinder(t_pixel_data *pixel_data,
		t_view *view, t_light *light, t_cylinder *cyl)
{
	t_point3	intersection;
	t_vec3		intersect_to_center;
	t_vec3		norm_vec;
	t_vec3		intersec_light;
	float		angle;

	intersection = vec_add(vec_mul(pixel_data->ray.dir,
				pixel_data->closest_t), pixel_data->ray.orig);
	intersect_to_center = vec_sub(intersection, cyl->center);
	norm_vec = cylinder_normal(intersect_to_center, cyl);
	intersec_light = unit_vector(vec_sub(light->origin, intersection));
	angle = dot_product(norm_vec, intersec_light);
	if (angle < 0.0)
		angle = 0.0;
	return (angle);
}
