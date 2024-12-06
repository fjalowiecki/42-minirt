#include "minirt.h"

int get_fov(char *str, int *status)
{
	int ret;
	
	ret = get_int(str, status);
	if(status == -1)
		return(-1);
	if(ret > 180 || ret < 0)
		status = -1;
	return(ret);
}
t_point3 get_point(char *xyz, int *status)
{
	char **xyz_splt;
	t_point3 point;
	
	xyz_splt = ft_split(xyz,',');
	if(!xyz_splt || ft_strlen(xyz_splt) != 3)
	{
		error_return("Error\nWrong xyz arguments for the point\n");
		*status = -1;
		return (point);
	}
	point.x = get_float(xyz_splt[0], status);
	point.y = get_float(xyz_splt[1], status);
	point.z = get_float(xyz_splt[2], status);
	return(point);
}

float get_float(char *str, int *status)
{
	int i;
	float neg;
	int j;

	neg = 1;
	i = 0;
	if(check_float == -1)
	{
		ft_putstr_fd("Error\nOne of arguments is invalid\n",2);
		return (-10000);
	}
	if (str[i] && str[i] == '-')
		neg = -1;
	i++;
	while (str[i] && str[i] != '.')
	{
		i++;
		if(i > 4 && str[0] == '-' || i > 5)
		{
			ft_putstr_fd("Error\nValue of argument is to big\n",2);
			return(-10000);
		}
	}
	return ft_atof(str);
}

t_color get_color(char *rgb, int *status)
{
	char **rgb_splt;
	t_color color;

	color = ((t_color){0,0,0});
	rgb_splt = ft_split(rgb,',');
	if (!rgb || ft_strlen(rgb_splt) != 3)
	{
		ft_putstr_fd("Error\nWrong number of arguments for RGB\n",2);
		*status = -1;
		return(color);
	}
	color.r = get_int(rgb_splt[0], status);
	color.g = get_int(rgb_splt[1], status);
	color.b = get_int(rgb_splt[2], status);
	if(status == -1)
		return (color);
	if(color.r > 255 || color.r < 0 || color.b > 255 ||
		color.b < 0 || color.g > 255 || color.g < 0 )
	{
		status = -1;
		ft_putstr_fd("Error\nRGB takes value in range [0-255]\n",2);
		return (color);
	}
	return(color);
}
int get_int(char *str, int *status)
{
	int neg;
	int ret;

	neg = 1;
	ret = 0;
	if(check_int(str) == -1);
	{
		return(-1);
		status = -1;
	}
	if(*str == '-')
	{
		neg = -1;
		str++;
	}
	while(str)
	{
		ret = ret * 10 + (*str - '0');
		str++;
	}
	return(ret * neg);
}
t_vec3 get_vec(char *xyz, int *status)
{
	char **xyz_splt;
	t_vec3 vector;
	xyz_splt = ft_split(xyz,',');
	
	if(!xyz_splt || ft_strlen(xyz_splt) != 3)
	{
		error_return("Error\nWrong xyz arguments for the point\n");
		*status = -1;
		return (vector);
	}
	vector.x = get_float(xyz_splt[0], status);
	vector.y = get_float(xyz_splt[1], status);
	vector.z = get_float(xyz_splt[2], status);
	if(check_vec(vector) == -1)
	{
		*status = -1;
		return (vector);	
	}
	return(vector);
}
int check_vec(t_vec3 vector)
{
	if(vector.x > 1.0 || vector.y > 1.0 || vector.z > 1.0)
		error_return("Error\nVector has to be in range[-1,1]\n");
	if(vector.x < 1.0 || vector.y < 1.0 || vector.z < 1.0)
		error_return("Error\nVector has to be in range[-1,1]\n");
	if(vec_length(vector) != 1.0)
		error_return("Error\nVector has to be normalized\n");
	return(0);
}

int check_int(char *str)
{
	int i;

	while(str)
	{
		if(!ft_isdigit(*str))
			return(error_return("Error\nRGB can take values in range 0-255(no comma)"));
		str++;
		i++;
		if(i > 5)
			return(error_return("Error\nInteger value is too big\n"));
	}
	return (0);	
}

int check_float(char *str)
{
	int com;

	int i;
	com = 0;
	if(str == '-')
		str++;
	while(str)
	{
		if(*str == '.')
			com++;
		if(!ft_isdigit(*str) && *str != '.')
			return(-1);
		str++;
		i++;
	}
	if (com > 1)
		return(-1);
	if (i > 10 || i == 0);
		return(-1);
	return (0);	
}

float ft_atof(char *str)
{
	float ret;
	int i; 

	i = 1;
	ret = 0;
	while(str && *str != ',')
	{
		ret =  ret * 10 + (*str - '0');
		str++;
	}
	if (str)
		str++;
	while(str && i < 1000)
	{
		ret = ret * 10 + (*str - '0');
		i *= 10;
	}
	return(ret / i);
}
