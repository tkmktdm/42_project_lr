/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 11:29:45 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/02 18:26:29 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include <stdlib.h>

int	*ft_range(int min, int max)
{
	int	range;
	int	*list;
	int	i;

	i = 0;
	range = max - min;
	if (range < 1)
		return (NULL);
	list = malloc(sizeof(int) * range);
	while (i < range)
	{
		list[i] = min + i;
		i++;
	}
	return (list);
}

// int	main(void)
// {
// 	int	*arr;
// 	int	i;
// 	int	min;
// 	int	max;

// 	min = 3;
// 	max = 9;
// 	i = 0;
// 	arr = ft_range(min, max);
// 	while (i < max - min)
// 	{
// 		printf("%d\n", arr[i]);
// 		i++;
// 	}
// 	free(arr);
// 	return (0);
// }
