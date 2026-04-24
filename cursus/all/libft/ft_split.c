/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokubo <kokubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 20:15:00 by kokubo            #+#    #+#             */
/*   Updated: 2026/04/23 01:00:00 by kokubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	word_count(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static size_t	word_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static void	free_all(char **arr, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static char	*next_word(char const *s, char c, size_t *ip)
{
	size_t	start;
	size_t	wl;

	while (s[*ip] == c)
		(*ip)++;
	start = *ip;
	wl = word_len(&s[start], c);
	*ip = start + wl;
	return (ft_substr(s, (unsigned int)start, wl));
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	wc;
	size_t	idx;
	size_t	i;

	if (!s)
		return (NULL);
	wc = word_count(s, c);
	arr = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!arr)
		return (NULL);
	idx = 0;
	i = 0;
	while (idx < wc)
	{
		arr[idx] = next_word(s, c, &i);
		if (!arr[idx])
		{
			free_all(arr, idx);
			return (NULL);
		}
		idx++;
	}
	arr[wc] = NULL;
	return (arr);
}
