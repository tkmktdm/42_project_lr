#include "test_helpers.h"
#include "libft.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static void	test_ft_isalpha(void)
{
	ASSERT_EQ_INT("isalpha 'A'", ft_isalpha('A'), 1);
	ASSERT_EQ_INT("isalpha 'Z'", ft_isalpha('Z'), 1);
	ASSERT_EQ_INT("isalpha 'a'", ft_isalpha('a'), 1);
	ASSERT_EQ_INT("isalpha 'z'", ft_isalpha('z'), 1);
	ASSERT_EQ_INT("isalpha '0'", ft_isalpha('0'), 0);
	ASSERT_EQ_INT("isalpha '@'", ft_isalpha('@'), 0);
	ASSERT_EQ_INT("isalpha ' '", ft_isalpha(' '), 0);
	ASSERT_EQ_INT("isalpha 0", ft_isalpha(0), 0);
	ASSERT_EQ_INT("isalpha 128", ft_isalpha(128), 0);
	ASSERT_EQ_INT("isalpha -1", ft_isalpha(-1), 0);
}

static void	test_ft_isdigit(void)
{
	ASSERT_EQ_INT("isdigit '0'", ft_isdigit('0'), 1);
	ASSERT_EQ_INT("isdigit '5'", ft_isdigit('5'), 1);
	ASSERT_EQ_INT("isdigit '9'", ft_isdigit('9'), 1);
	ASSERT_EQ_INT("isdigit 'a'", ft_isdigit('a'), 0);
	ASSERT_EQ_INT("isdigit 'A'", ft_isdigit('A'), 0);
	ASSERT_EQ_INT("isdigit ' '", ft_isdigit(' '), 0);
	ASSERT_EQ_INT("isdigit -1", ft_isdigit(-1), 0);
	ASSERT_EQ_INT("isdigit 128", ft_isdigit(128), 0);
}

static void	test_ft_isalnum(void)
{
	ASSERT_EQ_INT("isalnum 'a'", ft_isalnum('a'), 1);
	ASSERT_EQ_INT("isalnum 'Z'", ft_isalnum('Z'), 1);
	ASSERT_EQ_INT("isalnum '5'", ft_isalnum('5'), 1);
	ASSERT_EQ_INT("isalnum '_'", ft_isalnum('_'), 0);
	ASSERT_EQ_INT("isalnum '@'", ft_isalnum('@'), 0);
	ASSERT_EQ_INT("isalnum ' '", ft_isalnum(' '), 0);
	ASSERT_EQ_INT("isalnum 0", ft_isalnum(0), 0);
	ASSERT_EQ_INT("isalnum 128", ft_isalnum(128), 0);
}

static void	test_ft_isascii(void)
{
	ASSERT_EQ_INT("isascii 0", ft_isascii(0), 1);
	ASSERT_EQ_INT("isascii 127", ft_isascii(127), 1);
	ASSERT_EQ_INT("isascii 'A'", ft_isascii('A'), 1);
	ASSERT_EQ_INT("isascii 128", ft_isascii(128), 0);
	ASSERT_EQ_INT("isascii -1", ft_isascii(-1), 0);
	ASSERT_EQ_INT("isascii 256", ft_isascii(256), 0);
}

static void	test_ft_isprint(void)
{
	ASSERT_EQ_INT("isprint ' '", ft_isprint(' '), 1);
	ASSERT_EQ_INT("isprint '~'", ft_isprint('~'), 1);
	ASSERT_EQ_INT("isprint 'A'", ft_isprint('A'), 1);
	ASSERT_EQ_INT("isprint 31", ft_isprint(31), 0);
	ASSERT_EQ_INT("isprint 127", ft_isprint(127), 0);
	ASSERT_EQ_INT("isprint 0", ft_isprint(0), 0);
	ASSERT_EQ_INT("isprint -1", ft_isprint(-1), 0);
}

static void	test_ft_toupper(void)
{
	ASSERT_EQ_INT("toupper 'a'", ft_toupper('a'), 'A');
	ASSERT_EQ_INT("toupper 'z'", ft_toupper('z'), 'Z');
	ASSERT_EQ_INT("toupper 'A'", ft_toupper('A'), 'A');
	ASSERT_EQ_INT("toupper '1'", ft_toupper('1'), '1');
	ASSERT_EQ_INT("toupper '@'", ft_toupper('@'), '@');
	ASSERT_EQ_INT("toupper 0", ft_toupper(0), 0);
}

