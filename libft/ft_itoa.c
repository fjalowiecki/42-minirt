/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:27:27 by fjalowie          #+#    #+#             */
/*   Updated: 2024/03/09 19:41:24 by fjalowie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_num_digits(int n)
{
	int			num_digits;
	long int	temp;

	num_digits = 0;
	temp = (long int)n;
	if (n == 0)
		num_digits = 1;
	else
	{
		while (temp != 0)
		{
			num_digits++;
			temp /= 10;
		}
	}
	return (num_digits);
}

static int	is_negative(int n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}

static void	convert_n(int n, char *str)
{
	int	i;
	int	num_digits;
	int	n_cp;

	n_cp = n;
	num_digits = get_num_digits(n);
	i = num_digits - 1 + is_negative(n);
	if (is_negative(n))
	{
		str[0] = '-';
		n_cp = -n;
	}
	while (i >= is_negative(n))
	{
		str[i] = '0' + (n_cp % 10);
		n_cp /= 10;
		i--;
	}
	str[num_digits + is_negative(n)] = '\0';
}

char	*ft_itoa(int n)
{
	char	*str;
	int		num_digits;

	num_digits = get_num_digits(n);
	str = (char *)malloc((num_digits + is_negative(n) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (n == -2147483648)
	{
		ft_strlcpy(str, "-2147483648", 12);
		return (str);
	}
	convert_n(n, str);
	return (str);
}

/* int main ()
{
	int n = INT_MIN;
	printf("out: %s\n", ft_itoa(n));
	int m = -33;
	printf("out: %s\n", ft_itoa(m));
}
 */
