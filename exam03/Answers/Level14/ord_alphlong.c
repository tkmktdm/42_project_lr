/* allowed functions: write, malloc, free */
#include "ord_alphlong.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

static int	word_len(char *s)
{
	int	i;

	i = 0;
	while (s[i] && !is_space(s[i]))
		i++;
	return (i);
}

static int	count_words(char *s)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		while (s[i] && is_space(s[i]))
			i++;
		if (s[i])
		{
			n++;
			while (s[i] && !is_space(s[i]))
				i++;
		}
	}
	return (n);
}

static char	to_lower(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c - 'A' + 'a');
	return (c);
}

/*
** Case-insensitive ASCII comparison. Returns < 0, 0, > 0.
*/
static int	ci_cmp(char *a, char *b)
{
	int	i;
	int	d;

	i = 0;
	while (a[i] && b[i])
	{
		d = (int)to_lower(a[i]) - (int)to_lower(b[i]);
		if (d != 0)
			return (d);
		i++;
	}
	return ((int)to_lower(a[i]) - (int)to_lower(b[i]));
}

static char	*dup_word(char *src, int len)
{
	char	*r;
	int		i;

	r = (char *)malloc(sizeof(char) * (len + 1));
	if (!r)
		return (NULL);
	i = 0;
	while (i < len)
	{
		r[i] = src[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}

static void	free_words(char **w, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(w[i]);
		i++;
	}
	free(w);
}

static char	**split_words(char *s, int *out_n)
{
	int		n;
	int		i;
	int		k;
	char	**res;

	n = count_words(s);
	*out_n = n;
	res = (char **)malloc(sizeof(char *) * (n + 1));
	if (!res)
		return (NULL);
	i = 0;
	k = 0;
	while (s[i] && k < n)
	{
		while (s[i] && is_space(s[i]))
			i++;
		if (s[i])
		{
			int len = word_len(&s[i]);
			res[k] = dup_word(&s[i], len);
			if (!res[k])
			{
				free_words(res, k);
				return (NULL);
			}
			k++;
			i += len;
		}
	}
	res[n] = NULL;
	return (res);
}

static int	str_len(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*
** Stable sort by (length, ci_cmp). Insertion sort preserves original order for
** equal keys.
*/
static void	sort_words(char **w, int n)
{
	int		i;
	int		j;
	char	*tmp;

	i = 1;
	while (i < n)
	{
		j = i;
		while (j > 0)
		{
			int la = str_len(w[j - 1]);
			int lb = str_len(w[j]);
			int swap = 0;
			if (la > lb)
				swap = 1;
			else if (la == lb && ci_cmp(w[j - 1], w[j]) > 0)
				swap = 1;
			if (!swap)
				break ;
			tmp = w[j - 1];
			w[j - 1] = w[j];
			w[j] = tmp;
			j--;
		}
		i++;
	}
}

static void	put_str(char *s)
{
	write(1, s, str_len(s));
}

static void	print_grouped(char **w, int n)
{
	int	i;
	int	first;

	i = 0;
	while (i < n)
	{
		int j = i;
		int len = str_len(w[i]);
		first = 1;
		while (j < n && str_len(w[j]) == len)
		{
			if (!first)
				write(1, " ", 1);
			put_str(w[j]);
			first = 0;
			j++;
		}
		write(1, "\n", 1);
		i = j;
	}
}

int	main(int argc, char **argv)
{
	char	**words;
	int		n;

	if (argc != 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	words = split_words(argv[1], &n);
	if (!words)
		return (1);
	if (n == 0)
	{
		free(words);
		return (0);
	}
	sort_words(words, n);
	print_grouped(words, n);
	free_words(words, n);
	return (0);
}
