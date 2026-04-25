#include <stdio.h>
#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len);

static void	check(const char *label, int ok)
{
	printf("[%s] %s\n", ok ? "OK" : "NG", label);
}

int	main(void)
{
	char	dst[64];
	char	ref[64];

	/* 1. 通常コピー（重複なし） */
	memset(dst, 0, sizeof(dst));
	memset(ref, 0, sizeof(ref));
	ft_memmove(dst, "hello", 5);
	memmove(ref, "hello", 5);
	check("normal copy", memcmp(dst, ref, 5) == 0);

	/* 2. 戻り値が dst を指す */
	check("return value", ft_memmove(dst, "hi", 2) == (void *)dst);

	/* 3. len = 0 → 何もしない */
	memset(dst, 'A', sizeof(dst));
	memset(ref, 'A', sizeof(ref));
	ft_memmove(dst, "hello", 0);
	memmove(ref, "hello", 0);
	check("len=0", memcmp(dst, ref, sizeof(dst)) == 0);

	/* 4. dst == src → 何もしない */
	strcpy(dst, "hello");
	strcpy(ref, "hello");
	ft_memmove(dst, dst, 5);
	memmove(ref, ref, 5);
	check("dst==src", memcmp(dst, ref, 5) == 0);

	/* 5. 重複あり：dst が src より後ろ（後ろからコピーが必要） */
	strcpy(dst, "hello");
	strcpy(ref, "hello");
	ft_memmove(dst + 1, dst, 4);
	memmove(ref + 1, ref, 4);
	check("overlap dst>src", memcmp(dst, ref, 5) == 0);

	/* 6. 重複あり：dst が src より前（前からコピーで OK） */
	strcpy(dst, "hello");
	strcpy(ref, "hello");
	ft_memmove(dst, dst + 1, 4);
	memmove(ref, ref + 1, 4);
	check("overlap dst<src", memcmp(dst, ref, 5) == 0);

	/* 7. バイナリデータ */
	unsigned char	bin[8] = {0x00, 0xFF, 0x7F, 0x80, 0x01, 0x02, 0x03, 0x04};
	unsigned char	bin_ref[8];
	memcpy(bin_ref, bin, 8);
	ft_memmove(bin, bin + 2, 4);
	memmove(bin_ref, bin_ref + 2, 4);
	check("binary data", memcmp(bin, bin_ref, 8) == 0);

	return (0);
}
