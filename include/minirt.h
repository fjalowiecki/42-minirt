#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <stdio.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdbool.h>
# include "vec_utils.h"
# include "../mlx/mlx.h"

# define IMAGE_HEIGHT 768.0
# define IMAGE_WIDTH 1024.0
# define WINDOW_TITLE "miniRT"

/*KEYCODES*/

# define ESC 65307

typedef struct t_window
{
	void	*mlx_ptr;
	void	*win_ptr;
} t_window;

typedef struct {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_img;

typedef struct {
	int r;
	int g;
	int b;
} t_color;

typedef struct {
//todo: here go camera parameters from file. To add orientation vector and FOV in degrees
	t_point3 camera_center;
	t_point3 focal_length;
	float image_width;
	float image_height;
	float viewport_height;
	float viewport_width;
} t_view;

typedef struct {
//todo: here go light parameters from file
	t_point3 origin;
	float brightness;
} t_light;

typedef struct s_sphere {
	t_point3 center;
	double radius;
	t_color color;
} t_sphere;



typedef struct
{
	t_vec3 N;
	t_point3 center;
	t_color rgb_color;
} t_plane;

/*FUNCTIONS*/

int	close_esc(int keycode, t_window *window);
float hit_plane(t_ray ray, t_plane *plane);

#endif