/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_if.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:16:58 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/09 20:15:50 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_count_if(char **tab, int length, int (*f)(char *))
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < length)
	{
		if (f(tab[i]))
			count++;
		i++;
	}
	return (count);
}

// #include <stdio.h>

// static char	*g_empty[] = {NULL};
// static char	*g_short[] = {"hi", "yo", NULL};
// static char	*g_long[] = {"hello", "world", NULL};
// static char	*g_mix[] = {"hi", "hello", "yo", "world", NULL};
// static char	*g_a_mix[] = {"apple", "banana", NULL};
// static char	*g_no_a[] = {"hi", "yo", NULL};
// static char	*g_all_a[] = {"ant", "ape", "arc", NULL};

// static int	is_long(char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i > 3);
// }

// static int	starts_a(char *s)
// {
// 	return (s[0] == 'a');
// }

// static int	check(char *label, int got, int expected)
// {
// 	int	ok;

// 	ok = (got == expected);
// 	if (ok)
// 		printf("[OK] %s (got %d, expected %d)\n", label, got, expected);
// 	else
// 		printf("[KO] %s (got %d, expected %d)\n", label, got, expected);
// 	return (ok);
// }

// int	main(void)
// {
// 	int	passed;

// 	passed = 0;
// 	passed += check("length=0", ft_count_if(g_short, 0, is_long), 0);
// 	passed += check("empty tab", ft_count_if(g_empty, 4, is_long), 0);
// 	passed += check("all short", ft_count_if(g_short, 2, is_long), 0);
// 	passed += check("all long", ft_count_if(g_long, 2, is_long), 2);
// 	passed += check("mix 4: 2 long", ft_count_if(g_mix, 4, is_long), 2);
// 	passed += check("mix length=1: 0 long", ft_count_if(g_mix, 1, is_long), 0);
// 	passed += check("a_mix starts_a", ft_count_if(g_a_mix, 2, starts_a), 1);
// 	passed += check("no_a starts_a", ft_count_if(g_no_a, 2, starts_a), 0);
// 	passed += check("all_a starts_a", ft_count_if(g_all_a, 3, starts_a), 3);
// 	printf("\n%d/9 passed\n", passed);
// 	return (0);
// }
