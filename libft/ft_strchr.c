/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:36:46 by fjalowie          #+#    #+#             */
/*   Updated: 2024/03/12 15:00:18 by fjalowie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	const char	*p;
	int			i;

	p = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			p = &s[i];
			break ;
		}
		i++;
	}
	if (c == '\0')
		p = &s[i];
	return ((char *)p);
}

/* #include <stdio.h>
#include <string.h>

int main()
{
	char str[] = "ltripouiel";
	char f = 'l';
	printf("og: %s\n", strchr(str, f));
	printf("my: %s\n", ft_strchr(str, f));
} */
