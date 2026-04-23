/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkariya <kkariya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 18:52:29 by kkariya           #+#    #+#             */
/*   Updated: 2026/04/04 17:06:35 by kkariya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	is_separator(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	get_count(char *str, char *charset)
{
	int	word_count;
	int	i;

	i = 0;
	word_count = 0;
	while (str[i] != '\0')
	{
		if (!is_separator(str[i], charset)
			&& (i == 0 || is_separator(str[i - 1], charset)))
			word_count++;
		i++;
	}
	return (word_count);
}

int	*get_word_size(char *str, char *charset)
{
	int	index;
	int	i;
	int	word_count;
	int	*word_size;

	i = 0;
	word_count = get_count(str, charset);
	word_size = malloc(sizeof(int) * word_count);
	while (i < word_count)
	{
		word_size[i] = 0;
		i++;
	}
	i = 0;
	index = 0;
	while (str[i] != '\0')
	{
		if (!is_separator(str[i], charset))
			word_size[index]++;
		else if (i > 0 && !is_separator(str[i - 1], charset))
			index++;
		i++;
	}
	return (word_size);
}

static void	fill_words(char **words, char *str, char *charset, int *word_size)
{
	int	index;
	int	i;
	int	j;
	int	is_new_word;

	index = 0;
	j = 0;
	i = -1;
	while (str[++i] != '\0')
	{
		if (!is_separator(str[i], charset))
		{
			is_new_word = (i == 0 || is_separator(str[i - 1], charset));
			if (is_new_word)
				words[index] = malloc(sizeof(char) * (word_size[index] + 1));
			words[index][j] = str[i];
			words[index][++j] = '\0';
		}
		else if (i > 0 && !is_separator(str[i - 1], charset) && ++index)
			j = 0;
	}
}

char	**ft_split(char *str, char *charset)
{
	char	**words;
	int		*word_size;

	words = malloc(sizeof(char *) * (get_count(str, charset) + 1));
	word_size = get_word_size(str, charset);
	fill_words(words, str, charset, word_size);
	words[get_count(str, charset)] = 0;
	free(word_size);
	return (words);
}

// #include <stdio.h>
// int	main(int argc, char **argv)
// {
// 	if (argc == 1)
// 		return (0);
// 	char **ans = ft_split(argv[1], argv[2]);
// 	for(int i = 0; i < get_count(argv[1], argv[2]); i++)
// 	{
// 		printf("%d:%s\n", i+1, ans[i]);
// 	}
// }
