#include "minirt.h"

double	calc_spec(double angle, int color)
{
	double	shininess;
	double	spec_strength;
	double	spec;

	shininess = 32.0f;
	spec_strength = 0.3f;
	spec = spec_strength * pow(angle, shininess);
	return (spec * (color / 255.0f));
}

static void	calc_viewport_vectors(t_view *view,
	t_vec3	*viewport_u, t_vec3	*viewport_v)
{
	t_vec3	up;
	t_vec3	right;
	t_vec3	true_up;

	if (fabs(view->focal_length.x) < 0.0001f
		&& fabs(view->focal_length.z) < 0.0001f)
		up = (t_vec3){0, 0, -1};
	else
		up = (t_vec3){0, 1, 0};
	right = cross_product(up, view->focal_length);
	right = unit_vector(right);
	*viewport_u = vec_mul(right, view->viewport_width);
	true_up = cross_product(view->focal_length, right);
	true_up = unit_vector(true_up);
	*viewport_v = vec_mul(true_up, -view->viewport_height);
}

static void	set_viewport_parameters(t_view *view,
	t_pixel_data *pixel_data)
{
	t_vec3	viewport_u;
	t_vec3	viewport_v;
	t_vec3	viewport_upper_left;
	double	fov_radians;

	fov_radians = view->fov_degrees * M_PI / 180.0;
	view->image_width = IMAGE_WIDTH;
	view->image_height = IMAGE_HEIGHT;
	view->viewport_width = tan(fov_radians / 2.0);
	view->viewport_height = view->viewport_width
		/ (view->image_width / view->image_height);
	calc_viewport_vectors(view, &viewport_u, &viewport_v);
	pixel_data->pixel_delta_u = vec_mul(viewport_u, 1.0 / view->image_width);
	pixel_data->pixel_delta_v = vec_mul(viewport_v, 1.0 / view->image_height);
	viewport_upper_left = vec_sub(vec_sub(vec_sub(view->camera_center,
					view->focal_length), vec_mul(viewport_u, 0.5)),
			vec_mul(viewport_v, 0.5));
	pixel_data->pixel00_loc = vec_add(viewport_upper_left,
			vec_mul(vec_add(pixel_data->pixel_delta_u,
					pixel_data->pixel_delta_v), 0.5));
	pixel_data->angles_diff = NULL;
	pixel_data->angles_spec = NULL;
}

void	create_image(t_img *img, t_data *data)
{
	t_pixel_data	pixel_data;
	unsigned int	color;
	int				x;
	int				y;

	set_viewport_parameters(data->view, &pixel_data);
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
