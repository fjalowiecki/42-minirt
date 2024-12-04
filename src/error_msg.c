#include "minirt.h"

int perror_return(void)
{
	perror(NULL);
	return(-1);
}
void perror_exit(void)
{
	perror(NULL);
	exit(1);
}

int error_return(char *str)
{
	ft_putstr_fd(str, 2);
	return(1);
}
void error_exit(char *str)
{
	ft_putstr_fd(str,2);
	exit(1);
}