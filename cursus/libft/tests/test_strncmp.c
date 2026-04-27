#include <stdio.h>
#include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n);

static void	check(const char *label, int got, int exp)
{
	int	ok;

	ok = ((got == 0 && exp == 0) || (got < 0 && exp < 0) || (got > 0 && exp > 0));
	printf("[%s] %s\n", ok ? "OK" : "NG", label);
	if (!ok)
		printf("  got=%d exp=%d\n", got, exp);
}

int	main(void)
{
	/* 1. 等しい文字列 */
	check("equal strings", ft_strncmp("abc", "abc", 3), strncmp("abc", "abc", 3));

	/* 2. s1 < s2 */
	check("s1 < s2", ft_strncmp("abc", "abd", 3), strncmp("abc", "abd", 3));

	/* 3. s1 > s2 */
	check("s1 > s2", ft_strncmp("abd", "abc", 3), strncmp("abd", "abc", 3));

	/* 4. n = 0 → 常に 0 */
	check("n=0", ft_strncmp("abc", "xyz", 0), strncmp("abc", "xyz", 0));

	/* 5. n が文字列長より小さい（先頭n文字が同じ） */
	check("n smaller than diff", ft_strncmp("abcX", "abcY", 3), strncmp("abcX", "abcY", 3));

	/* 6. n が文字列長より小さい（先頭n文字で差がある） */
	check("n smaller diff found", ft_strncmp("aXc", "aYc", 2), strncmp("aXc", "aYc", 2));

	/* 7. 長さが違う文字列（s1が短い） */
	check("s1 shorter", ft_strncmp("ab", "abc", 3), strncmp("ab", "abc", 3));

	/* 8. 長さが違う文字列（s2が短い） */
	check("s2 shorter", ft_strncmp("abc", "ab", 3), strncmp("abc", "ab", 3));

	/* 9. 空文字列同士 */
	check("both empty", ft_strncmp("", "", 1), strncmp("", "", 1));

	/* 10. unsigned char として比較（\x80 vs \x01） */
	check("unsigned char cmp", ft_strncmp("\x80", "\x01", 1), strncmp("\x80", "\x01", 1));

	return (0);
}
