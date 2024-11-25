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

# define IMAGE_HEIGHT 1024
# define IMAGE_WIDTH 768
# define WINDOW_TITLE "miniRT"

typedef struct t_window
{
	void	*mlx_ptr;
	void	*win_ptr;
} t_window;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_data;

typedef struct s_sphere {
	t_point3 center;
	float radius;
} t_sphere;
#endif