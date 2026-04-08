/* allowed functions: write, malloc, free */
#include "str_maxlenoc.h"

static int	str_len(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*
** Returns 1 if the substring base[start..start+len-1] appears anywhere in s.
*/
static int	contains(char *s, char *base, int start, int len)
{
	int	i;
	int	j;

	if (len == 0)
		return (1);
	i = 0;
	while (s[i])
	{
		j = 0;
		while (j < len && s[i + j] && s[i + j] == base[start + j])
			j++;
		if (j == len)
			return (1);
		i++;
	}
	return (0);
}

static int	in_all(char **argv, int argc, int start, int len)
{
	int	k;

	k = 2;
	while (k < argc)
	{
		if (!contains(argv[k], argv[1], start, len))
			return (0);
		k++;
	}
	return (1);
}

static char	*dup_sub(char *src, int start, int len)
{
	char	*r;
	int		i;

	r = (char *)malloc(sizeof(char) * (len + 1));
	if (!r)
		return (NULL);
	i = 0;
	while (i < len)
	{
		r[i] = src[start + i];
		i++;
	}
	r[i] = '\0';
	return (r);
}

int	main(int argc, char **argv)
{
	int		n;
	int		best_start;
	int		best_len;
	int		i;
	int		len;
	char	*out;

	if (argc < 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	n = str_len(argv[1]);
	best_start = 0;
	best_len = 0;
	i = 0;
	while (i < n)
	{
		len = best_len + 1;
		while (i + len <= n && in_all(argv, argc, i, len))
		{
			best_start = i;
			best_len = len;
			len++;
		}
		i++;
	}
	out = dup_sub(argv[1], best_start, best_len);
	if (!out)
		return (1);
	write(1, out, best_len);
	write(1, "\n", 1);
	free(out);
	return (0);
}
