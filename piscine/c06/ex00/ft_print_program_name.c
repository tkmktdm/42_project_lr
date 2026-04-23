/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_program_name.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 11:14:18 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/01 11:29:06 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	main(int ac, char **av)
{
	ac = 0;
	while (*av[ac] != '\0')
	{
		ft_putchar(*av[ac]);
		av[ac]++;
	}
	ft_putchar('\n');
	return (0);
}
