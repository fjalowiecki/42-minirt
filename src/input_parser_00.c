#include "minirt.h"
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
- Ambient lighting: 3"A(ID) 0.2(brightnes[0.0,1.0]) R,G,B(0-255)"
- Camera: 4"C(ID) x,y,z(view_point) xyz(3d_normalized_vec) FOV(0-180)" 
- Light: 4"ID xyz light RGB"
- Sphere: 4"ID xyz diameter RGB"
- Plane: 4"ID xyz normalizednormalvector(xyz)(1-1) RGB "
- Cylinder: 6"ID xyz 3d_normalized_vector_of_axis_of_cylinder(xyz (-1)-1)
 diameter height RGB"
- Cone: 6"ID xyz(vertex) xyz(axis_vector) angle(radians) height RGB"
*/
//A C L sp pl cy co
//todo:each free input change to free_split

void	input_parser(int argc, char **argv, t_data *data)
{
	int	fd;

	data->objects = NULL;
	data->view = NULL;
	data->amb_light = NULL;
	data->diff_lights = NULL;
	check_file(argc, argv);
	fd = open_file(argv[1]);
	get_file_content(fd, data);
}

int	get_file_content(int fd, t_data *data)
{
	char	buf[4096];
	char	**input;
	int		byt;

	byt = read(fd, buf, 4096);
	if (byt <= 0)
		perror_exit();
	buf[byt] = '\0';
	input = ft_split(buf, '\n');
	if (!input)
		perror_exit();
	get_args(input, data);
	free_split(input);
	return (0);
}

void	get_args(char **input, t_data *data)
{
	int	*obj_types;

	data->objects_cnt = 0;
	check_chars(input, (int *) & (data->objects_cnt));
	if (data->objects_cnt == 0)
	{
		free_split(input);
		error_exit(NO_OBJ);
	}
	obj_types = malloc(sizeof(int) * data->objects_cnt);
	if (!obj_types)
	{
		free_split(input);
		perror_exit();
	}
	if (define_obj_types(input, obj_types) == -1)
	{
		free_split(input);
		free(obj_types);
		error_exit(OBJ_ID);
	}
	get_objects(input, data, obj_types);
	free(obj_types);
}

void	get_objects(char **input, t_data *data, int *obj_types)
{
	int	i;

	if (allocate_obj(data, obj_types) == -1)
	{
		free_split(input);
		free(obj_types);
		free_resources(data);
		exit(1);
	}
	i = -1;
	while (input[++i])
	{
		if (set_obj(input[i], data, obj_types[i]) == -1)
		{
			free_split(input);
			free(obj_types);
			free_resources(data);
			exit(1);
		}
	}
}

int	allocate_obj(t_data *data, int *obj_types)
{
	int	lights;
	int	amb_light;

	amb_light = sum_one_type(AMB_LIGHT, data, obj_types);
	if (amb_light != 1)
		return (error_return(SPOT_AMB));
	if (sum_one_type(CAMERA, data, obj_types) != 1)
		return (error_return(SPOT_CAMER));
	lights = sum_one_type(DIF_LIGHT, data, obj_types);
	data->objects_cnt = data->objects_cnt - 1 - amb_light - lights;
	if (data->objects_cnt != 0)
		data->objects = malloc(sizeof(t_object) * data->objects_cnt);
	if (!data->objects && data->objects_cnt != 0)
		perror_return();
	if (amb_light == 1)
		data->amb_light = malloc(sizeof(t_light) * 1);
	if (!data->amb_light && amb_light == 1)
		perror_return();
	if (lights != 0)
		data->diff_lights = malloc(sizeof(t_light) * lights);
	if (!data->diff_lights && lights != 0)
		perror_return();
	data->diff_lights_cnt = lights;
	null_obj(data);
	return (0);
}
