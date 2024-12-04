/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:34:35 by fjalowie          #+#    #+#             */
/*   Updated: 2024/03/05 14:34:44 by fjalowie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	if (!c)
		return ;
	write(fd, &c, 1);
}

/* int main()
{
	ft_putchar_fd('a', 1);
	ft_putchar_fd('\n', 1);
} */
