/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:18:11 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/06 22:42:06 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include <stdlib.h>

int	is_sep(char c, char *charset)
{
	while (*charset)
	{
		if (*charset == c)
			return (1);
		charset++;
	}
	return (0);
}

int	count_words(char *str, char *charset)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (is_sep(*str, charset))
			in_word = 0;
		else if (in_word == 0)
		{
			in_word = 1;
			count++;
		}
		str++;
	}
	return (count);
}

char	*get_word(char *str, char *charset)
{
	char	*copy;
	char	*temp;
	int		len;

	len = 0;
	while (str[len] && !is_sep(str[len], charset))
		len++;
	copy = malloc(len + 1);
	if (!copy)
		return (NULL);
	temp = copy;
	while (len-- > 0)
		*temp++ = *str++;
	*temp = '\0';
	return (copy);
}

char	**ft_split(char *str, char *charset)
{
	char	**words;
	int		count;
	int		i;

	i = 0;
	count = count_words(str, charset);
	words = malloc(sizeof(char *) * (count + 1));
	if (!words)
		return (NULL);
	while (*str)
	{
		while (*str && is_sep(*str, charset))
			str++;
		if (!*str)
			break ;
		words[i] = get_word(str, charset);
		if (!words[i])
			return (NULL);
		while (*str && !is_sep(*str, charset))
			str++;
		i++;
	}
	words[count] = NULL;
	return (words);
}

// int	main(void)
// {
// 	char	**ans;
// 	int		i;

// 	i = 0;
// 	ans = ft_split("malloc.IS!C!,A........N'T?split!!fin", "T.,!?'");
// 	i = 0;
// 	while (ans[i] != NULL)
// 	{
// 		printf("%d:%s\n", i + 1, ans[i]);
// 		free(ans[i]);
// 		i++;
// 	}
// 	free(ans);
// 	return (0);
// }
