#include <stdio.h>
#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n);

static void	check(const char *label, int ok)
{
	printf("[%s] %s\n", ok ? "OK" : "NG", label);
}

int	main(void)
{
	char	dst[64];
	char	src[64];
	char	ref[64];

	/* 1. 通常コピー */
	memset(dst, 0, sizeof(dst));
	memset(ref, 0, sizeof(ref));
	ft_memcpy(dst, "hello", 5);
	memcpy(ref, "hello", 5);
	check("normal copy", memcmp(dst, ref, 5) == 0);

	/* 2. n バイトだけコピー（残りは変更しない） */
	memset(dst, 'X', sizeof(dst));
	memset(ref, 'X', sizeof(ref));
	ft_memcpy(dst, "hello", 3);
	memcpy(ref, "hello", 3);
	check("partial copy", memcmp(dst, ref, sizeof(dst)) == 0);

	/* 3. n = 0 → 何もしない */
	memset(dst, 'A', sizeof(dst));
	memset(ref, 'A', sizeof(ref));
	ft_memcpy(dst, "hello", 0);
	memcpy(ref, "hello", 0);
	check("n=0 no write", memcmp(dst, ref, sizeof(dst)) == 0);

	/* 4. バイナリデータのコピー */
	unsigned char	bin_src[4] = {0x00, 0xFF, 0x7F, 0x80};
	unsigned char	bin_dst[4];
	unsigned char	bin_ref[4];
	ft_memcpy(bin_dst, bin_src, 4);
	memcpy(bin_ref, bin_src, 4);
	check("binary copy", memcmp(bin_dst, bin_ref, 4) == 0);

	/* 5. 戻り値が dest を指す */
	memset(dst, 0, sizeof(dst));
	check("return value", ft_memcpy(dst, "hi", 2) == (void *)dst);

	/* 6. 1バイトコピー */
	memset(dst, 0, sizeof(dst));
	memset(ref, 0, sizeof(ref));
	ft_memcpy(dst, "Z", 1);
	memcpy(ref, "Z", 1);
	check("1 byte copy", memcmp(dst, ref, 1) == 0);

	/* 7. 長いデータのコピー */
	memset(src, 'z', sizeof(src));
	memset(dst, 0, sizeof(dst));
	memset(ref, 0, sizeof(ref));
	ft_memcpy(dst, src, sizeof(src));
	memcpy(ref, src, sizeof(src));
	check("full buffer copy", memcmp(dst, ref, sizeof(dst)) == 0);

	return (0);
}
