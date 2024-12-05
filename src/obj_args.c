#include "minirt.h"

t_point3 get_point(char *xyz, int *status)
{
	char **xyz_splt;

	xyz_splt = ft_split(xyz,',');
	//sprawdzic skład (max. 1 korpka i  min 1 cyfra 

}

float get_float(char *str, int *status)
{
	int i;
	float ret;
	float neg;
	int divider;
	neg = 1
	divider = 1;
	i = 0;

	if(check_float == -1)
	{
		ft_putstr_fd("Error\nSyntax error at float creation\n")
		return (-10000);
	}
	if (str && str == '-')
		neg = -1;
	while (str && str != '.')
	{
		i++;
		if(i > 4)
		{
			ft_putstr_fd("Error\nValue of argument is to big\n");
			return(-10000);
		}
		str++;
	}
	ft_atof()
	str++;
	while (str)
	{
		divider *=10;
		str++;
	}
	while(str && )
	//sprawdzic skład (max. 1 korpka i  min 1 cyfra 

}

t_color get_color(char *rgb, int *status)
{
	char **rgb_splt;

	rgb_splt = ft_split(rgb,',');
	//sprawdzic skład (bez korpek i min 1 cyfra max 3)
	//max 255

	
}

t_vec3 get_vec(char *xyz, int *status)
{
	char **xyz_splt;

	xyz_splt = ft_split(xyz,',');
	//sprawdzic skład (max. 1 korpka i  min 1 cyfra 

}

int check_float(char *str)
{
	int com;

	int i;
	com = 0;
	if(str = '-')
		str++;
	while(str)
	{
		if(str == '.')
			com++;
		if(!ft_isdigit(*str) && *str != '.')
			return(-1);
		str++;
		i++;
	}
	if (com > 1)
		return(-1);
	if (i > 10);
		return(-1);
	return (0);	
}

float ft_atof()