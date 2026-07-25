/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_a_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 01:53:00 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/07/19 12:37:26 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>

static int	rotate_a_b(t_swap **stack)
{
	t_swap	*first;
	t_swap	*last;

	first = *stack;
	if (!stack || !*stack || (*stack)->next == NULL)
		return (0);
	last = *stack;
	while (last->next)
		last = last->next;
	*stack = first->next;
	(*stack)->pre = NULL;
	last->next = first;
	first->pre = last;
	first->next = NULL;
	return (1);
}

void	rotate_ra(t_swap **stack_a, t_bench *bench)
{
	if (rotate_a_b(stack_a) == 1)
	{
		write(1, "ra\n", 3);
		bench->ra++;
		bench->total++;
	}
}

void	rotate_rb(t_swap **stack_b, t_bench *bench)
{
	if (rotate_a_b(stack_b) == 1)
	{
		write(1, "rb\n", 3);
		bench->rb++;
		bench->total++;
	}
}

void	rotate_rr(t_swap **stack_a, t_swap **stack_b, t_bench *bench)
{
	int	check_a;
	int	check_b;

	check_a = rotate_a_b(stack_a);
	check_b = rotate_a_b(stack_b);
	if (check_a == 1 || check_b == 1)
	{
		write(1, "rr\n", 3);
		bench->rr++;
		bench->total++;
	}
}
