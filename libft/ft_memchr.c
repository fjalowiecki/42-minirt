/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:27:58 by fjalowie          #+#    #+#             */
/*   Updated: 2024/03/07 16:01:08 by fjalowie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*p;
	char	*ptr_s;

	p = 0;
	i = 0;
	ptr_s = (char *)s;
	while (i < n)
	{
		if (ptr_s[i] == (char)c)
		{
			p = &ptr_s[i];
			break ;
		}
		i++;
	}
	return (p);
}

/* #include <stdio.h>
#include <string.h>

int main()
{
	int str[] = {0, 1, 2, 4, 5, 3, 2, 9};
	int f = 7;
	int s = sizeof(str);
	printf("og: %p\n", memchr(str, f, s));
	printf("my: %p\n", ft_memchr(str, f, s));
} */
