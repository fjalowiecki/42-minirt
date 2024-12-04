#include "minirt.h"

int set_amb_light(char **obj_args, t_data *data)
{
	if(check_amount_args(obj_args, 3) == -1)
		return (-1);
}
int set_camera(char **obj_args, t_data *data)
{
	if(check_amount_args(obj_args, 4) == -1)
		return (-1);
}

int set_light(char **obj_args, t_data *data)
{
	if(check_amount_args(obj_args, 4) == -1)
		return (-1);
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