/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:18:03 by fjalowie          #+#    #+#             */
/*   Updated: 2024/03/08 14:02:26 by fjalowie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	char	*byte_ptr;
	size_t	i;

	ptr = 0;
	if (!nmemb || !size)
	{
		nmemb = 1;
		size = 1;
	}
	if (nmemb > 2147483647 / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	byte_ptr = (char *)ptr;
	i = 0;
	while (i < nmemb * size)
	{
		byte_ptr[i] = 0;
		i++;
	}
	return (ptr);
}
