#include <stdio.h>
#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n);

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
	/* 1. 等しいメモリ */
	check("equal", ft_memcmp("abc", "abc", 3), memcmp("abc", "abc", 3));

	/* 2. s1 < s2 */
	check("s1 < s2", ft_memcmp("abc", "abd", 3), memcmp("abc", "abd", 3));

	/* 3. s1 > s2 */
	check("s1 > s2", ft_memcmp("abd", "abc", 3), memcmp("abd", "abc", 3));

	/* 4. n = 0 → 常に 0 */
	check("n=0", ft_memcmp("abc", "xyz", 0), memcmp("abc", "xyz", 0));

	/* 5. 途中に '\0' バイトがある（strncmpと異なり止まらない） */
	check("null byte mid",
		ft_memcmp("\x00\x01", "\x00\x02", 2),
		memcmp("\x00\x01", "\x00\x02", 2));

	/* 6. 両方 '\0' バイトから始まる（止まらず比較継続） */
	check("both start null",
		ft_memcmp("\x00\x00", "\x00\x00", 2),
		memcmp("\x00\x00", "\x00\x00", 2));

	/* 7. 高値バイト（0xFF など）の比較 */
	check("high byte",
		ft_memcmp("\xFF", "\x01", 1),
		memcmp("\xFF", "\x01", 1));

	/* 8. n が実際の差より小さい（差の前で止まる） */
	check("n before diff",
		ft_memcmp("abcX", "abcY", 3),
		memcmp("abcX", "abcY", 3));

	/* 9. 1バイトだけ比較 */
	check("1 byte equal", ft_memcmp("a", "a", 1), memcmp("a", "a", 1));
	check("1 byte diff", ft_memcmp("a", "b", 1), memcmp("a", "b", 1));

	return (0);
}
