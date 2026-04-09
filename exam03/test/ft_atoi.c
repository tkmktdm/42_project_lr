/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 20:42:14 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/09 20:58:32 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// int	main(void)
// {
// 	return (0);
// }

void	ft_putnbr(int nb)
{
	long n;
	char	c;

	n = nb;
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n == 0)
	{
		write(1, "0", 1);
		return ;
	}
	if (n < 10)
	{
		c = n % 10 + '0';
		write(1, &c, 1);
	}
	ft_putnbr(n / 10);
}

int	ft_strlen(char *c)
{
	int	i;

	i = 0;
	while (*c)
	{
		i++;
		c++;
	}
	return (i);
}
