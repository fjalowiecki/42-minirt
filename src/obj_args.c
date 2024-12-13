#include "minirt.h"

int get_brightness(char *str, float *ret)
{
	int status;
	
	status = get_float(str, ret);
	if (status == -1)
		return(status);
	if(*ret > 1.0 || *ret < 0)
		return(error_return("Error\nBrightness has to be in range[0.0-1.0]"));
	return(0);
}
int get_fov(char *str, float *ret)
{	
	int status;
	int nr;

	status = get_int(str, &nr);
	*ret = (float)nr; 
	if(status == -1)
		return (-1);
	if(*ret > 180 || *ret < 0)
		return (error_return("Error\nFOV has to be in range [0-180]"));
	return (0);
}
int get_point(char *xyz, t_point3 *point)
{
	char		**xyz_splt;

	*point = (t_point3){0,0,0};
	xyz_splt = ft_split(xyz,',');
	if(!xyz_splt)
		return(error_return("Error\nWrong xyz arguments for the point\n"));
	if(arr_size(xyz_splt) != 3)
	{
		free_split(xyz_splt);
		return(error_return("Error\nWrong xyz arguments for the point\n"));
	}
	if(get_float(xyz_splt[0], &point->x) == -1)
		return(free_split(xyz_splt));
	if(get_float(xyz_splt[1], &point->y) == -1)
		return(free_split(xyz_splt));
	if(get_float(xyz_splt[2], &point->z) == -1)
		return(free_split(xyz_splt));
	free_split(xyz_splt);
	return(0);
}

int get_float(char *str, float *ret)
{
	int		i;
	float	neg;

	neg = 1.0;
	i = 0;
	if (check_float(str) == -1)
		return (error_return("Error\nOne of arguments is invalid - float\n"));
	if (str[i] && str[i] == '-')
	{
		neg = -1.0;
		i++;
	}
	while (str[i] && str[i] != '.')
	{
		i++;
		if ((i > 4 && str[0] == '-') || i > 5)
			return (error_return("Error\nValue of argument is to big\n"));
	}
	*ret = ft_atof(str) * neg;
	return (0);
}

int get_color(char *rgb, t_color *color)
{
	char **rgb_splt;

	*color = ((t_color){0,0,0});
	rgb_splt = ft_split(rgb,',');
	if (!rgb_splt)
		return(error_return("Error\nWrong number of arguments for RGB\n"));
	if (arr_size(rgb_splt)!= 3)
	{
		free_split(rgb_splt);
		return(error_return("Error\nWrong amount of arguments for RGB\n"));
	}
	if(get_int(rgb_splt[0], &color->r) == -1)
		return(free_split(rgb_splt));
	if(get_int(rgb_splt[1], &color->g) == -1)
		return(free_split(rgb_splt));
	if(get_int(rgb_splt[2], &color->b) == -1)
		return(free_split(rgb_splt));
	if(color->r > 255 || color->r < 0 || color->b > 255 ||
		color->b < 0 || color->g > 255 || color->g < 0 )
	{
		free_split(rgb_splt);
		return(error_return("Error\nRGB takes value in range [0-255]\n"));
	}
	free_split(rgb_splt);
	return(0);
}
int get_int(char *str, int* ret)
{
	int neg;

	neg = 1;
	*ret = 0;
	if(check_int(str) == -1)
		return(-1);
	if(*str == '-')
	{
		neg = -1;
		str++;
	}
	while(str && *str)
	{
		*ret = *ret * 10 + (*str - '0');
		str++;
	}
	*ret = *ret * neg;
	return(0);
}

int get_vec(char *xyz, t_vec3 *vector)
{
	char **xyz_splt;

	xyz_splt = ft_split(xyz,',');
	if(!xyz_splt)
		return(perror_return());
	if(arr_size(xyz_splt) != 3)
	{
		free_split(xyz_splt);
		return(error_return("Error\nWrong xyz arguments for the point\n"));
	}
	if(get_float(xyz_splt[0], &vector->x) == -1)
		return(free_split(xyz_splt));	
	if(get_float(xyz_splt[1], &vector->y) == -1)
		return(free_split(xyz_splt));
	if (get_float(xyz_splt[2], &vector->z) == -1)
		return(free_split(xyz_splt));	
	if(check_vec(*vector) == -1)
		return(free_split(xyz_splt));
	free_split(xyz_splt);	
	return(0);
}
int check_vec(t_vec3 vector)
{
	if(vector.x > 1.0 || vector.y > 1.0 || vector.z > 1.0)
		return (error_return("Error\nVector has to be in range[-1,1]\n"));
	if(vector.x < -1.0 || vector.y < -1.0 || vector.z < -1.0)
		return (error_return("Error\nVector has to be in range[-1,1]\n"));
	//if(vec_length(vector) != 1.0)
	//	return (error_return("Error\nVector has to be normalized\n"));
	return(0);
}

int check_int(char *str)
{
	int i;

	i = 0;
	while (str && *str)
	{
		if (!ft_isdigit(*str))
			return (error_return("Error\nRGB can take values in range 0-255(no comma)\n"));
		str++;
		i++;
		if (i > 5)
			return (error_return("Error\nInteger value is too big\n"));
	}
	return (0);	
}

int check_float(char *str)
{
	int com;

	int i;
	i = 0;
	com = 0;
	if(str && *str == '-')
		str++;
	while(str && *str)
	{
		if(*str == '.')
		{
			com++;
			str++;
			continue;
		}
		if(!ft_isdigit(*str))
			return(error_return("Error\nArgument should consists of digits only\n"));
		str++;
		i++;
	}
	if (com != 1 && com != 0)
		return(error_return("Error\nMore than one dot in single parameter\n"));
	if (i > 10 || i == 0)
		return(error_return("Error\nToo big number for the float be significant\n"));
	return (0);	
}

float ft_atof(char *str)
{
    float ret = 0.0;
    float decimal_part = 0.0;
	int i = 0;
	float divisor;

	if(str && str[i] == '-')
		i++;
    while (str[i] && str[i] != '.')
    {
        ret = ret * 10 + (str[i] - '0');
        i++;
    }
    if (str[i] == '.')
    {
        i++;
        divisor = 10.0;
        while (str[i])
        {
            decimal_part += (str[i] - '0') / divisor;
            divisor *= 10;
            i++;
        }
    }
    return (ret + decimal_part);
}

int arr_size(char **arr)
{
	int i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}