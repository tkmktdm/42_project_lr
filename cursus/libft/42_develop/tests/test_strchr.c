#include <stdio.h>
#include <string.h>

char	*ft_strchr(const char *s, int c);

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

	/* 1. 先頭の文字を検索 */
	check("find first char", ft_strchr(s, 'h'), strchr(s, 'h'));

	/* 2. 中間の文字を検索 */
	check("find middle char", ft_strchr(s, 'o'), strchr(s, 'o'));

	/* 3. 末尾の文字を検索 */
	check("find last char", ft_strchr(s, 'd'), strchr(s, 'd'));

	/* 4. 存在しない文字 → NULL */
	check("not found", ft_strchr(s, 'z'), strchr(s, 'z'));

	/* 5. '\0' を検索 → 末尾ポインタを返す */
	check("find null terminator", ft_strchr(s, '\0'), strchr(s, '\0'));

	/* 6. 空文字列で '\0' を検索 */
	check("empty str find null", ft_strchr("", '\0'), strchr("", '\0'));

	/* 7. 空文字列で文字を検索 → NULL */
	check("empty str not found", ft_strchr("", 'a'), strchr("", 'a'));

	/* 8. 同じ文字が複数ある → 最初のものを返す */
	check("first occurrence", ft_strchr("abcabc", 'b'), strchr("abcabc", 'b'));

	return (0);
}
