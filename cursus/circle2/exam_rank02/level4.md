# Level 4

---

## flood_fill（function）

`void flood_fill(char **tab, t_point size, t_point begin);`
begin と同じ文字でつながっている領域（上下左右のみ。斜めは含まない）を `'F'` で塗る。

`t_point.h`（渡される）:

```c
typedef struct s_point
{
	int	x;
	int	y;
}	t_point;
```

```c
#include "t_point.h"

void	fill(char **tab, t_point size, int x, int y, char target)
{
	if (x < 0 || y < 0 || x >= size.x || y >= size.y)
		return ;
	if (tab[y][x] != target)
		return ;
	tab[y][x] = 'F';
	fill(tab, size, x + 1, y, target);
	fill(tab, size, x - 1, y, target);
	fill(tab, size, x, y + 1, target);
	fill(tab, size, x, y - 1, target);
}

void	flood_fill(char **tab, t_point size, t_point begin)
{
	char	target;

	target = tab[begin.y][begin.x];
	if (target == 'F')
		return ;
	fill(tab, size, begin.x, begin.y, target);
}
```

- `tab[y][x]` の順番（行が y）を間違えやすい
- `target == 'F'` のときは何もしない。塗った場所がまた target に見えて無限に再帰するのを防ぐため

---

## fprime（program / printf, atoi）

正の整数を素因数分解して `*` でつなげて出力する。例: `225225` → `3*3*5*5*7*11*13`、`1` → `1`。

```c
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int	n;
	int	p;

	if (argc == 2)
	{
		n = atoi(argv[1]);
		if (n == 1)
			printf("1");
		p = 2;
		while (n > 1)
		{
			if (n % p == 0)
			{
				printf("%d", p);
				n /= p;
				if (n > 1)
					printf("*");
			}
			else
				p++;
		}
	}
	printf("\n");
	return (0);
}
```

---

## ft_itoa（function / malloc）

`char *ft_itoa(int nbr);` — **INT_MIN（-2147483648）でも正しく動くこと**。

```c
#include <stdlib.h>

char	*ft_itoa(int nbr)
{
	long	n;
	int		len;
	char	*s;

	n = nbr;
	len = (n <= 0);
	while (n)
	{
		n /= 10;
		len++;
	}
	s = malloc(len + 1);
	if (!s)
		return (NULL);
	s[len] = '\0';
	n = nbr;
	if (n < 0)
	{
		s[0] = '-';
		n = -n;
	}
	if (n == 0)
		s[0] = '0';
	while (n)
	{
		s[--len] = n % 10 + '0';
		n /= 10;
	}
	return (s);
}
```

`long` に入れてから符号を反転するので、INT_MIN でもオーバーフローしない。

---

## ft_list_foreach（function）

`void ft_list_foreach(t_list *begin_list, void (*f)(void *));` — 各要素の data に f を適用する。

```c
#include "ft_list.h"

void	ft_list_foreach(t_list *begin_list, void (*f)(void *))
{
	while (begin_list)
	{
		f(begin_list->data);
		begin_list = begin_list->next;
	}
}
```

（`ft_list.h` は Level 3 の ft_list_size と同じ。`next` と `data` を持つ構造体）

---

## ft_list_remove_if（function / free）

`void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)());`
`cmp(data, data_ref) == 0` の要素をリストから外して free する。

```c
#include <stdlib.h>
#include "ft_list.h"

void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list	*cur;

	if (!begin_list || !*begin_list)
		return ;
	cur = *begin_list;
	if (cmp(cur->data, data_ref) == 0)
	{
		*begin_list = cur->next;
		free(cur);
		ft_list_remove_if(begin_list, data_ref, cmp);
	}
	else
		ft_list_remove_if(&cur->next, data_ref, cmp);
}
```

> 自分の Mac の新しい clang では `int (*cmp)()` が `-Wdeprecated-non-prototype` エラーになることがあります。
> これは subject 指定のプロトタイプが原因です。本番ではプロトタイプを変えずにそのまま提出してください。

ダブルポインタを再帰で渡すと、「先頭を消す場合」と「途中を消す場合」を同じように書ける。

---

## ft_split（function / malloc）

`char **ft_split(char *str);` — スペース・タブ・改行で区切り、最後が NULL の配列を返す。

