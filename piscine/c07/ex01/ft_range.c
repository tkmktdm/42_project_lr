/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 11:29:45 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/06 22:42:21 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include <stdlib.h>

int	*ft_range(int min, int max)
{
	int	*list;
	int	i;

	i = 0;
	if (min >= max)
		return (NULL);
	list = (int *)malloc(sizeof(int) * (max - min));
	if (!list)
		return (NULL);
	while (min < max)
	{
		list[i] = min;
		i++;
		min++;
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
