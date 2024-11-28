#include "minirt.h"


typedef struct s_plane t_plane;

typedef struct s_color3 t_color3;

typedef struct s_color3
{
	int R;
	int G;
	int B;
};

typedef struct s_plane
{
	t_vec3 N; //why [-1,1]
	t_point3 center;
	t_color3 rgb_color;
};




float hit_plane(t_ray ray, t_plane plane)
{
	float ray_dot_N;
	float t;

	ray_dot_N = dot_product(ray.dir, plane.N);
    if (ray_dot_N == 0)
        return (-1.0); // Promień jest równoległy do płaszczyzny
 	t = dot_product(vec_sub(plane.center, ray.orig), plane.N) / ray_dot_N;	if (t < 0)
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