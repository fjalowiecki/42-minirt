#include "minirt.h"

int set_amb_light(char **obj_args, t_data *data)
{
	if(check_amount_args(obj_args, 3) == -1)
		return (-1);
	if (get_float(obj_args[1], &data->amb_light->brightness) == -1)
		return(-1);	
	if (get_color(obj_args[2], &data->amb_light->color) == -1)
		return(-1);
	data->amb_light->origin = (t_point3){0,0,0};
	return(0);
}
int set_camera(char **obj_args, t_data *data)
{
	t_view *view;

	if(check_amount_args(obj_args, 4) == -1)
		return (-1);
	view = malloc(sizeof(t_view));
	if(!view)
		return(perror_return());
	if(get_point(obj_args[1], &(view->camera_center)) == -1)
		return(-1);	
	if(get_vec(obj_args[2], &(view->focal_length)) == -1)
		return(-1);	
	if(get_fov(obj_args[3], &(view->fov_degrees)) == -1)
		return(-1);
	data->view = view;
	return(0);
}

int set_light(char **obj_args, t_data *data)
{
	static int i;
	t_light light;

	if(check_amount_args(obj_args, 4) == -1)
		return(-1);
	if(get_point(obj_args[1], &light.origin) == -1)
		return(-1);
	if(get_brightness(obj_args[2], &light.brightness) == -1)
		return(-1);
	if(get_color(obj_args[3], &light.color) == -1)
		return(-1);
	data->diff_lights[i] = light;
	i++;
	return(0);
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
	if (status == -1)
		return(-1);
	(data->objects[i]).type = type;
	i++;
	return (0);
}

int check_amount_args(char **obj_args, int i)
{
	int j;

	j = 0;
	while (obj_args[j])
		j++;
	if (j != i)
		return (-1);
	return (0);
}
