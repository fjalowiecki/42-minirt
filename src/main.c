#include "minirt.h"

static void	window_null(t_window *window, t_img *img)
{
	window->mlx_ptr = NULL;
	window->win_ptr = NULL;
	img->img = NULL;
	img->addr = NULL;
}

static void	init_window(t_window *window, t_img *img, t_data *data)
{
	window_null(window, img);
	window->mlx_ptr = mlx_init();
	if (window->mlx_ptr == NULL)
		error_exit(MLX_ERR);
	window->win_ptr = mlx_new_window(window->mlx_ptr,
			IMAGE_WIDTH, IMAGE_HEIGHT, WINDOW_TITLE);
	if (window->win_ptr == NULL)
	{
		free_all(data);
		error_exit(MLX_ERR);
	}
	img->img = mlx_new_image(window->mlx_ptr, IMAGE_WIDTH, IMAGE_HEIGHT);
	if (img->img == NULL)
	{
		free_all(data);
		error_exit(MLX_ERR);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (img->addr == NULL)
	{
		free_all(data);
		error_exit(IMG_ERR);
	}
}

int	main(int argc, char **argv)
{
	t_data		data;

	input_parser(argc, argv, &data);
	printf_all(&data);
	init_window(&data.window, &data.img, &data);
	create_image(&data.img, &data);
	mlx_put_image_to_window(data.window.mlx_ptr,
		data.window.win_ptr, data.img.img, 0, 0);
	mlx_hook(data.window.win_ptr, DestroyNotify, StructureNotifyMask,
		on_destroy, &data);
	mlx_hook(data.window.win_ptr, KeyPress, KeyPressMask, close_esc, &data);
	mlx_loop(data.window.mlx_ptr);
}
