#include <stdio.h>
#include <string.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size);

static void	check(const char *label, size_t got_ret, size_t exp_ret,
		const char *got_dst, const char *exp_dst)
{
	int	ok;

	ok = (got_ret == exp_ret) && (strcmp(got_dst, exp_dst) == 0);
	printf("[%s] %s\n", ok ? "OK" : "NG", label);
	if (!ok)
	{
		printf("  ret  : got=%zu exp=%zu\n", got_ret, exp_ret);
		printf("  dst  : got=\"%s\" exp=\"%s\"\n", got_dst, exp_dst);
	}
}

int	main(void)
{
	char	dst[64];
	size_t	ret;

	/* 1. 通常コピー (size > srclen + 1) */
	memset(dst, 'X', sizeof(dst));
	ret = ft_strlcpy(dst, "hello", 10);
	check("normal copy", ret, 5, dst, "hello");

	/* 2. ちょうど収まるサイズ (size == srclen + 1) */
	memset(dst, 'X', sizeof(dst));
	ret = ft_strlcpy(dst, "hello", 6);
	check("exact fit", ret, 5, dst, "hello");

	/* 3. 切り詰め (size < srclen + 1) */
	memset(dst, 'X', sizeof(dst));
	ret = ft_strlcpy(dst, "hello", 3);
	check("truncate to 2 chars", ret, 5, dst, "he");

	/* 4. size = 1 → ヌル文字だけ書く */
	memset(dst, 'X', sizeof(dst));
	ret = ft_strlcpy(dst, "hello", 1);
	check("size=1 only null", ret, 5, dst, "");

	/* 5. size = 0 → dst変更なし、戻り値は srclen */
	memset(dst, 'X', sizeof(dst));
	dst[0] = '\0';
	ret = ft_strlcpy(dst, "hello", 0);
	check("size=0 no write", ret, 5, dst, "");

	/* 6. src が空文字列 */
	memset(dst, 'X', sizeof(dst));
	ret = ft_strlcpy(dst, "", 10);
	check("empty src", ret, 0, dst, "");

	/* 7. src が空・size = 0 */
	memset(dst, 'X', sizeof(dst));
	dst[0] = '\0';
	ret = ft_strlcpy(dst, "", 0);
	check("empty src size=0", ret, 0, dst, "");

	/* 8. 長い文字列の切り詰め */
	memset(dst, 'X', sizeof(dst));
	ret = ft_strlcpy(dst, "abcdefghij", 5);
	check("long src truncate", ret, 10, dst, "abcd");

	/* 9. 戻り値は常に srclen (切り詰め時も) */
	memset(dst, 'X', sizeof(dst));
	ret = ft_strlcpy(dst, "12345678", 4);
	check("return is always srclen", ret, 8, dst, "123");

	return (0);
}
