#include "minirt.h"

int	close_esc (int keycode, t_data *data)
{
	if (keycode == ESC)
	{
		printf("Leaving the program...\n");
		free_all(data);
		exit(0);
	}
}

int	on_destroy(t_data *data)
{
	printf("Leaving the program...\n");
	free_all(data);
	exit(0);
	return (0);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	rgb_to_hex(int r, int g, int b)
{
	if (r < 0)
		r = 0;
	if (r > 255)
		r = 255;
	if (g < 0)
		g = 0;
	if (g > 255)
		g = 255;
	if (b < 0)
		b = 0;
	if (b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
}
