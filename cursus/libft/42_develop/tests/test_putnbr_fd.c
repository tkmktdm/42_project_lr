#include <stdio.h>
#include <limits.h>

void	ft_putnbr_fd(int n, int fd);

int	main(void)
{
	printf("--- ft_putnbr_fd (stdout, visual check) ---\n");

	printf("expected: 42           actual: ");
	ft_putnbr_fd(42, 1);
	printf("\n");

	printf("expected: -42          actual: ");
	ft_putnbr_fd(-42, 1);
	printf("\n");

	printf("expected: 0            actual: ");
	ft_putnbr_fd(0, 1);
	printf("\n");

	printf("expected: 2147483647   actual: ");
	ft_putnbr_fd(INT_MAX, 1);
	printf("\n");

	printf("expected: -2147483648  actual: ");
	ft_putnbr_fd(INT_MIN, 1);
	printf("\n");

	printf("expected: 1000000      actual: ");
	ft_putnbr_fd(1000000, 1);
	printf("\n");

	return (0);
}
