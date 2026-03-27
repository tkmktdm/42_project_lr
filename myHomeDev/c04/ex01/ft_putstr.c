/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 09:40:33 by htakumi           #+#    #+#             */
/*   Updated: 2026/03/27 09:56:56 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <unistd.h>

void	ft_putstr(char *str);

void	ft_putstr(char *str)
{
	while (*str)
	{
		write(1, str, 1);
		str++;
	}
}

// int	main(void)
// {
// 	ft_putstr("Hello world !!!! \n 42 tokyo is shinzyuku \0");
// 	return (0);
// }
