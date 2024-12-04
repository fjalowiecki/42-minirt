/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:37:56 by fjalowie          #+#    #+#             */
/*   Updated: 2024/03/11 11:30:17 by fjalowie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		f(i, s + i);
		i++;
	}
}

/* #include <stdio.h>

void print_index_char(unsigned int index, char *c)
{
    printf("index: %u, char: %c\n", index, *c);
}

int main()
{
    char str[] = "Abcd";
    ft_striteri(str, &print_index_char);
} */
