/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:45:14 by fjalowie          #+#    #+#             */
/*   Updated: 2024/03/08 12:33:34 by fjalowie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			i;
	int			s_len;
	const char	*p;

	p = 0;
	s_len = 0;
	while (s[s_len] != '\0')
		s_len++;
	i = 0;
	while (s_len - i > 0)
	{
		if (s[s_len - i - 1] == (char)c)
		{
			p = &s[s_len - i - 1];
			break ;
		}
		i++;
	}
	if (c == '\0')
		p = &s[s_len];
	return ((char *)p);
}

/* #include <string.h>
#include <stdio.h>

int main()
{
	char str[] = "ltripouiek";
	char f = 0;
	printf("og: %s\n", strrchr(str, f));
	printf("my: %s\n", ft_strrchr(str, f));
}*/
