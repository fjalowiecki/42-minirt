#include "minirt.h"

void	free_resources(t_data *data)
{
	if (data->diff_lights)
		free(data->diff_lights);
	if (data->objects)
		free_alocated_obj(data, data->objects_cnt);
	if (data->amb_light)
		free(data->amb_light);
	if (data->view)
		free(data->view);
}

void	free_alocated_obj(t_data *data, int i)
{
	int counter;

	counter = 0;
	while(counter < i)
	{
		free(data->objects[counter].object);
		counter++;
	}
	free(data->objects);
	data->objects = NULL;
}