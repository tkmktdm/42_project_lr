/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazonode <kazonode@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 22:13:50 by kazonode          #+#    #+#             */
/*   Updated: 2026/03/29 17:55:36 by kazonode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern int	*g_grid;
extern int	*g_hints;
extern int	g_size;

void	init_grid(void)
{
	int	i;

	i = 0;
	while (i < g_size * g_size)
	{
		g_grid[i] = 0;
		i++;
	}
}
