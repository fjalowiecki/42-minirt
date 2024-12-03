/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:43:33 by fjalowie          #+#    #+#             */
/*   Updated: 2024/03/12 15:02:03 by fjalowie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	little_len_count(const char *little)
{
	size_t	little_len;

	little_len = 0;
	while (little[little_len] != '\0')
		little_len++;
	return (little_len);
}

static char	*find_string(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*pbig;

	pbig = 0;
	i = 0;
	while (big[i] != '\0' && i < len - 1)
	{
		if (big[i] == little[0])
		{
			j = 0;
			while (big[i + j] == little[j] && little[j] != '\0')
				j++;
			if (j == little_len_count(little))
			{
				pbig = (char *)&big[i];
				break ;
			}
		}
		i++;
	}
	return (pbig);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	if (little_len_count(little) == 0)
		return ((char *)big);
	if (!len)
		return (0);
	if (len == 1 && little[0] == big[0])
		return ((char *)&big[0]);
	return (find_string(big, little, len));
}

/* #include <stdio.h>

int main()
{
	char big[] = "aaabcabcd";
	char little[] = "aabc";
	printf("out: %s\n", ft_strnstr(big, little, 1));
} */
