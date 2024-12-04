/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:48:40 by fjalowie          #+#    #+#             */
/*   Updated: 2024/03/12 14:30:44 by fjalowie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	int		l;

	ptr = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) < start || !len)
	{
		ptr = malloc(sizeof(char));
		if (!ptr)
			return (NULL);
		*ptr = 0;
		return (ptr);
	}
	if (len <= ft_strlen(s) - start)
		l = len + 1;
	else
		l = ft_strlen(s) - start + 1;
	ptr = (char *)malloc(sizeof(char) * l);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s + start, l);
	return (ptr);
}

/* #include <stdio.h>

int main()
{
	char str[] = "abcdefghijk";
	char *str2 = ft_substr(str, 0, 20);
	printf("out: %s\n", str2);
	printf("size: %lu\n", sizeof(str));
	printf("size: %lu\n", sizeof(*str2));
} */
