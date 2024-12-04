/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:38:04 by fjalowie          #+#    #+#             */
/*   Updated: 2024/03/08 14:25:19 by fjalowie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s_join;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	s_join = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s_join)
		return (NULL);
	ft_strlcpy(s_join, s1, ft_strlen(s1) + 1);
	i = 0;
	while (i < ft_strlen(s2))
	{
		s_join[ft_strlen(s1) + i] = s2[i];
		i++;
	}
	s_join[ft_strlen(s1) + i] = '\0';
	return (s_join);
}

/*#include <stdio.h>

int main()
{
	char str1[] = "tripouille";
	char str2[] = "42";
	char *str3;

	str3 = ft_strjoin(str1, str2);
	printf("out: %s\n", str3);
} */
