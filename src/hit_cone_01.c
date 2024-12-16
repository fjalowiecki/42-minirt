#include "minirt.h"

static double	calculate_t(double *abc, double discriminant, int index)
{
	if (index == 0)
		return ((-abc[1] - sqrt(discriminant)) / (2 * abc[0]));
	else
		return ((-abc[1] + sqrt(discriminant)) / (2 * abc[0]));
}

static int	is_valid_intersection(t_ray *ray, t_cone *cone, double t)
{
	t_point3	hit_point;
	t_vec3		hit_to_vertex;
	double		height_proj;

	if (t < 0)
		return (0);
	hit_point = vec_add(ray->orig, vec_mul(ray->dir, t));
	hit_to_vertex = vec_sub(hit_point, cone->vertex);
	height_proj = dot_product(hit_to_vertex, cone->axis);
	if (height_proj >= 0 && height_proj <= cone->height)
		return (1);
	return (0);
}

double	check_side_intersection(t_ray *ray, t_cone *cone, double *abc,
	double discriminant)
{
	double	t_closest;
	double	t;
	int		i;

	t_closest = -1;
	i = 0;
	while (i < 2)
	{
		t = calculate_t(abc, discriminant, i);
		if (is_valid_intersection(ray, cone, t))
		{
			if (t_closest < 0 || t < t_closest)
				t_closest = t;
			cone->inter_type = SIDE;
		}
		i++;
	}
	return (t_closest);
}

double	check_base_intersection(t_ray *ray, t_cone *cone)
{
	double		t;
	t_vec3		base_center;
	double		radius_base;
	double		denom_base;
	t_point3	hit_point;

	base_center = vec_add(cone->vertex, vec_mul(cone->axis, cone->height));
	radius_base = cone->height * tan(cone->angle);
	denom_base = dot_product(ray->dir, cone->axis);
	if (fabs(denom_base) > 1e-6)
	{
		t = dot_product(vec_sub(base_center, ray->orig), cone->axis)
			/ denom_base;
		if (t > 0)
		{
			hit_point = vec_add(ray->orig, vec_mul(ray->dir, t));
			if (vec_length(vec_sub(hit_point, base_center)) <= radius_base)
				return (t);
		}
		else
			return (-1);
	}
	return (-1);
}
