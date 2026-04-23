/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upper_bound.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazonode <kazonode@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 17:15:40 by kazonode          #+#    #+#             */
/*   Updated: 2026/03/29 17:54:31 by kazonode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern int	*g_grid;
extern int	*g_hints;
extern int	g_size;

int	get_max_val(int row, int col)
{
	int	n;
	int	max;
	int	v;

	n = g_size;
	max = n;
	v = n - g_hints[col] + row + 1;
	if (v < max)
		max = v;
	v = 2 * n - g_hints[n + col] - row;
	if (v < max)
		max = v;
	v = n - g_hints[2 * n + row] + col + 1;
	if (v < max)
		max = v;
	v = 2 * n - g_hints[3 * n + row] - col;
	if (v < max)
		max = v;
	return (max);
}