```c
#include <stdlib.h>

int	is_sep(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	count_words(char *s)
{
	int	n;

	n = 0;
	while (*s)
	{
		while (*s && is_sep(*s))
			s++;
		if (*s)
			n++;
		while (*s && !is_sep(*s))
			s++;
	}
	return (n);
}

char	**ft_split(char *str)
{
	char	**res;
	int		w;
	int		len;
	int		i;

	res = malloc(sizeof(char *) * (count_words(str) + 1));
	if (!res)
		return (NULL);
	w = 0;
	while (*str)
	{
		while (*str && is_sep(*str))
			str++;
		if (!*str)
			break ;
		len = 0;
		while (str[len] && !is_sep(str[len]))
			len++;
		res[w] = malloc(len + 1);
		if (!res[w])
			return (NULL);
		i = -1;
		while (++i < len)
			res[w][i] = str[i];
		res[w][len] = '\0';
		str += len;
		w++;
	}
	res[w] = NULL;
	return (res);
}
```

---

## rev_wrd（program / write）

単語の順番を逆にして、スペース1個で区切って出力する。

```c
#include <unistd.h>

int	is_sp(char c)
{
	return (c == ' ' || c == '\t');
}

int	main(int argc, char **argv)
{
	char	*s;
	int		i;
	int		end;
	int		first;

	if (argc == 2)
	{
		s = argv[1];
		i = 0;
		while (s[i])
			i++;
		first = 1;
		while (--i >= 0)
		{
			if (is_sp(s[i]))
				continue ;
			end = i;
			while (i > 0 && !is_sp(s[i - 1]))
				i--;
			if (!first)
				write(1, " ", 1);
			write(1, &s[i], end - i + 1);
			first = 0;
		}
	}
	write(1, "\n", 1);
	return (0);
}
```

後ろから見て、単語の末尾を見つけたらその単語の先頭まで戻り、まとめて write する。

---

## rostring（program / write）

最初の単語を最後に移動する。単語はスペース1個で区切って出力する。
例: `"abc   def ghi"` → `def ghi abc`。引数が1個以上あれば argv[1] だけ処理する。

```c
#include <unistd.h>

int	is_sp(char c)
{
	return (c == ' ' || c == '\t');
}

int	main(int argc, char **argv)
{
	char	*s;
	char	*first;
	int		flen;
	int		printed;

	if (argc >= 2)
	{
		s = argv[1];
		while (is_sp(*s))
			s++;
		first = s;
		flen = 0;
		while (s[flen] && !is_sp(s[flen]))
			flen++;
		s += flen;
		printed = 0;
		while (*s)
		{
			while (is_sp(*s))
				s++;
			if (!*s)
				break ;
			if (printed)
				write(1, " ", 1);
			while (*s && !is_sp(*s))
				write(1, s++, 1);
			printed = 1;
		}
		if (printed && flen)
			write(1, " ", 1);
		write(1, first, flen);
	}
	write(1, "\n", 1);
	return (0);
}
```

---

## sort_int_tab（function）

`void sort_int_tab(int *tab, unsigned int size);` — 昇順に並べる（同じ値があってもよい）。

```c
void	sort_int_tab(int *tab, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;
	int				tmp;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (tab[j] < tab[i])
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
```

`size` は unsigned なので `size - 1` を使わない書き方にする（size が 0 だと巨大な数になる）。

---

## sort_list（function）

`t_list *sort_list(t_list *lst, int (*cmp)(int, int));`
`cmp(a, b)` は a と b が正しい順番なら 0 以外を返す。並べ替えたリストの先頭を返す。

`list.h`（渡される。**data が int** なので Level 3 の ft_list.h とは違う）:

```c
typedef struct s_list	t_list;

struct s_list
{
	int		data;
	t_list	*next;
};
```

```c
#include "list.h"

t_list	*sort_list(t_list *lst, int (*cmp)(int, int))
{
	t_list	*cur;
	int		tmp;

	cur = lst;
	while (cur && cur->next)
	{
		if (!cmp(cur->data, cur->next->data))
		{
			tmp = cur->data;
			cur->data = cur->next->data;
			cur->next->data = tmp;
			cur = lst;
		}
		else
			cur = cur->next;
	}
	return (lst);
}
```

ノードはつなぎ替えず、data だけ交換する。交換したら先頭からやり直す（遅いが確実）。
