#include "minirt.h"

static bool	shadow_ray_hit(t_ray *shadow_ray,
	t_data *data, int object_index, float light_distance)
{
	int		i;
	float	t;

	i = 0;
	t = -1;
	while (i < data->objects_cnt)
	{
		if (data->objects[i].type == 0)
			t = hit_sphere(shadow_ray, (data->objects[i].object));
		else if (data->objects[i].type == 1)
			t = hit_plane(shadow_ray, (data->objects[i].object));
		else if (data->objects[i].type == 2)
			t = hit_cylinder(shadow_ray, data->objects[i].object);
		else if (data->objects[i].type == 3)
			t = hit_cone(shadow_ray, data->objects[i].object);
		if (t > 0.0001 && t < light_distance)
			return (true);
		i++;
	}
	return (false);
}

bool	shaded_pixel(int object_index,
	t_point3 intersection, t_point3 light, t_data *data)
{
	t_ray	shadow_ray;
	float	light_distance;

	intersection.z += 0.01;
	shadow_ray.orig = intersection;
	shadow_ray.dir = unit_vector(vec_sub(light, intersection));
	light_distance = vec_length(vec_sub(light, intersection));
	if (shadow_ray_hit(&shadow_ray, data, object_index, light_distance) == true)
		return (true);
	return (false);
}

