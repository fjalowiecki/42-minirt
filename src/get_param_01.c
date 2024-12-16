#include "minirt.h"

int	get_int(char *str, int *ret)
{
	int	neg;

	neg = 1;
	*ret = 0;
	if (check_int(str) == -1)
		return (-1);
	if (*str == '-')
	{
		neg = -1;
		str++;
	}
	while (str && *str)
	{
		*ret = *ret * 10 + (*str - '0');
		str++;
	}
	*ret = *ret * neg;
	return (0);
}

int	check_vec(t_vec3 vector)
{
	if (vector.x > 1.0 || vector.y > 1.0 || vector.z > 1.0)
		return (error_return(RANGE_VEC));
	if (vector.x < -1.0 || vector.y < -1.0 || vector.z < -1.0)
		return (0);
}

int	check_int(char *str)
{
	int	i;

	i = 0;
	while (str && *str)
	{
		if (!ft_isdigit(*str))
			return (error_return(NO_DOT));
		str++;
		i++;
		if (i > 5)
			return (error_return(TOO_BIG));
	}
	return (0);
}

int	open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		perror_exit();
	return (fd);
}
