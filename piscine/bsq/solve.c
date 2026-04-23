/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 20:46:47 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/08 21:01:31 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

static void	free_dp(int **dp, int rows)
{
	int	i;

	if (!dp)
		return ;
	i = 0;
	while (i < rows)
		free(dp[i++]);
	free(dp);
}

static int	**alloc_dp(int rows, int cols)
{
	int	**dp;
	int	i;

	dp = malloc(sizeof(int *) * rows);
	if (!dp)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		dp[i] = malloc(sizeof(int) * cols);
		if (!dp[i])
			return (free_dp(dp, i), NULL);
		i++;
	}
	return (dp);
}

static void	update_dp(t_map *map, int **dp, int i, int j)
{
	int	val;

	if (map->grid[i][j] == map->obst)
	{
		dp[i][j] = 0;
		return ;
	}
	if (i == 0 || j == 0)
	{
		dp[i][j] = 1;
		return ;
	}
	val = dp[i - 1][j - 1];
	if (dp[i - 1][j] < val)
		val = dp[i - 1][j];
	if (dp[i][j - 1] < val)
		val = dp[i][j - 1];
	dp[i][j] = val + 1;
}

static void	fill_dp(t_map *map, int **dp, int *mr, int *mc)
{
	int	i;
	int	j;
	int	best;

	best = 0;
	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			update_dp(map, dp, i, j);
			if (dp[i][j] > best)
			{
				best = dp[i][j];
				*mr = i;
				*mc = j;
			}
			j++;
		}
		i++;
	}
}

void	solve_bsq(t_map *map)
{
	int	**dp;
	int	mr;
	int	mc;

	dp = alloc_dp(map->rows, map->cols);
	if (!dp)
		return ;
	mr = 0;
	mc = 0;
	fill_dp(map, dp, &mr, &mc);
	if (dp[mr][mc] > 0)
		mark_square(map, dp[mr][mc], mr, mc);
	free_dp(dp, map->rows);
}
