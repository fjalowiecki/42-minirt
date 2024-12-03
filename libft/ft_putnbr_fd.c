/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:34:59 by fjalowie          #+#    #+#             */
/*   Updated: 2024/03/05 14:35:14 by fjalowie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	*c;

	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	c = ft_itoa(n);
	if (!c)
		return ;
	write(fd, c, ft_strlen(c));
	free(c);
}

/* int main()
{
	ft_putnbr_fd(-2147483647, 1);
	write(1, "\n", 1);
} */
