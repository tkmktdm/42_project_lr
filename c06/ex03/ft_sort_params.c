/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 11:52:05 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/02 15:56:56 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
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

void	ft_sort_char(int ac, char **av)
{
	int		i;
	int		j;
	char	*temp;

	i = 1;
	while (i < ac - 1)
	{
		j = i + 1;
		while (j < ac)
		{
			if (ft_strcmp(av[i], av[j]) > 0)
			{
				temp = av[i];
				av[i] = av[j];
				av[j] = temp;
			}
			j++;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	ft_sort_char(ac, av);
	while (i < ac)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			ft_putchar(av[i][j]);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
	return (0);
}
