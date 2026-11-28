# Level 1

各問題の仕様は要点だけ書いています。本番では必ず subject の例を確認してください。

---

## first_word（program / write）

最初の単語を出力する。単語の区切りはスペースとタブ。引数が1個でなければ `\n`。

```c
#include <unistd.h>

int	main(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc == 2)
	{
		while (argv[1][i] == ' ' || argv[1][i] == '\t')
			i++;
		while (argv[1][i] && argv[1][i] != ' ' && argv[1][i] != '\t')
			write(1, &argv[1][i++], 1);
	}
	write(1, "\n", 1);
	return (0);
}
```

---

## fizzbuzz（program / write）

1〜100 を出力する。3の倍数は `fizz`、5の倍数は `buzz`、15の倍数は `fizzbuzz`。

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

int	main(void)
{
	int	i;

	i = 1;
	while (i <= 100)
	{
		if (i % 15 == 0)
			write(1, "fizzbuzz", 8);
		else if (i % 3 == 0)
			write(1, "fizz", 4);
		else if (i % 5 == 0)
			write(1, "buzz", 4);
		else
			put_nbr(i);
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
```

---

## ft_putstr（function）

`void ft_putstr(char *str);`

```c
#include <unistd.h>

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}
```

---

## ft_strcpy（function）

`char *ft_strcpy(char *s1, char *s2);` — s2 を s1 にコピーして s1 を返す。

```c
char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
```

---

## ft_strlen（function）

`int ft_strlen(char *str);`

```c
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
```

---

## ft_swap（function）

`void ft_swap(int *a, int *b);`

```c
void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
```

---

## repeat_alpha（program / write）

アルファベットをその順番の回数だけ出力する（a=1回, b=2回 … 大文字も同じ）。それ以外の文字はそのまま。

```c
#include <unistd.h>

int	main(int argc, char **argv)
{
	int		i;
	int		n;
	char	*s;

	if (argc == 2)
	{
		s = argv[1];
		i = 0;
		while (s[i])
		{
			n = 1;
			if (s[i] >= 'a' && s[i] <= 'z')
				n = s[i] - 'a' + 1;
			else if (s[i] >= 'A' && s[i] <= 'Z')
				n = s[i] - 'A' + 1;
			while (n--)
				write(1, &s[i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
```

---

## rev_print（program / write）

文字列を逆順に出力する。

```c
#include <unistd.h>

int	main(int argc, char **argv)
{
	int	i;

	if (argc == 2)
	{
		i = 0;
		while (argv[1][i])
			i++;
		while (--i >= 0)
			write(1, &argv[1][i], 1);
	}
	write(1, "\n", 1);
	return (0);
}
```

---

## rot_13（program / write）

アルファベットを13文字ずらす（z の次は a に戻る）。大文字・小文字は保つ。

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
				c = (c - 'a' + 13) % 26 + 'a';
			else if (c >= 'A' && c <= 'Z')
				c = (c - 'A' + 13) % 26 + 'A';
			write(1, &c, 1);
			s++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
```

---

## rotone（program / write）

rot_13 と同じ形で、ずらす量が 1。上のコードの `13` を `1` に変えるだけ。

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
				c = (c - 'a' + 1) % 26 + 'a';
			else if (c >= 'A' && c <= 'Z')
				c = (c - 'A' + 1) % 26 + 'A';
			write(1, &c, 1);
			s++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
```

---

## search_and_replace（program / write）

`./search_and_replace "str" "a" "b"` — str の中の文字 a を b に置き換えて出力する。
引数が3個でない場合、または 2番目・3番目の引数が1文字でない場合は `\n` だけ出力する。

```c
#include <unistd.h>

int	main(int argc, char **argv)
{
	char	*s;

	if (argc == 4 && argv[2][0] && !argv[2][1] && argv[3][0] && !argv[3][1])
	{
		s = argv[1];
		while (*s)
		{
			if (*s == argv[2][0])
				write(1, &argv[3][0], 1);
			else
				write(1, s, 1);
			s++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
```

---

## ulstr（program / write）

大文字と小文字を入れ替える。

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
				c -= 32;
			else if (c >= 'A' && c <= 'Z')
				c += 32;
			write(1, &c, 1);
			s++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
```
