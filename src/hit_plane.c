#include "minirt.h"

float hit_plane(t_ray ray, t_plane *plane)
{
	float ray_dot_N;
	float t;

	ray_dot_N = dot_product(ray.dir, plane->N);
    if (ray_dot_N == 0)
        return (-1.0); // Promień jest równoległy do płaszczyzny
 	t = dot_product(vec_sub(plane->center, ray.orig), plane->N) / ray_dot_N;
	if (t < 0)
        return (-1.0); // Płaszczyzna znajduje się za początkowym punktem promienia
	/* Potencjalnie
	if(t > MAX_DISTANCE)
		return (-1.0);
	*/
	
	return (t);
	/*after returning t
	t_point3 intersection_point = point_intersection(ray.orig, ray.dir, t);
	inter

	*/
}

float calc_light_angle_plane(float t, t_vec3 ray_direction, t_view *view, t_light *light, t_plane *plane)
{			
	t_point3 intersection = point_intersection(view->camera_center, ray_direction, t);
	t_vec3 intersec_light = unit_vector(vec_sub(light->origin, intersection));
	float angle = dot_product(plane->N, intersec_light);
	float pos_angle = (angle > 0.0) ? angle : 0.0;

	return (pos_angle);
}