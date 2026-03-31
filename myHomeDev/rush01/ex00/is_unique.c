/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_unique.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazonode <kazonode@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 19:05:17 by kazonode          #+#    #+#             */
/*   Updated: 2026/03/29 17:54:41 by kazonode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern int	*g_grid;
extern int	*g_hints;
extern int	g_size;

int	is_unique(int pos, int num)
{
	int	row;
	int	col;
	int	i;

	row = pos / g_size;
	col = pos % g_size;
	i = 0;
	while (i < g_size)
	{
		if (g_grid[row * g_size + i] == num)
			return (0);
		if (g_grid[i * g_size + col] == num)
			return (0);
		i++;
	}
	return (1);
}
