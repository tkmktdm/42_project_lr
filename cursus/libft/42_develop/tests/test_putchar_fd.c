#include <stdio.h>

void	ft_putchar_fd(char c, int fd);

int	main(void)
{
	printf("--- ft_putchar_fd (stdout, visual check) ---\n");

	printf("expected: A  actual: ");
	ft_putchar_fd('A', 1);
	printf("\n");

	printf("expected: z  actual: ");
	ft_putchar_fd('z', 1);
	printf("\n");

	printf("expected: 0  actual: ");
	ft_putchar_fd('0', 1);
	printf("\n");

	printf("expected: (space)  actual: ");
	ft_putchar_fd(' ', 1);
	printf("\n");

	return (0);
}
