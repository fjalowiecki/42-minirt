#include "minirt.h"

int set_amb_light(char **obj_args, t_data *data)
{
	int status;

	printf_split(obj_args);
	status = 0;
	if(check_amount_args(obj_args, 3) == -1)
		return (-1);
	data->amb_light->brightness = get_float(obj_args[1], &status);
	if (status == -1)
		return(-1);	
	data->amb_light->color = get_color(obj_args[2], &status);
	if (status == -1)
		return(-1);
	data->amb_light->origin = (t_point3){0,0,0};
	return(0);
}
int set_camera(char **obj_args, t_data *data)
{
	int status;
	t_view *view;

	printf_split(obj_args);
	if(check_amount_args(obj_args, 4) == -1)
		return (-1);
	status = 0;
	view = malloc(sizeof(t_view));
	if(!view)
		return(-1);
	view->camera_center = get_point(obj_args[1], &status);
	if (status == -1)
		return(-1);	
	view->focal_length = get_vec(obj_args[2], &status);
	if (status == -1)
		return(-1);	
	view->fov_degrees = get_fov(obj_args[3], &status);
	if (status == -1)
		return(-1);
	data->view = view;
	return(0);
}

int set_light(char **obj_args, t_data *data)
{
	
	static int i;
	int status;
	t_light light;

	printf_split(obj_args);
	status = 0;
	if(check_amount_args(obj_args, 4) == -1)
		return (-1);
	light.origin = get_point(obj_args[1], &status);
	light.brightness = get_brightness(obj_args[2], &status);
	light.color = get_color(obj_args[3], &status);
	if (status == -1)
		return(-1);	
	data->diff_lights[i] = light;
	i++;
	
}

int set_figures(int type, char **obj_args, t_data *data)
{
	static int i;
	int status;

	if (type == SPHERE)
		status = set_sphere(i,obj_args, data);
	if (type == PLANE)
		status = set_plane(i,obj_args, data);
	if (type == CYLINDER)
		status = set_cylinder(i,obj_args, data);
	if (type == CONE)
		status = set_cone(i,obj_args, data);
	(data->objects[i]).type = type;
	i++;
	return(0);
}

int check_amount_args(char **obj_args, int i)
{
	int j;

	j = 0;
	while (obj_args[j])
		j++;
	if(j != i)
		return (-1);
	return (0);
}
