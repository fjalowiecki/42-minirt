#include "minirt.h"

float hit_sphere(t_point3 center, float radius, t_ray r) 
{
    t_vec3 oc = vec_sub(r.orig, center);
    float a = dot_product(r.dir, r.dir);
    float b = 2.0 * dot_product(r.dir, oc);
    float c = dot_product(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
		return (-1.0);
	else
    	return ((-b - sqrt(discriminant)) / (2.0 * a));
}

float calc_light_angle_sphere(float t, t_vec3 ray_direction, t_view *view, t_light *light, t_sphere *sph)
{			
	t_point3 intersection = point_intersection(view->camera_center, ray_direction, t);
	t_vec3 N =  unit_vector(vec_sub(intersection, sph->center));
	t_vec3 intersec_light = unit_vector(vec_sub(light->origin, intersection));
	float angle = dot_product(N, intersec_light);
	float pos_angle = (angle > 0.0) ? angle : 0.0;

	return (pos_angle);
}