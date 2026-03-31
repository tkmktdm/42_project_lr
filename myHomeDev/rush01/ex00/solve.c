/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazonode <kazonode@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 21:52:45 by kazonode          #+#    #+#             */
/*   Updated: 2026/03/29 17:54:35 by kazonode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern int	*g_grid;
extern int	*g_hints;
extern int	g_size;

int	check_hints(int pos);
int	get_max_val(int row, int col);
int	is_unique(int pos, int num);

int	solve(int pos)
{
	int	num;
	int	max_val;

	if (pos == g_size * g_size)
		return (1);
	if (g_grid[pos] != 0)
	{
		if (check_hints(pos))
			return (solve(pos + 1));
		return (0);
	}
	max_val = get_max_val(pos / g_size, pos % g_size);
	num = 1;
	while (num <= max_val)
	{
		if (is_unique(pos, num))
		{
			g_grid[pos] = num;
			if (check_hints(pos) && solve(pos + 1))
				return (1);
			g_grid[pos] = 0;
		}
		num++;
	}
	return (0);
}
