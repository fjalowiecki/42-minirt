#include "minirt.h"

float calculate_viewport_width(float focal_length, float fov_degrees) {
    float fov_radians = fov_degrees * M_PI / 180.0;
    return 2.0 * focal_length * tan(fov_radians / 2.0);
}

void init_sphere(t_sphere *sph, float x, float y, float z, float radius, int r, int g, int b) {
    sph->center = (t_vec3){x, y, z};
    sph->radius = radius;
    sph->color = (t_color){r, g, b};
}

void init_plane(t_plane *plane, float x, float y, float z, float nx, float ny, float nz, int r, int g, int b) {
    plane->center = (t_vec3){x, y, z};
    plane->N = (t_vec3){nx, ny, nz};
    plane->color = (t_color){r, g, b};
}

void init_cylinder(t_cylinder *cyl, float x, float y, float z, float diameter, float height, float nx, float ny, float nz, int r, int g, int b) {
    cyl->center = (t_vec3){x, y, z};
    cyl->diameter = diameter;
    cyl->height = height;
    cyl->N_axis_vec = (t_vec3){nx, ny, nz};
    cyl->color = (t_color){r, g, b};
}

void init_cone(t_cone *cone, float x, float y, float z, float angle, float nx, float ny, float nz, float height, int r, int g, int b) {
    cone->vertex = (t_vec3){x, y, z};
    cone->angle = angle;
    cone->axis = (t_vec3){nx, ny, nz};
    cone->height = height;
    cone->color = (t_color){r, g, b};
}

void init_light(t_light *light, float x, float y, float z, float brightness, int r, int g, int b) {
    light->origin = (t_vec3){x, y, z};
    light->brightness = brightness;
    light->color = (t_color){r, g, b};
}

void init_scene(t_data *data) {
    t_sphere *sph1 = malloc(sizeof(t_sphere));
    t_sphere *sph2 = malloc(sizeof(t_sphere));
    t_plane *plane = malloc(sizeof(t_plane));
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
    data->view->camera_center = (t_vec3){0, 0, 0};
    data->view->focal_length = (t_vec3){0, 0, 1};
    data->view->image_width = IMAGE_WIDTH;
    data->view->image_height = IMAGE_HEIGHT;
    data->view->fov_degrees = 70;
    data->view->viewport_width = calculate_viewport_width(data->view->focal_length.z, data->view->fov_degrees);
    data->view->viewport_height = data->view->viewport_width / (data->view->image_width / data->view->image_height);

    data->amb_light = malloc(sizeof(t_light));
    init_light(data->amb_light, 0, 0, 0, 0.1, 255, 255, 255);

	data->diff_lights = malloc(sizeof(t_light) * 1);
	init_light(&data->diff_lights[0], 0, 100, -100, 0.6, 255, 255, 255);
	data->diff_lights_cnt = 1;

	init_plane(plane, 0, -20, 0, 0, 1, 0, 128, 128, 128);
	init_sphere(sph1, -50, 0, -100, 20, 255, 0, 0);
	init_sphere(sph2, -10, 0, -100, 12, 0, 0, 255);
	init_cylinder(cylinder, 20, -15, -100, 8, 10, 0, 1, 0, 0, 255, 0);
	init_cone(cone, 50, 0, -100, 0.5, 0, 1, 0, 15, 255, 0, 255);
}

void	init_window(t_window *window, t_img *img)
{
	window->mlx_ptr = NULL;
	window->win_ptr = NULL;
	img->img = NULL;
	img->addr = NULL;

	window->mlx_ptr = mlx_init();
	if (window->mlx_ptr == NULL)
		error_exit(MLX_ERR);
	window->win_ptr = mlx_new_window(window->mlx_ptr,
			IMAGE_WIDTH, IMAGE_HEIGHT, WINDOW_TITLE);
	if (window->win_ptr == NULL)
	{
		free(window->mlx_ptr);
		error_exit(MLX_ERR);
	}
	img->img = mlx_new_image(window->mlx_ptr, IMAGE_WIDTH, IMAGE_HEIGHT);
	if (img->img == NULL)
	{
		free(window->mlx_ptr);
		free(window->win_ptr);
		error_exit(MLX_ERR);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

int	main(int argc, char **argv)
{
	t_window	window;
	t_img		img;
	t_data		data;

	input_parser(argc, argv, &data);
	init_window(&window, &img);
	init_scene(&data);
	create_image(&img, &data);
	mlx_put_image_to_window(window.mlx_ptr, window.win_ptr, img.img, 0, 0);
	mlx_hook(window.win_ptr, DestroyNotify, StructureNotifyMask,
		on_destroy, &window);
	mlx_hook(window.win_ptr, KeyPress, KeyPressMask, close_esc, &window);
	mlx_loop(window.mlx_ptr);
}
