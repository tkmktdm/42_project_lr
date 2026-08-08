/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotate_a_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 02:48:54 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/07/19 12:37:18 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	rev_rotate(t_swap **stack)
{
	t_swap	*last;
	t_swap	*first;

	if (!stack || !*stack || (*stack)->next == NULL)
		return (0);
	first = *stack;
	last = *stack;
	while (last->next)
		last = last->next;
	last->pre->next = NULL;
	last->next = first;
	first->pre = last;
	last->pre = NULL;
	*stack = last;
	return (1);
}

void	rev_rotate_a(t_swap **stack_a, t_bench *bench)
{
	if (rev_rotate(stack_a) == 1)
		report_op("rra\n", 4, &bench->rra, bench);
}

void	rev_rotate_b(t_swap **stack_b, t_bench *bench)
{
	if (rev_rotate(stack_b) == 1)
		report_op("rrb\n", 4, &bench->rrb, bench);
}

void	rev_rotate_r(t_swap **stack_a, t_swap **stack_b, t_bench *bench)
{
	int	check_a;
	int	check_b;

	check_a = rev_rotate(stack_a);
	check_b = rev_rotate(stack_b);
	if (check_a == 1 || check_b == 1)
		report_op("rrr\n", 4, &bench->rrr, bench);
}
