#include "minirt.h"

int	sum_one_type(int type, t_data *data, int *obj_types)
{
	size_t	i;
	int		counter;

	counter = 0;
	i = 0;
	while (i < data->objects_cnt)
	{
		if (obj_types[i] == type)
			counter++;
		i++;
	}
	return (counter);
}

int	arr_size(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

int	check_amount_args(char **obj_args, int i)
{
	int	j;

	j = 0;
	while (obj_args[j])
		j++;
	if (j != i)
	{
		printf(WRG_AMOUNT, obj_args[0]);
		return (-1);
	}
	return (0);
}
