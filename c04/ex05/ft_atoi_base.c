/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:06:50 by htakumi           #+#    #+#             */
/*   Updated: 2026/03/31 10:37:50 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

int		ft_atoi_base(char *str, char *base);

int	has_dup(char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i])
	{
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	base_check(char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		if (base[i] == ' ' || (base[i] >= 9 && base[i] <= 13))
			return (0);
		i++;
	}
	if (i <= 1)
		return (0);
	if (has_dup(base))
		return (0);
	return (i);
}

int	char_index(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*skip_prefix(char *str, int *mflg)
{
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			(*mflg)++;
		str++;
	}
	return (str);
}

int	ft_atoi_base(char *str, char *base)
{
	int		nx;
	int		mflg;
	long	n;

	nx = base_check(base);
	if (!nx)
		return (0);
	mflg = 0;
	str = skip_prefix(str, &mflg);
	n = 0;
	while (char_index(*str, base) != -1)
	{
		n = n * nx + char_index(*str, base);
		str++;
	}
	if (mflg % 2 == 1)
		n = -n;
	return ((int)n);
}

// int	main(void)
// {
// 	printf("%d\n", ft_atoi_base(" a---+--+1234ab567", "0123456789"));
// 	printf("%d\n", ft_atoi_base(" --f2-+--+1234ab567", "poneyvif"));
// 	printf("%d\n", ft_atoi_base("  -12-+--+1234ab567", "01"));
// 	printf("%d\n", ft_atoi_base("+-12345-+--+1234ab567", "01"));
// 	printf("%d\n", ft_atoi_base("+12345-+--+1234ab567", "01"));
// 	printf("%d\n", ft_atoi_base("-12345-+--+1234ab567", "01"));
// 	printf("%d\n", ft_atoi_base("21474836480", "poneyvif"));
// 	printf("%d\n", ft_atoi_base("-42", "0123456789"));
// 	return (0);
// }
