#include "minirt.h"

int	get_float(char *str, float *ret)
{
	int		i;
	float	neg;

	neg = 1.0;
	i = 0;
	if (check_float(str) == -1)
		return (error_return(FLT_ERR));
	if (str[i] && str[i] == '-')
	{
		neg = -1.0;
		i++;
	}
	while (str[i] && str[i] != '.')
	{
		i++;
		if ((i > 4 && str[0] == '-') || i > 5)
			return (error_return(TOO_BIG));
	}
	*ret = ft_atof(str) * neg;
	return (0);
}

int	check_float(char *str)
{
	int	com;
	int	i;

	i = 0;
	com = 0;
	if (str && *str == '-')
		str++;
	while (str && *str)
	{
		if (*str == '.')
		{
			com++;
			str++;
			continue ;
		}
		if (!ft_isdigit(*str))
			return (error_return(DIG_ONLY_F));
		str++;
		i++;
	}
	if (com != 1 && com != 0)
		return (error_return(DOT_ONE));
	if (i > 10 || i == 0)
		return (error_return(FLT_SIG));
	return (0);
}

float	ft_atof(char *str)
{
	float	ret;
	float	decimal_part;
	int		i;
	float	divisor;

	ret = 0.0;
	decimal_part = 0.0;
	i = 0;
	if (str && str[i] == '-')
		i++;
	while (str[i] && str[i] != '.')
	{
		ret = ret * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		i++;
	divisor = 10.0;
	while (str[i])
	{
		decimal_part += (str[i] - '0') / divisor;
		divisor *= 10;
		i++;
	}
	return (ret + decimal_part);
}
