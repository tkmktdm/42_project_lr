#include <stdio.h>

int	ft_recursive_power(int nb, int power);

int	main(void)
{
	printf("%d\n", ft_recursive_power(5, 0));
	printf("%d\n", ft_recursive_power(5, 1));
	printf("%d\n", ft_recursive_power(5, 2));
	printf("%d\n", ft_recursive_power(5, 3));
	printf("%d\n", ft_recursive_power(2, 10));
	printf("%d\n", ft_recursive_power(0, 0));
	printf("%d\n", ft_recursive_power(5, -1));
	printf("%d\n", ft_recursive_power(-3, 2));
	return (0);
}
