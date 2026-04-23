/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hidden_single.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazonode <kazonode@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 17:26:11 by kazonode          #+#    #+#             */
/*   Updated: 2026/03/29 19:26:10 by kazonode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern int	*g_grid;
extern int	*g_hints;
extern int	g_size;

int	get_max_val(int row, int col);
int	try_hidden_col(int col);

int	line_has_val(int start, int step, int val)
{
	int	i;

	i = 0;
	while (i < g_size)
	{
		if (g_grid[start + i * step] == val)
			return (1);
		i++;
	}
	return (0);
}

int	count_row_cands(int row, int val, int *last)
{
	int	col;
	int	count;

	count = 0;
	*last = -1;
	col = 0;
	while (col < g_size)
	{
		if (g_grid[row * g_size + col] == 0
			&& !line_has_val(col, g_size, val)
			&& val <= get_max_val(row, col))
		{
			count++;
			*last = col;
		}
		col++;
	}
	return (count);
}

int	try_hidden_row(int row)
{
	int	val;
	int	last;

	val = 1;
	while (val <= g_size)
	{
		if (line_has_val(row * g_size, 1, val))
		{
			val++;
			continue ;
		}
		if (count_row_cands(row, val, &last) == 1)
		{
			g_grid[row * g_size + last] = val;
			return (1);
		}
		val++;
	}
	return (0);
}

int	try_hidden_singles(void)
{
	int	i;
	int	changed;

	changed = 0;
	i = 0;
	while (i < g_size)
	{
		if (try_hidden_row(i))
			changed = 1;
		if (try_hidden_col(i))
			changed = 1;
		i++;
	}
	return (changed);
}
