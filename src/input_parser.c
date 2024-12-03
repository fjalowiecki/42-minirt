#include "minirt.h"
#include <fcntl.h>
/*
Each type of element can be separated by one or more line break(s).
◦ Each type of information from an element can be separated by one or more
space(s).
◦ Each type of element can be set in any order in the file.
◦ Elements which are defined by a capital letter can only be declared once in
the scene.
6
miniRT My first RayTracer with miniLibX
◦ Each element first’s information is the type identifier (composed by one or two
character(s)), followed by all specific information for each object in a strict
order such as:
extension .rt
*/

/* RULES FOR THE INPUT FILE*?
1. input file is rt. extension
2. characters avaliable are: space '.' ',' or alphanumeric
3. patern for one object  "ID arg arg arg arg"
4. each line with object has to start with its id
5. patern for variables : 
	- cordinates or anything that consist of couple of componenets has to
		be seperate just by single comma (1.9,2.0,2)
	- each variable has to be separated my space (pointx pointy)
	- each object has its own components and the order of insertion
6. patern for each object:
- Ambient lighting: "A(ID) 0.2(brightnes[0.0,1.0]) R,G,B(0-255)"
- Camera: "C(ID) x,y,z(view_point) " 
- Light:
- Sphere:
- Plane:
- Cylinder:
- Cone:
*/
//A C L sp pl cy co
//todo:each free input change to free_split
void	ft_file_checker(int argc, char **argv);
int 	get_file_content(int fd, t_data *data);
int 	open_file(char *file);

void input_parser(int argc, char *argv, t_data *data)
{
	int fd;

	data->objects = NULL;
	data->view = NULL;
	data->amb_light = NULL;
	data->diff_lights = NULL;
	ft_check_file(argc, argv);
	fd = open_file(argv);
	get_file_content(fd, data);
		

}

int open_file(char *file)
{
	int fd;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror(NULL);
		exit(1);
	}
	return(fd);
}

int get_file_content(int fd, t_data *data)
{
	char buf[4096];
	char **input;
	if (read(fd, buf, 4096) <= 0)
	{
		perror(NULL);
		exit(1);
	}
	input = ft_split(buf, '\n');
	if (!input)
		exit(1);
	get_args(input, data);


}

void get_args(char ** input, t_data *data)
{
	int *obj_types;
	data->objects_cnt = 0;
	check_chars(input, &(data->objects_cnt));
	if (data->objects_cnt == 0)
	{
		ft_putstr_fd("Error\nNo objects in the file\n",2);
		free(input);
		exit(1);
	}
	obj_types = malloc(sizeof(int) * data->objects_cnt);
	if (!obj_types)
	{
		perror(NULL);
		free(input);
		exit(1);
	}
	if (define_obj_types(input, obj_types) == -1)
	{
		ft_putstr_fd("Error\nWrong object's id\n",2);
		free(input);
		free(obj_types);
		exit(1);
	}
	get_objects(input, data, obj_types);
	
}
//1-A 2-C 3-L 4-sp 5-pl 6-cy 7-co
int define_obj_types(char **input, int *obj_types)
{
	int i;

	i = -1;
	while(input[++i])
	{
		if(!ft_strncmp(input[i], "A ", 2))
			obj_types[i] = 1;
		else if(!ft_strncmp(input[i], "C ", 2) )
			obj_types[i] = 2;
		else if(!ft_strncmp(input[i], "L ", 3) )
			obj_types[i] = 3;
		else if(!ft_strncmp(input[i], "sp ", 3) )
			obj_types[i] = 4;
		else if(!ft_strncmp(input[i], "pl ", 3) )
			obj_types[i] = 5;
		else if(!ft_strncmp(input[i], "cy ", 3) )
			obj_types[i] = 6;
		else if(!ft_strncmp(input[i], "co ", 3) )
			obj_types[i] = 7;
		else 
			return(-1);
	}
	return (0);
}
void get_objects(char **input, t_data *data, int *obj_types)
{
	int i;

	if (allocate_obj(data, obj_types) == -1)
	{
		free(input);
		free(obj_types);
		free_resources(data);
		exit(1);
	}
	i = -1;
	//checkpoint
	while(input[++i])
	{
		if (set_obj(input[i], data) == -1)
		{
			free(input);
			free(obj_types)
			free_obj_i(data->objects, i);//todo:now we need to free all already alocated
			exit(1);
		}
	}
}

int allocate_obj(t_data *data, int *obj_types)
{
	int lights;
	int amb_light;

	amb_light = sum_one_type(1, data, obj_types);
	if (amb_light != 0 && amb_light != 1)
		return(error_return("Error\nWrong amount of ambient light spots(0-1)\n"));
	if(sum_one_type(2, data, obj_types) != 1)
		return(error_return("Error\nWrong amount of camera spots(0-1)\n"));
	lights = sum_one_type(3, data, obj_types);
	data->objects_cnt = data->objects_cnt - 1 - amb_light - lights;
	if (data->objects_cnt != 0)
		data->objects = malloc(sizeof(t_object) * data->objects_cnt);
	if(!data->objects && data->objects_cnt != 0)
		perror_return();
	if(amb_light == 1)
		data->amb_light = malloc(sizeof(t_view) * 1);
	if(!data->amb_light && amb_light == 1)
		perror_return();
	if(lights != 0)
		data->amb_light = malloc(sizeof(t_light) * lights);
	if(!data->amb_light && lights != 0)
		perror_return();
	
}



int set_obj(char *line, t_data *data)
{
	int type;
	char **obj_args;

	type = define_obj_id(obj_args);
	if (type == -1)
	{
		ft_putstr_fd()
	}
}
void check_chars(char **input, int nr_of_obj)
{
	int i;
	int j;

	j = -1;
	while(input[++j])
	{
		i = 0;
		if(input[j][i] ||!ft_isalpha(input[j][i]))
		{
			free(input);
			ft_putstr_fd("Error\nProgram accepts alphanumeric arguments and \".\"\",\"\"\\n\"\"space\" \"\n", 2);
			exit(1);
		}
		while(input[j][i])
		{
	  		if (!ft_isalnum(input[j][i]) || !ft_strchr("., ",input[j][i]))
			{
				free(input);
				ft_putstr_fd("Error\nProgram accepts alphanumeric arguments and \".\"\",\"\"\\n\"\"space\" \"\n", 2);
				exit(1);
			}
			i++;
		}
		nr_of_obj++;
	}
}
void	ft_file_checker(int argc, char **argv)
{
	int	n;

	if(argc != 2)
	{
		ft_putstr_fd("Error\nProgram accepts only one argument which should be map.rt\n", 2);
		exit(1);
	}
	n = ft_strlen(argv[1]);
	if (n < 4)
	{
		ft_putstr_fd("Error\nWrong argument\n", 2);
		exit(1);
	}
	if (ft_strncmp(&argv[1][n - 3], ".rt", 4) == 0 && argv[1][n - 4] == '/')
	{
		ft_putstr_fd("Error\nWrong argument\n", 2);
		exit(1);
	}
	if (ft_strncmp(&argv[1][n - 3], ".rt", 4) != 0)
	{
		ft_putstr_fd("Error\nWrong file extension\n", 2);
		exit(1);
	}
}