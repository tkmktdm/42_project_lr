/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_range.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 11:40:51 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/02 19:24:23 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include <stdlib.h>

int	ft_ultimate_range(int **range, int min, int max)
{
	int	len;
	int	i;

	i = 0;
	len = max - min;
	if (len < 1)
	{
		*range = NULL;
		return (0);
	}
	*range = malloc(sizeof(int) * len);
	if (!*range)
		return (-1);
	while (i < len)
	{
		(*range)[i] = min + i;
		i++;
	}
	return (i);
}

// int	main(void)
// {
// 	int	len;
// 	int	*arr;

// 	len = ft_ultimate_range(&arr, 3, 9);
// 	// len = ft_ultimate_range(&arr, 3, 2);
// 	printf("%d\n", len);
// 	printf("%p\n", arr);
// 	free(arr);
// 	return (0);
// }
