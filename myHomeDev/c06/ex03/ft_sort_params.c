/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 11:52:05 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/01 13:00:54 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 > *s2)
		{
			return (*s1 - *s2);
		}
		else if (*s2 > *s1)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}
	return (0);
}

void	ft_sort_char(int n, char **c)
{
	int		i;
	int		j;
	char	*temp;

	i = 1;
	while (i < n)
	{
		j = 0;
		while (j <= n - 1)
		{
			printf("%s vs %s: %d\n", c[2], c[2], ft_strcmp(c[i], c[j]));
			if (ft_strcmp(c[i], c[j]))
			{
				temp = c[i];
				c[i] = c[j];
				c[j] = temp;
			}
			j++;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	int		i;
	char	**args;

	i = 0;
	while (i < av[i])
	{
		printf("av: %s\n", av[i]);
		*args = av[i];
		printf("args: %s\n", args[i]);
		args++;
		i++;
	}
	// if (ac > 1)
	// 	av[i]++;
	// ac = ac - 1;
	// ft_sort_char(ac, av);
	// while (i < ac)
	// {
	// 	printf("%s\n", av[i]);
	// 	i++;
	// }
	return (0);
}
