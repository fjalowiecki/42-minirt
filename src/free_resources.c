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
		if(data->objects[counter].object)
			free(data->objects[counter].object);
		counter++;
	}
	free(data->objects);
	data->objects = NULL;
}

int	free_split(char **str)
{
	int i;

	i = 0;
	if (!str)
		return (-1);
	while(str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return(-1);
}
void	free_window(t_window *window, t_img *img)
{
	if (img->img)
	{
		mlx_destroy_image(window->mlx_ptr, img->img);
		img->img = NULL;
	}
	if (window->win_ptr)
	{
		mlx_destroy_window(window->mlx_ptr, window->win_ptr);
		window->win_ptr = NULL;
	}
	if (window->mlx_ptr)
	{
		mlx_destroy_display(window->mlx_ptr);
		free(window->mlx_ptr);
		window->mlx_ptr = NULL;
	}
}

void free_all(t_data *data)
{
	free_window(&data->window, &data->img);
	free_resources(data);
}