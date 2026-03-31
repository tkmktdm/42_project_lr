/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazonode <kazonode@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 16:57:11 by kazonode          #+#    #+#             */
/*   Updated: 2026/03/29 17:54:20 by kazonode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

extern int	*g_grid;
extern int	*g_hints;
extern int	g_size;

int	count_numbers(char *s)
{
	int	count;

	if (!*s || *s < '0' || *s > '9')
		return (-1);
	count = 1;
	s++;
	while (*s)
	{
		if (*s != ' ')
			return (-1);
		s++;
		if (*s < '0' || *s > '9')
			return (-1);
		count++;
		s++;
	}
	return (count);
}

int	*parse_hints(char *s, int *count)
{
	int	*hints;
	int	i;

	*count = count_numbers(s);
	if (*count < 0)
		return (NULL);
	hints = malloc(sizeof(int) * (*count));
	if (!hints)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s >= '0' && *s <= '9')
		{
			hints[i] = *s - '0';
			i++;
		}
		s++;
	}
	return (hints);
}

int	validate_input(int count)
{
	int	size;

	if (count % 4 != 0)
		return (0);
	size = count / 4;
	if (size < 2 || size > 9)
		return (0);
	return (size);
}

int	validate_hints(void)
{
	int	i;

	i = 0;
	while (i < g_size * 4)
	{
		if (g_hints[i] < 1 || g_hints[i] > g_size)
			return (0);
		i++;
	}
	return (1);
}
