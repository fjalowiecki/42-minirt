#include "minirt.h"

int	on_destroy(t_window *window)
{
	mlx_destroy_window(window->mlx_ptr, window->win_ptr);
	mlx_destroy_display(window->mlx_ptr);
	free(window->mlx_ptr);
	exit(0);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
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

void create_image(t_data *img, t_sphere sph)
{
	t_ray ray;
	float t;
	
	t_point3 light = ray.orig;//{200, 0 , -10};
	t_point3 focal_length = {0, 0, 1.0};
    float viewport_height = 2.0;
    float viewport_width = viewport_height * (IMAGE_WIDTH / IMAGE_HEIGHT);
    t_point3 camera_center = {0, 0, 0};
	ray.orig = camera_center;

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    t_vec3 viewport_u = {viewport_width, 0, 0};
    t_vec3 viewport_v = {0, -viewport_height, 0};

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    t_vec3 pixel_delta_u = vec_mul(viewport_u, 1.0 / IMAGE_WIDTH);
    t_vec3 pixel_delta_v = vec_mul(viewport_v, 1.0 / IMAGE_HEIGHT);

    // Calculate the location of the upper left pixel.
    t_vec3 viewport_upper_left = vec_sub(vec_sub(vec_sub(camera_center, focal_length),
		vec_mul(viewport_u, 0.5)),vec_mul(viewport_v, 0.5));
    t_vec3 pixel00_loc = vec_add(viewport_upper_left, vec_mul(vec_add(pixel_delta_u, pixel_delta_v), 0.5));

    int x = 0;
    while (x < IMAGE_HEIGHT)
    {
        int y = 0;
        while (y < IMAGE_WIDTH)
        {
			t_point3 pixel_center = vec_add(pixel00_loc, vec_add(vec_mul(pixel_delta_u, y),vec_mul(pixel_delta_v, x)));
        	t_vec3 ray_direction = vec_sub(pixel_center, camera_center);
            ray.dir = ray_direction;
            t = hit_sphere(sph.center, sph.radius, ray);
			if(t > 0)
			{
				t_point3 intersection = point_intersection(camera_center, ray_direction, t);
				t_vec3 N = unit_vector(vec_sub(intersection, sph.center));
				t_vec3 intersec_light = unit_vector(vec_sub(light, intersection));
				float angle = cos(dot_product(N, intersec_light));
				// printf("%f\n", angle);
                my_mlx_pixel_put(img, x, y, 0x00FF0000 * angle);
			}
			else
                my_mlx_pixel_put(img, x, y, 0xADD8E6);

            y++;
        }
        x++;
    }
}

int main() 
{
	t_window window;
	t_data img;
	t_sphere sph1;
	sph1.center.x = 0;
	sph1.center.y = 0;
	sph1.center.z = -100;
	sph1.radius = 50;

	window.mlx_ptr = NULL;
	window.win_ptr = NULL;
	window.mlx_ptr = mlx_init(); //todo: add check for failure
	window.win_ptr = mlx_new_window(window.mlx_ptr, IMAGE_HEIGHT, IMAGE_WIDTH, WINDOW_TITLE); //todo: add check for failure
	

	mlx_hook(window.win_ptr, DestroyNotify, StructureNotifyMask, on_destroy, &window);
	mlx_hook(window.win_ptr, 2, (1L << 0), close_esc, &window);//todo: unification of arguments
	img.img = mlx_new_image(window.mlx_ptr, 1024, 768);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	
	create_image(&img, sph1);
	mlx_put_image_to_window(window.mlx_ptr, window.win_ptr, img.img, 0, 0);
	mlx_loop(window.mlx_ptr);
}