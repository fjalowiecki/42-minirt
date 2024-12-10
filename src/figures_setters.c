#include "minirt.h"

int set_sphere (int i, char **obj_args, t_data *data)
{
	int status;
	t_sphere *sphere;

	status = 0;
	printf_split(obj_args);
	if(check_amount_args(obj_args, 4) == -1)
		return (-1);
	sphere = malloc(sizeof(t_sphere));
	if(!sphere)
		return(-1);
	sphere->center = get_point(obj_args[1], &status);
	if (status == -1)
		return(-1);
	sphere->radius = get_float(obj_args[2], &status);
	if (status == -1)
		return(-1);
	sphere->color = get_color(obj_args[3], &status);
	if (status == -1)
		return(-1);
	data->objects[i].object = (void *)(sphere);
	return (0);
}

int set_plane (int i, char **obj_args, t_data *data)
{
	int status;
	t_plane *plane;
	printf_split(obj_args);

	status = 0;
	if(check_amount_args(obj_args, 4) == -1)
		return (-1);
	plane = malloc(sizeof(t_plane));
	if(!plane)
		return(-1);
	plane->center = get_point(obj_args[1], &status);
	if (status == -1)
		return(-1);
	plane->N = get_vec(obj_args[2], &status);
	if (status == -1)
		return(-1);
	plane->color = get_color(obj_args[3], &status);
	if (status == -1)
		return(-1);
	data->objects[i].object = (void *)(plane);
	return (0);
}

int set_cylinder (int i, char **obj_args, t_data *data)
{
	int status;
	t_cylinder *cylinder;
	printf_split(obj_args);

	status = 0;
	if(check_amount_args(obj_args, 6) == -1)
		return (-1);
	cylinder = malloc(sizeof(t_cylinder));
	if(!cylinder)
		return(-1);
	cylinder->center = get_point(obj_args[1], &status);
	if (status == -1)
		return(-1);
	cylinder->N_axis_vec = get_vec(obj_args[2], &status);
	if (status == -1)
		return(-1);
	cylinder->diameter = get_float(obj_args[3], &status);
	if (status == -1)
		return(-1);
	cylinder->height = get_float(obj_args[4], &status);
	if (status == -1)
		return(-1);
	cylinder->color = get_color(obj_args[5], &status);
	if (status == -1)
		return(-1);
	data->objects[i].object = (void *)(cylinder);
	return (0);
}

int set_cone (int i, char **obj_args, t_data *data)
{
	int status;
	t_cone *cone;
	printf_split(obj_args);

	status = 0;
	if(check_amount_args(obj_args, 6) == -1)
		return (-1);
	cone = malloc(sizeof(t_cone));
	if(!cone)
		return(-1);
	cone->vertex = get_point(obj_args[1], &status);
	if (status == -1)
		return(-1);
	cone->axis = get_vec(obj_args[2], &status);
	if (status == -1)
		return(-1);
	cone->angle = get_float(obj_args[3], &status);
	if (status == -1)
		return(-1);
	cone->height = get_float(obj_args[4], &status);
	if (status == -1)
		return(-1);
	cone->color = get_color(obj_args[5], &status);
	if (status == -1)
		return(-1);
	data->objects[i].object = (void *)(cone);
	return (0);
}

