#include "minirt.h"

static bool shadow_ray_hit(t_ray *shadow_ray, t_data *data, int object_index, t_object *objects, float light_distance);


bool shaded_pixel(int object_index, t_point3 intersection, t_point3 light, t_data *data)
{
	t_ray shadow_ray;
	float light_distance;
	
	shadow_ray.dir = unit_vector(vec_sub(light, intersection));
	shadow_ray.orig = intersection;
	light_distance = vec_length(vec_sub(light, intersection));
	if(shadow_ray_hit(&shadow_ray, data, object_index, data->objects, light_distance) == true)
		return (true);
	return (false);
}

bool shadow_ray_hit(t_ray *shadow_ray, t_data *data, int object_index, t_object *objects, float light_distance)
{
	//przechodze przez wszystkie obiekty oprócz tego na ktorym jestem i jezeli t jest wieksze od zero z ktorejkolwiek funckji to zwracam true
	//chyba ze t jest wieksze niz droga do swiatla
	int i;
	float t;

	i = 0;
	while(i < data->objects_cnt)
	{
		if (objects->type == 0)
			t = hit_sphere(shadow_ray, (objects[i].object));
		else if (objects->type == 1 && t < light_distance)
			t = hit_plane(shadow_ray, (objects[i].object));
		else if (objects->type == 2 && t < light_distance)
			t = hit_cylinder(shadow_ray, objects[i].object);
		else if (objects->type == 3 && t < light_distance)
			t = hit_cone(shadow_ray, objects[i].object);
		if (t >= 0 && t < light_distance)
			return(true);
		i++;
	}

	return (false);
}