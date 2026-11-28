# Level 3

数値を出力する問題が多いので、**`put_nbr` を何も見ずに書けるようにしておく**のが一番の対策です。

---

## add_prime_sum（program / write, exit）

正の整数 n を受け取り、n 以下の素数の合計を出力する。引数が1個でない、または n が正でなければ `0`。

```c
#include <unistd.h>

int	ft_atoi(char *s)
{
	int	n;
	int	sign;

	n = 0;
	sign = 1;
	if (*s == '-')
	{
		sign = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
		n = n * 10 + (*s++ - '0');
	return (n * sign);
}

void	put_nbr(int n)
{
	char	c;

	if (n >= 10)
		put_nbr(n / 10);
	c = n % 10 + '0';
	write(1, &c, 1);
}

int	is_prime(int n)
{
	int	i;

	if (n < 2)
		return (0);
	i = 2;
	while (i * i <= n)
	{
		if (n % i == 0)
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int	n;
	int	sum;

	sum = 0;
	if (argc == 2)
	{
		n = ft_atoi(argv[1]);
		while (n > 0)
		{
			if (is_prime(n))
				sum += n;
			n--;
		}
	}
	put_nbr(sum);
	write(1, "\n", 1);
	return (0);
}
```

---

## epur_str（program / write）

単語の間をスペース1個にし、先頭と末尾の空白を消す（空白はスペースとタブ）。

```c
#include <unistd.h>

int	main(int argc, char **argv)
{
	char	*s;
	int		first;

	if (argc == 2)
	{
		s = argv[1];
		first = 1;
		while (*s)
		{
			while (*s == ' ' || *s == '\t')
				s++;
			if (!*s)
				break ;
			if (!first)
				write(1, " ", 1);
			while (*s && *s != ' ' && *s != '\t')
				write(1, s++, 1);
			first = 0;
		}
	}
	write(1, "\n", 1);
	return (0);
}
```

「単語の前に区切りを出す（最初の単語を除く）」と考えると、末尾に余計な空白が出ない。

---

## expand_str（program / write）

epur_str と同じで、区切りがスペース **3 個**になる。

```c
#include <unistd.h>

int	main(int argc, char **argv)
{
	char	*s;
	int		first;

	if (argc == 2)
	{
		s = argv[1];
		first = 1;
		while (*s)
		{
			while (*s == ' ' || *s == '\t')
				s++;
			if (!*s)
				break ;
			if (!first)
				write(1, "   ", 3);
			while (*s && *s != ' ' && *s != '\t')
				write(1, s++, 1);
			first = 0;
		}
	}
	write(1, "\n", 1);
	return (0);
}
```

---

## ft_atoi_base（function）

`int ft_atoi_base(const char *str, int str_base);` — 基数 2〜16。数字は `0-9a-f`（大文字の `A-F` も可）。先頭の `-` に対応する。

```c
int	digit_val(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (-1);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int	res;
	int	sign;
	int	d;

	res = 0;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str)
	{
		d = digit_val(*str);
		if (d < 0 || d >= str_base)
			break ;
		res = res * str_base + d;
		str++;
	}
	return (res * sign);
}
```

---

## ft_list_size（function）

`int ft_list_size(t_list *begin_list);` — 渡される `ft_list.h`:

```c
typedef struct s_list
{
	struct s_list	*next;
	void			*data;
}	t_list;
```

```c
#include "ft_list.h"

int	ft_list_size(t_list *begin_list)
{
	int	n;

	n = 0;
	while (begin_list)
	{
		n++;
		begin_list = begin_list->next;
	}
	return (n);
}
```

---

## ft_range（function / malloc）

`int *ft_range(int start, int end);` — start から end まで（両端を含む）の配列を返す。
例: (1, 3) → `1, 2, 3`、(0, -3) → `0, -1, -2, -3`

```c
#include <stdlib.h>

int	*ft_range(int start, int end)
{
	int	len;
	int	step;
	int	*tab;
	int	i;

	step = 1;
	len = end - start + 1;
	if (start > end)
	{
		step = -1;
		len = start - end + 1;
	}
	tab = malloc(sizeof(int) * len);
	if (!tab)
		return (NULL);
	i = 0;
	while (i < len)
	{
		tab[i] = start + i * step;
		i++;
	}
	return (tab);
}
```

---

## ft_rrange（function / malloc）

`int *ft_rrange(int start, int end);` — **end から start へ**の配列。
例: (1, 3) → `3, 2, 1`、(0, -3) → `-3, -2, -1, 0`

```c
#include <stdlib.h>

int	*ft_rrange(int start, int end)
{
	int	len;
	int	step;
	int	*tab;
	int	i;

	step = -1;
	len = end - start + 1;
	if (start > end)
	{
		step = 1;
		len = start - end + 1;
	}
	tab = malloc(sizeof(int) * len);
	if (!tab)
		return (NULL);
	i = 0;
	while (i < len)
	{
		tab[i] = end + i * step;
		i++;
	}
	return (tab);
}
```

---

## hidenp（program / write）

`./hidenp s1 s2` — s1 が s2 の中に順番通り隠れていれば `1`、なければ `0`（wdmatch と同じ判定）。空の s1 は `1`。

