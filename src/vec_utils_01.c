#include "minirt.h"

float	vec_length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec3	unit_vector(t_vec3 vector)
{
	t_vec3	unit;
	float	length;

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
