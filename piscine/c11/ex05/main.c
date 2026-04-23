/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:51:35 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/09 20:16:15 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

static void	ft_putnbr(int nbr)
{
	char	c;
	long	n;

	n = nbr;
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr(n / 10);
	c = n % 10 + '0';
	write(1, &c, 1);
}

static int	ft_get_op_index(char *op)
{
	char	*ops;
	int		i;

	ops = "+-*/%";
	if (op[0] == '\0' || op[1] != '\0')
		return (-1);
	i = 0;
	while (ops[i])
	{
		if (ops[i] == op[0])
			return (i);
		i++;
	}
	return (-1);
}

static void	ft_init_fptr(int (**fptr)(int, int))
{
	fptr[0] = &ft_add;
	fptr[1] = &ft_sub;
	fptr[2] = &ft_mul;
	fptr[3] = &ft_div;
	fptr[4] = &ft_rem;
}

int	main(int ac, char **av)
{
	int	(*fptr[5])(int, int);
	int	idx;
	int	result;

	if (ac != 4)
		return (0);
	ft_init_fptr(fptr);
	idx = ft_get_op_index(av[2]);
	if (idx == -1)
	{
		ft_putnbr(0);
		write(1, "\n", 1);
		return (0);
	}
	result = fptr[idx](ft_atoi(av[1]), ft_atoi(av[3]));
	if ((idx == 3 || idx == 4) && ft_atoi(av[3]) == 0)
		return (0);
	ft_putnbr(result);
	write(1, "\n", 1);
	return (0);
}
