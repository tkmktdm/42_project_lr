/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 17:41:54 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/26 18:08:49 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

size_t	*search_word(char const s, char const *word)
{
	size_t	i;

	i = 0;
	while (word[i])
		if (s == word[i])
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*p1;
	size_t	count;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!p1)
		return (NULL);
	while (s1[i])
	{
		if (!search_word(s1[i], set))
			count++;
		i++;
	}
	p1 = malloc(sizeof(char) * count + 1);
	while (s1[i])
	{
		if (!search_word(s1[i], set))
			count++;
		i++;
	}
	p1[i] = '\0';
	return (p1);
}

// hello
