/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:17:34 by fjalowie          #+#    #+#             */
/*   Updated: 2024/03/06 13:35:13 by fjalowie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*p;
	size_t	i;

	p = (char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = '\0';
		i++;
	}
}

/* #include <stdio.h>
#include <string.h>

int main()
{
	char str[] = "abcdef";
	char str2[] = "abcdef";
	int i = 0;

	bzero(str, 7);
	ft_bzero(str2, 7);

	while (i < sizeof(str))
	{
		printf(" %d", str[i]);
		i++;
	}
	printf("\n");
	i = 0;
	while (i < sizeof(str))
	{
		printf(" %d", str2[i]);
		i++;
	}
} */
