/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 11:24:18 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/07/19 12:35:17 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "push_swap.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	setup_stack(int ac, char **av, t_ctx *ctx)
{
	int		n;
	char	*join;

	n = parse_options(av, &ctx->op, &ctx->bench_flag);
	if (n == -1)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	if (ac == 1)
		return (0);
	join = join_argv(av + n);
	if (!join)
		return (0);
	if (check_duplicate(join) == 0)
	{
		free(join);
		write(2, "Error\n", 6);
		return (0);
	}
	ctx->a = stack_init(join);
	ctx->disorder = disorder_ratio(ctx->a);
	ctx->dis_flg = disorder_flg(ctx->disorder);
	free(join);
	return (1);
}

static void	run_algorithm(t_ctx *ctx)
{
	if (ctx->op == 1)
		simple_algorithm(&ctx->a, &ctx->b, &ctx->bench);
	if (ctx->op == 2)
		medium_algorithm(&ctx->a, &ctx->b, &ctx->bench);
	if (ctx->op == 3)
		complex_algorithm(&ctx->a, &ctx->b, &ctx->bench);
	if (ctx->op == 0 || ctx->op == 4)
		adaptive_algorithm(&ctx->a, &ctx->b, &ctx->bench, ctx->dis_flg);
}

static void	print_all_bench(t_ctx *ctx)
{
	print_disorder(ctx->disorder);
	print_strategy(ctx->op, ctx->dis_flg);
	print_bench(&ctx->bench);
}

int	main(int ac, char **av)
{
	t_ctx	ctx;
	int		ret;

	ft_bzero(&ctx, sizeof(t_ctx));
	ret = setup_stack(ac, av, &ctx);
	if (ret != 1)
		return (0);
	run_algorithm(&ctx);
	if (ctx.bench_flag == 1)
		print_all_bench(&ctx);
	stack_free(ctx.a);
	stack_free(ctx.b);
	return (0);
}
