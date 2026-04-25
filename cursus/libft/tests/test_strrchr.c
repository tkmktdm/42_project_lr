#include <stdio.h>
#include <string.h>

char	*ft_strrchr(const char *s, int c);

static void	check(const char *label, char *got, char *exp)
{
	int	ok;

	ok = (got == exp);
	printf("[%s] %s\n", ok ? "OK" : "NG", label);
	if (!ok)
		printf("  got=%s exp=%s\n",
			got ? got : "(null)", exp ? exp : "(null)");
}

int	main(void)
{
	const char	*s;

	s = "hello world";

	/* 1. 最後の出現を返す */
	check("find last occurrence", ft_strrchr(s, 'l'), strrchr(s, 'l'));

	/* 2. 1つしかない文字 */
	check("single occurrence", ft_strrchr(s, 'h'), strrchr(s, 'h'));

	/* 3. 存在しない文字 → NULL */
	check("not found", ft_strrchr(s, 'z'), strrchr(s, 'z'));

	/* 4. '\0' を検索 → 末尾ポインタを返す */
	check("find null terminator", ft_strrchr(s, '\0'), strrchr(s, '\0'));

	/* 5. 空文字列で '\0' を検索 */
	check("empty str find null", ft_strrchr("", '\0'), strrchr("", '\0'));

	/* 6. 空文字列で文字を検索 → NULL */
	check("empty str not found", ft_strrchr("", 'a'), strrchr("", 'a'));

	/* 7. 全て同じ文字 → 最後のものを返す */
	check("all same char", ft_strrchr("aaaa", 'a'), strrchr("aaaa", 'a'));

	/* 8. 末尾の文字を検索 */
	check("find end char", ft_strrchr("abcde", 'e'), strrchr("abcde", 'e'));

	return (0);
}
