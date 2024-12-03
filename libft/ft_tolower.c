/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:49:23 by fjalowie          #+#    #+#             */
/*   Updated: 2024/03/06 12:59:04 by fjalowie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	else
		return (c);
}

/* #include <stdio.h>
#include <ctype.h>

int main()
{
	char lt = '5';
	printf("og: %c\n", tolower(lt));
	printf("my: %c\n", ft_tolower(lt));
} */
