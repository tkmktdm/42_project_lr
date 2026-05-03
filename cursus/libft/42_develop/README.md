*This project has been created as part of the 42 curriculum by htakumi.*

# libft — 自作Cライブラリ

## Description

libft は、C標準ライブラリの関数を自前で再実装した独自のCライブラリです。
42のカリキュラム全体を通じて活用できる汎用的な関数群を一から実装することで、
メモリ操作・文字列処理・リスト操作の仕組みを深く理解することを目的としています。

ライブラリは以下の3パートで構成されています：

| パート | 内容                                   |
| ------ | -------------------------------------- |
| Part 1 | libc標準関数の再実装（23関数）         |
| Part 2 | libcにないユーティリティ関数（11関数） |
| Part 3 | 連結リスト操作関数（9関数）            |

---

## Instructions

### ビルド

```bash
# libft.a をビルドする（全パート含む）
make

# オブジェクトファイルを削除
make clean

# オブジェクトファイルと libft.a を削除
make fclean

# 再ビルド（fclean + all）
make re
```

### プロジェクトへの組み込み方

```bash
# ヘッダをインクルードし、libft.a にリンクしてコンパイル
cc -Wall -Wextra -Werror main.c -L. -lft -I. -o program
```

```c
#include "libft.h"

int main(void)
{
    char    **words;
    int     i;

    words = ft_split("hello world 42", ' ');
    i = 0;
    while (words[i])
    {
        ft_putendl_fd(words[i], 1);
        free(words[i++]);
    }
    free(words);
    return (0);
}
```

---

## ライブラリの詳細説明

### Part 1 — libc 関数の再実装

標準ライブラリと同じ仕様で実装しています。

#### 文字判定系

| 関数           | プロトタイプ              | 説明                                   |
| -------------- | ------------------------- | -------------------------------------- |
| `ft_isalpha` | `int ft_isalpha(int c)` | アルファベットなら1、それ以外は0を返す |
| `ft_isdigit` | `int ft_isdigit(int c)` | 数字（0〜9）なら1、それ以外は0を返す   |
| `ft_isalnum` | `int ft_isalnum(int c)` | アルファベットまたは数字なら1を返す    |
| `ft_isascii` | `int ft_isascii(int c)` | ASCII文字（0〜127）なら1を返す         |
| `ft_isprint` | `int ft_isprint(int c)` | 印字可能文字なら1を返す                |
| `ft_toupper` | `int ft_toupper(int c)` | 小文字を大文字に変換して返す           |
| `ft_tolower` | `int ft_tolower(int c)` | 大文字を小文字に変換して返す           |

#### メモリ操作系

| 関数           | プロトタイプ                                                 | 説明                                   |
| -------------- | ------------------------------------------------------------ | -------------------------------------- |
| `ft_memset`  | `void *ft_memset(void *b, int c, size_t len)`              | メモリ領域を指定バイト値で埋める       |
| `ft_bzero`   | `void ft_bzero(void *s, size_t n)`                         | メモリ領域をゼロで埋める               |
| `ft_memcpy`  | `void *ft_memcpy(void *dst, const void *src, size_t n)`    | メモリをコピーする（重複不可）         |
| `ft_memmove` | `void *ft_memmove(void *dst, const void *src, size_t len)` | メモリをコピーする（重複可）           |
| `ft_memchr`  | `void *ft_memchr(const void *s, int c, size_t n)`          | メモリ内から最初に一致するバイトを探す |
| `ft_memcmp`  | `int ft_memcmp(const void *s1, const void *s2, size_t n)`  | 2つのメモリ領域を比較する              |
| `ft_calloc`  | `void *ft_calloc(size_t count, size_t size)`               | ゼロ初期化されたメモリを確保する       |

#### 文字列操作系

| 関数           | プロトタイプ                                                               | 説明                               |
| -------------- | -------------------------------------------------------------------------- | ---------------------------------- |
| `ft_strlen`  | `size_t ft_strlen(const char *s)`                                        | 文字列の長さを返す                 |
| `ft_strlcpy` | `size_t ft_strlcpy(char *dst, const char *src, size_t dstsize)`          | NUL終端を保証してコピーする        |
| `ft_strlcat` | `size_t ft_strlcat(char *dst, const char *src, size_t dstsize)`          | NUL終端を保証して連結する          |
| `ft_strchr`  | `char *ft_strchr(const char *s, int c)`                                  | 文字列内で最初に一致する文字を探す |
| `ft_strrchr` | `char *ft_strrchr(const char *s, int c)`                                 | 文字列内で最後に一致する文字を探す |
| `ft_strncmp` | `int ft_strncmp(const char *s1, const char *s2, size_t n)`               | 2つの文字列をn文字まで比較する     |
| `ft_strnstr` | `char *ft_strnstr(const char *haystack, const char *needle, size_t len)` | n文字以内で部分文字列を検索する    |
| `ft_strdup`  | `char *ft_strdup(const char *s1)`                                        | 文字列を複製して新しいメモリに返す |
| `ft_atoi`    | `int ft_atoi(const char *str)`                                           | 文字列を整数に変換する             |

