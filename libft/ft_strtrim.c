/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:45:46 by fjalowie          #+#    #+#             */
/*   Updated: 2024/09/24 09:02:01 by fjalowie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	calc_l_pos(char const *s1, char const *set)
{
	size_t		i;
	size_t		l_pos;

	l_pos = 0;
	i = 0;
	while (s1[i] != '\0')
	{
		if (ft_strchr(set, s1[i]))
			l_pos++;
		else
			break ;
		i++;
	}
	return (l_pos);
}

static size_t	calc_r_pos(char const *s1, char const *set)
{
	size_t		i;
	size_t		r_pos;

	r_pos = ft_strlen(s1) - 1;
	i = ft_strlen(s1) - 1;
	while (i != 0)
	{
		if (ft_strchr(set, s1[i]))
			r_pos--;
		else
			break ;
		i--;
	}
	return (r_pos);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*s_trim;
	size_t		s_trim_len;
	size_t		l_pos;
	size_t		r_pos;

	if (!s1 || !set)
		return (NULL);
	l_pos = calc_l_pos(s1, set);
	if (l_pos == ft_strlen(s1))
	{
		s_trim = (char *)malloc(sizeof(char));
		if (!s_trim)
			return (NULL);
		*s_trim = '\0';
		return (s_trim);
	}
	r_pos = calc_r_pos(s1, set);
	s_trim_len = r_pos - l_pos + 1;
	s_trim = (char *)malloc(sizeof(char) * (s_trim_len + 1));
	if (!s_trim)
		return (NULL);
	ft_strlcpy(s_trim, &s1[l_pos], s_trim_len + 1);
	return (s_trim);
}

/* #include <stdio.h>

int main()
{
	char set1[] = "@@";
	char str1[] = "@xxxtripouille@";
	printf("b: %s\n", ft_strtrim(str1, set1));
	char set2[] ="abc";
	char str2[] = "abcdefghggc";
	printf("r: %s\n", ft_strtrim(str2, set2));
	char set3[] ="abc";
	char str3[] = "defghabc";
	printf("l: %s\n", ft_strtrim(str3, set3));
	char *set4;
	char str4[] = "defghabc";
	printf("n: %s\n", ft_strtrim(str4, set4));
} */
