#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <stdio.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdbool.h>
# include <float.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "vec_utils.h"
# include "../mlx/mlx.h"

# define IMAGE_HEIGHT 768.0
# define IMAGE_WIDTH 1024.0
# define WINDOW_TITLE "miniRT"
# define T_MAX 10000

#ifndef M_PI
# define M_PI (3.14159265358979323846)
#endif

# define MLX_ERR "Error\nMinilibx failed\n"
# define MALL_ERR "Error\nMalloc failed\n"

/*KEYCODES*/

# define ESC 65307
# define TOP 1
# define SIDE 2
# define BOTTOM 3

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
//todo: here go camera parameters from file. To add orientation vector and FOV in degrees
	t_point3 camera_center;
	t_point3 focal_length;
	float image_width;
	float image_height;
	float viewport_height;
	float viewport_width;
	float fov_degrees;
} t_view;

typedef struct 
{
//todo: here go light parameters from file
	t_point3 origin;
	float brightness;
	t_color color;
} t_light;

typedef struct s_sphere 
{
	t_point3 center;
	double radius;
	t_color color;
} t_sphere;

typedef struct
{
	t_point3 center;
	t_vec3 N_axis_vec;
	float diameter;
	float height;
	t_color color;
	int inter_type;
} t_cylinder;

typedef struct
{
	t_vec3 N;
	t_point3 center;
	t_color color;
} t_plane;

typedef struct 
{
	int type;
	void *object;
} t_object;

typedef struct s_cone
{
	t_point3 vertex;
	t_color color;
	t_vec3 axis;
	float angle;//w radianach
	float height;
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
} t_data;

typedef struct
{
	t_ray ray;
	float closest_t;
	int obj_index;
	t_vec3 pixel_delta_u;
	t_vec3 pixel_delta_v;
	t_vec3 pixel00_loc;
} t_pixel_data;

typedef float	(*t_light_calc_fn)(t_pixel_data*, t_view*, t_light*, void*);

/*FUNCTIONS*/

/* image_creation - main, ray_params, pixel_color */
void	create_image(t_img *img, t_data *data);
void	calc_ray_params_for_pixel(t_data *data,
	t_pixel_data *pixel_data, int x, int y);
void	calc_closest_t_for_ray(t_data *data,
	t_pixel_data *pixel_data);
unsigned int	calc_color_for_pixel(t_data *data, t_pixel_data *pixel_data);

/* hit_cylinder.c */
float hit_cylinder(t_ray *ray, void *obj);
float calc_light_angle_cylinder(t_pixel_data *pixel_data, t_view *view, t_light *light, t_cylinder *cyl);

/* hit_plane.c */
float hit_plane(t_ray *ray, void *obj);
float calc_light_angle_plane(t_pixel_data *pixel_data, t_view *view, t_light *light, t_plane *plane);

/* hit_sphere.c */
float hit_sphere(t_ray *ray, void *obj);
float calc_light_angle_sphere(t_pixel_data *pixel_data, t_view *view, t_light *light, t_sphere *sph);

/*hit_cone.c*/
float hit_cone(t_ray *ray, void *obj);
float calc_light_angle_cone(t_pixel_data *pixel_data, t_view *view, t_light *light, t_cone *cone);

/*free_resources.c*/
void free_resources(t_data *data);
void free_alocated_obj(t_data *data, int i);

/* mlx_utils.c */
int	close_esc(int keycode, t_window *window);
int	on_destroy(t_window *window);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
unsigned int rgb_to_hex(int r, int g, int b);

/*obj_args.c*/
t_color get_color(char *rgb, int *status);
float get_float(char *str, int *status);
t_point3 get_point(char *xyz, int *status);
t_vec3 get_vec(char *xyz, int *status);

/* shaded_pixel.c */
bool shaded_pixel(int object_index, t_point3 intersection, t_point3 light, t_data *data);

/* error_msg.c */
int perror_return(void);
void perror_exit(void);
int error_return(char *str);
void error_exit(char *str);

#endif