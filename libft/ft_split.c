/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:35:42 by fjalowie          #+#    #+#             */
/*   Updated: 2024/03/13 14:41:58 by fjalowie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_words_count(char const *s, char c)
{
	int	num_words;
	int	i;

	num_words = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			num_words++;
		i++;
	}
	return (num_words);
}

static void	split_words(char **result, char const *s, char c, int i)
{
	int	start;
	int	j;
	int	k;

	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			result[j] = malloc((i - start + 1) * sizeof(char));
			if (!result[j])
				return ;
			k = 0;
			while (start < i)
				result[j][k++] = s[start++];
			result[j++][k] = '\0';
		}
		else
			i++;
	}
}

char	**ft_split(char const *s, char c)
{
	int		num_words;
	char	**result;
	int		i;

	i = 0;
	num_words = num_words_count(s, c);
	result = (char **)malloc((num_words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	split_words(result, s, c, i);
	result[num_words] = NULL;
	return (result);
}

/* #include <stdio.h>

int main ()
{
	int i = 0;
	char c = ',';
	char str[] = "ab,cd,efgh,ijk";
	char **out = ft_split(str, c);
	while (out[i] != NULL)
	{
		printf("%s\n", out[i]);
		i++;
	}
} */
