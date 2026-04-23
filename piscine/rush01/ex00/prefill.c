/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazonode <kazonode@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 17:28:54 by kazonode          #+#    #+#             */
/*   Updated: 2026/03/29 17:54:23 by kazonode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern int	*g_grid;
extern int	*g_hints;
extern int	g_size;

void	propagate_singles(void);

int	set_cell(int pos, int val)
{
	int	row;
	int	col;
	int	i;

	if (g_grid[pos] != 0 && g_grid[pos] != val)
		return (0);
	if (g_grid[pos] == val)
		return (1);
	row = pos / g_size;
	col = pos % g_size;
	i = 0;
	while (i < g_size)
	{
		if (g_grid[row * g_size + i] == val)
			return (0);
		if (g_grid[i * g_size + col] == val)
			return (0);
		i++;
	}
	g_grid[pos] = val;
	return (1);
}

int	prefill_line(int start, int step, int hint)
{
	int	i;

	if (hint == 1)
	{
		if (!set_cell(start, g_size))
			return (0);
	}
	else if (hint == g_size)
	{
		i = 0;
		while (i < g_size)
		{
			if (!set_cell(start + i * step, i + 1))
				return (0);
			i++;
		}
	}
	return (1);
}

int	prefill_grid(void)
{
	int	n;
	int	i;

	n = g_size;
	i = 0;
	while (i < n)
	{
		if (!prefill_line(i, n, g_hints[i]))
			return (0);
		if (!prefill_line((n - 1) * n + i, -n, g_hints[n + i]))
			return (0);
		if (!prefill_line(i * n, 1, g_hints[2 * n + i]))
			return (0);
		if (!prefill_line(i * n + n - 1, -1, g_hints[3 * n + i]))
			return (0);
		i++;
	}
	propagate_singles();
	return (1);
}
