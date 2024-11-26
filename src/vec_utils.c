#include "vec_utils.h"


float dot_product(t_vec3 a, t_vec3 b) {
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

t_vec3 vec_add(t_vec3 a, t_vec3 b) {
	t_vec3 result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return result;
}

t_vec3 vec_sub(t_vec3 a, t_vec3 b) {
	t_vec3 result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return result;
}

t_vec3 vec_mul(t_vec3 v, float scalar) {
	t_vec3 result;
	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return result;
}

t_vec3 vec_intersection(t_point3 c, t_vec3 p, float skalar)
{
	t_vec3 result;//todo: zmaian
	result.x = c.x + (p.x * skalar);
	result.y = c.y + (p.y * skalar);
	result.z = c.z + (p.z * skalar);
	return result;
}

float vec_length(t_vec3 v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vec3 unit_vector(t_vec3 vector) {
	t_vec3 unit;
	float length = vec_length(vector);
	if (length != 0) {
		unit.x = vector.x / length;
		unit.y = vector.y / length;
		unit.z = vector.z / length;
	} else {
		unit.x = 0;
		unit.y = 0;
		unit.z = 0;
	}
	return unit;
}