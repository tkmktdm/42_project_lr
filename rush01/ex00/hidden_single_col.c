/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hidden_single_col.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazonode <kazonode@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 19:24:53 by kazonode          #+#    #+#             */
/*   Updated: 2026/03/29 19:37:47 by kazonode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern int	*g_grid;
extern int	*g_hints;
extern int	g_size;

int	line_has_val(int start, int step, int val);
int	get_max_val(int row, int col);

int	count_col_cands(int col, int val, int *last)
{
	int	row;
	int	count;

	count = 0;
	*last = -1;
	row = 0;
	while (row < g_size)
	{
		if (g_grid[row * g_size + col] == 0
			&& !line_has_val(row * g_size, 1, val)
			&& val <= get_max_val(row, col))
		{
			count++;
			*last = row;
		}
		row++;
	}
	return (count);
}

int	try_hidden_col(int col)
{
	int	val;
	int	last;

	val = 1;
	while (val <= g_size)
	{
		if (line_has_val(col, g_size, val))
		{
			val++;
			continue ;
		}
		if (count_col_cands(col, val, &last) == 1)
		{
			g_grid[last * g_size + col] = val;
			return (1);
		}
		val++;
	}
	return (0);
}
