#include "test_helpers.h"
#include "libft.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>

static void	test_ft_substr(void)
{
	char	*r;

	r = ft_substr("hello world", 6, 5);
	ASSERT_EQ_STR("substr normal", r, "world");
	free(r);
	r = ft_substr("hello", 0, 100);
	ASSERT_EQ_STR("substr len overrun", r, "hello");
	free(r);
	r = ft_substr("abc", 10, 5);
	ASSERT_EQ_STR("substr start over", r, "");
	free(r);
	r = ft_substr("abc", 0, 0);
	ASSERT_EQ_STR("substr len 0", r, "");
	free(r);
	r = ft_substr("abc", 0, 1);
	ASSERT_EQ_STR("substr first", r, "a");
	free(r);
}

static void	test_ft_strjoin(void)
{
	char	*r;

	r = ft_strjoin("foo", "bar");
	ASSERT_EQ_STR("strjoin normal", r, "foobar");
	free(r);
	r = ft_strjoin("", "abc");
	ASSERT_EQ_STR("strjoin empty s1", r, "abc");
	free(r);
	r = ft_strjoin("abc", "");
	ASSERT_EQ_STR("strjoin empty s2", r, "abc");
	free(r);
	r = ft_strjoin("", "");
	ASSERT_EQ_STR("strjoin both empty", r, "");
	free(r);
}

static void	test_ft_strtrim(void)
{
	char	*r;

	r = ft_strtrim("  hi  ", " ");
	ASSERT_EQ_STR("strtrim both", r, "hi");
	free(r);
	r = ft_strtrim("aaa", "a");
	ASSERT_EQ_STR("strtrim all", r, "");
	free(r);
	r = ft_strtrim("abc", "");
	ASSERT_EQ_STR("strtrim empty set", r, "abc");
	free(r);
	r = ft_strtrim("xyabcyx", "xy");
	ASSERT_EQ_STR("strtrim multi", r, "abc");
	free(r);
	r = ft_strtrim(" a b ", " ");
	ASSERT_EQ_STR("strtrim inner kept", r, "a b");
	free(r);
}

static void	free_split(char **arr)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static size_t	split_size(char **arr)
{
	size_t	n;

	n = 0;
	while (arr[n])
		n++;
	return (n);
}

static void	test_ft_split(void)
{
	char	**r;

	r = ft_split("a,b,c", ',');
	ASSERT_EQ_INT("split size 3", split_size(r), 3);
	ASSERT_EQ_STR("split[0]", r[0], "a");
	ASSERT_EQ_STR("split[1]", r[1], "b");
	ASSERT_EQ_STR("split[2]", r[2], "c");
	ASSERT_NULL("split term NULL", r[3]);
	free_split(r);
	r = ft_split(",,a,b,,", ',');
	ASSERT_EQ_INT("split merged size", split_size(r), 2);
	ASSERT_EQ_STR("split merged[0]", r[0], "a");
	ASSERT_EQ_STR("split merged[1]", r[1], "b");
	free_split(r);
	r = ft_split("", ',');
	ASSERT_EQ_INT("split empty", split_size(r), 0);
	free_split(r);
	r = ft_split(",,,", ',');
	ASSERT_EQ_INT("split all delims", split_size(r), 0);
	free_split(r);
	r = ft_split("abc", '\0');
	ASSERT_EQ_INT("split c=0 size", split_size(r), 1);
	ASSERT_EQ_STR("split c=0 [0]", r[0], "abc");
	free_split(r);
}

static void	test_ft_itoa(void)
{
	char	*r;

	r = ft_itoa(0);
	ASSERT_EQ_STR("itoa 0", r, "0");
	free(r);
	r = ft_itoa(42);
	ASSERT_EQ_STR("itoa 42", r, "42");
	free(r);
	r = ft_itoa(-42);
	ASSERT_EQ_STR("itoa -42", r, "-42");
	free(r);
	r = ft_itoa(INT_MAX);
	ASSERT_EQ_STR("itoa INT_MAX", r, "2147483647");
	free(r);
	r = ft_itoa(INT_MIN);
	ASSERT_EQ_STR("itoa INT_MIN", r, "-2147483648");
	free(r);
	r = ft_itoa(1);
	ASSERT_EQ_STR("itoa 1", r, "1");
	free(r);
	r = ft_itoa(-1);
	ASSERT_EQ_STR("itoa -1", r, "-1");
	free(r);
	r = ft_itoa(10);
	ASSERT_EQ_STR("itoa 10", r, "10");
	free(r);
	r = ft_itoa(-10);
	ASSERT_EQ_STR("itoa -10", r, "-10");
	free(r);
	r = ft_itoa(100);
	ASSERT_EQ_STR("itoa 100", r, "100");
	free(r);
}