static void	test_ft_tolower(void)
{
	ASSERT_EQ_INT("tolower 'A'", ft_tolower('A'), 'a');
	ASSERT_EQ_INT("tolower 'Z'", ft_tolower('Z'), 'z');
	ASSERT_EQ_INT("tolower 'a'", ft_tolower('a'), 'a');
	ASSERT_EQ_INT("tolower '5'", ft_tolower('5'), '5');
	ASSERT_EQ_INT("tolower 0", ft_tolower(0), 0);
}

static void	test_ft_strlen(void)
{
	ASSERT_EQ_INT("strlen empty", ft_strlen(""), 0);
	ASSERT_EQ_INT("strlen one", ft_strlen("a"), 1);
	ASSERT_EQ_INT("strlen hello", ft_strlen("hello"), 5);
	ASSERT_EQ_INT("strlen with nl", ft_strlen("a\nb"), 3);
}

static void	test_ft_memset(void)
{
	char			buf[8];
	void			*r;
	unsigned char	ubuf[3];

	memset(buf, 0, sizeof(buf));
	r = ft_memset(buf, 'A', 3);
	ASSERT_EQ_PTR("memset ret", r, buf);
	ASSERT_EQ_INT("memset[0]", buf[0], 'A');
	ASSERT_EQ_INT("memset[2]", buf[2], 'A');
	ASSERT_EQ_INT("memset[3] untouched", buf[3], 0);
	buf[0] = 'X';
	ft_memset(buf, 'Y', 0);
	ASSERT_EQ_INT("memset n=0 no change", buf[0], 'X');
	ft_memset(ubuf, 0xFF, 3);
	ASSERT_EQ_INT("memset 0xFF[0]", ubuf[0], 0xFF);
	ASSERT_EQ_INT("memset 0xFF[2]", ubuf[2], 0xFF);
}

static void	test_ft_bzero(void)
{
	char	buf[5];

	memset(buf, 'X', 5);
	ft_bzero(buf, 3);
	ASSERT_EQ_INT("bzero[0]", buf[0], 0);
	ASSERT_EQ_INT("bzero[2]", buf[2], 0);
	ASSERT_EQ_INT("bzero[3] untouched", buf[3], 'X');
	buf[0] = 'Z';
	ft_bzero(buf, 0);
	ASSERT_EQ_INT("bzero n=0 no change", buf[0], 'Z');
}

static void	test_ft_memcpy(void)
{
	char	dst[8] = {0};
	char	dst2[4] = "abc";
	void	*r;

	r = ft_memcpy(dst, "hello", 6);
	ASSERT_EQ_PTR("memcpy ret", r, dst);
	ASSERT_EQ_STR("memcpy hello", dst, "hello");
	ft_memcpy(dst2, "xyz", 0);
	ASSERT_EQ_STR("memcpy n=0 no change", dst2, "abc");
	r = ft_memcpy(NULL, NULL, 0);
	ASSERT_NULL("memcpy NULL NULL 0", r);
}

static void	test_ft_memmove(void)
{
	char	fwd[8] = "abcdef";
	char	bwd[8] = "abcdef";
	char	same[4] = "abc";
	char	buf[4] = "xyz";

	ft_memmove(fwd + 1, fwd, 4);
	ASSERT_EQ_STR("memmove overlap bwd", fwd, "aabcdf");
	ft_memmove(bwd, bwd + 1, 4);
	ASSERT_EQ_STR("memmove overlap fwd", bwd, "bcdeef");
	ft_memmove(same, same, 3);
	ASSERT_EQ_STR("memmove same", same, "abc");
	ft_memmove(buf, "...", 0);
	ASSERT_EQ_STR("memmove len=0", buf, "xyz");
}

