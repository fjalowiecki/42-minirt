/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:37:14 by fjalowie          #+#    #+#             */
/*   Updated: 2024/03/13 12:53:12 by fjalowie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*s2;
	int		s_len;
	int		i;

	s_len = 0;
	while (s[s_len] != '\0')
		s_len++;
	s2 = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!s2)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		s2[i] = s[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

/* #include <stdio.h>
#include <string.h>

int main()
{
	char str[] = "abc";
	char *str2;
	char *str3;

	str2 = ft_strdup(str);
	printf("my: %s\n", str2);
	str3 = strdup(str);
	printf("og: %s\n", str3);
} */
