/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 12:35:17 by htakumi           #+#    #+#             */
/*   Updated: 2026/07/19 12:35:17 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "push_swap.h"

static void	print_label_num(char *label, int val)
{
	ft_putstr_fd(label, 2);
	ft_putnbr_fd(val, 2);
}

void	print_bench(t_bench *bench)
{
	print_label_num("[bench] total_ops: ", bench->total);
	ft_putstr_fd("\n", 2);
	print_label_num("[bench] sa: ", bench->sa);
	print_label_num("  sb: ", bench->sb);
	print_label_num("  ss: ", bench->ss);
	print_label_num("  pa: ", bench->pa);
	print_label_num("  pb: ", bench->pb);
	ft_putstr_fd("\n", 2);
	print_label_num("[bench] ra: ", bench->ra);
	print_label_num("  rb: ", bench->rb);
	print_label_num("  rr: ", bench->rr);
	print_label_num("  rra: ", bench->rra);
	print_label_num("  rrb: ", bench->rrb);
	print_label_num("  rrr: ", bench->rrr);
	ft_putstr_fd("\n", 2);
}

void	print_disorder(double disorder_result)
{
	int	scaled;
	int	int_part;
	int	frac_part;

	scaled = (int)(disorder_result * 10000 + 0.5);
	int_part = scaled / 100;
	frac_part = scaled % 100;
	ft_putstr_fd("[bench] disorder:  ", 2);
	ft_putnbr_fd(int_part, 2);
	ft_putstr_fd(".", 2);
	if (frac_part < 10)
		ft_putstr_fd("0", 2);
	ft_putnbr_fd(frac_part, 2);
	ft_putstr_fd("%\n", 2);
}

void	print_strategy(int op, int dis_flg)
{
	ft_putstr_fd("[bench] strategy:  ", 2);
	if (op == 1)
		ft_putstr_fd("Simple / O(n²)\n", 2);
	else if (op == 2)
		ft_putstr_fd("Medium / O(n√n)\n", 2);
	else if (op == 3)
		ft_putstr_fd("Complex / O(n log n)\n", 2);
	else if (dis_flg == 1)
		ft_putstr_fd("Adaptive / O(n²)\n", 2);
	else if (dis_flg == 2)
		ft_putstr_fd("Adaptive / O(n√n)\n", 2);
	else if (dis_flg == 3)
		ft_putstr_fd("Adaptive / O(n log n)\n", 2);
}
