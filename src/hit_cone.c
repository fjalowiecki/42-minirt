#include "minirt.h"

float hit_cone(t_ray *ray, void* obj) {
	t_cone *cone;
	cone = (t_cone *)obj;
	t_vec3 v = vec_sub(ray->orig, cone->vertex);
	t_vec3 d = ray->dir;
	t_vec3 axis = unit_vector(cone->axis);
	float cos_theta = tan(cone->angle);
	float cos_theta_sq = cos_theta * cos_theta;

	// Obliczanie składowych wektorów
	t_vec3 d_parallel = vec_mul(axis, dot_product(d, axis));
	t_vec3 d_perpendicular = vec_sub(d, d_parallel);
	t_vec3 v_parallel = vec_mul(axis, dot_product(v, axis));
	t_vec3 v_perpendicular = vec_sub(v, v_parallel);

	// Współczynniki kwadratowe
	float a = dot_product(d_perpendicular, d_perpendicular) - cos_theta_sq * dot_product(d_parallel, d_parallel);
	float b = 2.0 * (dot_product(d_perpendicular, v_perpendicular) - cos_theta_sq * dot_product(d_parallel, v_parallel));
	float c = dot_product(v_perpendicular, v_perpendicular) - cos_theta_sq * dot_product(v_parallel, v_parallel);

	// Rozwiązywanie równania kwadratowego
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0) {
		return -1; // Brak przecięcia
	}

	float sqrt_discriminant = sqrt(discriminant);
	float t1 = (-b - sqrt_discriminant) / (2 * a);
	float t2 = (-b + sqrt_discriminant) / (2 * a);

	// Zmienna do przechowywania najmniejszego t
	float t_closest = -1;

	// Sprawdzamy przecięcie z powierzchnią boczną
	for (int i = 0; i < 2; i++) {
		float t = (i == 0) ? t1 : t2;
		if (t < 0) continue;

		t_point3 hit_point = vec_add(ray->orig, vec_mul(ray->dir, t));
		t_vec3 hit_to_vertex = vec_sub(hit_point, cone->vertex);
		float height_proj = dot_product(hit_to_vertex, axis);
		if (height_proj >= 0 && height_proj <= cone->height) {
			t_closest = (t_closest < 0 || t < t_closest) ? t : t_closest;
			cone->inter_type = SIDE;
		}
	}

	// Obliczanie przecięcia z podstawą stożka
	float t_base = -1;
	float height_from_vertex = cone->height;
	t_vec3 base_center = vec_add(cone->vertex, vec_mul(axis, height_from_vertex));
	float radius_base = height_from_vertex * tan(cone->angle);

	// Obliczamy przecięcie promienia z płaszczyzną podstawy
	float denom_base = dot_product(ray->dir, axis);
	if (fabs(denom_base) > 1e-6) { // Sprawdzamy, czy promień nie jest równoległy do osi
		float t = dot_product(vec_sub(base_center, ray->orig), axis) / denom_base;
		if (t > 0) {
			t_point3 hit_point = vec_add(ray->orig, vec_mul(ray->dir, t));
			float dist_to_base_center = vec_length(vec_sub(hit_point, base_center));
			if (dist_to_base_center <= radius_base) {
				t_base = t;
			}
		}
	}
	//else if ()


	// Porównujemy t_closest i t_base
	if (t_base >= 0 && (t_closest < 0 || t_base < t_closest)) {
		t_closest = t_base;
		cone->inter_type = BOTTOM;
	}
	return t_closest;
}

t_vec3 cone_normal(t_point3 hit_point, t_cone *cone) 
{
	t_vec3 unit_axis = unit_vector(cone->axis);
	t_vec3 hit_to_vertex = vec_sub(hit_point, cone->vertex);

	if(cone->inter_type == SIDE) // Sprawdzamy, czy przecięcie jest na powierzchni bocznej
	{
		float height_proj = dot_product(hit_to_vertex, unit_axis); 

		// Obliczamy promień w tej wysokości
		float radius_proj = tan(cone->angle) * height_proj;

		// Wektor normalny będzie różnicą wektora hit_to_vertex i jego projekcji na oś stożka
		t_vec3 normal = vec_sub(hit_to_vertex, vec_mul(unit_axis, height_proj));

		// Normalizowanie wektora normalnego
		return unit_vector(normal);  
	}
	else
	{
		return (unit_vector(cone->axis));
	}
}

float	calc_light_angle_cone(t_pixel_data *pixel_data,
	t_view *view, t_light *light, t_cone *cone)
{
	t_point3	intersection;
	t_vec3		norm_vec;
	t_vec3		intersec_light;
	float		angle;

	intersection = vec_add(vec_mul(pixel_data->ray.dir,
				pixel_data->closest_t), pixel_data->ray.orig);
	norm_vec = cone_normal(intersection, cone);
	intersec_light = unit_vector(vec_sub(light->origin, intersection));
	angle = dot_product(norm_vec, intersec_light);
	if (angle < 0.0)
		angle = 0.0;
	return (angle);
}
