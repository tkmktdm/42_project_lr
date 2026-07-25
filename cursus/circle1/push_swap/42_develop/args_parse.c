/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 12:35:17 by htakumi           #+#    #+#             */
/*   Updated: 2026/07/19 12:35:17 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "push_swap.h"
#include <stdlib.h>

char	*join_argv(char **av)
{
	int		total;
	int		i;
	char	*result;

	i = 0;
	total = 0;
	while (av[i])
	{
		total += ft_strlen(av[i]) + 1;
		i++;
	}
	result = malloc(total + 1);
	if (!result)
		return (NULL);
	result[0] = '\0';
	i = 0;
	while (av[i])
	{
		ft_strlcat(result, av[i], total + 1);
		if (av[i + 1])
			ft_strlcat(result, " ", total + 1);
		i++;
	}
	return (result);
}

static int	select_option(char *av)
{
	if (ft_strcmp(av, "--simple") == 0)
		return (1);
	if (ft_strcmp(av, "--medium") == 0)
		return (2);
	if (ft_strcmp(av, "--complex") == 0)
		return (3);
	if (ft_strcmp(av, "--adaptive") == 0)
		return (4);
	if (ft_strcmp(av, "--bench") == 0)
		return (5);
	return (0);
}

int	is_valid_number(char *str)
{
	int		i;
	int		neg;
	long	value;

	i = 0;
	neg = 0;
	if (str[i] == '-')
	{
		neg = 1;
		i++;
	}
	if (str[i] == '\0')
		return (0);
	value = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		value = value * 10 + (str[i] - '0');
		i++;
	}
	if ((!neg && value > 2147483647) || (neg && value > 2147483648))
		return (0);
	return (1);
}

int	parse_options(char **av, int *op, int *bench_flag)
{
	int	count;
	int	type;

	count = 1;
	*op = 0;
	*bench_flag = 0;
	while (av[count] != NULL)
	{
		type = select_option(av[count]);
		if (type == 0)
			break ;
		if (type == 5 && *bench_flag == 1)
			return (-1);
		if (type == 5)
			*bench_flag = 1;
		else if (*op != 0)
			return (-1);
		else
			*op = type;
		count++;
	}
	return (count);
}
