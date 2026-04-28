#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char	*ft_strtrim(char const *s1, char const *set);

static void	check(const char *label, int ok)
{
	printf("[%s] %s\n", ok ? "OK" : "NG", label);
}

int	main(void)
{
	char	*p;

	p = ft_strtrim("  hello  ", " ");
	check("trim spaces", p && strcmp(p, "hello") == 0);
	free(p);

	p = ft_strtrim("xxhelloxx", "x");
	check("trim x", p && strcmp(p, "hello") == 0);
	free(p);

	p = ft_strtrim("abcHELLOcba", "abc");
	check("trim multi chars in set", p && strcmp(p, "HELLO") == 0);
	free(p);

	p = ft_strtrim("hello", "");
	check("empty set: unchanged", p && strcmp(p, "hello") == 0);
	free(p);

	p = ft_strtrim("xxxx", "x");
	check("all trimmed: empty string", p && strcmp(p, "") == 0);
	free(p);

	p = ft_strtrim("hello", "xyz");
	check("no match: unchanged", p && strcmp(p, "hello") == 0);
	free(p);

	p = ft_strtrim(" hello world ", " ");
	check("only front/back trimmed", p && strcmp(p, "hello world") == 0);
	free(p);

	check("NULL s1: NULL", ft_strtrim(NULL, " ") == NULL);

	return (0);
}
