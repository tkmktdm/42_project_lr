/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_a_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 01:53:00 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/07/25 17:30:33 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	rotate_a_b(t_swap **stack)
{
	t_swap	*first;
	t_swap	*last;

	if (!stack || !*stack || (*stack)->next == NULL)
		return (0);
	first = *stack;
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
		report_op("ra\n", 3, &bench->ra, bench);
}

void	rotate_rb(t_swap **stack_b, t_bench *bench)
{
	if (rotate_a_b(stack_b) == 1)
		report_op("rb\n", 3, &bench->rb, bench);
}

void	rotate_rr(t_swap **stack_a, t_swap **stack_b, t_bench *bench)
{
	int	check_a;
	int	check_b;

	check_a = rotate_a_b(stack_a);
	check_b = rotate_a_b(stack_b);
	if (check_a == 1 || check_b == 1)
		report_op("rr\n", 3, &bench->rr, bench);
}
