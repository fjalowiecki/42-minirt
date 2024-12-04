/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:26:22 by fjalowie          #+#    #+#             */
/*   Updated: 2024/03/06 12:34:25 by fjalowie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if ((c >= ' ' && c <= '~'))
		return (16384);
	else
		return (0);
}

/* #include <stdio.h>
#include <ctype.h>

int main()
{
	printf("%d\n", isprint('!'));
	printf("%d\n", ft_isprint('!'));
} */
