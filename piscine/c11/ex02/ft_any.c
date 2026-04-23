/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_any.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 20:15:41 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/09 20:15:42 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_any(char **tab, int (*f)(char *))
{
	int	i;

	i = 0;
	while (tab[i] != 0)
	{
		if (f(tab[i]))
			return (1);
		i++;
	}
	return (0);
}

// #include <stdio.h>

// // テスト用の関数
// int	ft_strlen(char *c)
// {
// 	int	i;

// 	i = 0;
// 	while (*c)
// 	{
// 		c++;
// 		i++;
// 	}
// 	return (i);
// }

// int	is_long(char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i > 3);
// }
// int	starts_a(char *s)
// {
// 	return (s[0] == 'a');
// }

// // テストケース定義
// typedef struct
// {
// 	char	*name;
// 	char	**tab;
// 	int		(*f)(char *);
// 	int		expected;
// }			t_test;

// int	main(void)
// {
// 	char	*tab1[] = {"hi", "yo", NULL};
// 	char	*tab2[] = {"hello", "world", NULL};
// 	char	*tab3[] = {"apple", "banana", NULL};
// 	char	*tab4[] = {"hi", "yo", NULL};
// 	int		n;
// 	int		passed;
// 	int		result;
// 	int		ok;

// 	t_test tests[] = {
// 		{"短い文字列のみ", tab1, is_long, 0},
// 		{"長い文字列あり", tab2, is_long, 1},
// 		{"aで始まるものあり", tab3, starts_a, 1},
// 		{"aで始まるものなし", tab4, starts_a, 0},
// 	};
// 	n = sizeof(tests) / sizeof(tests[0]);
// 	passed = 0;
// 	for (int i = 0; i < n; i++)
// 	{
// 		result = ft_any(tests[i].tab, tests[i].f);
// 		ok = result == tests[i].expected;
// 		printf("[%s] %s (got %d, expected %d)\n", ok ? "OK" : "KO",
// 			tests[i].name, result, tests[i].expected);
// 		if (ok)
// 			passed++;
// 	}
// 	printf("\n%d/%d passed\n", passed, n);
// 	return (0);
// }