---

### Part 2 — 追加ユーティリティ関数

libcにない独自関数です。

| 関数              | プロトタイプ                                                       | 説明                                        |
| ----------------- | ------------------------------------------------------------------ | ------------------------------------------- |
| `ft_substr`     | `char *ft_substr(char const *s, unsigned int start, size_t len)` | 文字列から部分文字列を切り出す              |
| `ft_strjoin`    | `char *ft_strjoin(char const *s1, char const *s2)`               | 2つの文字列を連結した新しい文字列を返す     |
| `ft_strtrim`    | `char *ft_strtrim(char const *s1, char const *set)`              | 先頭・末尾から指定文字集合を除去する        |
| `ft_split`      | `char **ft_split(char const *s, char c)`                         | 指定デリミタで文字列を分割し配列で返す      |
| `ft_itoa`       | `char *ft_itoa(int n)`                                           | 整数を文字列に変換する（負数・INT_MIN対応） |
| `ft_strmapi`    | `char *ft_strmapi(char const *s, char (*f)(unsigned int, char))` | 各文字に関数を適用した新しい文字列を返す    |
| `ft_striteri`   | `void ft_striteri(char *s, void (*f)(unsigned int, char *))`     | 各文字にインプレースで関数を適用する        |
| `ft_putchar_fd` | `void ft_putchar_fd(char c, int fd)`                             | 1文字を指定fdに出力する                     |
| `ft_putstr_fd`  | `void ft_putstr_fd(char *s, int fd)`                             | 文字列を指定fdに出力する                    |
| `ft_putendl_fd` | `void ft_putendl_fd(char *s, int fd)`                            | 文字列と改行を指定fdに出力する              |
| `ft_putnbr_fd`  | `void ft_putnbr_fd(int n, int fd)`                               | 整数を指定fdに出力する                      |

---

### Part 3 — 連結リスト操作

`t_list` 構造体を使ったリスト操作関数です。

```c
typedef struct s_list
{
    void            *content;   // 任意のデータ
    struct s_list   *next;      // 次のノードへのポインタ
}   t_list;
```

| 関数                | プロトタイプ                                                                | 説明                                        |
| ------------------- | --------------------------------------------------------------------------- | ------------------------------------------- |
| `ft_lstnew`       | `t_list *ft_lstnew(void *content)`                                        | 新しいノードを作成する                      |
| `ft_lstadd_front` | `void ft_lstadd_front(t_list **lst, t_list *new)`                         | リストの先頭にノードを追加する              |
| `ft_lstsize`      | `int ft_lstsize(t_list *lst)`                                             | リストのノード数を返す                      |
| `ft_lstlast`      | `t_list *ft_lstlast(t_list *lst)`                                         | 末尾ノードを返す                            |
| `ft_lstadd_back`  | `void ft_lstadd_back(t_list **lst, t_list *new)`                          | リストの末尾にノードを追加する              |
| `ft_lstdelone`    | `void ft_lstdelone(t_list *lst, void (*del)(void *))`                     | ノード1つを削除・解放する（次は解放しない） |
| `ft_lstclear`     | `void ft_lstclear(t_list **lst, void (*del)(void *))`                     | リスト全体を削除・解放しNULLにする          |
| `ft_lstiter`      | `void ft_lstiter(t_list *lst, void (*f)(void *))`                         | 各ノードのコンテンツに関数を適用する        |
| `ft_lstmap`       | `t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))` | 各ノードに関数を適用した新しいリストを返す  |

---

## Resources

- [C標準ライブラリリファレンス (cppreference)](https://en.cppreference.com/w/c)
- [man pages](https://linux.die.net/man/3/)
- [42 Norm](https://cdn.intra.42.fr/pdf/pdf/960/norme.en.pdf)

### AI の使用について

- **使用**: Part1~3のテスト生成の補助ツール、仕様書作成として使用
