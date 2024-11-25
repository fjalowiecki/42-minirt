#ifndef VEC_UTILS_H
#define VEC_UTILS_H

typedef struct s_vec3 {
    float x;
    float y;
    float z;
} t_vec3;

typedef t_vec3 t_point3;

typedef struct s_ray {
	t_point3 orig;
	t_vec3 dir;
} t_ray;

float dot_product(t_vec3 a, t_vec3 b);
t_vec3 vec_add(t_vec3 a, t_vec3 b);
t_vec3 vec_sub(t_vec3 a, t_vec3 b);
t_vec3 vec_mul(t_vec3 v, float scalar);

#endif