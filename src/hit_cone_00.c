#include "minirt.h"

static void	calc_discriminant_components(double *abc, t_cone *cone, t_ray *ray)
{
	t_vec3	axis;
	t_vec3	d_parallel;
	t_vec3	d_perpendicular;
	t_vec3	v_parallel;
	t_vec3	v_perpendicular;

	axis = unit_vector(cone->axis);
	d_parallel = vec_mul(axis, dot_product(ray->dir, axis));
	d_perpendicular = vec_sub(ray->dir, d_parallel);
	v_parallel = vec_mul(axis, dot_product(vec_sub
				(ray->orig, cone->vertex), axis));
	v_perpendicular = vec_sub(vec_sub
			(ray->orig, cone->vertex), v_parallel);
	abc[0] = dot_product(d_perpendicular, d_perpendicular) - (tan(cone->angle)
			* tan(cone->angle)) * dot_product(d_parallel, d_parallel);
	abc[1] = 2.0 * (dot_product(d_perpendicular, v_perpendicular)
			- (tan(cone->angle) * tan(cone->angle))
			* dot_product(d_parallel, v_parallel));
	abc[2] = dot_product(v_perpendicular, v_perpendicular) - (tan(cone->angle)
			* tan(cone->angle)) * dot_product(v_parallel, v_parallel);
}

static double	calc_discriminant(t_cone *cone, t_ray *ray, double *abc)
{
	double	discriminant;
	double	a;
	double	b;
	double	c;

	calc_discriminant_components(abc, cone, ray);
	a = abc[0];
	b = abc[1];
	c = abc[2];
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	else
		return (discriminant);
}

double	hit_cone(t_ray *ray, void *obj)
{
	t_cone	*cone;
	double	discriminant;
	double	abc[3];
	double	t_closest;
	double	t_base;

	cone = (t_cone *)obj;
	cone->axis = unit_vector(cone->axis);
	discriminant = calc_discriminant(cone, ray, abc);
	if (discriminant < 0)
		return (-1);
	t_closest = check_side_intersection(ray, cone, abc, discriminant);
	t_base = check_base_intersection(ray, cone);
	if (t_base >= 0 && (t_closest < 0 || t_base < t_closest))
	{
		t_closest = t_base;
		cone->inter_type = BOTTOM;
	}
	return (t_closest);
}