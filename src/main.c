#include "minirt.h"

float calculate_viewport_width(float focal_length, float fov_degrees) {
    float fov_radians = fov_degrees * M_PI / 180.0;
    return 2.0 * focal_length * tan(fov_radians / 2.0);
}

void init_scene(t_data *data) //t_view *view, t_light **light, t_object **obj_arr)
{
	data->view->image_width = IMAGE_WIDTH;
	data->view->image_height = IMAGE_HEIGHT;
	data->view->viewport_width = calculate_viewport_width(data->view->focal_length.z, data->view->fov_degrees);
	data->view->viewport_height = data->view->viewport_width / (data->view->image_width/data->view->image_height);
	/*t_sphere *sph1 = malloc(sizeof(t_sphere));
	t_sphere *sph2 = malloc(sizeof(t_sphere));
	t_plane *plane = malloc(sizeof(t_plane));
	t_plane *plane2 = malloc(sizeof(t_plane));
	t_cylinder *cylinder = malloc(sizeof(t_cylinder));
	t_cone *cone = malloc(sizeof(t_cone));

    data->objects = malloc(sizeof(t_object) * 5);
    data->objects[0].type = 0;
    data->objects[0].object = sph1;
    data->objects[1].type = 0;
    data->objects[1].object = sph2;
    data->objects[2].type = 1;
    data->objects[2].object = plane;
    data->objects[3].type = 2;
    data->objects[3].object = cylinder;
    data->objects[4].type = 3;
    data->objects[4].object = cone;

    data->objects_cnt = 5;

	data->view = malloc(sizeof(t_view));
	data->view->camera_center.x = 0;
	data->view->camera_center.y = 0;
	data->view->camera_center.z = 0;
	data->view->focal_length.x = 0;
	data->view->focal_length.y = 0;
	data->view->focal_length.z = 1;

    data->amb_light = malloc(sizeof(t_light));
    init_light(data->amb_light, 0, 0, 0, 0.1, 255, 255, 255);

	data->diff_lights = malloc(sizeof(t_light) * 2);
	data->diff_lights[0].origin.x = -30;
	data->diff_lights[0].origin.y = 100;
	data->diff_lights[0].origin.z = -20;
	data->diff_lights[0].brightness = 0.5;
	data->diff_lights[0].color = (t_color){48, 41, 181};
	data->diff_lights[1].origin.x = -10;
	data->diff_lights[1].origin.y = 10;
	data->diff_lights[1].origin.z = 10;
	data->diff_lights[1].brightness = 0.4;
	data->diff_lights[1].color = (t_color){120, 37, 37};
	data->diff_lights_cnt = 2;

	sph1->center.x = -15;
	sph1->center.y = 0;
	sph1->center.z = -100;
	sph1->radius = 15;
	sph1->color.r = 148;
	sph1->color.g = 25;
	sph1->color.b = 25;

	sph2->center.x = 10;
	sph2->center.y = -5;
	sph2->center.z = -100;
	sph2->radius = 10;
	sph2->color.r = 47;
	sph2->color.g = 184;
	sph2->color.b = 37;

	plane->center.x = 0;
	plane->center.y = -15;
	plane->center.z = 0;
	plane->N.x = 0;
	plane->N.y = 1;
	plane->N.z = 0;
	plane->color.r = 26;
	plane->color.g = 16;
	plane->color.b = 161;

	cylinder->center.x = 10;
	cylinder->center.y = -10;
	cylinder->center.z = -40;
	cylinder->diameter = 5;
	cylinder-> height = 7;
	cylinder->N_axis_vec.x =  -1;
	cylinder->N_axis_vec.y =  1;
	cylinder->N_axis_vec.z =  1;
	cylinder->color.r = 0;
	cylinder->color.g = 255;
	cylinder->color.b = 0;

	cone->angle = 0.7;
	cone->axis.x = 0;
	cone->axis.y = -0.1;
	cone->axis.z = 0;
	cone->color.r = 255;
	cone->color.g = 0;
	cone->color.b = 0;
	cone->height = 10;
	cone->vertex.x = 0;
	cone->vertex.y = 0;
	cone->vertex.z = -30;*/
	
}

void	init_window(t_window *window, t_img *img, t_data *data)
{
	window_null(window,img);
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
	if(img->addr == NULL)
	{
		free_all(data);
		error_exit(IMG_ERR);
	}
}

void window_null(t_window *window, t_img *img)
{
	window->mlx_ptr = NULL;
	window->win_ptr = NULL;
	img->img = NULL;
	img->addr = NULL;
}

int	main(int argc, char **argv)
{
	t_data		data;

	input_parser(argc, argv, &data);
	printf_all(&data);
	init_window(&data.window, &data.img ,&data);
	init_scene(&data);
	create_image(&data.img, &data);
	mlx_put_image_to_window(data.window.mlx_ptr, data.window.win_ptr, data.img.img, 0, 0);
	mlx_hook(data.window.win_ptr, DestroyNotify, StructureNotifyMask,
		on_destroy, &data);
	mlx_hook(data.window.win_ptr, KeyPress, KeyPressMask, close_esc, &data);
	mlx_loop(data.window.mlx_ptr);
}
