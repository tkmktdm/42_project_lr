/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 13:59:26 by htakumi           #+#    #+#             */
/*   Updated: 2026/03/22 14:08:26 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <unistd.h>

void	ft_sort_int_tab(int *tab, int size);

void	ft_sort_int_tab(int *tab, int size)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	while (i <= size - 1)
	{
		j = 0;
		while (j <= size - 1)
		{
			if (tab[i] < tab[j])
			{
				temp = tab[i];
				tab[i] = tab[j];
				tab[j] = temp;
			}
			j++;
		}
		i++;
	}
}

// int	main(void)
// {
// 	int	tab[5];
// 	int	size;
// 	int	i;

// 	tab[0] = 10;
// 	tab[1] = 5;
// 	tab[2] = 7;
// 	tab[3] = 3;
// 	tab[4] = 8;
// 	size = 5;
// 	i = 0;
// 	while (tab[i] != '\0')
// 	{
// 		printf("bef: %d\n", tab[i]);
// 		i++;
// 	}
// 	printf("\n");
// 	ft_sort_int_tab(tab, size);
// 	i = 0;
// 	while (tab[i] != '\0')
// 	{
// 		printf("aft: %d\n", tab[i]);
// 		i++;
// 	}
// 	return (0);
// }
