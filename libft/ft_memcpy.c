/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:28:57 by fjalowie          #+#    #+#             */
/*   Updated: 2024/03/06 13:35:47 by fjalowie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const char	*s;
	char		*d;
	size_t		i;

	s = (const char *)src;
	d = (char *)dest;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}

/* #include <stdio.h>
#include <string.h>

int main()
{
	char dest[15] = "abcd";
	char src[] = "efgh";
	char dest2[15] = "abcd";

	memcpy(dest, src, 2);
	ft_memcpy(dest2, src, 2);

	printf("%s\n", dest);
	printf("%s\n", dest2);
} */
