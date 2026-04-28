#include <stdio.h>

void	ft_putstr_fd(char *s, int fd);

int	main(void)
{
	printf("--- ft_putstr_fd (stdout, visual check) ---\n");

	printf("expected: hello  actual: ");
	ft_putstr_fd("hello", 1);
	printf("\n");

	printf("expected: (empty)  actual: [");
	ft_putstr_fd("", 1);
	printf("]\n");

	printf("expected: Hello, World!  actual: ");
	ft_putstr_fd("Hello, World!", 1);
	printf("\n");

	return (0);
}
