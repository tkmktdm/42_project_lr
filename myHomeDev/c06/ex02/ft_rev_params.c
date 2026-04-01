/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 11:40:51 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/01 11:44:53 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	main(int ac, char **av)
{
	int	i;

	i = 1;
	while (i <= ac - 1)
	{
		while (*av[ac - 1] != '\0')
		{
			ft_putchar(*av[ac - 1]);
			av[ac - 1]++;
		}
		ft_putchar('\n');
		ac--;
	}
	return (0);
}
