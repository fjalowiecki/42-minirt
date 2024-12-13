#include "minirt.h"

typedef struct
{
	float	a_coeff;
	float	b_coeff;
	float	c_coeff;
	float	t_side;
	float	t_bott;
	float	t_top;
	float	discrmnt;
} t_calc_cy;

static void	calculate_bott_t(t_cylinder *cylinder, t_ray *ray, t_calc_cy *calc);
static void	calculate_top_t(t_cylinder *cylinder, t_ray *ray, t_calc_cy *calc);
static void	calculate_side_t(t_cylinder *cylinder, t_ray *ray,
				t_calc_cy *calc, float *t);


float	hit_cylinder(t_ray *ray, void *obj)
{
	t_cylinder	*cylinder;
	t_vec3		o;
	t_vec3		d_perp;
	t_vec3		o_perp;
	t_calc_cy	calc;
	float		t[2];

	calc.t_side = -1;
	calc.t_bott = -1;
	calc.t_top = -1;

	cylinder = (t_cylinder *)obj;
	o = vec_sub(ray->orig, cylinder->center);
	d_perp = vec_sub(ray->dir, vec_mul(cylinder->N_axis, dot_product(ray->dir, cylinder->N_axis))); // d projected perpendicular to the axis
	o_perp = vec_sub(o, vec_mul(cylinder->N_axis, dot_product(o, cylinder->N_axis))); // o projected perpendicular to the axis
	calc.a_coeff = dot_product(d_perp, d_perp);
	calc.b_coeff  = 2.0 * dot_product(d_perp, o_perp);
	calc.c_coeff = dot_product(o_perp, o_perp) - cylinder->r * cylinder->r;
	calc.discrmnt = pow(calc.b_coeff, 2) - 4.0 * calc.a_coeff * calc.c_coeff;
	t[0] = (-calc.b_coeff - sqrt(calc.discrmnt)) / (2.0 * calc.a_coeff);
	t[1] = (-calc.b_coeff + sqrt(calc.discrmnt)) / (2.0 * calc.a_coeff);
	calculate_side_t(cylinder, ray, &calc, t);
	calculate_bott_t(cylinder, ray, &calc);
	calculate_top_t(cylinder, ray, &calc);
	return (closest_cyl_t(calc.t_side, calc.t_bott, calc.t_top, cylinder));
}

t_vec3	cylinder_normal(t_point3 intersect_to_center, t_cylinder *cyl)
{
	t_vec3	unit_vec;

	unit_vec = unit_vector(cyl->N_axis);
	if (cyl->inter_type == SIDE)
		return (unit_vector(vec_sub(intersect_to_center, vec_mul
					(unit_vec, dot_product(intersect_to_center, unit_vec)))));
	if (cyl->inter_type == BOTTOM)
		return (vec_mul(unit_vec, -1));
	else
		return (unit_vec);
}

float	calc_light_angle_cylinder(t_pixel_data *pixel_data,
		t_view *view, t_light *light, t_cylinder *cyl)
{
	t_point3	intersection;
	t_vec3		intersect_to_center;
	t_vec3		norm_vec;
	t_vec3		intersec_light;
	float		angle;

	intersection = vec_add(vec_mul(pixel_data->ray.dir,
				pixel_data->closest_t), pixel_data->ray.orig);
	intersect_to_center = vec_sub(intersection, cyl->center);
	norm_vec = cylinder_normal(intersect_to_center, cyl);
	intersec_light = unit_vector(vec_sub(light->origin, intersection));
	angle = dot_product(norm_vec, intersec_light);
	if (angle < 0.0)
		angle = 0.0;
	return (angle);
}

float	closest_cyl_t(float t_side, float t_bott,
	float t_top, t_cylinder *cylinder)
{
	float	t_closest;

	t_closest = -1;
	if (t_side >= 0)
	{
		t_closest = t_side;
		cylinder->inter_type = SIDE;
	}
	if (t_bott >= 0 && (t_closest < 0 || t_bott < t_closest))
	{
		t_closest = t_bott;
		cylinder->inter_type = BOTTOM;
	}
	if (t_top >= 0 && (t_closest < 0 || t_top < t_closest))
	{
		t_closest = t_top;
		cylinder->inter_type = TOP;
	}
	return (t_closest);
}

