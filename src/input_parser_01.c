#include "minirt.h"

int	check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isalpha(line[i]))
		i++;
	while (line[i])
	{
		if (ft_isalpha(line[i]))
			return (error_return(ARG_DIG)); 
		i++;
	}
	return (0);
}

void	check_chars(char **input, int *nr_of_obj)
{
	int	i;
	int	j;

	j = -1;
	while (input[++j])
	{
		i = 0;
		if (input[j][i] && !ft_isalpha(input[j][i]))
		{
			free_split(input);
			error_exit(CHAR_OK);
		}
		while (input[j][i])
		{
			if (!ft_isalnum(input[j][i]) && !ft_strchr("., -", input[j][i]))
			{
				free_split(input);
				error_exit(CHAR_OK);
			}
			i++;
		}
		(*nr_of_obj)++;
	}
}

void	check_file(int argc, char **argv)
{
	int	n;

	if (argc != 2)
		error_exit(WRG_ARGC);
	n = ft_strlen(argv[1]);
	if (n < 4)
		error_exit(WRG_FILE);
	if (ft_strncmp(&argv[1][n - 3], ".rt", 4) == 0 && argv[1][n - 4] == '/')
		error_exit(WRG_FILE);
	if (ft_strncmp(&argv[1][n - 3], ".rt", 4) != 0)
		error_exit(WRG_FILE_EXT);
}

void	null_obj(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->objects_cnt)
	{
		data->objects[i].object = NULL;
		i++;
	}
}

int	define_obj_types(char **input, int *obj_types)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_strncmp(input[i], "A ", 2))
			obj_types[i] = AMB_LIGHT;
		else if (!ft_strncmp(input[i], "C ", 2))
			obj_types[i] = CAMERA;
		else if (!ft_strncmp(input[i], "L ", 2))
			obj_types[i] = DIF_LIGHT;
		else if (!ft_strncmp(input[i], "sp ", 3))
			obj_types[i] = SPHERE;
		else if (!ft_strncmp(input[i], "pl ", 3))
			obj_types[i] = PLANE;
		else if (!ft_strncmp(input[i], "cy ", 3))
			obj_types[i] = CYLINDER;
		else if (!ft_strncmp(input[i], "co ", 3))
			obj_types[i] = CONE;
		else
			return (-1);
		i++;
	}
	return (0);
}
