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

