#include "minirt.h"

int	get_brightness(char *str, float *ret)
{
	int	status;

	status = get_float(str, ret);
	if (status == -1)
		return (status);
	if (*ret > 1.0 || *ret < 0)
		return (error_return(RANGE_BRIGHT));
	return (0);
}

int	get_fov(char *str, float *ret)
{
	int	status;
	int	nr;

	status = get_int(str, &nr);
	*ret = (float)nr;
	if (status == -1)
		return (-1);
	if (*ret > 180 || *ret < 0)
		return (error_return(RANGE_FOV));
	return (0);
}

int	get_point(char *xyz, t_point3 *point)
{
	char		**xyz_splt;

	*point = (t_point3){0, 0, 0};
	xyz_splt = ft_split(xyz, ',');
	if (!xyz_splt)
		return (error_return(WRG_XYZ));
	if (arr_size(xyz_splt) != 3)
	{
		free_split(xyz_splt);
		return (error_return(WRG_XYZ));
	}
	if (get_float(xyz_splt[0], &point->x) == -1)
		return (free_split(xyz_splt));
	if (get_float(xyz_splt[1], &point->y) == -1)
		return (free_split(xyz_splt));
	if (get_float(xyz_splt[2], &point->z) == -1)
		return (free_split(xyz_splt));
	free_split(xyz_splt);
	return (0);
}

int	get_color(char *rgb, t_color *color)
{
	char	**rgb_splt;

	*color = ((t_color){0, 0, 0});
	rgb_splt = ft_split(rgb, ',');
	if (!rgb_splt)
		return (error_return(WRG_RGB));
	if (arr_size(rgb_splt) != 3)
	{
		free_split(rgb_splt);
		return (error_return(WRG_RGB));
	}
	if (get_int(rgb_splt[0], &color->r) == -1)
		return (free_split(rgb_splt));
	if (get_int(rgb_splt[1], &color->g) == -1)
		return (free_split(rgb_splt));
	if (get_int(rgb_splt[2], &color->b) == -1)
		return (free_split(rgb_splt));
	if (color->r > 255 || color->r < 0 || color->b > 255
		|| color->b < 0 || color->g > 255 || color->g < 0)
	{
		free_split(rgb_splt);
		return (error_return(RANGE_RGB));
	}
	free_split(rgb_splt);
	return (0);
}

int	get_vec(char *xyz, t_vec3 *vector)
{
	char	**xyz_splt;

	xyz_splt = ft_split(xyz, ',');
	if (!xyz_splt)
		return (perror_return());
	if (arr_size(xyz_splt) != 3)
	{
		free_split(xyz_splt);
		return (error_return(WRG_VEC));
	}
	if (get_float(xyz_splt[0], &vector->x) == -1)
		return (free_split(xyz_splt));
	if (get_float(xyz_splt[1], &vector->y) == -1)
		return (free_split(xyz_splt));
	if (get_float(xyz_splt[2], &vector->z) == -1)
		return (free_split(xyz_splt));
	if (check_vec(*vector) == -1)
		return (free_split(xyz_splt));
	free_split(xyz_splt);
	return (0);
}
