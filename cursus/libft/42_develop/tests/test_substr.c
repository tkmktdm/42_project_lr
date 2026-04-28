#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len);

static void	check(const char *label, int ok)
{
	printf("[%s] %s\n", ok ? "OK" : "NG", label);
}

int	main(void)
{
	char	*p;

	p = ft_substr("Hello, World!", 7, 5);
	check("normal: 'World'", p && strcmp(p, "World") == 0);
	free(p);

	p = ft_substr("Hello", 10, 5);
	check("start out of range: empty string", p && strcmp(p, "") == 0);
	free(p);

	p = ft_substr("Hello", 0, 0);
	check("len=0: empty string", p && strcmp(p, "") == 0);
	free(p);

	p = ft_substr("Hello", 0, 100);
	check("len > strlen: full string", p && strcmp(p, "Hello") == 0);
	free(p);

	p = ft_substr("Hello", 2, 3);
	check("middle: 'llo'", p && strcmp(p, "llo") == 0);
	free(p);

	p = ft_substr("Hello", 0, 5);
	check("exact length", p && strcmp(p, "Hello") == 0);
	free(p);

	check("NULL input: NULL", ft_substr(NULL, 0, 5) == NULL);

	return (0);
}