static void	test_ft_strlcpy(void)
{
	char	buf[10];
	size_t	r;

	memset(buf, 'X', sizeof(buf));
	r = ft_strlcpy(buf, "hello", 10);
	ASSERT_EQ_STR("strlcpy full", buf, "hello");
	ASSERT_EQ_INT("strlcpy ret full", r, 5);
	memset(buf, 'X', sizeof(buf));
	r = ft_strlcpy(buf, "hello", 3);
	ASSERT_EQ_STR("strlcpy trunc", buf, "he");
	ASSERT_EQ_INT("strlcpy ret trunc", r, 5);
	buf[0] = 'Z';
	r = ft_strlcpy(buf, "hello", 0);
	ASSERT_EQ_INT("strlcpy dstsize=0 no change", buf[0], 'Z');
	ASSERT_EQ_INT("strlcpy ret dstsize=0", r, 5);
	r = ft_strlcpy(buf, "", 10);
	ASSERT_EQ_STR("strlcpy empty src", buf, "");
	ASSERT_EQ_INT("strlcpy ret empty", r, 0);
}

static void	test_ft_strlcat(void)
{
	char	buf[10];
	char	full[6] = "abcde";
	size_t	r;

	strcpy(buf, "abc");
	r = ft_strlcat(buf, "de", 10);
	ASSERT_EQ_STR("strlcat normal", buf, "abcde");
	ASSERT_EQ_INT("strlcat ret normal", r, 5);
	strcpy(buf, "abc");
	r = ft_strlcat(buf, "defgh", 6);
	ASSERT_EQ_STR("strlcat trunc", buf, "abcde");
	ASSERT_EQ_INT("strlcat ret trunc", r, 8);
	r = ft_strlcat(buf, "xyz", 0);
	ASSERT_EQ_INT("strlcat dstsize=0", r, 3);
	r = ft_strlcat(full, "xy", 3);
	ASSERT_EQ_INT("strlcat dl>=dstsize", r, 3 + 2);
}

static void	test_ft_strchr(void)
{
	const char	*s = "hello";
	const char	*e = "";
	const char	*hi = "abc\x80";
	char		*r;

	r = ft_strchr(s, 'l');
	ASSERT_EQ_PTR("strchr found", r, &s[2]);
	r = ft_strchr(s, '\0');
	ASSERT_EQ_PTR("strchr end", r, &s[5]);
	r = ft_strchr(s, 'z');
	ASSERT_NULL("strchr not found", r);
	r = ft_strchr(e, '\0');
	ASSERT_EQ_PTR("strchr empty \\0", r, e);
	r = ft_strchr(hi, (char)0x80);
	ASSERT_EQ_PTR("strchr high byte", r, &hi[3]);
}

static void	test_ft_strrchr(void)
{
	const char	*s = "abcba";

	ASSERT_EQ_PTR("strrchr last 'b'", ft_strrchr(s, 'b'), &s[3]);
	ASSERT_EQ_PTR("strrchr end", ft_strrchr(s, '\0'), &s[5]);
	ASSERT_NULL("strrchr not found", ft_strrchr(s, 'z'));
}

static void	test_ft_strncmp(void)
{
	ASSERT_EQ_INT("strncmp eq", ft_strncmp("abc", "abc", 3), 0);
	ASSERT_TRUE("strncmp lt", ft_strncmp("abc", "abd", 3) < 0);
	ASSERT_TRUE("strncmp gt", ft_strncmp("abd", "abc", 3) > 0);
	ASSERT_TRUE("strncmp shorter s1", ft_strncmp("ab", "abc", 5) < 0);
	ASSERT_EQ_INT("strncmp n=0", ft_strncmp("abc", "xyz", 0), 0);
	ASSERT_TRUE("strncmp unsigned",
		ft_strncmp("\xFF", "\x01", 1) > 0);
}

static void	test_ft_memchr(void)
{
	const char	*s = "abcdef";
	const char	bin[] = {1, 2, 0, 3, 4};

	ASSERT_EQ_PTR("memchr found", ft_memchr(s, 'c', 6), &s[2]);
	ASSERT_NULL("memchr not found", ft_memchr(s, 'z', 6));
	ASSERT_NULL("memchr n=0", ft_memchr(s, 'a', 0));
	ASSERT_EQ_PTR("memchr binary 0", ft_memchr(bin, 0, 5), &bin[2]);
}

static void	test_ft_memcmp(void)
{
	ASSERT_EQ_INT("memcmp eq", ft_memcmp("abc", "abc", 3), 0);
	ASSERT_TRUE("memcmp lt", ft_memcmp("abc", "abd", 3) < 0);
	ASSERT_TRUE("memcmp gt", ft_memcmp("abd", "abc", 3) > 0);
	ASSERT_EQ_INT("memcmp n=0", ft_memcmp("abc", "xyz", 0), 0);
}

