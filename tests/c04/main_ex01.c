/* tests/c04/main_ex01.c — ft_putstr 動作テスト用 main */
#include <unistd.h>

void	ft_putstr(char *str);

int	main(void)
{
	ft_putstr("hello world");
	write(1, "\n", 1);
	ft_putstr("");
	write(1, "\n", 1);
	ft_putstr("a");
	write(1, "\n", 1);
	ft_putstr("Hello, 42!");
	write(1, "\n", 1);
	return (0);
}
