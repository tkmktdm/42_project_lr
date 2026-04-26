#include <stdio.h>
#include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len);

static void	check_ptr(const char *label, char *got, char *exp)
{
	int	ok;

	ok = (got == exp);
	printf("[%s] %s\n", ok ? "OK" : "NG", label);
	if (!ok)
		printf("  got=%s exp=%s\n",
			got ? got : "(null)", exp ? exp : "(null)");
}

static void	check_null(const char *label, char *got)
{
	printf("[%s] %s\n", got == NULL ? "OK" : "NG", label);
	if (got != NULL)
		printf("  got=%s exp=(null)\n", got);
}

int	main(void)
{
	const char	*big;

	big = "hello world";

	/* 1. 通常の検索（見つかる） → "world" の先頭ポインタ */
	check_ptr("normal found",
		ft_strnstr(big, "world", 11), (char *)(big + 6));

	/* 2. 先頭から一致 */
	check_ptr("match at start",
		ft_strnstr(big, "hello", 11), (char *)big);

	/* 3. 中間で一致 */
	check_ptr("match middle",
		ft_strnstr(big, "ello", 11), (char *)(big + 1));

	/* 4. 見つからない → NULL */
	check_null("not found", ft_strnstr(big, "xyz", 11));

	/* 5. little が空文字列 → big を返す */
	check_ptr("empty little",
		ft_strnstr(big, "", 11), (char *)big);

	/* 6. len = 0 → NULL */
	check_null("len=0", ft_strnstr(big, "hello", 0));

	/* 7. len が一致箇所の手前で切れる → NULL */
	check_null("len cuts before match", ft_strnstr(big, "world", 9));

	/* 8. len がぴったり末尾まで → 見つかる */
	check_ptr("len exact match",
		ft_strnstr(big, "world", 11), (char *)(big + 6));

	/* 9. little が big と同じ */
	check_ptr("same string",
		ft_strnstr("abc", "abc", 3), (char *)"abc");

	/* 10. little が big より長い → NULL */
	check_null("little longer", ft_strnstr("ab", "abc", 2));

	return (0);
}
