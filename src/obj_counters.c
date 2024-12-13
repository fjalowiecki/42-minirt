#include "minirt.h"

//1-A 2-C 3-L 4-sp 5-pl 6-cy 7-co
int sum_one_type(int type, t_data *data, int *obj_types)
{
	size_t i;
	int 	counter;

	counter = 0;
	i = 0;
	while(i < data->objects_cnt)
	{
		if (obj_types[i] == type)
			counter++;		
		i++;
	}
	return(counter);
}
