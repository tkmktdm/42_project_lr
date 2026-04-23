/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hint_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazonode <kazonode@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 17:17:58 by kazonode          #+#    #+#             */
/*   Updated: 2026/03/29 17:54:48 by kazonode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern int	*g_grid;
extern int	*g_hints;
extern int	g_size;

int	validate_count(int count, int max, int len, int hint)
{
	if (count > hint)
		return (0);
	if (len == g_size && count != hint)
		return (0);
	if (len < g_size && max < g_size && count >= hint)
		return (0);
	if (count + (g_size - max) < hint)
		return (0);
	return (1);
}

int	check_partial(int start, int step, int len, int hint)
{
	int	count;
	int	max;
	int	i;

	if (hint == 0)
		return (1);
	count = 0;
	max = 0;
	i = 0;
	while (i < len)
	{
		if (g_grid[start + i * step] > max)
		{
			max = g_grid[start + i * step];
			count++;
		}
		i++;
	}
	return (validate_count(count, max, len, hint));
}

int	check_row_hints(int row, int col)
{
	int	n;
	int	result;

	n = g_size;
	result = check_partial(row * n, 1, col + 1, g_hints[2 * n + row]);
	if (result != 1)
		return (0);
	if (col == n - 1)
	{
		result = check_partial(row * n + n - 1, -1, n,
				g_hints[3 * n + row]);
		if (result != 1)
			return (0);
	}
	return (1);
}

int	check_col_hints(int row, int col)
{
	int	n;
	int	result;

	n = g_size;
	result = check_partial(col, n, row + 1, g_hints[col]);
	if (result != 1)
		return (0);
	if (row == n - 1)
	{
		result = check_partial((n - 1) * n + col, -n, n,
				g_hints[n + col]);
		if (result != 1)
			return (0);
	}
	return (1);
}

int	check_hints(int pos)
{
	int	row;
	int	col;

	row = pos / g_size;
	col = pos % g_size;
	if (check_row_hints(row, col) != 1)
		return (0);
	if (check_col_hints(row, col) != 1)
		return (0);
	return (1);
}
