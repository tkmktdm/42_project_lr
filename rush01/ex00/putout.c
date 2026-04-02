/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putout.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazonode <kazonode@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 16:53:44 by kazonode          #+#    #+#             */
/*   Updated: 2026/03/29 18:05:35 by kazonode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

extern int	*g_grid;
extern int	*g_hints;
extern int	g_size;

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	while (*s)
	{
		ft_putchar(*s++);
	}
}

void	print_grid(void)
{
	int	i;

	i = 0;
	while (i < g_size * g_size)
	{
		ft_putchar('0' + g_grid[i]);
		if ((i + 1) % g_size == 0)
			ft_putchar('\n');
		else
			ft_putchar(' ');
		i++;
	}
}
