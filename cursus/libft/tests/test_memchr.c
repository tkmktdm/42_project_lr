#include <stdio.h>
#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n);

static void	check(const char *label, void *got, void *exp)
{
	int	ok;

	ok = (got == exp);
	printf("[%s] %s\n", ok ? "OK" : "NG", label);
	if (!ok)
		printf("  got=%p exp=%p\n", got, exp);
}

int	main(void)
{
	const char	*s = "hello world";

	/* 1. 通常の検索 */
	check("find char", ft_memchr(s, 'o', 11), memchr(s, 'o', 11));

	/* 2. 先頭の文字を検索 */
	check("find first", ft_memchr(s, 'h', 11), memchr(s, 'h', 11));

	/* 3. 末尾の文字を検索 */
	check("find last", ft_memchr(s, 'd', 11), memchr(s, 'd', 11));

	/* 4. 存在しない文字 → NULL */
	check("not found", ft_memchr(s, 'z', 11), memchr(s, 'z', 11));

	/* 5. n = 0 → NULL */
	check("n=0", ft_memchr(s, 'h', 0), memchr(s, 'h', 0));

	/* 6. '\0' バイトを検索（文字列の途中に '\0' がある場合） */
	const char	bin[] = {0x01, 0x00, 0x02};
	check("find null byte", ft_memchr(bin, 0x00, 3), memchr(bin, 0x00, 3));

	/* 7. n が文字列長より小さい（見つかる前に終わる） */
	check("n too small", ft_memchr(s, 'o', 4), memchr(s, 'o', 4));

	/* 8. 0xFF などの高値バイトを検索 */
	const unsigned char	hi[] = {0x7F, 0xFF, 0x80};
	check("high byte", ft_memchr(hi, 0xFF, 3), memchr(hi, 0xFF, 3));

	return (0);
}
