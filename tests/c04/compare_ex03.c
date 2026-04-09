/* tests/c04/compare_ex03.c — ft_atoi vs atoi 比較テスト */
#include <stdlib.h>
#include <stdio.h>

int		ft_atoi(char *str);

static int	cmp(char *input, char *label)
{
	int		ft;
	int		std;

	ft = ft_atoi(input);
	std = atoi(input);
	if (ft == std)
	{
		printf("[PASS] %-30s : atoi=%d, ft_atoi=%d\n", label, std, ft);
		return (1);
	}
	else
	{
		printf("[FAIL] %-30s : atoi=%d, ft_atoi=%d\n", label, std, ft);
		return (0);
	}
}

int	main(void)
{
	int	pass;
	int	total;

	pass = 0;
	total = 0;
	pass += cmp("42",                 "正の数");              total++;
	pass += cmp("-42",                "負の数");              total++;
	pass += cmp("+42",                "プラス符号");          total++;
	pass += cmp("   42",              "先頭スペース");        total++;
	pass += cmp("  -42",              "スペース+負");         total++;
	pass += cmp("0",                  "ゼロ");                total++;
	pass += cmp("1234ab567",          "途中に英字");         total++;
	pass += cmp("   42abc",           "スペース+英字終端");   total++;
	pass += cmp("2147483647",         "INT_MAX");             total++;
	pass += cmp("abc",                "非数字のみ");          total++;
	printf("\n%d/%d passed\n", pass, total);
	return (pass == total ? 0 : 1);
}
