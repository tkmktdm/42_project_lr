/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 12:35:17 by htakumi           #+#    #+#             */
/*   Updated: 2026/07/19 12:35:17 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	count_in_chunk(t_swap *a, int start, int end)
{
	int	count;

	count = 0;
	while (a != NULL)
	{
		if (a->rank >= start && a->rank < end)
			count++;
		a = a->next;
	}
	return (count);
}

static int	find_chunk_index(t_swap *a, int start, int end)
{
	int	j;

	j = 0;
	while (a != NULL)
	{
		if (a->rank >= start && a->rank < end)
			return (j);
		a = a->next;
		j++;
	}
	return (0);
}

void	bring_chunk(t_swap **a, t_swap **b, int chunk_size, t_bench *bench)
{
	int	chunk_start;
	int	chunk_end;
	int	count;

	chunk_start = 0;
	chunk_end = chunk_size;
	while (*a != NULL)
	{
		count = count_in_chunk(*a, chunk_start, chunk_end);
		while (count > 0)
		{
			if ((*a)->rank >= chunk_start && (*a)->rank < chunk_end)
			{
				push_pb(a, b, bench);
				count--;
			}
			else if (find_chunk_index(*a, chunk_start,
					chunk_end) <= stack_size(*a) / 2)
				rotate_ra(a, bench);
			else
				rev_rotate_a(a, bench);
		}
		chunk_start = chunk_end;
		chunk_end += chunk_size;
	}
}
