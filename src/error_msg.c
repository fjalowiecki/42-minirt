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
	write(2, str, ft_strlen(str));
	return(1);
}
void error_exit(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}