static char	map_upper(unsigned int i, char c)
{
	(void)i;
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

static char	map_idx(unsigned int i, char c)
{
	(void)c;
	return ((char)('0' + (i % 10)));
}

static void	test_ft_strmapi(void)
{
	char	*r;

	r = ft_strmapi("hello", map_upper);
	ASSERT_EQ_STR("strmapi upper", r, "HELLO");
	free(r);
	r = ft_strmapi("", map_upper);
	ASSERT_EQ_STR("strmapi empty", r, "");
	free(r);
	r = ft_strmapi("abc", map_idx);
	ASSERT_EQ_STR("strmapi idx", r, "012");
	free(r);
}

static void	iter_star(unsigned int i, char *c)
{
	(void)i;
	if (*c == 'x')
		*c = '*';
}

static void	test_ft_striteri(void)
{
	char	buf[] = "xyzxy";
	char	empty[] = "";

	ft_striteri(buf, iter_star);
	ASSERT_EQ_STR("striteri rewrite", buf, "*yz*y");
	ft_striteri(empty, iter_star);
	ASSERT_EQ_STR("striteri empty", empty, "");
}

static int	open_tmpfd(FILE **fp_out)
{
	FILE	*fp;

	fp = tmpfile();
	*fp_out = fp;
	return (fileno(fp));
}

static void	read_tmpfd(FILE *fp, char *buf, size_t cap)
{
	size_t	n;

	fflush(fp);
	rewind(fp);
	n = fread(buf, 1, cap - 1, fp);
	buf[n] = '\0';
	fclose(fp);
}

static void	test_ft_putchar_fd(void)
{
	FILE	*fp;
	int		fd;
	char	buf[16];

	fd = open_tmpfd(&fp);
	ft_putchar_fd('A', fd);
	read_tmpfd(fp, buf, sizeof(buf));
	ASSERT_EQ_STR("putchar_fd", buf, "A");
}

static void	test_ft_putstr_fd(void)
{
	FILE	*fp;
	int		fd;
	char	buf[64];

	fd = open_tmpfd(&fp);
	ft_putstr_fd("hello", fd);
	read_tmpfd(fp, buf, sizeof(buf));
	ASSERT_EQ_STR("putstr_fd", buf, "hello");
	fd = open_tmpfd(&fp);
	ft_putstr_fd(NULL, fd);
	read_tmpfd(fp, buf, sizeof(buf));
	ASSERT_EQ_STR("putstr_fd NULL", buf, "");
}

static void	test_ft_putendl_fd(void)
{
	FILE	*fp;
	int		fd;
	char	buf[64];

	fd = open_tmpfd(&fp);
	ft_putendl_fd("hi", fd);
	read_tmpfd(fp, buf, sizeof(buf));
	ASSERT_EQ_STR("putendl_fd", buf, "hi\n");
}

static void	test_ft_putnbr_fd(void)
{
	FILE	*fp;
	int		fd;
	char	buf[64];

	fd = open_tmpfd(&fp);
	ft_putnbr_fd(0, fd);
	read_tmpfd(fp, buf, sizeof(buf));
	ASSERT_EQ_STR("putnbr 0", buf, "0");
	fd = open_tmpfd(&fp);
	ft_putnbr_fd(-42, fd);
	read_tmpfd(fp, buf, sizeof(buf));
	ASSERT_EQ_STR("putnbr -42", buf, "-42");
	fd = open_tmpfd(&fp);
	ft_putnbr_fd(INT_MIN, fd);
	read_tmpfd(fp, buf, sizeof(buf));
	ASSERT_EQ_STR("putnbr INT_MIN", buf, "-2147483648");
	fd = open_tmpfd(&fp);
	ft_putnbr_fd(INT_MAX, fd);
	read_tmpfd(fp, buf, sizeof(buf));
	ASSERT_EQ_STR("putnbr INT_MAX", buf, "2147483647");
}

void	run_part2_tests(void)
{
	test_ft_substr();
	test_ft_strjoin();
	test_ft_strtrim();
	test_ft_split();
	test_ft_itoa();
	test_ft_strmapi();
	test_ft_striteri();
	test_ft_putchar_fd();
	test_ft_putstr_fd();
	test_ft_putendl_fd();
	test_ft_putnbr_fd();
}
