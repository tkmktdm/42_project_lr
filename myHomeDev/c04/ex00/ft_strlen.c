/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 09:37:41 by htakumi           #+#    #+#             */
/*   Updated: 2026/03/27 09:56:25 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

int	ft_strlen(char *str);

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (*str++)
	{
		i++;
	}
	return (i);
}

// int	main(void)
// {
// 	int	i;

// 	i = ft_strlen("HelloWorld12345");
// 	printf("HelloWorld12345: (15)= %d", i);
// 	return (0);
// }
