#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char	*ft_strdup(const char *s);

static void	check(const char *label, int ok)
{
	printf("[%s] %s\n", ok ? "OK" : "NG", label);
}

int	main(void)
{
	char	*p;

	/* 1. 通常の文字列 */
	p = ft_strdup("hello");
	check("normal string content", p && strcmp(p, "hello") == 0);
	check("normal string not null", p != NULL);
	free(p);

	/* 2. 空文字列 */
	p = ft_strdup("");
	check("empty string", p && strcmp(p, "") == 0);
	free(p);

	/* 3. 1文字 */
	p = ft_strdup("a");
	check("single char", p && strcmp(p, "a") == 0);
	free(p);

	/* 4. ヌル終端が正しく入っている */
	p = ft_strdup("hi");
	check("null terminated", p && p[2] == '\0');
	free(p);

	/* 5. 元の文字列を変更してもコピーに影響しない */
	char	src[8];
	strcpy(src, "hello");
	p = ft_strdup(src);
	strcpy(src, "xxxxx");
	check("independent copy", p && strcmp(p, "hello") == 0);
	free(p);

	/* 6. 長い文字列 */
	p = ft_strdup("abcdefghijklmnopqrstuvwxyz");
	check("long string", p && strcmp(p, "abcdefghijklmnopqrstuvwxyz") == 0);
	free(p);

	return (0);
}
