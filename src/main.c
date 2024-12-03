#include "minirt.h"

float calculate_viewport_width(float focal_length, float fov_degrees) {
    float fov_radians = fov_degrees * M_PI / 180.0;
    return 2.0 * focal_length * tan(fov_radians / 2.0);
}

void init_scene(t_data *data) //t_view *view, t_light **light, t_object **obj_arr)
{
	t_sphere *sph1 = malloc(sizeof(t_sphere));
	t_sphere *sph2 = malloc(sizeof(t_sphere));
	t_plane *plane = malloc(sizeof(t_plane));
	// t_plane *plane2 = malloc(sizeof(t_plane));
	// t_cylinder *cylinder = malloc(sizeof(t_cylinder));

	data->objects = malloc(sizeof(t_object) * 3);
	data->objects[0].type = 0;
	data->objects[0].object = sph1;
	data->objects[1].type = 0;
	data->objects[1].object = sph2;
	data->objects[2].type = 1;
	data->objects[2].object = plane;
	// data->objects[3].type = 1;
	// data->objects[3].object = plane2;
	// data->objects[4].type = 2;
	// data->objects[4].object = cylinder;
	data->objects_cnt = 3;

	data->view = malloc(sizeof(t_view));
	data->view->camera_center.x = 0;
	data->view->camera_center.y = 0;
	data->view->camera_center.z = 0;
	data->view->focal_length.x = 0;
	data->view->focal_length.y = 0;
	data->view->focal_length.z = 1;
	data->view->image_width = IMAGE_WIDTH;
	data->view->image_height = IMAGE_HEIGHT;
	data->view->viewport_height = 2.0;
	data->view->fov_degrees = 70;
	data->view->viewport_width = calculate_viewport_width(data->view->focal_length.z, data->view->fov_degrees);
	data->view->viewport_height = data->view->viewport_width / (data->view->image_width/data->view->image_height);

	data->amb_light = malloc(sizeof(t_light));
	data->amb_light->origin = (t_vec3){0, 0, 0};
	data->amb_light->brightness = 0;
	// data->amb_light->color = (t_color){191, 135, 21};
	data->amb_light->color = (t_color){255, 255, 255};

	data->diff_lights = malloc(sizeof(t_light) * 2);
	data->diff_lights[0].origin.x = -50;
	data->diff_lights[0].origin.y = 50;
	data->diff_lights[0].origin.z = -100;
	data->diff_lights[0].brightness = 0;
	data->diff_lights[0].color = (t_color){181, 181, 181};
	data->diff_lights[1].origin.x = 30;
	data->diff_lights[1].origin.y = 50;
	data->diff_lights[1].origin.z = -40;
	data->diff_lights[1].brightness = 0.5;
	data->diff_lights[1].color = (t_color){0, 0, 0};
	// data->diff_lights[1].color = (t_color){30, 21, 191};
	data->diff_lights_cnt = 2;

	//red
	sph1->center.x = -15;
	sph1->center.y = 0;
	sph1->center.z = -100;
	sph1->radius = 15;
	sph1->color.r = 148;
	sph1->color.g = 25;
	sph1->color.b = 25;

	//green
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

	// plane2->center.x = -500;
	// plane2->center.y = 0;
	// plane2->center.z = 0;
	// plane2->N.x = 1;
	// plane2->N.y = 0;
	// plane2->N.z = 0;
	// plane2->color.r = 0;
	// plane2->color.g = 0;
	// plane2->color.b = 255;

	// cylinder->center.x = 15;
	// cylinder->center.y = -10;
	// cylinder->center.z = -30;
	// cylinder->diameter = 5;
	// cylinder-> height = 7;
	// cylinder->N_axis_vec.x =  -1;
	// cylinder->N_axis_vec.y =  1;
	// cylinder->N_axis_vec.z =  1;
	// cylinder->color.r = 0;
	// cylinder->color.g = 255;
	// cylinder->color.b = 0;
}

int main() 
{
	t_window window;
	t_img img;
	t_data data;

	window.mlx_ptr = mlx_init(); //todo: add check for failure
	window.win_ptr = mlx_new_window(window.mlx_ptr, IMAGE_WIDTH, IMAGE_HEIGHT, WINDOW_TITLE); //todo: add check for failure
	mlx_hook(window.win_ptr, DestroyNotify, StructureNotifyMask, on_destroy, &window);
	mlx_hook(window.win_ptr, 2, (1L << 0), close_esc, &window);//todo: unification of arguments
	img.img = mlx_new_image(window.mlx_ptr, IMAGE_WIDTH, IMAGE_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	init_scene(&data);
	create_image(&img, &data);
	mlx_put_image_to_window(window.mlx_ptr, window.win_ptr, img.img, 0, 0);
	mlx_loop(window.mlx_ptr);
}