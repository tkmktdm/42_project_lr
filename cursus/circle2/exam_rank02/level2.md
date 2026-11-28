# Level 2

---

## alpha_mirror（program / write）

アルファベットを反対側の文字に変える（a↔z, b↔y, … 大文字も同じ）。

```c
#include <unistd.h>

int	main(int argc, char **argv)
{
	char	*s;
	char	c;

	if (argc == 2)
	{
		s = argv[1];
		while (*s)
		{
			c = *s;
			if (c >= 'a' && c <= 'z')
				c = 'z' - (c - 'a');
			else if (c >= 'A' && c <= 'Z')
				c = 'Z' - (c - 'A');
			write(1, &c, 1);
			s++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
```

---

## camel_to_snake（program / write）

`hereIsACamelCase` → `here_is_a_camel_case`。大文字を `_` + 小文字に置き換える。

```c
#include <unistd.h>

int	main(int argc, char **argv)
{
	char	*s;
	char	c;

	if (argc == 2)
	{
		s = argv[1];
		while (*s)
		{
			c = *s;
			if (c >= 'A' && c <= 'Z')
			{
				write(1, "_", 1);
				c += 32;
			}
			write(1, &c, 1);
			s++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
```

---

## do_op（program / atoi, printf, write）

`./do_op "1" "+" "2"` → `3`。演算子は `+ - * / %`。引数が3個でなければ `\n`。
0除算はテストされない。

```c
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int	a;
	int	b;
	char	op;

	if (argc == 4)
	{
		a = atoi(argv[1]);
		b = atoi(argv[3]);
		op = argv[2][0];
		if (op == '+')
			printf("%d", a + b);
		else if (op == '-')
			printf("%d", a - b);
		else if (op == '*')
			printf("%d", a * b);
		else if (op == '/')
			printf("%d", a / b);
		else if (op == '%')
			printf("%d", a % b);
	}
	printf("\n");
	return (0);
}
```

---

## ft_atoi（function）

`int ft_atoi(const char *str);` — 標準の atoi と同じ動き（先頭の空白、符号1つ、数字）。

```c
int	ft_atoi(const char *str)
{
	int	sign;
	int	res;

	sign = 1;
	res = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * sign);
}
```

---

## ft_strcmp（function）

`int ft_strcmp(char *s1, char *s2);`

```c
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
```

---

## ft_strcspn（function）

`size_t ft_strcspn(const char *s, const char *reject);` — 先頭から、reject の文字が初めて出てくるまでの長さ。

```c
#include <stddef.h>

size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (reject[j])
		{
			if (s[i] == reject[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}
```

---

## ft_strdup（function / malloc）

`char *ft_strdup(char *src);`

```c
#include <stdlib.h>

char	*ft_strdup(char *src)
{
	char	*dst;
	int		len;
	int		i;

	len = 0;
	while (src[len])
		len++;
	dst = malloc(len + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (i <= len)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}
```

---

## ft_strpbrk（function）

`char *ft_strpbrk(const char *s1, const char *s2);` — s1 の中で s2 のどれかの文字が最初に出てくる位置。なければ NULL。

```c
#include <stddef.h>

char	*ft_strpbrk(const char *s1, const char *s2)
{
	int	j;

	while (*s1)
	{
		j = 0;
		while (s2[j])
		{
			if (*s1 == s2[j])
				return ((char *)s1);
			j++;
		}
		s1++;
	}
	return (NULL);
}
```

---

## ft_strrev（function）

`char *ft_strrev(char *str);` — その場で反転して str を返す。

```c
char	*ft_strrev(char *str)
{
	int		i;
	int		j;
	char	tmp;

	j = 0;
	while (str[j])
		j++;
	j--;
	i = 0;
	while (i < j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
	return (str);
}
```

---

## ft_strspn（function）

`size_t ft_strspn(const char *s, const char *accept);` — 先頭から accept の文字だけが続く長さ。

```c
#include <stddef.h>

size_t	ft_strspn(const char *s, const char *accept)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (accept[j] && accept[j] != s[i])
			j++;
		if (!accept[j])
			return (i);
		i++;
	}
	return (i);
}
```

---

## inter（program / write）

`./inter s1 s2` — 両方に含まれる文字を、s1 に出てくる順で重複なしに出力する。

256 個のフラグ配列を使うのが定石。

