# Libft 実装手順書

本書は Plan モードで **そのまま実行可能** な粒度に分解した実装タスク集。
subject / 要件書 / 設計書に完全準拠。差分があれば上位文書が優先。

- subject: `/Users/kota/dev/42-cursus/libft/subject/en.subject.pdf`
- 要件書: `/Users/kota/dev/42-cursus/libft/docs/requirements.md`
- 設計書: `/Users/kota/dev/42-cursus/libft/docs/design.md`

---

## 0. 実行前提

### 0.1 作業ディレクトリ

リポジトリ root = `/Users/kota/dev/42-cursus/libft/`

提出ファイルはすべてこの root に置く (subject IV.1 / VI)。
`subject/`, `docs/` は提出対象外。`tests/` は作らない (設計書 §10.2)。

### 0.2 共通規約 (全タスク共通)

| 項目 | 規約 |
|---|---|
| インデント | **タブ文字** (スペース不可、Norm) |
| フラグ | `-Wall -Wextra -Werror` |
| コンパイラ | `cc` |
| プロトタイプ | 要件書・設計書と一字一句一致 (`restrict` 不可) |
| グローバル変数 | 禁止 |
| ヘルパ関数 | `static` のみ |
| 関数本体 | 25 行以内 (超える場合は static で分割) |
| 1 ファイル関数数 | 5 個以下 |
| 変数宣言 | 関数先頭にまとめる |
| ループ | `while` 推奨 (Norm 保守派) |
| 戻り値型と関数名 | `.c` の関数定義では改行、ヘッダは 1 行 |

### 0.3 タスク完了基準 (各タスク共通)

以下すべて満たしたタスクのみ完了扱い:

1. `make` がエラー・警告なしで通る
2. `libft.a` が root に生成される
3. 警告 (`-Wall -Wextra -Werror`) ゼロ
4. 新規関数を簡易ドライバ (一時的な `main.c`) から呼び、期待値と一致
5. 簡易ドライバ確認後、**テストファイルは削除** (subject IV.1「未使用ファイル禁止」準拠)
6. (環境に norminette があれば) `norminette <file>` で `OK` 表示

### 0.4 簡易ドライバのテンプレート

タスク検証用に root 外へ一時的に書く:

```c
/* /tmp/libft_drv.c */
#include "libft.h"
#include <stdio.h>

int main(void)
{
    /* テスト対象関数の呼び出し */
    return (0);
}
```

コンパイル:

```sh
cc -Wall -Wextra -Werror -I /Users/kota/dev/42-cursus/libft /tmp/libft_drv.c /Users/kota/dev/42-cursus/libft/libft.a -o /tmp/libft_drv
/tmp/libft_drv
```

確認後:

```sh
rm /tmp/libft_drv /tmp/libft_drv.c
```

### 0.5 全体タスク数

- Phase 0: スケルトン 2 タスク
- Phase 1: Part 1 Group A (文字分類・基本メモリ) 10 タスク
- Phase 2: Part 1 Group B (メモリ・文字列操作) 10 タスク
- Phase 3: Part 1 Group C (変換・確保) 3 タスク
- Phase 4: Part 2 追加関数 11 タスク
- Phase 5: Part 3 連結リスト 9 タスク
- Phase 6: 最終検証 3 タスク

**合計 48 タスク**。Phase 0 → Phase 6 の順で実行。Phase 内のタスクは (依存がない限り) 並行実行可能だが、順次のほうが make の検証が確実。

---

## Phase 0: スケルトン

### Task 0.1: `libft.h` を作成

**ファイル**: `/Users/kota/dev/42-cursus/libft/libft.h`

**手順**: 以下をそのまま書き込む。インデントはタブ (` `→`\t`)。

```c
#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/* --- Part 1: libc functions --- */
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);

/* --- Part 2: additional functions --- */
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

/* --- Part 3: linked list --- */
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
```

**完了条件**:
- ファイル存在
- 43 プロトタイプが要件書 §5.2 / §6 / §7 と一字一句一致
- `t_list` 構造体が subject §IV.4 原文と一致
- インクルードガード `LIBFT_H` あり
- `<stddef.h>` のみ include
- `restrict` が含まれない

### Task 0.2: `Makefile` を作成

**ファイル**: `/Users/kota/dev/42-cursus/libft/Makefile`

**手順**: 以下をそのまま書き込む。インデントはタブ必須 (Makefile 構文要件)。

```makefile
NAME	= libft.a

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
AR		= ar rcs
RM		= rm -f

HEADER	= libft.h

SRCS_PART1	=

SRCS_PART2	=

SRCS_PART3	=

SRCS	= $(SRCS_PART1) $(SRCS_PART2) $(SRCS_PART3)
OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
```

**検証**:

```sh
cd /Users/kota/dev/42-cursus/libft
make          # 空 libft.a が作られる (ar が空アーカイブ作成)
ls libft.a    # 存在確認
make          # 2 回目: "Nothing to be done" が期待値
make clean    # .o (無し) の削除
make fclean   # libft.a 削除
ls libft.a    # 無し確認
```

**完了条件**:
- 必須ルール `all`, `clean`, `fclean`, `re`, `$(NAME)` 存在
- `-Wall -Wextra -Werror` 使用
- `cc` 使用、`ar` 使用
- `libtool` 不使用
- `.PHONY` 宣言あり
- 以降の Phase で `SRCS_PARTN` に追記していく

