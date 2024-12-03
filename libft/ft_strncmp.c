/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:43:18 by fjalowie          #+#    #+#             */
/*   Updated: 2024/03/06 13:13:45 by fjalowie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0' && i < n - 1)
	{
		i++;
	}
	if (s1[i] == s2[i])
		return (0);
	else
		return (s1[i] - s2[i]);
}

/* #include <stdio.h>
#include <string.h>

int main()
{
	char s1[1];
	char s2[] = "";
	size_t n = 3;

	printf("fts: %d\n", ft_strncmp(s1, s2, n));
	printf("str: %d\n", strncmp(s1, s2, n));
} */
