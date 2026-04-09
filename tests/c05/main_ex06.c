#include <stdio.h>

int	ft_is_prime(int nb);

int	main(void)
{
	printf("%d\n", ft_is_prime(-1));
	printf("%d\n", ft_is_prime(0));
	printf("%d\n", ft_is_prime(1));
	printf("%d\n", ft_is_prime(2));
	printf("%d\n", ft_is_prime(3));
	printf("%d\n", ft_is_prime(4));
	printf("%d\n", ft_is_prime(11));
	printf("%d\n", ft_is_prime(15));
	printf("%d\n", ft_is_prime(71));
	return (0);
}
