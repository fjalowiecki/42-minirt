#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <stdio.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdbool.h>
//# include <float.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "vec_utils.h"
# include "../mlx/mlx.h"
# include <fcntl.h>

# define IMAGE_HEIGHT 768.0
# define IMAGE_WIDTH 1024.0
# define WINDOW_TITLE "miniRT"
# define T_MAX 10000

#ifndef M_PI
# define M_PI (3.14159265358979323846)
#endif

# define MLX_ERR "Error\nMinilibx failed\n"
# define MALL_ERR "Error\nMalloc failed\n"
# define IMG_ERR "Error\nGeting adr of img didnt't work\n"
# define CHAR_OK "Error\nProgram accepts only alphanumerics and (., -\\n)\n"
# define ARG_DIG "Error\nOnly digits and minus sign as parameter\n"
# define FLT_ERR "Error\ndouble argument is invalid\n"
# define TOO_BIG "Error\nValue is too big\n"
# define DIG_ONLY_F "Error\ndouble arg includes sign diffrent than digit\n"
# define FLT_SIG "Error\nToo \"big\" number for the double\n"
# define DOT_ONE "Error\nMore than one dot in single parameter\n"
# define NO_DOT "Error\nRGB, FOV are positive integers value\n"
# define N_VEC "Error\nVector has to be normalized\n"
# define RANGE_VEC "Error\nVector has to be in range [-1,1]\n"
# define SPOT_AMB "Error\nProgram needs one amb_light(A)\n" 
# define SPOT_CAMER "Error\nProgram need one camera(C)\n"
# define OBJ_ID "Error\nWrong object's id\n"
# define NO_OBJ "Error\nNo objects in the file\n"
# define WRG_ARGC "Error\nProgram accepts map.rt as an input\n"
# define WRG_FILE "Error\nWrong argument as an input file\n"
# define WRG_FILE_EXT "Error\nWrong file extension\n"
# define RANGE_BRIGHT "Error\nBrightness has to be in range [0.0-1.0]\n"
# define RANGE_FOV "Error\nFOV has to be in range [0-180]\n"
# define WRG_XYZ "Error\nWrong parameters for the point\n"
# define WRG_RGB "Error\nWrong parameters for the rgb color\n"
# define WRG_VEC "Error\nWrong parameters for the vector\n"
# define RANGE_RGB "Error\nRGB has to be in range [0-255]\n"
# define WRG_AMOUNT "Error\nWrong amount of arguments for %s\n"

/*KEYCODES*/

# define ESC 65307
# define TOP 1
# define SIDE 2
# define BOTTOM 3

# define CAMERA		6
# define DIF_LIGHT	7
# define AMB_LIGHT	8
# define SPHERE		0
# define PLANE		1
# define CONE		3
# define CYLINDER	2

typedef struct t_window
{
	void	*mlx_ptr;
	void	*win_ptr;
} t_window;

typedef struct 
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_img;

typedef struct 
{
	int r;
	int g;
	int b;
} t_color;


typedef struct
{
	double	a_coeff;
	double	b_coeff;
	double	c_coeff;
	double	t_side;
	double	t_bott;
	double	t_top;
	double	discrmnt;
	double	t[2];
} t_calc_cy;

typedef struct 
{
//todo: here go camera parameters from file. To add orientation vector and FOV in degrees
	t_point3 camera_center;
	t_vec3 focal_length;
	double image_width;
	double image_height;
	double viewport_height;
	double viewport_width;
	double fov_degrees;
} t_view;

typedef struct 
{
//todo: here go light parameters from file
	t_point3 origin;
	double brightness;
	t_color color;
} t_light;

typedef struct 
{
	int type;
	void *object;
} t_object;

typedef struct s_sphere 
{
	t_point3 center;
	double radius;
	t_color color;
} t_sphere;

typedef struct
{
	t_vec3 N;
	t_point3 center;
	t_color color;
} t_plane;

typedef struct
{
	t_point3 center;
	t_vec3 N_axis;
	double diameter;
	double h;
	t_color color;
	int inter_type;
	double r;
} t_cylinder;

typedef struct s_cone
{
	t_point3 vertex;
	t_color color;
	t_vec3 axis;
	double angle;//w radianach
	double height;
	int inter_type;
} t_cone;

typedef struct 
{
	t_view *view;
	t_light *amb_light;
	t_light *diff_lights;
	size_t diff_lights_cnt;
	t_object *objects;
	size_t objects_cnt;
	t_window window;
	t_img	 img;
} t_data;

typedef struct
{
	t_ray ray;
	double closest_t;
	int obj_index;
	t_vec3 normal;
	t_vec3 pixel_delta_u;
	t_vec3 pixel_delta_v;
	t_vec3 pixel00_loc;
	double *angles_diff;
	double *angles_spec;
} t_pixel_data;

