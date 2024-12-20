#include "minirt.h"

int	set_obj(char *line, t_data *data, int type)
{
	char	**obj_args;
	int		status;

	status = 0;
	if (check_line(line) == -1)
		return (-1);
	obj_args = ft_split(line, ' ');
	if (!obj_args)
		perror_return();
	if (type == AMB_LIGHT)
		status = set_amb_light(obj_args, data);
	else if (type == CAMERA)
		status = set_camera(obj_args, data);
	else if (type == DIF_LIGHT)
		status = set_light(obj_args, data);
	else
		status = set_figures(type, obj_args, data);
	free_split(obj_args);
	if (status == -1)
		return (-1);
	return (0);
}

int	set_amb_light(char **obj_args, t_data *data)
{
	if (check_amount_args(obj_args, 3) == -1)
		return (-1);
	if (get_brightness(obj_args[1], &data->amb_light->brightness) == -1)
		return (-1);
	if (get_color(obj_args[2], &data->amb_light->color) == -1)
		return (-1);
	data->amb_light->origin = (t_point3){0, 0, 0};
	return (0);
}

int	set_camera(char **obj_args, t_data *data)
{
	t_view	*view;

	if (check_amount_args(obj_args, 4) == -1)
		return (-1);
	view = malloc(sizeof(t_view));
	if (!view)
		return (perror_return());
	data->view = view;
	if (get_point(obj_args[1], &(view->camera_center)) == -1)
		return (-1);
	if (get_vec(obj_args[2], &(view->focal_length)) == -1)
		return (-1);
	if (get_fov(obj_args[3], &(view->fov_degrees)) == -1)
		return (-1);
	return (0);
}

int	set_light(char **obj_args, t_data *data)
{
	static int	i;
	t_light		light;

	if (check_amount_args(obj_args, 4) == -1)
		return (-1);
	if (get_point(obj_args[1], &light.origin) == -1)
		return (-1);
	if (get_brightness(obj_args[2], &light.brightness) == -1)
		return (-1);
	if (get_color(obj_args[3], &light.color) == -1)
		return (-1);
	data->diff_lights[i] = light;
	i++;
	return (0);
}

int	set_figures(int type, char **obj_args, t_data *data)
{
	static int	i;
	int			status;

	if (type == SPHERE)
		status = set_sphere(i, obj_args, data);
	if (type == PLANE)
		status = set_plane(i, obj_args, data);
	if (type == CYLINDER)
		status = set_cylinder(i, obj_args, data);
	if (type == CONE)
		status = set_cone(i, obj_args, data);
	if (status == -1)
		return (-1);
	(data->objects[i]).type = type;
	i++;
	return (0);
}
