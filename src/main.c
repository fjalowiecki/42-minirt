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

bool hit_sphere(t_point3 center, float radius, t_ray r) {
    t_vec3 oc = vec_sub(r.orig, center);
    float a = dot_product(r.dir, r.dir);
    float b = 2.0 * dot_product(r.dir, oc);
    float c = dot_product(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    return (discriminant >= 0);
}

void create_image(t_data *img, t_sphere sph)
{
	t_ray ray;
	ray.orig.x = 0;
	ray.orig.y = 0;
	ray.orig.z = 0;

    int x = 0;
    while (x < IMAGE_HEIGHT)
    {
        int y = 0;
        while (y < IMAGE_WIDTH)
        {
            ray.dir.x = (float)x / (IMAGE_HEIGHT - 1);
            ray.dir.y = (float)y / (IMAGE_WIDTH - 1);
            ray.dir.z = -1.0;

            if (hit_sphere(sph.center, sph.radius, ray))
                my_mlx_pixel_put(img, x, y, 0x00FF0000);
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
	sph1.center.x = 100;
	sph1.center.y = 100;
	sph1.center.z = -200;
	sph1.radius = 10;

	window.mlx_ptr = NULL;
	window.win_ptr = NULL;
	window.mlx_ptr = mlx_init(); //todo: add check for failure
	window.win_ptr = mlx_new_window(window.mlx_ptr, IMAGE_HEIGHT, IMAGE_WIDTH, WINDOW_TITLE); //todo: add check for failure
	

	mlx_hook(window.win_ptr, DestroyNotify, StructureNotifyMask, on_destroy, &window);
	mlx_hook(window.win_ptr, 2, (1L << 0), close_esc, &window);//todo: unification of arguments
	img.img = mlx_new_image(window.mlx_ptr, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	
	create_image(&img, sph1);
	mlx_put_image_to_window(window.mlx_ptr, window.win_ptr, img.img, 0, 0);
	mlx_loop(window.mlx_ptr);
}