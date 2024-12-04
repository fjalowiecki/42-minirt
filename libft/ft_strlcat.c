/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:39:19 by fjalowie          #+#    #+#             */
/*   Updated: 2024/03/08 12:07:48 by fjalowie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_len(const char *str)
{
	size_t	str_len;

	str_len = 0;
	while (str[str_len] != '\0')
		str_len++;
	return (str_len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	if (!dst || !src)
		return (0);
	dst_len = count_len(dst);
	src_len = count_len(src);
	i = 0;
	if (size > dst_len)
	{
		while (src[i] != '\0' && i < size - dst_len - 1)
		{
			dst[dst_len + i] = src[i];
			i++;
		}
		dst[dst_len + i] = '\0';
		return (src_len + dst_len);
	}
	else
		return (size + src_len);
}

/* #include <stdio.h>
#include <string.h>

int main()
{
	//char dest[20] = "BBBB";
	char dest[20] = "CCCCC";
	char str[] = "AAAAAAAAA";
	printf("length: %lu\n", ft_strlcat(dest, str, -1));
	//ft_strlcat(dest, str, 20);
	printf("%s\n", dest);
}
 */