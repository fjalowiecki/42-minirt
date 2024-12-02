#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <stdio.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdbool.h>
# include <float.h>
# include "vec_utils.h"
# include "../mlx/mlx.h"

# define IMAGE_HEIGHT 768.0
# define IMAGE_WIDTH 1024.0
# define WINDOW_TITLE "miniRT"

#ifndef M_PI
# define M_PI (3.14159265358979323846)
#endif

/*KEYCODES*/

# define ESC 65307

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

typedef struct 
{
	t_view *view;
	t_light *lights;
	size_t light_cnt;
	t_object *objects;
	size_t objects_cnt;
} t_data;

/*FUNCTIONS*/

/* hit_cylinder.c */
float hit_cylinder(t_ray *ray, t_cylinder *cylinder);
float calc_light_angle_cylinder(float t, t_ray ray, t_view *view, t_light *light, t_cylinder *cyl);

/* hit_plane.c */
float hit_plane(t_ray ray, t_plane *plane);
float calc_light_angle_plane(float t, t_vec3 ray_direction, t_view *view, t_light *light, t_plane *plane);

/* hit_sphere.c */
float hit_sphere(t_point3 center, float radius, t_ray r);
float calc_light_angle_sphere(float t, t_vec3 ray_direction, t_view *view, t_light *light, t_sphere *sph);

/* image_creation.c */
void create_image(t_img *img, t_data *data);

/* mlx_utils.c */
int	close_esc(int keycode, t_window *window);
int	on_destroy(t_window *window);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
unsigned int rgb_to_hex(int r, int g, int b);

#endif