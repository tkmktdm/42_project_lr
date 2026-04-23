/* tests/c04/main_ex00.c — ft_strlen 動作テスト用 main */
#include <stdio.h>

int		ft_strlen(char *str);

int	main(void)
{
	printf("%d\n", ft_strlen("Hello"));
	printf("%d\n", ft_strlen(""));
	printf("%d\n", ft_strlen("a"));
	printf("%d\n", ft_strlen("Hello, World!"));
	printf("%d\n", ft_strlen("abc"));
	return (0);
}
