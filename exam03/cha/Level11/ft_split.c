/* allowed functions: malloc */
#include <stdlib.h>

static int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static int	count_words(char *str)
{
	int	i;
	int	count;
	int	in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (str[i])
	{
		if (is_space(str[i]))
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static char	*dup_word(char *str, int start, int end)
{
	char	*word;
	int		i;

	word = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (0);
	i = 0;
	while (start < end)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char *str)
{
	char	**res;
	int		i;
	int		w;
	int		start;

	res = (char **)malloc(sizeof(char *) * (count_words(str) + 1));
	if (!res)
		return (0);
	i = 0;
	w = 0;
	while (str[i])
	{
		while (str[i] && is_space(str[i]))
			i++;
		if (!str[i])
			break ;
		start = i;
		while (str[i] && !is_space(str[i]))
			i++;
		res[w] = dup_word(str, start, i);
		if (!res[w])
			return (0);
		w++;
	}
	res[w] = 0;
	return (res);
}
