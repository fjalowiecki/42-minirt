#include "minirt.h"

double	vec_length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec3	unit_vector(t_vec3 vector)
{
	t_vec3	unit;
	double	length;

	length = vec_length(vector);
	if (length != 0)
	{
		unit.x = vector.x / length;
		unit.y = vector.y / length;
		unit.z = vector.z / length;
	}
	else
	{
		unit.x = 0;
		unit.y = 0;
		unit.z = 0;
	}
	return (unit);
}

t_vec3	cross_product(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}
