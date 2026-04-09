/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_foreach.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:29:56 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/08 21:53:09 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

void	ft_foreach(int *tab, int length, void (*f)(int))
{
	int	*end;

	end = tab + length;
	while (tab < end)
	{
		f(*tab);
		tab++;
	}
}

// void	_printf(int nbr)
// {
// 	printf("%d\n", nbr);
// }

// int	main(void)
// {
// 	int	tab[4];

// 	tab[0] = 1;
// 	tab[1] = 2;
// 	tab[2] = 3;
// 	tab[3] = 4;
// 	ft_foreach(tab, 1337, &_printf);
// 	return (0);
// }
