/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:42:50 by fjalowie          #+#    #+#             */
/*   Updated: 2024/03/05 14:43:02 by fjalowie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ptr;
	int		i;

	if (!s || !f)
		return (NULL);
	ptr = (char *) malloc (sizeof(char) * (ft_strlen(s) + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		ptr[i] = f(i, s[i]);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

/* #include <stdio.h>

char f(unsigned int i, char c)
{
	return (c - ('a' - 'A'));
}

int main()
{
	char s[] = "abc";
	char *s2 = ft_strmapi(s, &f);
	printf("out: %s\n", s2);
}
 */
