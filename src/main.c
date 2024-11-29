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
	// float fov = 2 * atan(view->viewport_width / (2 * view->focal_length.z)) * (180 / PI);
	// printf("fov: %f\n", fov);
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

	return (pos_angle);
}
float calc_light_angle_plane(float t, t_vec3 ray_direction, t_view *view, t_light *light, t_plane *sph)
{			
	t_point3 intersection = point_intersection(view->camera_center, ray_direction, t);
	t_vec3 intersec_light = unit_vector(vec_sub(light->origin, intersection));
	float angle = dot_product(sph->N, intersec_light);
	float pos_angle = (angle > 0.0) ? angle : 0.0;

	return (pos_angle);
}

int count_objects(t_object *obj_arr)
{
	int i;

	if (obj_arr == NULL)
		return (0);
	i = 0;
	while (obj_arr[i].object != NULL)
		i++;
	return (i);
}

void calc_t_for_objects(float *t, t_object *obj_arr, t_ray ray)
{
	int i;
	int obj_cnt;
	
	obj_cnt = count_objects(obj_arr);
	i = 0;
	while (i < obj_cnt)
	{
		if (obj_arr[i].type == 0)
		{
			t_sphere *sphere = (t_sphere *)obj_arr[i].object;
			t[i] = hit_sphere(sphere->center, sphere->radius, ray);
		}
		else if (obj_arr[i].type == 1)
		{
			t_plane *plane = (t_plane *)obj_arr[i].object;
			t[i] = hit_plane(ray, plane);
		}
		i++;
	}
	// return (t);
}

unsigned int calc_color(int brightness, t_color color, float angle)
{
	int r, g, b;

	r = color.r * angle * brightness;
	g = color.g * angle * brightness;
	b = color.b * angle * brightness;
	return (rgb_to_hex(r, g, b));
}

float calc_closest_t(float *t_arr, int t_arr_size, int *obj_index)
{
	int i;
	float t_temp;

	t_temp = 10000.0;
	*obj_index = -1;
	i = 0;
	while (i < t_arr_size)
	{
		if (t_arr[i] > 0 && t_arr[i] < t_temp)
		{
			t_temp = t_arr[i];
			*obj_index = i;
		}
		i++;
	}
	if (*obj_index == -1)
		return (-1);
	return (t_temp);
}

void create_image2(t_img *img, t_view *view, t_light *light, t_object *obj_arr)
{
	t_ray ray;
	float *t;
	int obj_cnt;

	obj_cnt = count_objects(obj_arr);

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
			ray.dir  = unit_vector(vec_sub(pixel_center, view->camera_center));

			t = malloc(sizeof(float) * (obj_cnt + 1));
			calc_t_for_objects(t, obj_arr, ray);
			float closest_t;
			int obj_index;
			closest_t = calc_closest_t(t, obj_cnt, &obj_index);
			if (closest_t < 0)
				my_mlx_pixel_put(img, x, y, 0xADD8E6);
			else
			{
				int r, g, b;
				unsigned int pixel_color;
				if (obj_arr[obj_index].type == 0)
				{	
					t_sphere *sphere = obj_arr[obj_index].object;
					float angle = calc_light_angle(closest_t, ray.dir, view, light, sphere);	
					pixel_color = calc_color(light->brightness, sphere->color, angle);
				}
				else if (obj_arr[obj_index].type == 1)
				{
					t_plane *plane = obj_arr[obj_index].object;
					float angle = calc_light_angle_plane(closest_t, ray.dir, view, light, plane);	
					pixel_color = calc_color(light->brightness, plane->color, angle);
				}
				my_mlx_pixel_put(img, x, y, pixel_color);
			}
			free(t);
			y++;
        }
        x++;
    }
}

float calculate_viewport_width(float focal_length, float fov_degrees) {
    float fov_radians = fov_degrees * M_PI / 180.0;
    return 2.0 * focal_length * tan(fov_radians / 2.0);
}

void init_scene(t_view *view, t_light *light, t_object **obj_arr)
{
	t_sphere *sph1 = malloc(sizeof(t_sphere));
	t_sphere *sph2 = malloc(sizeof(t_sphere));
	t_plane *plane = malloc(sizeof(t_plane));

	*obj_arr = malloc(sizeof(t_object) * 4);
	(*obj_arr)[0].type = 0;
	(*obj_arr)[0].object = sph1;
	(*obj_arr)[1].type = 0;
	(*obj_arr)[1].object = sph2;
	(*obj_arr)[2].type = 1;
	(*obj_arr)[2].object = plane;
	(*obj_arr)[3].type = -1;
	(*obj_arr)[3].object = NULL;

	view->camera_center.x = 0;
	view->camera_center.y = 0;
	view->camera_center.z = 0;
	view->focal_length.x = 0;
	view->focal_length.y = 0;
	view->focal_length.z = 1;
	view->image_width = IMAGE_WIDTH;
	view->image_height = IMAGE_HEIGHT;
	view->viewport_height = 2.0;
	view->fov_degrees = 70;
	view->viewport_width = calculate_viewport_width(view->focal_length.z, view->fov_degrees);
	view->viewport_height = view->viewport_width / (view->image_width/view->image_height);

	light->origin.x = 10;
	light->origin.y = 80;
	light->origin.z = -10;
	light->brightness = 1;

	//red
	sph1->center.x = -10;
	sph1->center.y = 0;
	sph1->center.z = -100;
	sph1->radius = 15;
	sph1->color.r = 255;
	sph1->color.g = 0;
	sph1->color.b = 0;

	//green
	sph2->center.x = 10;
	sph2->center.y = 0;
	sph2->center.z = -100;
	sph2->radius = 10;
	sph2->color.r = 0;
	sph2->color.g = 255;
	sph2->color.b = 0;

	plane->center.x = 0;
	plane->center.y = -100;
	plane->center.z = 0;
	plane->N.x = 0;
	plane->N.y = 1;
	plane->N.z = 0;
	plane->color.r = 0;
	plane->color.g = 0;
	plane->color.b = 255;
}

int main() 
{
	t_window window;
	t_img img;
	t_view view;
	t_light light;

	t_object *obj_arr;


	window.mlx_ptr = mlx_init(); //todo: add check for failure
	window.win_ptr = mlx_new_window(window.mlx_ptr, IMAGE_WIDTH, IMAGE_HEIGHT, WINDOW_TITLE); //todo: add check for failure
	mlx_hook(window.win_ptr, DestroyNotify, StructureNotifyMask, on_destroy, &window);
	mlx_hook(window.win_ptr, 2, (1L << 0), close_esc, &window);//todo: unification of arguments
	img.img = mlx_new_image(window.mlx_ptr, IMAGE_WIDTH, IMAGE_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	init_scene(&view, &light, &obj_arr);
	// create_image(&img, &view, &light, &sph1, &sph2, &plane);
	create_image2(&img, &view, &light, obj_arr);
	mlx_put_image_to_window(window.mlx_ptr, window.win_ptr, img.img, 0, 0);
	mlx_loop(window.mlx_ptr);
}