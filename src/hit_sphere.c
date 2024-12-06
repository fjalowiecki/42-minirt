#include "minirt.h"

float	hit_sphere(t_ray *ray, void *obj)
{
	t_vec3	oc;
	float	a;
	float	b;
	float	c;
	float	discriminant;

	oc = vec_sub(ray->orig, ((t_sphere *)obj)->center);
	a = dot_product(ray->dir, ray->dir);
	b = 2.0 * dot_product(ray->dir, oc);
	c = dot_product(oc, oc) - ((t_sphere *)obj)->radius
		* ((t_sphere *)obj)->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1.0);
	else
		return ((-b - sqrt(discriminant)) / (2.0 * a));
}

float	calc_light_angle_sphere(t_pixel_data *pixel_data,
	t_view *view, t_light *light, t_sphere *sphere)
{
	t_point3	intersection;
	t_vec3		norm_vec;
	t_vec3		intersec_light;
	float		angle;

	intersection = point_intersection(view->camera_center,
			pixel_data->ray.dir, pixel_data->closest_t);
	norm_vec = unit_vector(vec_sub(intersection, sphere->center));
	intersec_light = unit_vector(vec_sub(light->origin, intersection));
	angle = dot_product(norm_vec, intersec_light);
	if (angle < 0.0)
		angle = 0.0;
	return (angle);
}
