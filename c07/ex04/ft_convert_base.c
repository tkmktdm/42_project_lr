/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 11:52:05 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/06 13:06:41 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include <stdlib.h>

int		base_check(char *base);
int		digit_count(long n, int base_len);
char	*convert(char *nbr, char *base_from, char *base_to);
int		has_dup(char *base);
int		char_index(char c, char *base);
char	*skip_prefix(char *str, int *mflg);

int	ft_atoi_base(char *str, char *base)
{
	long	n;
	int		nx;
	int		mflg;

	n = 0;
	mflg = 0;
	nx = base_check(base);
	if (!nx)
		return (0);
	str = skip_prefix(str, &mflg);
	while (char_index(*str, base) != -1)
	{
		n = n * nx + char_index(*str, base);
		str++;
	}
	if (mflg % 2 == 1)
		n = -n;
	return ((int)n);
}

char	*ft_itoa_base(int nbr, char *base)
{
	int		i;
	int		nx;
	char	*str;
	char	*temp;

	nx = base_check(base);
	if (!nx)
		return (NULL);
	i = digit_count(nbr, nx);
	str = malloc(sizeof(char) * i + 1);
	temp = str;
	temp[i] = '\0';
	if (nbr < 0)
	{
		nbr *= -1;
		temp[0] = '-';
	}
	if (nbr == 0)
		temp[0] = base[0];
	while (nbr > 0)
	{
		temp[--i] = base[nbr % nx];
		nbr /= nx;
	}
	return (str);
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	int		n1;
	int		n2;
	char	*str;

	n1 = base_check(base_from);
	n2 = base_check(base_to);
	if (!n1 || !n2)
		return (0);
	str = convert(nbr, base_from, base_to);
	return (str);
}

char	*convert(char *nbr, char *base_from, char *base_to)
{
	int		bf;
	char	*bt;

	bf = ft_atoi_base(nbr, base_from);
	bt = ft_itoa_base(bf, base_to);
	return (bt);
}

// int	main(void)
// {
// 	printf("### 10 ~ 16進数に変換 ###\n");
// 	printf("%s\n", ft_convert_base("0", "0123456789", "0123456789ABCDEF"));
// 	printf("%s\n", ft_convert_base("15", "0123456789", "0123456789ABCDEF"));
// 	printf("%s\n", ft_convert_base("+15", "0123456789", "0123456789ABCDEF"));
// 	printf("%s\n", ft_convert_base("-15", "0123456789", "0123456789ABCDEF"));
// 	printf("%s\n", ft_convert_base("++--15", "0123456789", "0123456789ABCDEF"));
// 	printf("%s\n", ft_convert_base(" -1b5", "0123456789", "0123456789ABCDEF"));
// 	printf("### 16 ~ 10進数に変換 ###\n");
// 	printf("%s\n", ft_convert_base("0", "0123456789ABCDEF", "0123456789"));
// 	printf("%s\n", ft_convert_base("15", "0123456789ABCDEF", "0123456789"));
// 	printf("%s\n", ft_convert_base("+15", "0123456789ABCDEF", "0123456789"));
// 	printf("%s\n", ft_convert_base("-15", "0123456789ABCDEF", "0123456789"));
// 	printf("%s\n", ft_convert_base("++--15", "0123456789ABCDEF", "0123456789"));
// 	printf("%s\n", ft_convert_base(" -1b5", "0123456789ABCDEF", "0123456789"));
// 	printf("### 無効test ###\n");
// 	printf("%s\n", ft_convert_base(" -1b5", "aaaaaaa", "ccccccc"));
// 	printf("%s\n", ft_convert_base(" -15", "15", "ccccccc"));
// 	printf("%s\n", ft_convert_base(" -a15", "15", "ccccccc"));
// 	return (0);
// }