static void	calculate_side_t(t_cylinder *cylinder, t_ray *ray,
		t_calc_cy *calc, float *t)
{
	int		i;
	float	height_proj;
	t_vec3	v;
	t_vec3	hit_point;

	i = -1;
	if (calc->discrmnt >= 0) 
	{
		while (++i < 2)
		{
			if (t[i] >= 0)
			{
				hit_point = vec_add(ray->orig, vec_mul(ray->dir, t[i]));
				v = vec_sub(hit_point, cylinder->center);
				height_proj = dot_product(v, cylinder->N_axis);
				if (height_proj >= 0 && height_proj <= cylinder->h)
				{
					if (calc->t_side < 0 || t[i] < calc->t_side)
						calc->t_side = t[i];
				}
			}
		}
	}
}

static void	calculate_top_t(t_cylinder *cylinder,
			t_ray *ray, t_calc_cy *calc)
{
	float		denom_top;
	t_vec3		hit_point;
	float		t;
	float		dist_to_top;
	t_point3	c_top;

	c_top = vec_add(cylinder->center, vec_mul(cylinder->N_axis, cylinder->h));
	denom_top = dot_product(ray->dir, cylinder->N_axis);
	if (fabs(denom_top) > 1e-6)
	{
		t = dot_product(vec_sub(c_top, ray->orig),
				cylinder->N_axis) / denom_top;
		if (t >= 0)
		{
			hit_point = vec_add(ray->orig, vec_mul(ray->dir, t));
			dist_to_top = vec_length(vec_sub(hit_point, c_top));
			if (dist_to_top <= cylinder->r)
				calc->t_top = t;
		}
	}
}


static void	calculate_bott_t(t_cylinder *cylinder, t_ray *ray,
	t_calc_cy *calc)
{
	float	denom_bott;
	float	t;
	float	dist_to_center;
	t_vec3	hit_point;

	denom_bott = dot_product(ray->dir, cylinder->N_axis);
	if (fabs(denom_bott) > 1e-6) 
	{
		t = dot_product(vec_sub(cylinder->center, ray->orig),
				cylinder->N_axis) / denom_bott;
		if (t >= 0)
		{
			hit_point = vec_add(ray->orig, vec_mul(ray->dir, t));
			dist_to_center = vec_length(vec_sub(hit_point, cylinder->center));
			if (dist_to_center <= cylinder->r)
				calc->t_bott = t;
		}
	}
}

/*Na pierwszy rzut oka Twój kod wygląda solidnie, jednak po dokładnym 
przejrzeniu można znaleźć potencjalne błędy lub miejsca, które mogą 
powodować problemy. Oto szczegółowa analiza i możliwe problemy:
1. Brak inicjalizacji zmiennych lokalnych

W funkcjach calculate_top_t i calculate_bott_t zmienne lokalne t_top 
i t_bott są używane bez inicjalizacji przed ich potencjalnym przypisaniem 
do calc->t_top i calc->t_bott. Jeśli warunki ich przypisania nie zostaną 
spełnione, wartość pozostanie nieokreślona, co może prowadzić do błędów.
Poprawka:

Zainicjalizuj zmienne do wartości domyślnej, np. t_top = -1; i t_bott = -1;
na początku funkcji.
2. Problem z tolerancją w obliczeniach równań płaszczyzn

W calculate_top_t i calculate_bott_t używasz fabs(denom_top) > 1e-6 oraz
 fabs(denom_bott) > 1e-6 jako warunku sprawdzającego, czy promień nie jest
  równoległy do płaszczyzn. Ta tolerancja może być za mała lub za duża w 
  zależności od skali sceny i precyzji obliczeń. Dla scen w większej skali 
  1e−61e−6 może prowadzić do ignorowania promieni, które powinny trafiać.
Poprawka:

Upewnij się, że tolerancja jest skalowalna, np.:

const float EPSILON = 1e-6 * fmax(1.0, cylinder->r);
if (fabs(denom_top) > EPSILON) { ... }

3. Obliczenia promienia dla powierzchni bocznej

W calculate_side_t obliczasz dwa możliwe rozwiązania t[0]t[0] i t[1]t[1]
 równania kwadratowego, ale ignorujesz przypadki, w których promień zaczyna
  wewnątrz cylindra. Jeśli początkowa pozycja promienia (ray.orig) znajduje
   się już w cylindrze, oba tt mogą być dodatnie, ale pierwszy t[0]t[0]
    może być punktem wyjścia z cylindra, a nie wejścia.
Poprawka:

Sprawdź, czy promień zaczyna wewnątrz cylindra:

float start_dist = dot_product(o_perp, o_perp) - cylinder->r * cylinder->r;
if (start_dist < 0) {
    // Promień zaczyna wewnątrz cylindra, obsłuż to zgodnie z logiką swojej
	 aplikacji
}
*/