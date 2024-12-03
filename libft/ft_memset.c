/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:34:13 by fjalowie          #+#    #+#             */
/*   Updated: 2024/03/06 13:36:02 by fjalowie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*p;
	size_t	i;

	p = (char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = c;
		i++;
	}
	return (p);
}

/* #include <stdio.h>
#include <string.h>

int main()
{
	char str[] = "abcdef";
	printf("%s\n", (char *)memset(str, 'A', 3));
	printf("%s\n", (char *)ft_memset(str, 'A', 3));
} */
