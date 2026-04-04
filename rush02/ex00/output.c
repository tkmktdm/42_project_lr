/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 16:18:04 by msumiji           #+#    #+#             */
/*   Updated: 2026/04/04 17:40:10 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	put_error(int i)
{
	if (i == 0)
		write(2, "Error\n", 6);
	if (i == 1)
		write(2, "Dict Error\n", 11);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_putstrs(char *str)
{
	int	n;

	n = ft_strlen(str);
	write(1, str, n);
}

void	ft_putstr(char *str)
{
	write(1, str, 1);
}
