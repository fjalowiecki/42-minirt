#include "minirt.h"

double	hit_plane(t_ray *ray, void *obj)
{
	double	ray_dot_n;
	double	t;
	t_plane	*plane;

	plane = (t_plane *)obj;
	ray_dot_n = dot_product(ray->dir, plane->N);
	if (ray_dot_n == 0.0)
		return (-1.0);
	t = dot_product(vec_sub(plane->center, ray->orig), plane->N) / ray_dot_n;
	if (t < 0)
		return (-1.0);
	return (t);
}

double	calc_light_angle_plane(t_pixel_data *pixel_data,
		t_view *view, t_light *light, t_plane *plane)
{
	t_point3	intersection;
	t_vec3		intersec_light;
	double		angle;

	intersection = point_intersection(view->camera_center,
			pixel_data->ray.dir, pixel_data->closest_t);
	intersec_light = unit_vector(vec_sub(light->origin, intersection));
	angle = dot_product(plane->N, intersec_light);
	pixel_data->normal = plane->N;
	if (angle < 0.0)
		angle = 0.0;
	return (angle);
}
