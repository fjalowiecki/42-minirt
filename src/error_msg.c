#include "minirt.h"

static int ft_strlen(char *str)
{
	int str_len = 0;

	if (!str)
		return (0);
	while (str[str_len] != '\0')
		str_len++;
	return (str_len);
}

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
	return (1);
}
void error_exit(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}