typedef double	(*t_light_calc_fn)(t_pixel_data*, t_view*, t_light*, void*);

/*FUNCTIONS*/

/* image_creation - main, ray_params, pixel_color */
void	create_image(t_img *img, t_data *data);
void	calc_ray_params_for_pixel(t_data *data,
	t_pixel_data *pixel_data, int x, int y);
void	calc_closest_t_for_ray(t_data *data,
	t_pixel_data *pixel_data);
unsigned int	calc_color_for_pixel(t_data *data, t_pixel_data *pixel_data);
double	calc_spec(double angle, int color);

/* hit_cylinder.c */
double hit_cylinder(t_ray *ray, void *obj);
double calc_light_angle_cylinder(t_pixel_data *pixel_data, t_view *view, t_light *light, t_cylinder *cyl);

/* hit_plane.c */
double hit_plane(t_ray *ray, void *obj);
double calc_light_angle_plane(t_pixel_data *pixel_data, t_view *view, t_light *light, t_plane *plane);

/* hit_sphere.c */
double hit_sphere(t_ray *ray, void *obj);
double calc_light_angle_sphere(t_pixel_data *pixel_data, t_view *view, t_light *light, t_sphere *sph);

/*hit_cone.c*/
double hit_cone(t_ray *ray, void *obj);
double calc_light_angle_cone(t_pixel_data *pixel_data, t_view *view, t_light *light, t_cone *cone);
double	check_base_intersection(t_ray *ray, t_cone *cone);
double	check_side_intersection(t_ray *ray, t_cone *cone, double *abc,
	double discriminant);

/*free_resources.c*/
void free_resources(t_data *data);
void free_alocated_obj(t_data *data, int i);

/* mlx_utils.c */
int	close_esc(int keycode, t_data *data);
int	on_destroy(t_data *data);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
unsigned int rgb_to_hex(int r, int g, int b);

/*obj_args.c*/


/* shaded_pixel.c */
bool	shaded_pixel(t_point3 intersection, t_point3 light, t_data *data);

/* error_msg.c */
int perror_return(void);
void perror_exit(void);
int error_return(char *str);
void error_exit(char *str);


void input_parser(int argc, char **argv, t_data *data);
int open_file(char *file);
int get_file_content(int fd, t_data *data);

void get_args(char ** input, t_data *data);

int define_obj_types(char **input, int *obj_types);

void get_objects(char **input, t_data *data, int *obj_types);

int allocate_obj(t_data *data, int *obj_types);

int set_obj(char *line, t_data *data, int type);

int check_line(char *line);


void check_chars(char **input, int *nr_of_obj);

void check_file(int argc, char **argv);

int set_sphere (int i, char **obj_args, t_data *data);
int set_plane (int i, char **obj_args, t_data *data);
int set_cylinder (int i, char **obj_args, t_data *data);
int set_cone (int i, char **obj_args, t_data *data);
int set_amb_light(char **obj_args, t_data *data);
int set_camera(char **obj_args, t_data *data);
int set_light(char **obj_args, t_data *data);
int set_figures(int type, char **obj_args, t_data *data);
int check_amount_args(char **obj_args, int i);
int sum_one_type(int type, t_data *data, int *obj_types);

int get_fov(char *str, double *ret);
int get_point(char *xyz, t_point3 *point);

int get_double(char *str, double *ret);
int get_color(char *rgb, t_color *color);
int get_int(char *str, int* ret);
int get_vec(char *xyz, t_vec3 *vector);
int check_vec(t_vec3 vector);
int check_int(char *str);
int check_double(char *str);
double ft_atof(char *str);
int arr_size(char **arr);
void printf_split(char **str);
int get_brightness(char *str, double *ret);


/*helpers.c*/

void	printf_all(t_data *data);
void	printf_objects(t_object *objects, size_t objects_cnt);
void	printf_lights(t_light *amb_light, t_light *diff_lights, size_t diff_lights_cnt);
void	printf_view(t_view *view);
void	printf_cylinder(t_cylinder *cylinder);
void	printf_cone(t_cone *cone);
void	printf_plane(t_plane *plane);
void	printf_sphere(t_sphere *sphere);
void	printf_vec3(t_vec3 vec);
void	printf_point3(t_point3 point);
void	printf_color(t_color color);
int		free_split(char **str);
void	null_obj(t_data *data);
void	free_window(t_window *window, t_img *img);
void free_all(t_data *data);
double	closest_cyl_t(double t_side, double t_bott, double t_top, t_cylinder *cylinder);
t_vec3	cylinder_normal(t_point3 intersect_to_center, t_cylinder *cyl);

#endif