/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 19:07:08 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/07/19 14:44:41 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"
# include <stdlib.h>

typedef struct s_swap
{
	int				num;
	int				rank;
	struct s_swap	*pre;
	struct s_swap	*next;

}					t_swap;

typedef struct s_arrs
{
	int				*arr;
	int				*temp;
}					t_arrs;

typedef struct s_bench
{
	int				sa;
	int				sb;
	int				ss;
	int				pa;
	int				pb;
	int				ra;
	int				rb;
	int				rr;
	int				rra;
	int				rrb;
	int				rrr;
	int				total;
}					t_bench;

typedef struct s_ctx
{
	t_swap			*a;
	t_swap			*b;
	t_bench			bench;
	int				op;
	int				bench_flag;
	int				dis_flg;
	double			disorder;
}					t_ctx;

void				report_op(char *label, int len, int *counter,
						t_bench *bench);
void				swap_sa(t_swap *node, t_bench *bench);
void				swap_sb(t_swap *node, t_bench *bench);
void				swap_ss(t_swap *node_a, t_swap *node_b, t_bench *bench);
void				push_pa(t_swap **stack_a, t_swap **stack_b, t_bench *bench);
void				push_pb(t_swap **stack_a, t_swap **stack_b, t_bench *bench);
void				rotate_ra(t_swap **stack_a, t_bench *bench);
void				rotate_rb(t_swap **stack_b, t_bench *bench);
void				rotate_rr(t_swap **stack_a, t_swap **stack_b,
						t_bench *bench);
void				rev_rotate_a(t_swap **stack_a, t_bench *bench);
void				rev_rotate_b(t_swap **stack_b, t_bench *bench);
void				rev_rotate_r(t_swap **stack_a, t_swap **stack_b,
						t_bench *bench);
int					stack_size(t_swap *stack);
void				chunk_rank(t_swap *a);
void				bring_chunk(t_swap **a, t_swap **b, int chunk_size,
						t_bench *bench);
void				pull_from_b(t_swap **a, t_swap **b, t_bench *bench);
void				simple_algorithm(t_swap **a, t_swap **b, t_bench *bench);
void				medium_algorithm(t_swap **a, t_swap **b, t_bench *bench);
void				complex_algorithm(t_swap **a, t_swap **b, t_bench *bench);
int					is_sorted(t_swap *a);

double				calculate_disorder_fast(int a[], int n);
int					disorder_flg(double n);
int					ft_strcmp(char *s1, char *s2);

void				adaptive_algorithm(t_swap **a, t_swap **b, t_bench *bench,
						int dis_flg);
void				stack_free(t_swap *stack);
void				stack_to_array(t_swap *a, int *n_arr);
double				disorder_ratio(t_swap *a);

char				*join_argv(char **av);
int					is_valid_number(char *str);
int					parse_options(char **av, int *op, int *bench_flag);
int					check_duplicate(char *av);
t_swap				*stack_init(char *str);
void				print_bench(t_bench *bench);
void				print_disorder(double disorder_result);
void				print_strategy(int op, int dis_flg);

#endif
