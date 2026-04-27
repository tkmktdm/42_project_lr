#include <stdio.h>
#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size);

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

	/* 1. 通常結合 (size が十分大きい) */
	memset(dst, 0, sizeof(dst));
	strcpy(dst, "hello");
	ret = ft_strlcat(dst, " world", 20);
	check("normal concat", ret, 11, dst, "hello world");

	/* 2. 切り詰め (size が途中まで) */
	memset(dst, 0, sizeof(dst));
	strcpy(dst, "hello");
	ret = ft_strlcat(dst, " world", 8);
	check("truncate concat", ret, 11, dst, "hello w");

	/* 3. size == dstlen → 何も追記しない */
	memset(dst, 0, sizeof(dst));
	strcpy(dst, "hello");
	ret = ft_strlcat(dst, " world", 5);
	check("size==dstlen no append", ret, 11, dst, "hello");

	/* 4. size < dstlen → 何も追記しない、戻り値 = size + srclen */
	memset(dst, 0, sizeof(dst));
	strcpy(dst, "hello");
	ret = ft_strlcat(dst, " world", 3);
	check("size<dstlen no append", ret, 9, dst, "hello");

	/* 5. size = 0 → 何もしない、戻り値 = 0 + srclen */
	memset(dst, 0, sizeof(dst));
	strcpy(dst, "hello");
	ret = ft_strlcat(dst, " world", 0);
	check("size=0", ret, 6, dst, "hello");

	/* 6. dst が空文字列 */
	memset(dst, 0, sizeof(dst));
	ret = ft_strlcat(dst, "hello", 10);
	check("empty dst", ret, 5, dst, "hello");

	/* 7. src が空文字列 */
	memset(dst, 0, sizeof(dst));
	strcpy(dst, "hello");
	ret = ft_strlcat(dst, "", 10);
	check("empty src", ret, 5, dst, "hello");

	/* 8. dst・src 両方空文字列 */
	memset(dst, 0, sizeof(dst));
	ret = ft_strlcat(dst, "", 10);
	check("both empty", ret, 0, dst, "");

	/* 9. size = dstlen + 1 → src の1文字だけ追記してヌル終端 */
	memset(dst, 0, sizeof(dst));
	strcpy(dst, "hi");
	ret = ft_strlcat(dst, "bye", 4);
	check("append 1 char only", ret, 5, dst, "hib");

	/* 10. 戻り値は dstlen + srclen (切り詰め時も) */
	memset(dst, 0, sizeof(dst));
	strcpy(dst, "abc");
	ret = ft_strlcat(dst, "defghij", 6);
	check("return is dstlen+srclen", ret, 10, dst, "abcde");

	return (0);
}