```c
#include <unistd.h>

int	main(int argc, char **argv)
{
	int				in_s2[256] = {0};
	int				done[256] = {0};
	unsigned char	*s;

	if (argc == 3)
	{
		s = (unsigned char *)argv[2];
		while (*s)
			in_s2[*s++] = 1;
		s = (unsigned char *)argv[1];
		while (*s)
		{
			if (in_s2[*s] && !done[*s])
			{
				write(1, s, 1);
				done[*s] = 1;
			}
			s++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
```

---

## is_power_of_2（function）

`int is_power_of_2(unsigned int n);` — 2のべき乗なら 1、違えば 0。

```c
int	is_power_of_2(unsigned int n)
{
	return (n != 0 && (n & (n - 1)) == 0);
}
```

`n & (n - 1)` は一番下の 1 ビットを消す。2のべき乗は 1 ビットしか立っていないので 0 になる。

---

## last_word（program / write）

最後の単語を出力する（区切りはスペースとタブ。末尾に空白があってもよい）。

```c
#include <unistd.h>

int	main(int argc, char **argv)
{
	char	*s;
	int		i;

	if (argc == 2)
	{
		s = argv[1];
		i = 0;
		while (s[i])
			i++;
		i--;
		while (i >= 0 && (s[i] == ' ' || s[i] == '\t'))
			i--;
		while (i >= 0 && s[i] != ' ' && s[i] != '\t')
			i--;
		i++;
		while (s[i] && s[i] != ' ' && s[i] != '\t')
			write(1, &s[i++], 1);
	}
	write(1, "\n", 1);
	return (0);
}
```

---

## max（function）

`int max(int *tab, unsigned int len);` — 最大値を返す。len が 0 なら 0。

```c
int	max(int *tab, unsigned int len)
{
	unsigned int	i;
	int				m;

	if (len == 0)
		return (0);
	m = tab[0];
	i = 1;
	while (i < len)
	{
		if (tab[i] > m)
			m = tab[i];
		i++;
	}
	return (m);
}
```

---

## print_bits（function / write）

`void print_bits(unsigned char octet);` — 8 ビットを上位から出力する（2 → `00000010`、改行なし）。

```c
#include <unistd.h>

void	print_bits(unsigned char octet)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((octet >> i) & 1)
			write(1, "1", 1);
		else
			write(1, "0", 1);
		i--;
	}
}
```

---

## reverse_bits（function）

`unsigned char reverse_bits(unsigned char octet);` — ビット順を反転する（`00100110` → `01100100`）。

```c
unsigned char	reverse_bits(unsigned char octet)
{
	unsigned char	res;
	int				i;

	res = 0;
	i = 0;
	while (i < 8)
	{
		res = (res << 1) | (octet & 1);
		octet >>= 1;
		i++;
	}
	return (res);
}
```

---

## snake_to_camel（program / write）

`here_is_a_snake_case_word` → `hereIsASnakeCaseWord`。

```c
#include <unistd.h>

int	main(int argc, char **argv)
{
	char	*s;
	char	c;

	if (argc == 2)
	{
		s = argv[1];
		while (*s)
		{
			if (*s == '_')
			{
				s++;
				c = *s;
				if (c >= 'a' && c <= 'z')
					c -= 32;
			}
			else
				c = *s;
			if (c)
				write(1, &c, 1);
			if (*s)
				s++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
```

---

## swap_bits（function）

`unsigned char swap_bits(unsigned char octet);` — 上位4ビットと下位4ビットを入れ替える。

```c
unsigned char	swap_bits(unsigned char octet)
{
	return ((octet >> 4) | (octet << 4));
}
```

---

## union（program / write）

`./union s1 s2` — s1、s2 の順に、まだ出していない文字を出力する。

```c
#include <unistd.h>

int	main(int argc, char **argv)
{
	int				done[256] = {0};
	unsigned char	*s;
	int				k;

	if (argc == 3)
	{
		k = 1;
		while (k <= 2)
		{
			s = (unsigned char *)argv[k];
			while (*s)
			{
				if (!done[*s])
				{
					write(1, s, 1);
					done[*s] = 1;
				}
				s++;
			}
			k++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
```

---

## wdmatch（program / write）

`./wdmatch s1 s2` — s1 の文字が順番通りに s2 の中に見つかれば（飛び飛びでよい）s1 を出力する。

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
		if (!argv[1][i])
		{
			i = 0;
			while (argv[1][i])
				write(1, &argv[1][i++], 1);
		}
	}
	write(1, "\n", 1);
	return (0);
}
```
