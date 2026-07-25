/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_a_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 22:00:39 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/07/19 12:56:18 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>

static int	push_a_b(t_swap **before, t_swap **after)
{
	t_swap	*before_node;

	if (before == NULL || *before == NULL)
		return (0);
	before_node = *before;
	*before = before_node->next;
	if (*before != NULL)
		(*before)->pre = NULL;
	before_node->next = *after;
	before_node->pre = NULL;
	if (*after != NULL)
		(*after)->pre = before_node;
	*after = before_node;
	return (1);
}

void	push_pa(t_swap **stack_a, t_swap **stack_b, t_bench *bench)
{
	int	check;

	check = push_a_b(stack_b, stack_a);
	if (check == 1)
	{
		write(1, "pa\n", 3);
		bench->pa++;
		bench->total++;
	}
	return ;
}

void	push_pb(t_swap **stack_a, t_swap **stack_b, t_bench *bench)
{
	int	check;

	check = push_a_b(stack_a, stack_b);
	if (check == 1)
	{
		write(1, "pb\n", 3);
		bench->pb++;
		bench->total++;
	}
	return ;
}
