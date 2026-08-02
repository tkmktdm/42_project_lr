/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujikaw <tfujikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 01:08:55 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/05/10 19:29:51 by tfujikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	check_c(char const s, char c)
{
	return (s == c);
}

static int	check_word(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && check_c(s[i], c))
			i++;
		if (s[i] && !check_c(s[i], c))
		{
			count++;
			while (s[i] && !check_c(s[i], c))
				i++;
		}
	}
	return (count);
}

static void	*free_split(char **s, int j)
{
	while (j >= 0)
	{
		free(s[j]);
		j--;
	}
	free(s);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char			**split_word;
	int				i;
	int				j;
	unsigned int	start;

	split_word = (char **)malloc(sizeof(char *) * (check_word(s, c) + 1));
	if (!split_word)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && check_c(s[i], c))
			i++;
		if (s[i])
		{
			start = i;
			while (s[i] && !check_c(s[i], c))
				i++;
			split_word[j++] = ft_substr(s, start, i - start);
			if (!split_word[j - 1])
				return (free_split(split_word, j - 2));
		}
	}
	return (split_word[j] = NULL, split_word);
}
/*
void	print_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
	{
		printf("(null tab)\n");
		return ;
	}
	while (tab[i] != NULL)
	{
		printf("tab[%d]: [%s]\n", i, tab[i]);
		i++;
	}
	printf("tab[%d]: NULL\n", i);
}

int	main(void)
{
	char	**result;

	printf("--- Test 1: Normal ---\n");
	result = ft_split("sssssassbsscsssss", 's');
	print_tab(result);
	printf("\n--- Test 2: Multi separators ---\n");
	result = ft_split("   VEE VdyvTHjLJjDcebtGm07NKcPIWvKOTe  Di", 'D');
	print_tab(result);
	printf("\n--- Test 3: Only separators ---\n");
	result = ft_split("!!!!!", '!');
	print_tab(result);
	printf("\n--- Test 4: Empty string ---\n");
	result = ft_split("", 'a');
	print_tab(result);
	return (0);
}
*/
