#include "minirt.h"

int	on_destroy(t_window *window)
{
	mlx_destroy_window(window->mlx_ptr, window->win_ptr);
	mlx_destroy_display(window->mlx_ptr);
	free(window->mlx_ptr);
	exit(0);
	return (0);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

float hit_sphere(t_point3 center, float radius, t_ray r) {
    t_vec3 oc = vec_sub(r.orig, center);
    float a = dot_product(r.dir, r.dir);
    float b = 2.0 * dot_product(r.dir, oc);
    float c = dot_product(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
		return (-1.0);
	else
    	return ((-b - sqrt(discriminant)) / (2.0 * a));
}

unsigned int rgb_to_hex(int r, int g, int b) {
    // Upewnij się, że wartości RGB są w zakresie 0-255
    if (r < 0) r = 0;
    if (r > 255) r = 255;
    if (g < 0) g = 0;
    if (g > 255) g = 255;
    if (b < 0) b = 0;
    if (b > 255) b = 255;

    // Konwertuj wartości RGB na zapis szesnastkowy
    return (r << 16) | (g << 8) | b;
}

void set_viewport_pixel_parameters(t_view *view, t_vec3 *pixel_delta_u, t_vec3 *pixel_delta_v, t_vec3 *pixel00_loc)
{
   // Calculate the vectors across the horizontal and down the vertical viewport edges.
    t_vec3 viewport_u = {view->viewport_width, 0, 0};
    t_vec3 viewport_v = {0, -view->viewport_height, 0};

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    *pixel_delta_u = vec_mul(viewport_u, 1.0 / view->image_width);
    *pixel_delta_v = vec_mul(viewport_v, 1.0 / view->image_height);

    // Calculate the location of the upper left pixel.
    t_vec3 viewport_upper_left = vec_sub(vec_sub(vec_sub(view->camera_center, view->focal_length),
		vec_mul(viewport_u, 0.5)),vec_mul(viewport_v, 0.5));
    *pixel00_loc = vec_add(viewport_upper_left, vec_mul(vec_add(*pixel_delta_u, *pixel_delta_v), 0.5));
}

float calc_light_angle(float t, t_vec3 ray_direction, t_view *view, t_light *light, t_sphere *sph)
{			
	t_point3 intersection = point_intersection(view->camera_center, ray_direction, t);
	t_vec3 N =  unit_vector(vec_sub(intersection, sph->center));
	t_vec3 intersec_light = unit_vector(vec_sub(light->origin, intersection));
	float angle = dot_product(N, intersec_light);
	float pos_angle = (angle > 0.0) ? angle : 0.0;
	int brightness = 1;

	return (angle);
}

void create_image(t_img *img, t_view *view, t_light *light, t_sphere *sph1, t_sphere *sph2)
{
	t_ray ray;
	float t1;
	float t2;
	
	t_vec3 pixel_delta_u;
	t_vec3 pixel_delta_v;
	t_vec3 pixel00_loc;
	set_viewport_pixel_parameters(view, &pixel_delta_u, &pixel_delta_v, &pixel00_loc);

	ray.orig = view->camera_center;
    int x = 0;
    while (x < IMAGE_WIDTH)
    {
        int y = 0;
        while (y < IMAGE_HEIGHT)
        {
			t_point3 pixel_center = vec_add(pixel00_loc, vec_add(vec_mul(pixel_delta_u, x),vec_mul(pixel_delta_v, y)));
        	t_vec3 ray_direction = vec_sub(pixel_center, view->camera_center);
            ray.dir = ray_direction;
            t1 = hit_sphere(sph1->center, sph1->radius, ray);
            t2 = hit_sphere(sph2->center, sph2->radius, ray);
			if(t1 > t2)
			{
				float angle = calc_light_angle(t1, ray_direction, view, light, sph1);
				int r = sph1->color.r * angle * light->brightness;
				int g = sph1->color.g * angle * light->brightness;
				int b = sph1->color.b * angle * light->brightness;
				my_mlx_pixel_put(img, x, y, rgb_to_hex(r, g, b));
			}
			else if (t1 < t2)
			{
				float angle = calc_light_angle(t2, ray_direction, view, light, sph2);
				int r = sph2->color.r * angle * light->brightness;
				int g = sph2->color.g * angle * light->brightness;
				int b = sph2->color.b * angle * light->brightness;
				my_mlx_pixel_put(img, x, y, rgb_to_hex(r, g, b));
			}
			else 
				my_mlx_pixel_put(img, x, y, 0xADD8E6);
            y++;
        }
        x++;
    }
}

void init_scene(t_view *view, t_light *light, t_sphere *sph1, t_sphere *sph2)
{
	view->camera_center.x = 0;
	view->camera_center.y = 0;
	view->camera_center.z = 0;
	view->focal_length.x = 0;
	view->focal_length.y = 0;
	view->focal_length.z = 1;
	view->image_width = IMAGE_WIDTH;
	view->image_height = IMAGE_HEIGHT;
	view->viewport_height = 2.0;
	view->viewport_width = view->viewport_height * IMAGE_WIDTH / IMAGE_HEIGHT;

	light->origin.x = 0;
	light->origin.y = 100;
	light->origin.z = -60;
	light->brightness = 1;

	sph1->center.x = 0;
	sph1->center.y = 0;
	sph1->center.z = -100;
	sph1->radius = 30;
	sph1->color.r = 255;
	sph1->color.g = 0;
	sph1->color.b = 0;

	sph2->center.x = 50;
	sph2->center.y = 0;
	sph2->center.z = -80;
	sph2->radius = 30;
	sph2->color.r = 0;
	sph2->color.g = 255;
	sph2->color.b = 0;
}

int main() 
{
	t_window window;
	t_img img;
	t_view view;
	t_light light;
	t_sphere sph1;
	t_sphere sph2;

	window.mlx_ptr = mlx_init(); //todo: add check for failure
	window.win_ptr = mlx_new_window(window.mlx_ptr, IMAGE_WIDTH, IMAGE_HEIGHT, WINDOW_TITLE); //todo: add check for failure
	mlx_hook(window.win_ptr, DestroyNotify, StructureNotifyMask, on_destroy, &window);
	mlx_hook(window.win_ptr, 2, (1L << 0), close_esc, &window);//todo: unification of arguments
	img.img = mlx_new_image(window.mlx_ptr, IMAGE_WIDTH, IMAGE_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	init_scene(&view, &light, &sph1, &sph2);
	create_image(&img, &view, &light, &sph1, &sph2);
	mlx_put_image_to_window(window.mlx_ptr, window.win_ptr, img.img, 0, 0);
	mlx_loop(window.mlx_ptr);
}