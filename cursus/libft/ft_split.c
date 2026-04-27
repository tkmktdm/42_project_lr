/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 00:00:00 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/27 00:00:00 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	count_words(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (count);
}

static char	*make_word(char const *s, char c, size_t *i)
{
	size_t	start;
	size_t	j;
	char	*word;

	while (s[*i] == c)
		(*i)++;
	start = *i;
	while (s[*i] && s[*i] != c)
		(*i)++;
	word = malloc(*i - start + 1);
	if (!word)
		return (NULL);
	j = 0;
	while (start + j < *i)
	{
		word[j] = s[start + j];
		j++;
	}
	word[j] = '\0';
	return (word);
}

static void	free_words(char **res, size_t n)
{
	while (n > 0)
		free(res[--n]);
	free(res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	n;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	n = count_words(s, c);
	res = malloc((n + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (j < n)
	{
		res[j] = make_word(s, c, &i);
		if (!res[j])
		{
			free_words(res, j);
			return (NULL);
		}
		j++;
	}
	res[j] = NULL;
	return (res);
}
