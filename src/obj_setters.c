#include "minirt.h"

int set_amb_light(char **obj_args, t_data *data)
{
	int status;
	t_light *amb_light;

	if(check_amount_args(obj_args, 3) == -1)
		return (-1);
	amb_light = malloc(sizeof(t_light));
	if(!amb_light)
		return(-1);
	amb_light->brightness = get_float(obj_args[1], &status);
	if (status == -1)
		return(-1);	
	amb_light->color = get_color(obj_args[2], &status);
	if (status == -1)
		return(-1);
	data->amb_light = amb_light;
	return(0);
}
int set_camera(char **obj_args, t_data *data)
{
	int status;
	t_view *view;
	if(check_amount_args(obj_args, 4) == -1)
		return (-1);
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

	status = 0;
	if(check_amount_args(obj_args, 4) == -1)
		return (-1);
	light.origin = get_point(obj_args[1], &status);
	light.brightness = get_fov(obj_args[2], &status);
	light.color = get_color(obj_args[3], &status);
	if (status == -1)
		return(-1);	
	data->diff_lights[i] = light;
	i++;
	return(i);
	
}

int set_figures(int type, char **obj_args, t_data *data)
{
	static int i;
	int status;

	if (type == 4)
		status = set_sphere(i,obj_args, data);
	if (type == 5)
		status = set_plane(i,obj_args, data);
	if (type == 6)
		status = set_cylinder(i,obj_args, data);
	if (type == 7)
		status = set_cone(i,obj_args, data);
	i++;
}

int check_amount_args(char **obj_args, int i)
{
	int j;

	j = 0;
	while (obj_args[i])
		j++;
	if(j != i)
		return (-1);
	return (0);
}
