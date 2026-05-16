/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 14:04:01 by htakumi           #+#    #+#             */
/*   Updated: 2026/05/16 09:41:41 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr_base(int nbr, char *base);

int	base_check(char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		i++;
	}
	if (i <= 1)
		return (0);
	i = 0;
	while (base[i])
	{
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (i);
}

void	ft_putnbr(int nb, int nx, char *base)
{
	long	n;

	n = nb;
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n > nx - 1)
	{
		ft_putnbr(n / nx, nx, base);
		n = n % nx;
	}
	if (n < nx)
	{
		n = base[n % nx];
		write(1, &n, 1);
	}
}

void	ft_putnbr_base(int nbr, char *base)
{
	int	n;

	n = base_check(base);
	if (!n)
		return ;
	ft_putnbr(nbr, n, base);
}