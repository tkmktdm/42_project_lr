/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_duplicate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 12:35:17 by htakumi           #+#    #+#             */
/*   Updated: 2026/07/19 12:35:17 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "push_swap.h"
#include <stdlib.h>

static void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static int	has_duplicate(char **arr, int i)
{
	int	j;

	j = i + 1;
	while (arr[j])
	{
		if (ft_atoi(arr[i]) == ft_atoi(arr[j]))
			return (1);
		j++;
	}
	return (0);
}

int	check_duplicate(char *av)
{
	char	**arr;
	int		i;

	arr = ft_split(av, ' ');
	if (!arr)
		return (0);
	if (!arr[0])
	{
		free(arr);
		return (0);
	}
	i = 0;
	while (arr[i])
	{
		if (!is_valid_number(arr[i]) || has_duplicate(arr, i))
		{
			free_arr(arr);
			return (0);
		}
		i++;
	}
	free_arr(arr);
	return (1);
}
