#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char	*ft_itoa(int n);

static void	check(const char *label, int ok)
{
	printf("[%s] %s\n", ok ? "OK" : "NG", label);
}

int	main(void)
{
	char	*p;

	p = ft_itoa(0);
	check("0", p && strcmp(p, "0") == 0);
	free(p);

	p = ft_itoa(42);
	check("42", p && strcmp(p, "42") == 0);
	free(p);

	p = ft_itoa(-42);
	check("-42", p && strcmp(p, "-42") == 0);
	free(p);

	p = ft_itoa(1000000);
	check("1000000", p && strcmp(p, "1000000") == 0);
	free(p);

	p = ft_itoa(-1);
	check("-1", p && strcmp(p, "-1") == 0);
	free(p);

	p = ft_itoa(INT_MAX);
	check("INT_MAX: 2147483647", p && strcmp(p, "2147483647") == 0);
	free(p);

	p = ft_itoa(INT_MIN);
	check("INT_MIN: -2147483648", p && strcmp(p, "-2147483648") == 0);
	free(p);

	return (0);
}
