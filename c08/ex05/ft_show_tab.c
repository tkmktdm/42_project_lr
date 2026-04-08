/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:50:50 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/07 20:46:04 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stock_str.h"
#include <unistd.h>

static int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

static void	ft_putchar(char *c)
{
	int	len;

	len = ft_strlen(c);
	write(1, c, len);
}

static void	ft_putnbr(int nb)
{
	long	n;

	n = nb;
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n > 9)
	{
		ft_putnbr(n / 10);
	}
	n = (n % 10) + '0';
	write(1, &n, 1);
}

void	ft_show_tab(struct s_stock_str *par)
{
	int	i;

	i = 0;
	while (par->str != NULL)
	{
		ft_putchar(par->str);
		ft_putchar("\n");
		ft_putnbr(par->size);
		ft_putchar("\n");
		ft_putchar(par->copy);
		ft_putchar("\n");
		par++;
	}
}

// int	main(void)
// {
// 	struct s_stock_str	tab[3];

// 	tab[0].str = "hello";
// 	tab[0].size = 5;
// 	tab[0].copy = "hello";
// 	tab[1].str = "world";
// 	tab[1].size = 5;
// 	tab[1].copy = "world";
// 	tab[2].str = 0;
// 	ft_show_tab(tab);
// 	return (0);
// }
