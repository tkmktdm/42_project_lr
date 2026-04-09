/* tests/c04/main_ex03.c — ft_atoi 動作テスト用 main */
#include <stdio.h>

int		ft_atoi(char *str);

int	main(void)
{
	/* PDF の実行例 */
	printf("%d\n", ft_atoi(" ---+--+1234ab567"));
	/* 基本 */
	printf("%d\n", ft_atoi("42"));
	printf("%d\n", ft_atoi("-42"));
	printf("%d\n", ft_atoi("+42"));
	/* 先頭スペース */
	printf("%d\n", ft_atoi("   100"));
	/* 先頭の符号複数 */
	printf("%d\n", ft_atoi("--42"));
	printf("%d\n", ft_atoi("---42"));
	/* 数字の後に文字 */
	printf("%d\n", ft_atoi("1234ab567"));
	/* 0 */
	printf("%d\n", ft_atoi("0"));
	/* 全部スペース or 非数字 */
	printf("%d\n", ft_atoi("abc"));
	return (0);
}
