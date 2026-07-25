/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_algorithm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 15:09:08 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/07/19 12:37:43 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	find_min_index(t_swap *stack)
{
	int	i;
	int	min;
	int	count;

	if (stack == NULL)
		return (-1);
	i = 0;
	count = 0;
	min = stack->num;
	while (stack != NULL)
	{
		if (min > stack->num)
		{
			min = stack->num;
			i = count;
		}
		stack = stack->next;
		count++;
	}
	return (i);
}

static void	bring_min_to_top(t_swap **a, int min_index, int size,
		t_bench *bench)
{
	int	i;

	i = 0;
	if (min_index <= size / 2)
	{
		while (i < min_index)
		{
			rotate_ra(a, bench);
			i++;
		}
	}
	else
	{
		while (i < (size - min_index))
		{
			rev_rotate_a(a, bench);
			i++;
		}
	}
}

void	simple_algorithm(t_swap **a, t_swap **b, t_bench *bench)
{
	int	n;
	int	i;
	int	min_index;
	int	size;

	n = stack_size(*a);
	if (n <= 1 || is_sorted(*a))
		return ;
	i = 0;
	while (i < n - 2)
	{
		min_index = find_min_index(*a);
		size = stack_size(*a);
		bring_min_to_top(a, min_index, size, bench);
		push_pb(a, b, bench);
		i++;
	}
	if ((*a)->num > (*a)->next->num)
		swap_sa(*a, bench);
	while (*b != NULL)
		push_pa(a, b, bench);
}
