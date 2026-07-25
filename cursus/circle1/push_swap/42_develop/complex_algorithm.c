/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_algorithm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 12:51:02 by htakumi           #+#    #+#             */
/*   Updated: 2026/07/19 12:35:43 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "push_swap.h"

int	bit_size(int n)
{
	int	i;

	i = 0;
	if (n <= 1)
		return (1);
	while ((1 << i) < n)
		i++;
	return (i);
}

int	radix_pass(t_swap **a, t_swap **b, int bit, t_bench *bench)
{
	int	i;
	int	count;

	i = 0;
	while (i < bit)
	{
		count = stack_size(*a);
		while (count)
		{
			if (((*a)->rank >> i) & 1)
				rotate_ra(a, bench);
			else
				push_pb(a, b, bench);
			count--;
		}
		while (*b != NULL)
			push_pa(a, b, bench);
		i++;
	}
	return (0);
}

int	is_sorted(t_swap *a)
{
	while (a != NULL && a->next != NULL)
	{
		if (a->num > a->next->num)
			return (0);
		a = a->next;
	}
	return (1);
}

void	complex_algorithm(t_swap **a, t_swap **b, t_bench *bench)
{
	int	n;
	int	bit;

	if (is_sorted(*a))
		return ;
	chunk_rank(*a);
	n = stack_size(*a);
	if (n <= 1)
		return ;
	bit = bit_size(n);
	radix_pass(a, b, bit, bench);
}
