#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

static void	check(const char *label, int ok)
{
	printf("[%s] %s\n", ok ? "OK" : "NG", label);
}

static char	to_upper(unsigned int i, char c)
{
	(void)i;
	return ((char)toupper((unsigned char)c));
}

static char	even_upper(unsigned int i, char c)
{
	if (i % 2 == 0)
		return ((char)toupper((unsigned char)c));
	return (c);
}

int	main(void)
{
	char	*p;

	p = ft_strmapi("hello", to_upper);
	check("all uppercase: HELLO", p && strcmp(p, "HELLO") == 0);
	free(p);

	p = ft_strmapi("hello", even_upper);
	check("even indices upper: HeLlO", p && strcmp(p, "HeLlO") == 0);
	free(p);

	p = ft_strmapi("", to_upper);
	check("empty string: empty", p && strcmp(p, "") == 0);
	free(p);

	p = ft_strmapi("a", to_upper);
	check("single char: A", p && strcmp(p, "A") == 0);
	free(p);

	return (0);
}
