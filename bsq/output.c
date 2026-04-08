/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 20:46:08 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/08 21:01:26 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

void	mark_square(t_map *map, int size, int mr, int mc)
{
	int	r;
	int	c;

	r = mr - size + 1;
	while (r <= mr)
	{
		c = mc - size + 1;
		while (c <= mc)
		{
			map->grid[r][c] = map->full;
			c++;
		}
		r++;
	}
}

void	print_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->rows)
	{
		write(1, map->grid[i], map->cols);
		write(1, "\n", 1);
		i++;
	}
}
