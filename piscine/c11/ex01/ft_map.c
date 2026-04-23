/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 20:38:26 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/09 20:15:23 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include <stdlib.h>

int	*ft_map(int *tab, int length, int (*f)(int))
{
	int	i;
	int	*p;
	int	*temp;

	i = 0;
	p = malloc(sizeof(int) * (length + 1));
	if (p == NULL)
		return (NULL);
	temp = p;
	while (i < length)
	{
		*temp = f(tab[i]);
		temp++;
		i++;
	}
	return (p);
}

// void	_printf(int nbr)
// {
// 	printf("%d\n", nbr);
// }

// int	_push(int nbr)
// {
// 	int	n;

// 	n = 0;
// 	n = nbr + 42;
// 	_printf(n);
// 	return (n);
// }

// int	main(void)
// {
// 	int	tab[4];

// 	tab[0] = 100;
// 	tab[1] = 200;
// 	tab[2] = 300;
// 	tab[3] = 400;
// 	ft_map(tab, 4, &_push);
// 	return (0);
// }
