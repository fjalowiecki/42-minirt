#include "minirt.h"

int	set_sphere(int i, char **obj_args, t_data *data)
{
	t_sphere	*sphere;

	if (check_amount_args(obj_args, 4) == -1)
		return (-1);
	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (perror_return());
	data->objects[i].object = (void *)(sphere);
	if (get_point(obj_args[1], &sphere->center) == -1)
		return (-1);
	if (get_double(obj_args[2], &sphere->radius) == -1)
		return (-1);
	if (get_color(obj_args[3], &sphere->color) == -1)
		return (-1);
	return (0);
}

int	set_plane(int i, char **obj_args, t_data *data)
{
	t_plane	*plane;

	if (check_amount_args(obj_args, 4) == -1)
		return (-1);
	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (perror_return());
	data->objects[i].object = (void *)(plane);
	if (get_point(obj_args[1], &plane->center) == -1)
		return (-1);
	if (get_vec(obj_args[2], &plane->N) == -1)
		return (-1);
	if (get_color(obj_args[3], &plane->color) == -1)
		return (-1);
	return (0);
}

int	set_cylinder(int i, char **obj_args, t_data *data)
{
	t_cylinder	*cylinder;

	if (check_amount_args(obj_args, 6) == -1)
		return (-1);
	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (perror_return());
	data->objects[i].object = (void *)(cylinder);
	if (get_point(obj_args[1], &cylinder->center) == -1)
		return (-1);
	if (get_vec(obj_args[2], &cylinder->N_axis) == -1)
		return (-1);
	if (get_double(obj_args[3], &cylinder->diameter) == -1)
		return (-1);
	cylinder->r = cylinder->diameter / 2.0;
	if (get_double(obj_args[4], &cylinder->h) == -1)
		return (-1);
	if (get_color(obj_args[5], &cylinder->color) == -1)
		return (-1);
	return (0);
}

int	set_cone(int i, char **obj_args, t_data *data)
{
	t_cone	*cone;

	if (check_amount_args(obj_args, 6) == -1)
		return (-1);
	cone = malloc(sizeof(t_cone));
	if (!cone)
		return (perror_return());
	data->objects[i].object = (void *)(cone);
	if (get_point(obj_args[1], &cone->vertex) == -1)
		return (-1);
	if (get_vec(obj_args[2], &cone->axis) == -1)
		return (-1);
	if (get_double(obj_args[3], &cone->angle) == -1)
		return (-1);
	if (cone->angle < 0 || cone->angle > 1.5)
		return (error_return(RANGE_CONE));
	if (get_double(obj_args[4], &cone->height) == -1)
		return (-1);
	if (get_color(obj_args[5], &cone->color) == -1)
		return (-1);
	return (0);
}