static void	test_ft_strnstr(void)
{
	const char	*h = "hello world";

	ASSERT_EQ_PTR("strnstr empty needle", ft_strnstr(h, "", 11), h);
	ASSERT_EQ_PTR("strnstr empty needle len0",
		ft_strnstr("aaa", "", 0), (void *)"aaa");
	ASSERT_EQ_PTR("strnstr found", ft_strnstr(h, "world", 11), &h[6]);
	ASSERT_NULL("strnstr len short", ft_strnstr("abcabc", "abc", 2));
	ASSERT_NOT_NULL("strnstr boundary", ft_strnstr("abcabc", "abc", 3));
	ASSERT_NULL("strnstr needle longer", ft_strnstr("ab", "abc", 5));
	ASSERT_NULL("strnstr not found", ft_strnstr(h, "zzz", 11));
}

static void	test_ft_atoi(void)
{
	ASSERT_EQ_INT("atoi 42", ft_atoi("42"), 42);
	ASSERT_EQ_INT("atoi -42", ft_atoi("-42"), -42);
	ASSERT_EQ_INT("atoi +42", ft_atoi("+42"), 42);
	ASSERT_EQ_INT("atoi spaces", ft_atoi("   -42abc"), -42);
	ASSERT_EQ_INT("atoi tab nl", ft_atoi("\t\n  42"), 42);
	ASSERT_EQ_INT("atoi empty", ft_atoi(""), 0);
	ASSERT_EQ_INT("atoi non-digit", ft_atoi("abc"), 0);
	ASSERT_EQ_INT("atoi zero", ft_atoi("0"), 0);
	ASSERT_EQ_INT("atoi --42", ft_atoi("--42"), 0);
	ASSERT_EQ_INT("atoi trailing", ft_atoi("42abc"), 42);
}

static void	test_ft_calloc(void)
{
	int		*p;
	size_t	i;
	void	*z1;
	void	*z2;
	void	*z3;

	p = (int *)ft_calloc(10, sizeof(int));
	ASSERT_NOT_NULL("calloc normal", p);
	i = 0;
	while (i < 10)
	{
		ASSERT_EQ_INT("calloc zero", p[i], 0);
		i++;
	}
	free(p);
	z1 = ft_calloc(0, 10);
	ASSERT_NOT_NULL("calloc 0x10", z1);
	free(z1);
	z2 = ft_calloc(10, 0);
	ASSERT_NOT_NULL("calloc 10x0", z2);
	free(z2);
	z3 = ft_calloc(0, 0);
	ASSERT_NOT_NULL("calloc 0x0", z3);
	free(z3);
	ASSERT_NULL("calloc overflow SIZE_MAX*2",
		ft_calloc((size_t)-1, 2));
	ASSERT_NULL("calloc overflow boundary",
		ft_calloc(((size_t)-1) / 2 + 1, 2));
}

static void	test_ft_strdup(void)
{
	char	*d;
	char	src[] = "hello";

	d = ft_strdup(src);
	ASSERT_NOT_NULL("strdup non-null", d);
	ASSERT_EQ_STR("strdup content", d, "hello");
	ASSERT_TRUE("strdup distinct ptr", d != src);
	src[0] = 'X';
	ASSERT_EQ_INT("strdup independent", d[0], 'h');
	free(d);
	d = ft_strdup("");
	ASSERT_NOT_NULL("strdup empty non-null", d);
	ASSERT_EQ_STR("strdup empty", d, "");
	free(d);
}

void	run_part1_tests(void)
{
	test_ft_isalpha();
	test_ft_isdigit();
	test_ft_isalnum();
	test_ft_isascii();
	test_ft_isprint();
	test_ft_toupper();
	test_ft_tolower();
	test_ft_strlen();
	test_ft_memset();
	test_ft_bzero();
	test_ft_memcpy();
	test_ft_memmove();
	test_ft_strlcpy();
	test_ft_strlcat();
	test_ft_strchr();
	test_ft_strrchr();
	test_ft_strncmp();
	test_ft_memchr();
	test_ft_memcmp();
	test_ft_strnstr();
	test_ft_atoi();
	test_ft_calloc();
	test_ft_strdup();
}
