/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 11:24:18 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/06/13 15:17:07 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include <stdio.h>
#include <unistd.h>

int	select_option(char *av)
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
int	check_duplicate(char **av)
{
	int				i;
	char			s[256];
	unsigned char	c;

	printf("printf0:%s:printf\n", *av);
	printf("printf1:%c:printf\n", *av[i]);
	i = 0;
	while (i < 256)
	{
		s[i] = 0;
		i++;
	}
	i = 0;
	while (*av[i])
	{
		if (*av[i] == ' ')
		{
			i++;
			continue ;
		}
		c = (unsigned char)*av[i];
		if (*av[i] == '-')
		{
			i++;
			if (s[c] == 0)
				s[c] = 1;
			else if (s[c] == 1)
			{
				// write (1, "- error", 8);
				return (132);
			}
		}
		if (s[c] == 0)
			s[c] = 1;
		else if (s[c] == 1)
		{
			printf("printf:%c:printf\n", s[c]);
			// write (1, "error", 8);
			// write(1, &s[c], 1);
			return (8);
		}
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	int		i;
	int		op;
	t_swap	a;
	t_swap	b;
	int		check;

	i = 0;
	if (ac != 2 && ac != 3)
	{
		write(2, "1: Error\n", 9);
		return (0);
	}
	// option
	if (ac == 3)
	{
		av++;
		op = select_option(*av);
		if (op == 0)
		{
			write(2, "2: Error\n", 9);
			return (0);
		}
	}
	av++;
	// number check
	check = check_duplicate(av);
	printf("check: %d", check);
	if (check == 0)
	{
		write(2, "3: Error\n", 9);
		return (0);
	}
	// // stack
	// while (**av != '\0')
	// {
	// 	if (**av != ' ')
	// 	{
	// 		a.num = (int)*av;
	// 		write(1, *av, 1);
	// 	}
	// 	(*av)++;
	// }
	return (0);
}

// # イメージ（疑似コード）
// mistakes = 0
// total_pairs = 0
// for i in range(len(a)):
//     for j in range(i+1, len(a)):
//         total_pairs += 1
//         if a[i] > a[j]:
//             mistakes += 1
// disorder = mistakes / total_pairs

