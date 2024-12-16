#ifndef VEC_UTILS_H
#define VEC_UTILS_H

#include <math.h>
typedef struct s_vec3 {
    double x;
    double y;
    double z;
} t_vec3;

typedef t_vec3 t_point3;

typedef struct s_ray {
	t_point3 orig;
	t_vec3 dir;
} t_ray;

double dot_product(t_vec3 a, t_vec3 b);
t_vec3 vec_add(t_vec3 a, t_vec3 b);
t_vec3 vec_sub(t_vec3 a, t_vec3 b);
t_vec3 vec_mul(t_vec3 v, double scalar);
t_point3 point_intersection(t_point3 c, t_vec3 p, double skalar);
double vec_length(t_vec3 v);
t_vec3 unit_vector(t_vec3 vector);
t_vec3 cross_product(t_vec3 a, t_vec3 b);

#endif