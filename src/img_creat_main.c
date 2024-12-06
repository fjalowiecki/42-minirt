#include "minirt.h"

static void	set_viewport_pixel_parameters(t_view *view,
	t_pixel_data *pixel_data)
{
	t_vec3	viewport_u;
	t_vec3	viewport_v;
	t_vec3	viewport_upper_left;

	viewport_u = (t_vec3){view->viewport_width, 0, 0};
	viewport_v = (t_vec3){0, -view->viewport_height, 0};
	pixel_data->pixel_delta_u = vec_mul(viewport_u, 1.0 / view->image_width);
	pixel_data->pixel_delta_v = vec_mul(viewport_v, 1.0 / view->image_height);
	viewport_upper_left = vec_sub(vec_sub(vec_sub(view->camera_center,
					view->focal_length), vec_mul(viewport_u, 0.5)),
			vec_mul(viewport_v, 0.5));
	pixel_data->pixel00_loc = vec_add(viewport_upper_left,
			vec_mul(vec_add(pixel_data->pixel_delta_u,
					pixel_data->pixel_delta_v), 0.5));
}

void	create_image(t_img *img, t_data *data)
{
	t_pixel_data	pixel_data;
	unsigned int	color;
	int				x;
	int				y;

	set_viewport_pixel_parameters(data->view, &pixel_data);
	x = 0;
	while (x < IMAGE_WIDTH)
	{
		y = 0;
		while (y < IMAGE_HEIGHT)
		{
			calc_ray_params_for_pixel(data, &pixel_data, x, y);
			calc_closest_t_for_ray(data, &pixel_data);
			if (pixel_data.closest_t < 0)
				my_mlx_pixel_put(img, x, y, 0xADD8E6);
			else
			{
				color = calc_color_for_pixel(data, &pixel_data);
				my_mlx_pixel_put(img, x, y, color);
			}
			y++;
		}
		x++;
	}
}
