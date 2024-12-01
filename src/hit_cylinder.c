#include "minirt.h"

float hit_cylinder(t_ray *ray, t_cylinder *cylinder) {
    // Cylinder parameters
    t_point3 c = cylinder->center;
    t_vec3 a = unit_vector(cylinder->N_axis_vec); // Normalized axis
    float r = cylinder->diameter / 2.0;
    float h = cylinder->height;

    // Ray parameters
    t_vec3 d = ray->dir;
    t_vec3 o = vec_sub(ray->orig, c);

    // Solve for the lateral surface intersection
    t_vec3 d_perp = vec_sub(d, vec_mul(a, dot_product(d, a))); // d projected perpendicular to the axis
    t_vec3 o_perp = vec_sub(o, vec_mul(a, dot_product(o, a))); // o projected perpendicular to the axis

    float a_coeff = dot_product(d_perp, d_perp);
    float b_coeff = 2.0 * dot_product(d_perp, o_perp);
    float c_coeff = dot_product(o_perp, o_perp) - r * r;

    float discriminant = b_coeff * b_coeff - 4.0 * a_coeff * c_coeff;
    float t_cylinder = -1;

    if (discriminant >= 0) {
        float sqrt_discriminant = sqrt(discriminant);
        float t1 = (-b_coeff - sqrt_discriminant) / (2.0 * a_coeff);
        float t2 = (-b_coeff + sqrt_discriminant) / (2.0 * a_coeff);

        // Iterate over possible solutions
        float t_candidates[2] = {t1, t2};
        for (int i = 0; i < 2; i++) {
            if (t_candidates[i] >= 0) {
                t_vec3 hit_point = vec_add(ray->orig, vec_mul(ray->dir, t_candidates[i]));
                t_vec3 v = vec_sub(hit_point, c);
                float height_proj = dot_product(v, a);
                // Ensure hit_point is within the cylinder height
                if (height_proj >= 0 && height_proj <= h) {
                    if (t_cylinder < 0 || t_candidates[i] < t_cylinder) {
                        t_cylinder = t_candidates[i];
                    }
                }
            }
        }
    }

    // Solve for the caps (bottom and top caps)
    // Bottom cap
    float t_bottom = -1;
    float denom_bottom = dot_product(ray->dir, a);
    if (fabs(denom_bottom) > 1e-9) {
        float t = dot_product(vec_sub(c, ray->orig), a) / denom_bottom;
        if (t >= 0) {
            t_vec3 hit_point = vec_add(ray->orig, vec_mul(ray->dir, t));
            // Check if the hit point lies within the base circle radius
            float dist_to_center = vec_length(vec_sub(hit_point, c));
            if (dist_to_center <= r) {
                t_bottom = t;
            }
        }
    }

    // Top cap
    float t_top = -1;
    t_point3 c_top = vec_add(c, vec_mul(a, h));
    float denom_top = dot_product(ray->dir, a);
    if (fabs(denom_top) > 1e-9) {
        float t = dot_product(vec_sub(c_top, ray->orig), a) / denom_top;
        if (t >= 0) {
            t_vec3 hit_point = vec_add(ray->orig, vec_mul(ray->dir, t));
            // Check if the hit point lies within the top base circle radius
            float dist_to_top = vec_length(vec_sub(hit_point, c_top));
            if (dist_to_top <= r) {
                t_top = t;
            }
        }
    }

    // Return the closest positive t
    float t_closest = -1;
    if (t_cylinder >= 0) t_closest = t_cylinder;
    if (t_bottom >= 0 && (t_closest < 0 || t_bottom < t_closest)) t_closest = t_bottom;
    if (t_top >= 0 && (t_closest < 0 || t_top < t_closest)) t_closest = t_top;
    return t_closest;
}


t_vec3 cylinder_normal(t_point3 intersection, t_cylinder *cyl) {
    t_vec3 intersect_to_center = vec_sub(intersection, cyl->center);
    return unit_vector(vec_sub(intersect_to_center, vec_mul(cyl->N_axis_vec, dot_product(intersect_to_center, cyl->N_axis_vec))));
}