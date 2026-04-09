/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_any.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 10:02:43 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/04/09 10:27:45 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ft_any(char **tab, int(*f)(char*)) {
    int i;
    i=0;
    while(tab[i] != 0) {
        if (f(tab[i]))
            return 1;
        i++;
    }
    return 0;
}

int	ft_strlen(char *c)
{
	int	i;

    i = 0;
    while(*c) {
        c++;
        i++;
    }
	return (i);
}


#include <stdio.h>
// テスト用の関数
int is_long(char *s)   { int i = 0; while(s[i]) i++; return i > 3; }
int starts_a(char *s)  { return s[0] == 'a'; }

// テストケース定義
typedef struct {
    char    *name;
    char    **tab;
    int     (*f)(char*);
    int     expected;
} t_test;

int main(void)
{
    char *tab1[] = {"hi", "yo", NULL};
    char *tab2[] = {"hello", "world", NULL};
    char *tab3[] = {"apple", "banana", NULL};
    char *tab4[] = {"hi", "yo", NULL};

    t_test tests[] = {
        {"短い文字列のみ",       tab1, is_long,  0},
        {"長い文字列あり",       tab2, is_long,  1},
        {"aで始まるものあり",    tab3, starts_a, 1},
        {"aで始まるものなし",    tab4, starts_a, 0},
    };

    int n = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;

    for (int i = 0; i < n; i++) {
        int result = ft_any(tests[i].tab, tests[i].f);
        int ok = result == tests[i].expected;
        printf("[%s] %s (got %d, expected %d)\n",
            ok ? "OK" : "KO",
            tests[i].name,
            result,
            tests[i].expected);
        if (ok) passed++;
    }
    printf("\n%d/%d passed\n", passed, n);
    return 0;
}