#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char	**ft_split(char const *s, char c);

static void	check(const char *label, int ok)
{
	printf("[%s] %s\n", ok ? "OK" : "NG", label);
}

static void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	main(void)
{
	char	**res;

	res = ft_split("hello world foo", ' ');
	check("3 words [0]='hello'", res && strcmp(res[0], "hello") == 0);
	check("3 words [1]='world'", res && strcmp(res[1], "world") == 0);
	check("3 words [2]='foo'",   res && strcmp(res[2], "foo") == 0);
	check("3 words [3]=NULL",    res && res[3] == NULL);
	free_split(res);

	res = ft_split("  hello  ", ' ');
	check("multiple separators: 1 word", res && strcmp(res[0], "hello") == 0 && res[1] == NULL);
	free_split(res);

	res = ft_split("", ',');
	check("empty string: empty array", res && res[0] == NULL);
	free_split(res);

	res = ft_split("hello", ',');
	check("no separator: 1 word", res && strcmp(res[0], "hello") == 0 && res[1] == NULL);
	free_split(res);

	res = ft_split(",,,", ',');
	check("all separators: empty array", res && res[0] == NULL);
	free_split(res);

	res = ft_split("a,b,c", ',');
	check("single chars", res && strcmp(res[0], "a") == 0
		&& strcmp(res[1], "b") == 0 && strcmp(res[2], "c") == 0);
	free_split(res);

	check("NULL: NULL", ft_split(NULL, ',') == NULL);

	return (0);
}