```c
#include <unistd.h>

int	main(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc == 3)
	{
		i = 0;
		j = 0;
		while (argv[1][i] && argv[2][j])
		{
			if (argv[1][i] == argv[2][j])
				i++;
			j++;
		}
		if (argv[1][i])
			write(1, "0", 1);
		else
			write(1, "1", 1);
	}
	write(1, "\n", 1);
	return (0);
}
```

---

## lcm（function）

`unsigned int lcm(unsigned int a, unsigned int b);` — 最小公倍数。どちらかが 0 なら 0。

```c
unsigned int	lcm(unsigned int a, unsigned int b)
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	t;

	if (a == 0 || b == 0)
		return (0);
	x = a;
	y = b;
	while (y)
	{
		t = x % y;
		x = y;
		y = t;
	}
	return (a / x * b);
}
```

ユークリッドの互除法で最大公約数 x を求め、`a / x * b` で計算する（先に割るのはオーバーフローを避けるため）。

---

## paramsum（program / write）

渡された引数の数を出力する（引数なしなら `0`）。

```c
#include <unistd.h>

void	put_nbr(int n)
{
	char	c;

	if (n >= 10)
		put_nbr(n / 10);
	c = n % 10 + '0';
	write(1, &c, 1);
}

int	main(int argc, char **argv)
{
	(void)argv;
	put_nbr(argc - 1);
	write(1, "\n", 1);
	return (0);
}
```

---

## pgcd（program / printf, atoi, malloc, free）

2つの正の整数の最大公約数を出力する。引数が2個でなければ `\n`。

```c
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int	a;
	int	b;
	int	t;

	if (argc == 3)
	{
		a = atoi(argv[1]);
		b = atoi(argv[2]);
		while (b)
		{
			t = a % b;
			a = b;
			b = t;
		}
		printf("%d", a);
	}
	printf("\n");
	return (0);
}
```

---

## print_hex（program / write）

正の整数（10進の文字列）を小文字の16進で出力する。

```c
#include <unistd.h>

int	ft_atoi(char *s)
{
	int	n;

	n = 0;
	while (*s >= '0' && *s <= '9')
		n = n * 10 + (*s++ - '0');
	return (n);
}

void	put_hex(int n)
{
	if (n >= 16)
		put_hex(n / 16);
	write(1, &"0123456789abcdef"[n % 16], 1);
}

int	main(int argc, char **argv)
{
	if (argc == 2)
		put_hex(ft_atoi(argv[1]));
	write(1, "\n", 1);
	return (0);
}
```

---

## rstr_capitalizer（program / write）

各単語の**最後の文字**を大文字、それ以外を小文字にする。引数は複数あり、1つ出力するごとに `\n`。引数なしなら `\n`。

```c
#include <unistd.h>

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\0');
}

int	main(int argc, char **argv)
{
	int		k;
	int		i;
	char	c;

	if (argc == 1)
		write(1, "\n", 1);
	k = 1;
	while (k < argc)
	{
		i = 0;
		while (argv[k][i])
		{
			c = argv[k][i];
			if (c >= 'A' && c <= 'Z')
				c += 32;
			if (c >= 'a' && c <= 'z' && is_space(argv[k][i + 1]))
				c -= 32;
			write(1, &c, 1);
			i++;
		}
		write(1, "\n", 1);
		k++;
	}
	return (0);
}
```

---

## str_capitalizer（program / write）

各単語の**最初の文字**を大文字、それ以外を小文字にする。引数の扱いは rstr_capitalizer と同じ。

```c
#include <unistd.h>

int	main(int argc, char **argv)
{
	int		k;
	int		i;
	char	c;

	if (argc == 1)
		write(1, "\n", 1);
	k = 1;
	while (k < argc)
	{
		i = 0;
		while (argv[k][i])
		{
			c = argv[k][i];
			if (c >= 'A' && c <= 'Z')
				c += 32;
			if (c >= 'a' && c <= 'z' && (i == 0
					|| argv[k][i - 1] == ' ' || argv[k][i - 1] == '\t'))
				c -= 32;
			write(1, &c, 1);
			i++;
		}
		write(1, "\n", 1);
		k++;
	}
	return (0);
}
```

---

## tab_mult（program / write）

`./tab_mult 9` →

```
1 x 9 = 9
2 x 9 = 18
...
9 x 9 = 81
```

```c
#include <unistd.h>

int	ft_atoi(char *s)
{
	int	n;

	n = 0;
	while (*s >= '0' && *s <= '9')
		n = n * 10 + (*s++ - '0');
	return (n);
}

void	put_nbr(int n)
{
	char	c;

	if (n >= 10)
		put_nbr(n / 10);
	c = n % 10 + '0';
	write(1, &c, 1);
}

int	main(int argc, char **argv)
{
	int	n;
	int	i;

	if (argc != 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	n = ft_atoi(argv[1]);
	i = 1;
	while (i <= 9)
	{
		put_nbr(i);
		write(1, " x ", 3);
		put_nbr(n);
		write(1, " = ", 3);
		put_nbr(i * n);
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
```
