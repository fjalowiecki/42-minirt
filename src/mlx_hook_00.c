#include "minirt.h"

int	close_esc (int keycode, t_window *window)
{
	if (keycode == ESC)
	{
		printf("Leaving the program...\n");
		//todo: freeing memory
		exit(0);
	}
}
