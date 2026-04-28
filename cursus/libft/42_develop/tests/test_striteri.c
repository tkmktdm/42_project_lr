#include <stdio.h>
#include <string.h>
#include <ctype.h>

void	ft_striteri(char *s, void (*f)(unsigned int, char *));

static void	check(const char *label, int ok)
{
	printf("[%s] %s\n", ok ? "OK" : "NG", label);
}

static void	to_upper_ptr(unsigned int i, char *c)
{
	(void)i;
	*c = (char)toupper((unsigned char)*c);
}

static void	even_upper_ptr(unsigned int i, char *c)
{
	if (i % 2 == 0)
		*c = (char)toupper((unsigned char)*c);
}

int	main(void)
{
	char	s1[] = "hello";
	char	s2[] = "hello";
	char	s3[] = "";

	ft_striteri(s1, to_upper_ptr);
	check("all uppercase: HELLO", strcmp(s1, "HELLO") == 0);

	ft_striteri(s2, even_upper_ptr);
	check("even indices upper: HeLlO", strcmp(s2, "HeLlO") == 0);

	ft_striteri(s3, to_upper_ptr);
	check("empty string: no change", strcmp(s3, "") == 0);

	return (0);
}
