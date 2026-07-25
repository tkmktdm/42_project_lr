/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_algorithm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 12:35:17 by htakumi           #+#    #+#             */
/*   Updated: 2026/07/19 12:35:17 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	chunk_rank(t_swap *a)
{
	t_swap	*min_rank;
	t_swap	*cur;
	int		rank_count;

	min_rank = a;
	while (min_rank != NULL)
	{
		cur = a;
		rank_count = 0;
		while (cur != NULL)
		{
			if (cur->num < min_rank->num)
			{
				rank_count++;
			}
			cur = cur->next;
		}
		min_rank->rank = rank_count;
		min_rank = min_rank->next;
	}
}

static int	chunk_size(t_swap *stack)
{
	int	n;
	int	i;

	n = stack_size(stack);
	i = 1;
	if (n <= 3)
		return (n);
	while (i * i <= n)
		i++;
	return (i - 1);
}

static int	find_max_rank_index(t_swap *b)
{
	int	max_rank;
	int	max_index;
	int	i;

	max_rank = b->rank;
	max_index = 0;
	i = 0;
	while (b != NULL)
	{
		if (b->rank > max_rank)
		{
			max_rank = b->rank;
			max_index = i;
		}
		b = b->next;
		i++;
	}
	return (max_index);
}

void	pull_from_b(t_swap **a, t_swap **b, t_bench *bench)
{
	int	max_idx;
	int	size;

	while (*b != NULL)
	{
		size = stack_size(*b);
		max_idx = find_max_rank_index(*b);
		if (max_idx <= size / 2)
		{
			while (max_idx-- > 0)
				rotate_rb(b, bench);
		}
		else
		{
			max_idx = size - max_idx;
			while (max_idx-- > 0)
				rev_rotate_b(b, bench);
		}
		push_pa(a, b, bench);
	}
}

void	medium_algorithm(t_swap **a, t_swap **b, t_bench *bench)
{
	int	n;

	if (is_sorted(*a))
		return ;
	chunk_rank(*a);
	n = chunk_size(*a);
	bring_chunk(a, b, n, bench);
	pull_from_b(a, b, bench);
}
