/* tests/c04/compare_ex00.c — ft_strlen vs strlen 比較テスト */
#include <string.h>
#include <stdio.h>

int		ft_strlen(char *str);

static int	cmp(char *input, char *label)
{
	int		ft;
	int		std;

	ft = ft_strlen(input);
	std = (int)strlen(input);
	if (ft == std)
	{
		printf("[PASS] %-20s : strlen=%d, ft_strlen=%d\n", label, std, ft);
		return (1);
	}
	else
	{
		printf("[FAIL] %-20s : strlen=%d, ft_strlen=%d\n", label, std, ft);
		return (0);
	}
}

int	main(void)
{
	int	pass;
	int	total;

	pass = 0;
	total = 0;
	pass += cmp("Hello",          "通常文字列");       total++;
	pass += cmp("",               "空文字列");         total++;
	pass += cmp("a",              "1文字");            total++;
	pass += cmp("Hello, World!",  "記号含む");         total++;
	pass += cmp("abc\0def",       "NULL文字含む");     total++;
	pass += cmp("   spaces   ",   "スペース含む");     total++;
	printf("\n%d/%d passed\n", pass, total);
	return (pass == total ? 0 : 1);
}
