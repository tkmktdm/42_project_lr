/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 20:46:15 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/08 21:01:32 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

static int	count_lines(char *s)
{
	int		n;
	char	*p;

	n = 0;
	p = s;
	while (*p)
		if (*p++ == '\n')
			n++;
	if (p != s && p[-1] != '\n')
		n++;
	return (n);
}

static int	add_line(char **res, char *start, char *end, int *i)
{
	char	*dup;

	dup = ft_strdup_n(start, end - start);
	if (!dup)
		return (-1);
	res[(*i)++] = dup;
	return (0);
}

static int	fill_lines(char **res, char *s)
{
	int		i;
	char	*start;

	i = 0;
	start = s;
	while (*s)
	{
		if (*s == '\n')
		{
			if (add_line(res, start, s, &i) == -1)
				return (-1);
			start = s + 1;
		}
		s++;
	}
	if (*start && add_line(res, start, s, &i) == -1)
		return (-1);
	res[i] = NULL;
	return (0);
}

char	**split_content(char *s)
{
	char	**res;
	int		n;
	int		i;

	n = count_lines(s);
	if (n == 0)
		return (NULL);
	res = malloc(sizeof(char *) * (n + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i <= n)
		res[i++] = NULL;
	if (fill_lines(res, s) == -1)
		return (free_split(res), NULL);
	return (res);
}
