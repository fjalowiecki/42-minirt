/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:32:02 by fjalowie          #+#    #+#             */
/*   Updated: 2024/03/06 13:34:31 by fjalowie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*csrc;
	char		*cdest;
	size_t		i;

	cdest = (char *)dest;
	csrc = (char *)src;
	i = 0;
	if (!cdest && !csrc)
		return (NULL);
	if (cdest > csrc)
		while (n-- > 0)
			cdest[n] = csrc[n];
	else
	{
		while (i < n)
		{
			cdest[i] = csrc[i];
			i++;
		}
	}
	return (dest);
}

/* #include <stdio.h>
#include <string.h>

int main()
{
	char dest[30] = "a shiny white sphere";
	char dest2[30] = "a shiny white sphere";
	char *p = dest + 8;
	char *p2 = dest2 + 8;
	char *src = dest + 2;

	memmove(p, src, 5);
	ft_memmove(p2, src, 5);

	printf("og: %s\n", dest);
	printf("my: %s\n", dest2);
}
 */
