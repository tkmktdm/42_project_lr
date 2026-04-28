#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2);

static void	check(const char *label, int ok)
{
	printf("[%s] %s\n", ok ? "OK" : "NG", label);
}

int	main(void)
{
	char	*p;

	p = ft_strjoin("Hello, ", "World!");
	check("normal join", p && strcmp(p, "Hello, World!") == 0);
	free(p);

	p = ft_strjoin("", "World");
	check("empty s1", p && strcmp(p, "World") == 0);
	free(p);

	p = ft_strjoin("Hello", "");
	check("empty s2", p && strcmp(p, "Hello") == 0);
	free(p);

	p = ft_strjoin("", "");
	check("both empty", p && strcmp(p, "") == 0);
	free(p);

	p = ft_strjoin("abc", "def");
	check("null terminator", p && p[6] == '\0');
	free(p);

	check("NULL s1: NULL", ft_strjoin(NULL, "world") == NULL);
	check("NULL s2: NULL", ft_strjoin("hello", NULL) == NULL);

	return (0);
}
