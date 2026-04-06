/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 16:18:04 by msumiji           #+#    #+#             */
/*   Updated: 2026/04/05 20:39:15 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"
#include <unistd.h>

int	put_error(void)
{
	write(2, "Error\n", 6);
	return (1);
}

int	dict_error(void)
{
	write(2, "Dict Error\n", 11);
	return (1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	int	n;

	if (!str)
	{
		write(2, "Dict Error", 10);
		return ;
	}
	n = ft_strlen(str);
	write(1, str, n);
}

int	split_groups(char *num_str, char groups[][4])
{
	int	len;
	int	i;
	int	start;
	int	j;

	len = ft_strlen(num_str);
	i = len;
	j = 0;
	while (i > 0)
	{
		start = 0;
		if (i >= 3)
			start = i - 3;
		len = 0;
		while (len < i - start)
		{
			groups[j][len] = num_str[start + len];
			len++;
		}
		groups[j][len] = '\0';
		j++;
		i = start;
	}
	return (j);
}
