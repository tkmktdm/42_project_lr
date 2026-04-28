#include <stdio.h>

void	ft_putendl_fd(char *s, int fd);

int	main(void)
{
	printf("--- ft_putendl_fd (stdout, visual check, includes newline) ---\n");

	printf("expected: hello + newline\nactual:   ");
	ft_putendl_fd("hello", 1);

	printf("expected: (empty) + newline\nactual:   ");
	ft_putendl_fd("", 1);

	printf("expected: abc + newline\nactual:   ");
	ft_putendl_fd("abc", 1);

	return (0);
}
