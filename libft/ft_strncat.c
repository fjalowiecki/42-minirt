/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 21:50:49 by fjalowie          #+#    #+#             */
/*   Updated: 2024/07/28 21:50:50 by fjalowie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	char	*start;

	start = dest;
	while (*dest != '\0')
		dest++;
	while (*src != '\0' && n-- > 0)
		*dest++ = *src++;
	*dest = '\0';
	return (start);
}
