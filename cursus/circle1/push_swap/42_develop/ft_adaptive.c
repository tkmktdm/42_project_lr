/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_adaptive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 12:53:28 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/07/19 12:35:54 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	stack_to_array(t_swap *a, int *n_arr)
{
	while (a != NULL)
	{
		*n_arr = a->num;
		n_arr++;
		a = a->next;
	}
	return ;
}

double	disorder_ratio(t_swap *a)
{
	int		n;
	int		*n_arr;
	double	disorder_result;

	n = stack_size(a);
	n_arr = malloc(sizeof(int) * n);
	if (!n_arr)
		return (0);
	stack_to_array(a, n_arr);
	disorder_result = calculate_disorder_fast(n_arr, n);
	free(n_arr);
	return (disorder_result);
}

int	disorder_flg(double n)
{
	if (n < 0.2)
		return (1);
	if (0.2 <= n && n < 0.5)
		return (2);
	if (n >= 0.5)
		return (3);
	return (0);
}

void	adaptive_algorithm(t_swap **a, t_swap **b, t_bench *bench, int dis_flg)
{
	if (dis_flg == 1)
		simple_algorithm(a, b, bench);
	else if (dis_flg == 2)
		medium_algorithm(a, b, bench);
	else if (dis_flg == 3)
		complex_algorithm(a, b, bench);
	else
		return ;
}