---

## Phase 1: Part 1 Group A (文字分類 + 基本メモリ) — 10 タスク

すべて subject IV.2「外部関数に依存してはならない」対象。libc 関数呼び出し禁止。

**各タスク共通手順**:
1. `/Users/kota/dev/42-cursus/libft/<file>.c` を作成
2. 下記「実装ロジック」に従い関数を書く
3. `Makefile` の `SRCS_PART1 =` 行に `<file>.c` をスペース区切りで追加 (改行継続 `\` を使ってよい)
4. `make fclean && make` でビルド確認
5. 簡易ドライバ (§0.4) で動作確認 → ドライバ削除

### Task 1.1: `ft_isalpha.c`

**プロトタイプ**: `int ft_isalpha(int c);`

**ロジック**: `(c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')` なら 1、それ以外 0。

**検証**: `ft_isalpha('A')==1`, `ft_isalpha('z')==1`, `ft_isalpha('0')==0`, `ft_isalpha(0)==0`, `ft_isalpha(128)==0`。

### Task 1.2: `ft_isdigit.c`

**プロトタイプ**: `int ft_isdigit(int c);`

**ロジック**: `c >= '0' && c <= '9'` なら 1、それ以外 0。

**検証**: `ft_isdigit('0')==1`, `ft_isdigit('9')==1`, `ft_isdigit('a')==0`, `ft_isdigit(-1)==0`。

### Task 1.3: `ft_isalnum.c`

**プロトタイプ**: `int ft_isalnum(int c);`

**ロジック**: isalpha と isdigit の条件式を **直書き** (設計書 §5.2 方針)。libc/libft 関数は呼ばない。

```
(c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') → 1 else 0
```

**検証**: `ft_isalnum('A')==1`, `ft_isalnum('5')==1`, `ft_isalnum('@')==0`。

### Task 1.4: `ft_isascii.c`

**プロトタイプ**: `int ft_isascii(int c);`

**ロジック**: `c >= 0 && c <= 127` なら 1。

**検証**: `ft_isascii(0)==1`, `ft_isascii(127)==1`, `ft_isascii(128)==0`, `ft_isascii(-1)==0`。

### Task 1.5: `ft_isprint.c`

**プロトタイプ**: `int ft_isprint(int c);`

**ロジック**: `c >= 32 && c <= 126` (スペース〜`~`) なら 1。

**検証**: `ft_isprint(' ')==1`, `ft_isprint('~')==1`, `ft_isprint(31)==0`, `ft_isprint(127)==0`。

### Task 1.6: `ft_strlen.c`

**プロトタイプ**: `size_t ft_strlen(const char *s);`

**ロジック**: `while (s[i] != '\0') i++;` で長さ計測。`i` を返す (`size_t`)。

**検証**: `ft_strlen("")==0`, `ft_strlen("abc")==3`。

### Task 1.7: `ft_memset.c`

**プロトタイプ**: `void *ft_memset(void *b, int c, size_t len);`

**ロジック**:
1. `unsigned char *p = (unsigned char *)b;`
2. `while (i < len) p[i++] = (unsigned char)c;`
3. `b` を返す

**検証**: `char buf[5]; ft_memset(buf, 'A', 3);` で `buf[0..2]=='A'`。

### Task 1.8: `ft_bzero.c`

**プロトタイプ**: `void ft_bzero(void *s, size_t n);`

**ロジック**: 内部で memset と同じ処理を直書き (`p[i++] = 0;`)。`ft_memset` を呼ばず自己完結。

**検証**: `char buf[5]; ft_bzero(buf, 3);` で `buf[0..2]==0`。

### Task 1.9: `ft_memcpy.c`

**プロトタイプ**: `void *ft_memcpy(void *dst, const void *src, size_t n);`

**ロジック**:
1. `if (n == 0) return dst;` (設計書 §5.4)
2. `unsigned char *d = dst; const unsigned char *s = src;`
3. `while (i < n) d[i] = s[i]; i++;`
4. `dst` を返す

**注意**: overlap は考慮しない (memmove の責務)。`n > 0` で `dst==NULL && src==NULL` は undefined のまま許容。

**検証**: `char d[5]; char s[]="abc"; ft_memcpy(d, s, 4);` で `d=="abc"`。

### Task 1.10: `ft_memmove.c`

**プロトタイプ**: `void *ft_memmove(void *dst, const void *src, size_t len);`

**ロジック**:
1. `if (dst == src || len == 0) return dst;`
2. `if (dst < src)` → 先頭から `i = 0..len-1` でコピー
3. `else` → 末尾から `i = len-1..0` でコピー (逆順)
4. `dst` を返す

**検証**: overlap パターン `char buf[]="abcdef"; ft_memmove(buf+1, buf, 4);` → `buf=="aabcdf"`。

### Phase 1 終了時の Makefile SRCS_PART1

```
SRCS_PART1	= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
			  ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
			  ft_memcpy.c ft_memmove.c
```

**Phase 1 完了条件**: 10 ファイル存在、`make re` 成功、警告ゼロ、各関数動作確認済み。

---

## Phase 2: Part 1 Group B (メモリ・文字列操作) — 10 タスク

### Task 2.1: `ft_strlcpy.c`

**プロトタイプ**: `size_t ft_strlcpy(char *dst, const char *src, size_t dstsize);`

**ロジック** (BSD 準拠):
1. `size_t srclen = 0; while (src[srclen]) srclen++;`
2. `if (dstsize > 0)`:
   - `size_t i = 0; while (i < dstsize - 1 && src[i]) { dst[i] = src[i]; i++; } dst[i] = '\0';`
3. `return srclen;`

**検証**: `ft_strlcpy(buf, "hello", 3)` → buf="he"、戻り値 5。

### Task 2.2: `ft_strlcat.c`

**プロトタイプ**: `size_t ft_strlcat(char *dst, const char *src, size_t dstsize);`

**ロジック** (BSD 準拠):
1. `size_t dl = 0; while (dl < dstsize && dst[dl]) dl++;` (dst 長、dstsize で打ち切り)
2. `size_t sl = 0; while (src[sl]) sl++;`
3. `if (dl == dstsize) return dstsize + sl;` (dst が終端なし、何もしない)
4. `i = 0; while (src[i] && dl + i < dstsize - 1) { dst[dl+i] = src[i]; i++; } dst[dl+i] = '\0';`
5. `return dl + sl;`

**検証**: buf="abc\0  ", `ft_strlcat(buf, "de", 6)` → buf="abcde"、戻り値 5。

### Task 2.3: `ft_toupper.c`

**プロトタイプ**: `int ft_toupper(int c);`

**ロジック**: `c >= 'a' && c <= 'z'` なら `c - 32`、それ以外は `c`。

**検証**: `ft_toupper('a')=='A'`, `ft_toupper('A')=='A'`, `ft_toupper('1')=='1'`。

### Task 2.4: `ft_tolower.c`

**プロトタイプ**: `int ft_tolower(int c);`

**ロジック**: `c >= 'A' && c <= 'Z'` なら `c + 32`、それ以外は `c`。

**検証**: `ft_tolower('A')=='a'`, `ft_tolower('a')=='a'`。

### Task 2.5: `ft_strchr.c`

**プロトタイプ**: `char *ft_strchr(const char *s, int c);`

**ロジック**:
1. `unsigned char ch = (unsigned char)c;`
2. `while (*s) { if ((unsigned char)*s == ch) return (char *)s; s++; }`
3. ループ抜けたら末尾 `'\0'` 位置。`ch == 0` なら `(char *)s` を返す、そうでなければ NULL

**検証**: `ft_strchr("hello", 'l')` が 'l' 位置を指す。`ft_strchr("abc", '\0')` が末尾 `'\0'` を指す。

### Task 2.6: `ft_strrchr.c`

**プロトタイプ**: `char *ft_strrchr(const char *s, int c);`

**ロジック**:
1. `unsigned char ch = (unsigned char)c;`
2. `const char *last = NULL; size_t i = 0;`
3. `while (s[i]) { if ((unsigned char)s[i] == ch) last = &s[i]; i++; }`
4. `if (ch == 0) return (char *)&s[i];`
5. `return (char *)last;` (見つからなければ NULL)

**検証**: `ft_strrchr("abcba", 'b')` → 後ろの 'b' 位置。

### Task 2.7: `ft_strncmp.c`

**プロトタイプ**: `int ft_strncmp(const char *s1, const char *s2, size_t n);`

**ロジック**:
1. `size_t i = 0;`
2. `while (i < n && (s1[i] || s2[i]))`:
   - `if (s1[i] != s2[i]) return (unsigned char)s1[i] - (unsigned char)s2[i];`
   - `i++;`
3. `return 0;`

**検証**: `ft_strncmp("abc", "abd", 3) < 0`, `ft_strncmp("abc", "abc", 3) == 0`。

### Task 2.8: `ft_memchr.c`

**プロトタイプ**: `void *ft_memchr(const void *s, int c, size_t n);`

**ロジック**:
1. `const unsigned char *p = s; unsigned char ch = (unsigned char)c;`
2. `while (i < n) { if (p[i] == ch) return (void *)&p[i]; i++; }`
3. `return NULL;`

**検証**: `ft_memchr("abcdef", 'c', 6)` が 'c' 位置。

### Task 2.9: `ft_memcmp.c`

**プロトタイプ**: `int ft_memcmp(const void *s1, const void *s2, size_t n);`

**ロジック**:
1. `const unsigned char *a = s1; const unsigned char *b = s2;`
2. `while (i < n) { if (a[i] != b[i]) return a[i] - b[i]; i++; }`
3. `return 0;`

**検証**: `ft_memcmp("abc", "abd", 3) < 0`。

### Task 2.10: `ft_strnstr.c`

**プロトタイプ**: `char *ft_strnstr(const char *haystack, const char *needle, size_t len);`

**ロジック**:
1. `if (needle[0] == '\0') return (char *)haystack;` (man 準拠)
2. `size_t nlen = 0; while (needle[nlen]) nlen++;`
3. `size_t i = 0;`
4. `while (i + nlen <= len && haystack[i])`:
   - 内側ループで `haystack[i..i+nlen-1]` と `needle` を比較
   - 一致なら `return (char *)&haystack[i];`
   - `i++;`
5. `return NULL;`

**注意**: `i + nlen <= len` 条件で len を超えないことを保証。

**検証**: `ft_strnstr("hello world", "world", 11)` → "world" 位置。`ft_strnstr("hi", "", 2)` → "hi" 位置。

### Phase 2 終了時の SRCS_PART1

```
SRCS_PART1	= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
			  ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
			  ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
			  ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
			  ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c
```

**Phase 2 完了条件**: 20 ファイル、`make re` 成功、警告ゼロ、各関数動作確認済み。

---

## Phase 3: Part 1 Group C (変換・確保) — 3 タスク

### Task 3.1: `ft_atoi.c`

**プロトタイプ**: `int ft_atoi(const char *str);`

**ロジック**:
1. `size_t i = 0; int sign = 1; int result = 0;`
2. 空白スキップ: `while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)) i++;` (スペース, \t, \n, \v, \f, \r)
3. 符号: `if (str[i] == '+' || str[i] == '-') { if (str[i] == '-') sign = -1; i++; }`
4. 数字累積: `while (str[i] >= '0' && str[i] <= '9') { result = result * 10 + (str[i] - '0'); i++; }`
5. `return result * sign;`

**注意**: man atoi 準拠で overflow 挙動は未定義。defensive な overflow チェックは行わない (設計書 §5.6)。

**検証**: `ft_atoi("   -42abc")==-42`, `ft_atoi("+123")==123`, `ft_atoi("")==0`。

### Task 3.2: `ft_calloc.c`

**プロトタイプ**: `void *ft_calloc(size_t count, size_t size);`

**必要な include**: `<stdlib.h>` (malloc), `<limits.h>` (SIZE_MAX)。`.c` 側で include。

**ロジック**:
1. オーバーフロー検出: `if (size != 0 && count > SIZE_MAX / size) return NULL;` (設計書 §5.6、defensive)
2. `size_t total = count * size;`
3. `void *p = malloc(total);`
4. `if (!p) return NULL;`
5. 0 埋め: `unsigned char *b = p; size_t i = 0; while (i < total) b[i++] = 0;` (自己完結、ft_bzero 不使用)
6. `return p;`

**注意**: `count == 0 || size == 0` の場合 `total == 0`、`malloc(0)` は実装依存だが subject 要件「free() 可能な unique ポインタ」を満たす (macOS の malloc(0) も unique ポインタ返却)。

**検証**: `int *p = ft_calloc(3, sizeof(int));` で `p[0]==p[1]==p[2]==0`、`free(p);` がクラッシュしない。`ft_calloc(0, 0)` が `free()` 可能なポインタを返す。

### Task 3.3: `ft_strdup.c`

**プロトタイプ**: `char *ft_strdup(const char *s1);`

**必要な include**: `<stdlib.h>` (malloc)。

**ロジック**:
1. `size_t len = 0; while (s1[len]) len++;`
2. `char *dup = malloc(len + 1);`
3. `if (!dup) return NULL;`
4. `size_t i = 0; while (i < len) { dup[i] = s1[i]; i++; } dup[len] = '\0';`
5. `return dup;`

**検証**: `char *d = ft_strdup("hello");` → `d` が別アドレスで内容 "hello"、`free(d)` 正常。

### Phase 3 終了時の SRCS_PART1

```
SRCS_PART1	= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
			  ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
			  ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
			  ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
			  ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
			  ft_atoi.c ft_calloc.c ft_strdup.c
```

**Phase 3 完了条件**: 23 ファイル、`make re` 成功。Part 1 完了。

---

## Phase 4: Part 2 追加関数 — 11 タスク

Part 2 からは内部で `ft_strlen` 等の libft 関数を呼んでよい (設計書 §6.12)。
`malloc` 失敗時は必ず NULL を返し、途中確保したメモリはすべて解放する。

### Task 4.1: `ft_substr.c`

**プロトタイプ**: `char *ft_substr(char const *s, unsigned int start, size_t len);`

**必要な include**: `<stdlib.h>`。

**ロジック**:
1. `if (!s) return NULL;`
2. `size_t slen = ft_strlen(s);`
3. `if (start >= slen) { return ft_strdup(""); }` (空文字列を malloc して返す)
4. `size_t copy_len = slen - start; if (copy_len > len) copy_len = len;`
5. `char *sub = malloc(copy_len + 1);`
6. `if (!sub) return NULL;`
7. `i = 0; while (i < copy_len) { sub[i] = s[start + i]; i++; } sub[copy_len] = '\0';`
8. `return sub;`

**検証**: `ft_substr("hello", 1, 3)` → "ell"、`ft_substr("abc", 10, 5)` → ""。

### Task 4.2: `ft_strjoin.c`

**プロトタイプ**: `char *ft_strjoin(char const *s1, char const *s2);`

**ロジック**:
1. `if (!s1 || !s2) return NULL;`
2. `size_t l1 = ft_strlen(s1); size_t l2 = ft_strlen(s2);`
3. `char *r = malloc(l1 + l2 + 1); if (!r) return NULL;`
4. s1 をコピー、続けて s2 をコピー、末尾 `'\0'`
5. `return r;`

**検証**: `ft_strjoin("abc", "def")` → "abcdef"。

### Task 4.3: `ft_strtrim.c`

**プロトタイプ**: `char *ft_strtrim(char const *s1, char const *set);`

**ロジック**:
1. `if (!s1 || !set) return NULL;`
2. `static int in_set(char c, char const *set)` ヘルパを同ファイルに定義
3. 前方 `i`、後方 `j` で trim 範囲を決定:
   - `while (s1[i] && in_set(s1[i], set)) i++;`
   - `j = ft_strlen(s1); while (j > i && in_set(s1[j-1], set)) j--;`
4. `char *r = malloc(j - i + 1); if (!r) return NULL;`
5. `s1[i..j-1]` をコピー、末尾 `'\0'`

**検証**: `ft_strtrim("  hi  ", " ")` → "hi"、`ft_strtrim("aaa", "a")` → ""。

### Task 4.4: `ft_split.c`

**プロトタイプ**: `char **ft_split(char const *s, char c);`

**実装**: ヘルパ複数で分割 (Norm 25 行制約)。以下はすべて同ファイル内 `static`:

- `static size_t word_count(char const *s, char c)`: 非 c 文字の連続回数を数える
- `static size_t word_len(char const *s, char c)`: 先頭単語長
- `static void free_all(char **arr, size_t n)`: `arr[0..n-1]` を free、`arr` 自体も free

**本体ロジック**:
1. `if (!s) return NULL;`
2. `size_t wc = word_count(s, c);`
3. `char **arr = malloc(sizeof(char *) * (wc + 1)); if (!arr) return NULL;`
4. `size_t idx = 0; size_t i = 0;`
5. `while (idx < wc)`:
   - 区切りスキップ: `while (s[i] == c) i++;`
   - `size_t wl = word_len(&s[i], c);`
   - `arr[idx] = ft_substr(s, i, wl);`
   - `if (!arr[idx]) { free_all(arr, idx); return NULL; }`
   - `i += wl; idx++;`
6. `arr[wc] = NULL;` (NULL 終端、要件書 §6.4)
7. `return arr;`

**検証**: `ft_split("a,b,c", ',')` → `["a","b","c",NULL]`。`ft_split(",,,", ',')` → `[NULL]`。

### Task 4.5: `ft_itoa.c`

**プロトタイプ**: `char *ft_itoa(int n);`

**実装**: ヘルパで桁数計算。

- `static size_t num_len(int n)`: 符号含む文字数 (n==0 なら 1、負なら +1)

**本体ロジック**:
1. `size_t len = num_len(n);`
2. `char *r = malloc(len + 1); if (!r) return NULL;`
3. `r[len] = '\0';`
4. `unsigned int abs_n;` (INT_MIN 対応のため unsigned で扱う)
   - `if (n < 0) { r[0] = '-'; abs_n = -(unsigned int)n; } else { abs_n = n; }`
5. ループ下限を先に決める (Norm は三項演算子不可):
   - `size_t start;`
   - `if (n < 0) start = 1; else start = 0;`
6. `size_t i = len; while (i > start) { i--; r[i] = '0' + (abs_n % 10); abs_n /= 10; }`
7. **注意**: n==0 の場合も `r[0] = '0'` になること (num_len が 1 を返せばループで書き込まれる)
8. `return r;`

**検証**: `ft_itoa(0)` → "0"、`ft_itoa(-42)` → "-42"、`ft_itoa(INT_MIN)` → "-2147483648"。

### Task 4.6: `ft_strmapi.c`

**プロトタイプ**: `char *ft_strmapi(char const *s, char (*f)(unsigned int, char));`

**ロジック**:
1. `if (!s || !f) return NULL;`
2. `size_t len = ft_strlen(s);`
3. `char *r = malloc(len + 1); if (!r) return NULL;`
4. `unsigned int i = 0; while (i < len) { r[i] = f(i, s[i]); i++; } r[len] = '\0';`
5. `return r;`

**検証**: 各文字を大文字化する `f` を渡して "abc" → "ABC"。

### Task 4.7: `ft_striteri.c`

**プロトタイプ**: `void ft_striteri(char *s, void (*f)(unsigned int, char*));`

**ロジック**:
1. `if (!s || !f) return;`
2. `unsigned int i = 0; while (s[i]) { f(i, &s[i]); i++; }`

**注意**: **アドレス渡し** で modify 可能 (要件書 §6.7)。

**検証**: 各文字をインデックス + 文字で書き換える `f` を渡して動作確認。

### Task 4.8: `ft_putchar_fd.c`

**プロトタイプ**: `void ft_putchar_fd(char c, int fd);`

**必要な include**: `<unistd.h>` (write)。

**ロジック**: `write(fd, &c, 1);`

**検証**: `ft_putchar_fd('A', 1);` で標準出力に `A`。

### Task 4.9: `ft_putstr_fd.c`

**プロトタイプ**: `void ft_putstr_fd(char *s, int fd);`

**必要な include**: `<unistd.h>`。

**ロジック**:
1. `if (!s) return;`
2. `write(fd, s, ft_strlen(s));`

**検証**: `ft_putstr_fd("hello", 1);` で `hello`。

### Task 4.10: `ft_putendl_fd.c`

**プロトタイプ**: `void ft_putendl_fd(char *s, int fd);`

**ロジック**: 内部で `ft_putstr_fd(s, fd); ft_putchar_fd('\n', fd);`

**検証**: `ft_putendl_fd("hi", 1);` で `hi\n`。

### Task 4.11: `ft_putnbr_fd.c`

**プロトタイプ**: `void ft_putnbr_fd(int n, int fd);`

**実装**: INT_MIN 対応のため、内部ヘルパで unsigned に変換。

- `static void put_uint(unsigned int n, int fd)`: 再帰で上位桁から出力
  - `if (n >= 10) put_uint(n / 10, fd);`
  - `ft_putchar_fd('0' + (n % 10), fd);`

**本体ロジック**:
1. `unsigned int u;`
2. `if (n < 0) { ft_putchar_fd('-', fd); u = -(unsigned int)n; } else { u = n; }`
3. `put_uint(u, fd);`

**検証**: `ft_putnbr_fd(-2147483648, 1);` で `-2147483648`。

### Phase 4 終了時の SRCS_PART2

```
SRCS_PART2	= ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
			  ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
			  ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
```

**Phase 4 完了条件**: 34 ファイル、`make re` 成功、警告ゼロ、valgrind/leaks でリークなし。

---

## Phase 5: Part 3 連結リスト — 9 タスク

すべて `t_list` を操作。`#include "libft.h"` で `t_list` を参照。

### Task 5.1: `ft_lstnew.c`

**プロトタイプ**: `t_list *ft_lstnew(void *content);`

**必要な include**: `<stdlib.h>`。

**ロジック**:
1. `t_list *node = malloc(sizeof(t_list));`
2. `if (!node) return NULL;`
3. `node->content = content; node->next = NULL;`
4. `return node;`

**検証**: `t_list *n = ft_lstnew("x");` → `n->content == "x"`, `n->next == NULL`。

### Task 5.2: `ft_lstadd_front.c`

**プロトタイプ**: `void ft_lstadd_front(t_list **lst, t_list *new);`

**ロジック**:
1. `if (!lst || !new) return;`
2. `new->next = *lst; *lst = new;`

**検証**: 空リストに追加、既存リストの先頭に追加。

### Task 5.3: `ft_lstsize.c`

**プロトタイプ**: `int ft_lstsize(t_list *lst);`

**ロジック**:
1. `int count = 0;`
2. `while (lst) { count++; lst = lst->next; }`
3. `return count;`

**検証**: 空 → 0、3 要素 → 3。

### Task 5.4: `ft_lstlast.c`

**プロトタイプ**: `t_list *ft_lstlast(t_list *lst);`

**ロジック**:
1. `if (!lst) return NULL;`
2. `while (lst->next) lst = lst->next;`
3. `return lst;`

**検証**: 3 要素リストで最後の要素が返る。

### Task 5.5: `ft_lstadd_back.c`

**プロトタイプ**: `void ft_lstadd_back(t_list **lst, t_list *new);`

**ロジック**:
1. `if (!lst || !new) return;`
2. `if (!*lst) { *lst = new; return; }`
3. `ft_lstlast(*lst)->next = new;`

**検証**: 空リストと既存リストの両方に追加可能。

### Task 5.6: `ft_lstdelone.c`

**プロトタイプ**: `void ft_lstdelone(t_list *lst, void (*del)(void *));`

**必要な include**: `<stdlib.h>` (free)。

**ロジック**:
1. `if (!lst || !del) return;`
2. `del(lst->content);`
3. `free(lst);`

**注意**: **`lst->next` は絶対に free しない** (subject §IV.4 明記、設計書 §7.6)。

**検証**: `free` 可能な content で `ft_lstdelone(node, free);`、valgrind でリークなし、next ノードは残る。

### Task 5.7: `ft_lstclear.c`

**プロトタイプ**: `void ft_lstclear(t_list **lst, void (*del)(void *));`

**ロジック**:
1. `if (!lst || !del) return;`
2. `t_list *cur = *lst;`
3. `while (cur) { t_list *next = cur->next; ft_lstdelone(cur, del); cur = next; }`
4. `*lst = NULL;` (要件書 §7.7 / subject §IV.4 明記)

**検証**: 3 要素を `ft_lstclear(&head, free);` で全 free、`head == NULL`、valgrind リークなし。

### Task 5.8: `ft_lstiter.c`

**プロトタイプ**: `void ft_lstiter(t_list *lst, void (*f)(void *));`

**ロジック**:
1. `if (!lst || !f) return;`
2. `while (lst) { f(lst->content); lst = lst->next; }`

**検証**: `f` が各 content を処理することを確認 (例: カウンタ加算)。

### Task 5.9: `ft_lstmap.c`

**プロトタイプ**: `t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));`

**ロジック** (設計書 §7.9 詳細):
1. `if (!lst || !f) return NULL;`
2. `t_list *new_head = NULL;`
3. `while (lst)`:
   - `void *new_content = f(lst->content);`
   - `t_list *new_node = ft_lstnew(new_content);`
   - `if (!new_node)`:
     - `del(new_content);` (今回反復の content を解放)
     - `ft_lstclear(&new_head, del);` (既存新リスト全体を解放)
     - `return NULL;`
   - `ft_lstadd_back(&new_head, new_node);`
   - `lst = lst->next;`
4. `return new_head;`

**検証**:
- 3 要素リストに `f = strdup-like` を適用 → 新 3 要素リスト、元リストと独立
- malloc 失敗模擬 (大量確保など) 時にリーク無し (valgrind)

### Phase 5 終了時の SRCS_PART3

```
SRCS_PART3	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			  ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
			  ft_lstmap.c
```

**Phase 5 完了条件**: 43 ファイル、`make re` 成功、警告ゼロ、リークゼロ。Mandatory 実装完了。

---

## Phase 6: 最終検証 — 3 タスク

### Task 6.1: Norm (norminette) チェック

**目的**: Norm 違反 0 を確認 (subject II 「Norm エラーがあれば 0 点」)。

**手順**:

```sh
cd /Users/kota/dev/42-cursus/libft
norminette libft.h ft_*.c
```

- 全ファイルで `OK!` が出ること
- `Error` が出たら該当箇所を修正。典型違反:
  - タブ/スペース混在
  - 1 関数 25 行超え → ヘルパ分割
  - 変数宣言が関数先頭でない
  - 1 行 80 字超え → 改行
  - `for` 不使用 (現行 norminette は `for` 許可だが安全のため `while` を推奨)

**完了条件**: 全ファイル norminette `OK!`。norminette 未インストールの場合は項目「省略可」だが、defense 前には必ず実行。

### Task 6.2: メモリリーク・クラッシュチェック

**目的**: subject II 「メモリリーク・クラッシュ不可」を満たす確認。

**手順** (macOS):

```sh
cat > /tmp/libft_full_drv.c << 'EOF'
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static void *f_strdup(void *c) { return ft_strdup((char *)c); }
static void f_upper_addr(unsigned int i, char *c) { (void)i; if (*c >= 'a' && *c <= 'z') *c -= 32; }
static char f_upper_val(unsigned int i, char c) { (void)i; if (c >= 'a' && c <= 'z') return c - 32; return c; }

int main(void)
{
    /* Part 2 alloc 系を総動員 */
    char    *s = ft_substr("hello world", 6, 5);
    char    *j = ft_strjoin("foo", "bar");
    char    *t = ft_strtrim("  hi  ", " ");
    char    **sp = ft_split("a,b,c,,d", ',');
    char    *it = ft_itoa(INT_MIN);
    char    *sm = ft_strmapi("abc", f_upper_val);                /* 正常系 f */
    char    *sm_null = ft_strmapi("abc", NULL);                   /* defensive NULL パス */
    (void)sm_null;
    printf("%s|%s|%s|%s|%s\n", s, j, t, it, sm);
    for (int i = 0; sp[i]; i++) printf("[%s]", sp[i]);
    printf("\n");
    free(s); free(j); free(t); free(it); free(sm);
    for (int i = 0; sp[i]; i++) free(sp[i]);
    free(sp);

    /* Part 3 リスト */
    t_list *lst = ft_lstnew(ft_strdup("a"));
    ft_lstadd_back(&lst, ft_lstnew(ft_strdup("b")));
    ft_lstadd_back(&lst, ft_lstnew(ft_strdup("c")));
    t_list *mapped = ft_lstmap(lst, f_strdup, free);
    ft_lstclear(&lst, free);
    ft_lstclear(&mapped, free);

    /* striteri */
    char buf[] = "xyz";
    ft_striteri(buf, f_upper_addr);
    printf("%s\n", buf);

    return (0);
}
EOF

cc -Wall -Wextra -Werror -I /Users/kota/dev/42-cursus/libft /tmp/libft_full_drv.c /Users/kota/dev/42-cursus/libft/libft.a -o /tmp/libft_full_drv
leaks --atExit -- /tmp/libft_full_drv
```

**期待結果**:
- コンパイル警告ゼロ
- 実行クラッシュなし
- `leaks Report: ... 0 leaks for 0 total leaked bytes`

**Linux 環境の場合**: `valgrind --leak-check=full /tmp/libft_full_drv` を使う。

**完了条件**: リーク 0、クラッシュなし。終わったら `/tmp/libft_full_drv*` を削除。

### Task 6.3: `README.md` 作成

**目的**: subject Chapter V 準拠の README をリポジトリ root に作成。

**ファイル**: `/Users/kota/dev/42-cursus/libft/README.md`

**テンプレート**:

```markdown
*This project has been created as part of the 42 curriculum by <your-login>.*

## Description

Libft is the first 42 project: a self-made C library (`libft.a`) that
reimplements a selection of standard libc functions plus additional
string / memory / linked-list utilities. The library becomes the
foundation for every subsequent C project in the 42 curriculum.

## Instructions

Build the static library at the repository root:

```sh
make          # produces libft.a
make clean    # removes object files
make fclean   # removes object files and libft.a
make re       # fclean + all
```

Link against it from another project:

```sh
cc -Wall -Wextra -Werror your_main.c -L. -lft -o your_program
# or link libft.a directly:
cc -Wall -Wextra -Werror your_main.c libft.a -o your_program
```

Include the header:

```c
#include "libft.h"
```

## Resources

- C standard (`man 3 strlen`, `man 3 memcpy`, etc.)
- 42 intranet: Libft project page
- BSD `strlcpy` / `strlcat` specifications

### AI usage

AI (Claude) was used in this project for:
- Reviewing the subject PDF and producing a Japanese requirements
  summary (`docs/requirements.md`)
- Drafting the architectural design (`docs/design.md`)
- Producing the step-by-step implementation guide (`docs/implementation.md`)
- Spot-checking Norm compliance and Makefile dependency rules

All actual C implementations, debugging, and testing were performed by
the author; AI output was used as scaffolding and review, not as
drop-in code.

## Library details

### Part 1 — libc reimplementations (23 functions)

Character classification: `ft_isalpha`, `ft_isdigit`, `ft_isalnum`,
`ft_isascii`, `ft_isprint` (return 1 / 0).

Case conversion: `ft_toupper`, `ft_tolower`.

String length / search: `ft_strlen`, `ft_strchr`, `ft_strrchr`,
`ft_strncmp`, `ft_strnstr`, `ft_memchr`, `ft_memcmp`.

Memory manipulation: `ft_memset`, `ft_bzero`, `ft_memcpy`, `ft_memmove`.

Safe string copy: `ft_strlcpy`, `ft_strlcat` (BSD-style, returning
intended length).

Conversion / allocation: `ft_atoi`, `ft_calloc` (zero-init, 0-size
returns a free()-able unique pointer), `ft_strdup`.

### Part 2 — additional helpers (11 functions)

String construction: `ft_substr`, `ft_strjoin`, `ft_strtrim`, `ft_split`
(NULL-terminated array), `ft_itoa` (handles `INT_MIN`).

String mapping: `ft_strmapi`, `ft_striteri` (by-address).

File-descriptor output: `ft_putchar_fd`, `ft_putstr_fd`, `ft_putendl_fd`,
`ft_putnbr_fd`.

### Part 3 — linked list (9 functions)

Struct:

```c
typedef struct s_list
{
    void            *content;
    struct s_list   *next;
}   t_list;
```

Node / list ops: `ft_lstnew`, `ft_lstadd_front`, `ft_lstsize`,
`ft_lstlast`, `ft_lstadd_back`, `ft_lstdelone` (never frees `next`),
`ft_lstclear` (sets pointer to NULL), `ft_lstiter`, `ft_lstmap` (frees
partially-built new list on allocation failure).

### Constraints

- Written in C, compiled with `cc -Wall -Wextra -Werror`
- Norm-compliant (42 norminette)
- No global variables, helpers declared `static`
- No memory leaks under valgrind / leaks
- Library archive produced with `ar rcs`
```

**完了条件**:
- 1 行目が斜体で `*This project has been created as part of the 42 curriculum by <login1>[, <login2>[, <login3>[...]]].*` パターン (複数人なら全員列挙)
- Description / Instructions / Resources セクション存在
- Resources に AI 使用記述あり
- ライブラリ詳細説明セクション存在 (要件書 §8 の追加要求)

---

## 7. 全 Phase 完了後のチェックリスト

### 7.1 提出ファイル

- [ ] `/Users/kota/dev/42-cursus/libft/Makefile`
- [ ] `/Users/kota/dev/42-cursus/libft/libft.h`
- [ ] `/Users/kota/dev/42-cursus/libft/ft_*.c` × 43 本
- [ ] `/Users/kota/dev/42-cursus/libft/README.md`
- [ ] 上記以外のファイルが root にない (`docs/`, `subject/` は提出時に除外するか、そもそも別リポジトリに分ける)

### 7.2 ビルド

- [ ] `make` 正常終了、警告ゼロ
- [ ] `libft.a` が root に生成
- [ ] `make` 再実行で `Nothing to be done` (不要再リンクなし)
- [ ] `make clean` で `.o` のみ削除
- [ ] `make fclean` で `libft.a` も削除
- [ ] `make re` 成功

### 7.3 動作

- [ ] 全 43 関数が期待動作
- [ ] 文字分類関数が 1/0 を返す (非ゼロでなく厳密に 1)
- [ ] `ft_calloc(0, 0)` が `free()` 可能
- [ ] `ft_split` が NULL 終端配列を返す
- [ ] `ft_lstclear` 後に `*lst == NULL`
- [ ] INT_MIN 扱う関数 (`ft_itoa`, `ft_putnbr_fd`) がクラッシュしない

### 7.4 品質

- [ ] `norminette` 全ファイル `OK!`
- [ ] `valgrind` / `leaks` でリーク 0
- [ ] グローバル変数ゼロ
- [ ] `restrict` 不使用
- [ ] `-std=c99` でコンパイルしていない

### 7.5 提出リポジトリに含めないもの

- `subject/` (subject PDF)
- `docs/` (本書を含む設計文書群)
- `tests/` や `main.c` の一時テストドライバ
- `.o` / `libft.a` (`make fclean` で削除)
- `.DS_Store` など OS 生成物 (`.gitignore` 対象)

実際の 42 提出リポジトリにはこれらを置かないこと (または `.gitignore` で除外)。本ディレクトリは開発作業用で、提出リポジトリとは別管理する前提。

---

## 8. トラブルシューティング

| 症状 | 原因 | 対処 |
|---|---|---|
| `make` で `undefined reference to ft_XXX` | `.c` を作ったが `SRCS_PARTN` に追加していない | 該当 Phase の SRCS 行に追記 |
| `norminette` が `SPACE_REPLACE_TAB` | スペースでインデントしている | エディタでタブに置換 (`expandtab off`) |
| `norminette` が `TOO_MANY_LINES` | 関数が 25 行超え | `static` ヘルパに分割 |
| `leaks` でリーク検出 | 途中 malloc の失敗時解放漏れ | `ft_split` / `ft_lstmap` の失敗パス確認 |
| `-Werror` でビルド失敗 | unused parameter / unused variable | キャストで握りつぶす (`(void)x;`) か、未使用なら削除 |
| `ar: no archive members` 警告 | SRCS が空の状態で `make` | Phase 0 直後のみ発生。Phase 1.1 完了後は消える |
| `make` 2 回目に再リンクが走る | `%.o: %.c $(HEADER)` 依存の不備 or Makefile 変更で OBJS が更新扱い | Makefile 自体は変更するが、一度成立すれば再実行は no-op のはず。差分があればタイムスタンプ確認 |
