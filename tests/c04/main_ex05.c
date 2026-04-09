#include <stdio.h>

int	ft_atoi_base(char *str, char *base);

static void	test_basic(void)
{
	printf("%d\n", ft_atoi_base("0", "0123456789"));
	printf("%d\n", ft_atoi_base("42", "0123456789"));
	printf("%d\n", ft_atoi_base("2147483647", "0123456789"));
	printf("%d\n", ft_atoi_base("1010", "01"));
	printf("%d\n", ft_atoi_base("1000", "01"));
	printf("%d\n", ft_atoi_base("ff", "0123456789abcdef"));
	printf("%d\n", ft_atoi_base("FF", "0123456789ABCDEF"));
	printf("%d\n", ft_atoi_base("1a", "0123456789abcdef"));
	printf("%d\n", ft_atoi_base("on", "poneyvif"));
	printf("%d\n", ft_atoi_base("oyy", "poneyvif"));
}

static void	test_sign(void)
{
	printf("%d\n", ft_atoi_base("-42", "0123456789"));
	printf("%d\n", ft_atoi_base("+42", "0123456789"));
	printf("%d\n", ft_atoi_base("--42", "0123456789"));
	printf("%d\n", ft_atoi_base("---42", "0123456789"));
	printf("%d\n", ft_atoi_base("-+42", "0123456789"));
	printf("%d\n", ft_atoi_base("  42", "0123456789"));
	printf("%d\n", ft_atoi_base("\t42", "0123456789"));
	printf("%d\n", ft_atoi_base("  -42", "0123456789"));
	printf("%d\n", ft_atoi_base("42abc", "0123456789"));
	printf("%d\n", ft_atoi_base("1010xyz", "01"));
}

static void	test_invalid(void)
{
	printf("%d\n", ft_atoi_base("42", "+0123456789"));
	printf("%d\n", ft_atoi_base("42", "-0123456789"));
	printf("%d\n", ft_atoi_base("42", "0"));
	printf("%d\n", ft_atoi_base("42", ""));
	printf("%d\n", ft_atoi_base("42", "001"));
	printf("%d\n", ft_atoi_base("42", "0 1"));
	printf("%d\n", ft_atoi_base("42", "0\t1"));
}

int	main(void)
{
	test_basic();
	test_sign();
	test_invalid();
	return (0);
}
