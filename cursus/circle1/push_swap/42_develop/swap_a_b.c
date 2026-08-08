/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_a_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 19:16:51 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/07/19 12:56:08 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	swap_a_b(t_swap *node)
{
	int	tmp;

	if (node == NULL || node->next == NULL)
		return (0);
	tmp = node->num;
	node->num = node->next->num;
	node->next->num = tmp;
	return (1);
}

void	swap_sa(t_swap *node, t_bench *bench)
{
	if (swap_a_b(node) == 1)
		report_op("sa\n", 3, &bench->sa, bench);
	return ;
}

void	swap_sb(t_swap *node, t_bench *bench)
{
	if (swap_a_b(node) == 1)
		report_op("sb\n", 3, &bench->sb, bench);
	return ;
}

void	swap_ss(t_swap *node_a, t_swap *node_b, t_bench *bench)
{
	int	check;

	check = 0;
	check += swap_a_b(node_a);
	check += swap_a_b(node_b);
	if (check >= 1)
		report_op("ss\n", 3, &bench->ss, bench);
	return ;
}
