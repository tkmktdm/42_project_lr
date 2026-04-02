/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constraint_propagation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazonode <kazonode@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 17:27:55 by kazonode          #+#    #+#             */
/*   Updated: 2026/03/29 17:56:35 by kazonode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern int	*g_grid;
extern int	*g_hints;
extern int	g_size;

int	get_max_val(int row, int col);
int	try_hidden_singles(void);

void	mark_used(int *used, int row, int col)
{
	int	i;
	int	max;

	i = 0;
	while (i <= g_size)
	{
		used[i] = 0;
		i++;
	}
	i = 0;
	while (i < g_size)
	{
		if (g_grid[row * g_size + i] != 0)
			used[g_grid[row * g_size + i]] = 1;
		if (g_grid[i * g_size + col] != 0)
			used[g_grid[i * g_size + col]] = 1;
		i++;
	}
	max = get_max_val(row, col);
	i = max + 1;
	while (i <= g_size)
	{
		used[i] = 1;
		i++;
	}
}

int	find_only_value(int row, int col)
{
	int	used[10];
	int	i;
	int	count;
	int	val;

	mark_used(used, row, col);
	count = 0;
	val = 0;
	i = 1;
	while (i <= g_size)
	{
		if (!used[i])
		{
			count++;
			val = i;
		}
		i++;
	}
	if (count == 1)
		return (val);
	return (0);
}

int	propagate_naked(void)
{
	int	i;
	int	val;
	int	changed;

	changed = 0;
	i = 0;
	while (i < g_size * g_size)
	{
		if (g_grid[i] == 0)
		{
			val = find_only_value(i / g_size, i % g_size);
			if (val > 0)
			{
				g_grid[i] = val;
				changed = 1;
			}
		}
		i++;
	}
	return (changed);
}

void	propagate_singles(void)
{
	int	changed;

	changed = 1;
	while (changed)
	{
		changed = propagate_naked();
		if (try_hidden_singles())
			changed = 1;
	}
}
