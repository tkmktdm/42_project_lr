# Libft テスト実装手順書

本書は Plan モードで **そのまま実行可能** な粒度に分解した、テストの実装タスク集。
subject / 要件書 / 設計書 / テスト設計書に完全準拠。差分があれば上位文書が優先。

- subject: `/Users/kota/dev/42-cursus/libft/subject/en.subject.pdf`
- 要件書: `/Users/kota/dev/42-cursus/libft/docs/requirements.md`
- 設計書: `/Users/kota/dev/42-cursus/libft/docs/design.md`
- テスト設計書: `/Users/kota/dev/42-cursus/libft/test/test_design.md`

---

## 0. 前提

### 0.1 作業ディレクトリ

テスト資源のルート = `/Users/kota/dev/42-cursus/libft/test/`

生成するファイルはすべてこのディレクトリ配下。
**root の Makefile / libft.h / ft_*.c は一切変更しない**。

### 0.2 全体タスク数

- Phase 0: 基盤 (helpers / Makefile / main) — 4 タスク
- Phase 1: Part 1 テスト — 23 タスク
- Phase 2: Part 2 テスト — 11 タスク
- Phase 3: Part 3 テスト — 9 タスク
- Phase 4: 実行・リーク検証 — 3 タスク

**合計 50 タスク**。

### 0.3 共通規約

| 項目 | 規約 |
|---|---|
| コンパイラ | `cc -Wall -Wextra -I ..` (Werror なし、テストは採点対象外) |
| 静的解析 | norminette は **かけない** (test/ は採点対象外) |
| インデント | タブ (見やすさのため) |
| 静的状態 | テスト間で累積しないよう各テスト冒頭でリセット |
| 終了コード | `g_fail == 0` → 0、それ以外 → 1 |
| 期待値形式 | テスト設計書 §5〜§7 に記載されたケースを網羅 |

### 0.4 タスク完了基準 (各タスク共通)

1. 指定ファイルが作成 / 更新されている
2. Phase 0 完了後は `cd test && make` が通る
3. Phase 1-3 の各タスク完了後も `make run` が通り、対象関数の ASSERT がすべて PASS
4. Phase 4 で `FAIL=0` かつ `leaks` / `valgrind` でリーク 0

### 0.5 依存関係

Phase 0 → Phase 1 / 2 / 3 → Phase 4。
Phase 1 / 2 / 3 は相互独立 (並列実行可能)。

---

## Phase 0: テスト基盤

### Task 0.1: `test_helpers.h` を作成

**ファイル**: `/Users/kota/dev/42-cursus/libft/test/test_helpers.h`

**内容**: テスト設計書 §4.2 に準拠。

```c
#ifndef TEST_HELPERS_H
# define TEST_HELPERS_H

# include <stddef.h>

extern int	g_pass;
extern int	g_fail;

/* 整数比較 (long で受ける) */
# define ASSERT_EQ_INT(label, actual, expected) \
	assert_eq_int((label), (long)(actual), (long)(expected), __FILE__, __LINE__)

/* 文字列比較 (NULL 安全) */
# define ASSERT_EQ_STR(label, actual, expected) \
	assert_eq_str((label), (actual), (expected), __FILE__, __LINE__)

/* メモリブロック比較 */
# define ASSERT_EQ_MEM(label, a, b, n) \
	assert_eq_mem((label), (a), (b), (size_t)(n), __FILE__, __LINE__)

/* ポインタ NULL / 非 NULL */
# define ASSERT_NULL(label, p) \
	assert_null((label), (p), __FILE__, __LINE__)
# define ASSERT_NOT_NULL(label, p) \
	assert_not_null((label), (p), __FILE__, __LINE__)

/* ポインタ一致 */
# define ASSERT_EQ_PTR(label, actual, expected) \
	assert_eq_ptr((label), (const void *)(actual), (const void *)(expected), __FILE__, __LINE__)

/* 真偽 */
# define ASSERT_TRUE(label, cond) \
	assert_true((label), (int)(cond), __FILE__, __LINE__)

void	assert_eq_int(const char *label, long a, long e, const char *f, int l);
void	assert_eq_str(const char *label, const char *a, const char *e, const char *f, int l);
void	assert_eq_mem(const char *label, const void *a, const void *b, size_t n, const char *f, int l);
void	assert_null(const char *label, const void *p, const char *f, int l);
void	assert_not_null(const char *label, const void *p, const char *f, int l);
void	assert_eq_ptr(const char *label, const void *a, const void *e, const char *f, int l);
void	assert_true(const char *label, int cond, const char *f, int l);

void	run_part1_tests(void);
void	run_part2_tests(void);
void	run_part3_tests(void);

#endif
```

**完了条件**:
- ファイル存在、`extern int g_pass; extern int g_fail;` あり
- 7 種の ASSERT マクロと 3 種の `run_partN_tests` 宣言あり

### Task 0.2: `test_helpers.c` を作成

**ファイル**: `/Users/kota/dev/42-cursus/libft/test/test_helpers.c`

**内容**: 7 種の assert 関数を実装。NULL 安全。失敗時は stderr に `FAIL <file>:<line> <label>` を出す。

```c
#include "test_helpers.h"
#include <stdio.h>
#include <string.h>

static void	fail_header(const char *label, const char *f, int l)
{
	fprintf(stderr, "FAIL %s:%d %s ", f, l, label);
}

void	assert_eq_int(const char *label, long a, long e, const char *f, int l)
{
	if (a == e)
	{
		g_pass++;
		return ;
	}
	g_fail++;
	fail_header(label, f, l);
	fprintf(stderr, "got %ld, want %ld\n", a, e);
}

void	assert_eq_str(const char *label, const char *a, const char *e, const char *f, int l)
{
	if (a == NULL && e == NULL)
	{
		g_pass++;
		return ;
	}
	if (a != NULL && e != NULL && strcmp(a, e) == 0)
	{
		g_pass++;
		return ;
	}
	g_fail++;
	fail_header(label, f, l);
	fprintf(stderr, "got %s, want %s\n",
		a ? a : "(null)", e ? e : "(null)");
}

void	assert_eq_mem(const char *label, const void *a, const void *b, size_t n, const char *f, int l)
{
	if (memcmp(a, b, n) == 0)
	{
		g_pass++;
		return ;
	}
	g_fail++;
	fail_header(label, f, l);
	fprintf(stderr, "memcmp failed (n=%zu)\n", n);
}

void	assert_null(const char *label, const void *p, const char *f, int l)
{
	if (p == NULL)
	{
		g_pass++;
		return ;
	}
	g_fail++;
	fail_header(label, f, l);
	fprintf(stderr, "expected NULL, got %p\n", p);
}

void	assert_not_null(const char *label, const void *p, const char *f, int l)
{
	if (p != NULL)
	{
		g_pass++;
		return ;
	}
	g_fail++;
	fail_header(label, f, l);
	fprintf(stderr, "expected non-NULL, got NULL\n");
}

void	assert_eq_ptr(const char *label, const void *a, const void *e, const char *f, int l)
{
	if (a == e)
	{
		g_pass++;
		return ;
	}
	g_fail++;
	fail_header(label, f, l);
	fprintf(stderr, "got %p, want %p\n", a, e);
}

void	assert_true(const char *label, int cond, const char *f, int l)
{
	if (cond)
	{
		g_pass++;
		return ;
	}
	g_fail++;
	fail_header(label, f, l);
	fprintf(stderr, "condition false\n");
}
```

**完了条件**: ビルドが通る、各 assert 関数が `g_pass` / `g_fail` を更新。

### Task 0.3: `test_main.c` を作成

**ファイル**: `/Users/kota/dev/42-cursus/libft/test/test_main.c`

```c
#include <stdio.h>
#include "test_helpers.h"

int	g_pass = 0;
int	g_fail = 0;

int	main(void)
{
	run_part1_tests();
	run_part2_tests();
	run_part3_tests();
	printf("\n=== RESULT: PASS=%d FAIL=%d ===\n", g_pass, g_fail);
	if (g_fail != 0)
		return (1);
	return (0);
}
```

**完了条件**: コンパイル成功、`main` が `run_partN_tests` を呼ぶ。

### Task 0.4: `test/Makefile` を作成

**ファイル**: `/Users/kota/dev/42-cursus/libft/test/Makefile`

**内容**: テスト設計書 §4.5 準拠。

```makefile
NAME		= libft_test
LIBFT_DIR	= ..
LIBFT		= $(LIBFT_DIR)/libft.a

CC			= cc
CFLAGS		= -Wall -Wextra -I $(LIBFT_DIR)
RM			= rm -f

SRCS		= test_helpers.c test_main.c test_part1.c test_part2.c test_part3.c
OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c test_helpers.h
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(NAME)

leaks: all
	leaks --atExit -- ./$(NAME)

valgrind: all
	valgrind --leak-check=full --error-exitcode=1 ./$(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all run leaks valgrind clean fclean re
```

**完了条件**: `test_part{1,2,3}.c` がまだ無くても SRCS に列挙してあるため、Phase 1-3 終了まで `make` は通らない。Phase 0 終了時点では Makefile 自体の作成のみを完了基準とし、ビルド確認は Phase 1 以降で行う。

---

## Phase 1: Part 1 テスト (23 タスク)

**共通事項**:
- 全タスクで対象ファイル: `/Users/kota/dev/42-cursus/libft/test/test_part1.c`
- Phase 1 最初のタスク (Task 1.1) で以下のヘッダを書く:

```c
#include "test_helpers.h"
#include "libft.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/* 各 test_ft_xxx をここに追加していく */

void	run_part1_tests(void)
{
	/* 各 test_ft_xxx をここで呼ぶ */
}
```

- 以降のタスクでは対応する `test_ft_xxx()` static 関数を追記し、`run_part1_tests()` にも追加。

### Task 1.1: `test_ft_isalpha`

**参照**: テスト設計書 §5.1

```c
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
```

**`run_part1_tests()` に `test_ft_isalpha();` を追加**。

### Task 1.2: `test_ft_isdigit`

```c
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
```

### Task 1.3: `test_ft_isalnum`

```c
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
```

### Task 1.4: `test_ft_isascii`

```c
static void	test_ft_isascii(void)
{
	ASSERT_EQ_INT("isascii 0", ft_isascii(0), 1);
	ASSERT_EQ_INT("isascii 127", ft_isascii(127), 1);
	ASSERT_EQ_INT("isascii 'A'", ft_isascii('A'), 1);
	ASSERT_EQ_INT("isascii 128", ft_isascii(128), 0);
	ASSERT_EQ_INT("isascii -1", ft_isascii(-1), 0);
	ASSERT_EQ_INT("isascii 256", ft_isascii(256), 0);
}
```

### Task 1.5: `test_ft_isprint`

```c
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
```

### Task 1.6: `test_ft_toupper`

```c
static void	test_ft_toupper(void)
{
	ASSERT_EQ_INT("toupper 'a'", ft_toupper('a'), 'A');
	ASSERT_EQ_INT("toupper 'z'", ft_toupper('z'), 'Z');
	ASSERT_EQ_INT("toupper 'A'", ft_toupper('A'), 'A');
	ASSERT_EQ_INT("toupper '1'", ft_toupper('1'), '1');
	ASSERT_EQ_INT("toupper '@'", ft_toupper('@'), '@');
	ASSERT_EQ_INT("toupper 0", ft_toupper(0), 0);
}
```

### Task 1.7: `test_ft_tolower`

```c
static void	test_ft_tolower(void)
{
	ASSERT_EQ_INT("tolower 'A'", ft_tolower('A'), 'a');
	ASSERT_EQ_INT("tolower 'Z'", ft_tolower('Z'), 'z');
	ASSERT_EQ_INT("tolower 'a'", ft_tolower('a'), 'a');
	ASSERT_EQ_INT("tolower '5'", ft_tolower('5'), '5');
	ASSERT_EQ_INT("tolower 0", ft_tolower(0), 0);
}
```

### Task 1.8: `test_ft_strlen`

```c
static void	test_ft_strlen(void)
{
	ASSERT_EQ_INT("strlen empty", ft_strlen(""), 0);
	ASSERT_EQ_INT("strlen one", ft_strlen("a"), 1);
	ASSERT_EQ_INT("strlen hello", ft_strlen("hello"), 5);
	ASSERT_EQ_INT("strlen with nl", ft_strlen("a\nb"), 3);
}
```

### Task 1.9: `test_ft_memset`

```c
static void	test_ft_memset(void)
{
	char	buf[8];
	void	*r;

	memset(buf, 0, sizeof(buf));
	r = ft_memset(buf, 'A', 3);
	ASSERT_EQ_PTR("memset ret", r, buf);
	ASSERT_EQ_INT("memset[0]", buf[0], 'A');
	ASSERT_EQ_INT("memset[2]", buf[2], 'A');
	ASSERT_EQ_INT("memset[3] untouched", buf[3], 0);
	/* n == 0 */
	buf[0] = 'X';
	ft_memset(buf, 'Y', 0);
	ASSERT_EQ_INT("memset n=0 no change", buf[0], 'X');
	/* 0xFF 書き込み (unsigned char 保証) */
	unsigned char	ubuf[3];
	ft_memset(ubuf, 0xFF, 3);
	ASSERT_EQ_INT("memset 0xFF[0]", ubuf[0], 0xFF);
	ASSERT_EQ_INT("memset 0xFF[2]", ubuf[2], 0xFF);
}
```

### Task 1.10: `test_ft_bzero`

```c
static void	test_ft_bzero(void)
{
	char	buf[5];

	memset(buf, 'X', 5);
	ft_bzero(buf, 3);
	ASSERT_EQ_INT("bzero[0]", buf[0], 0);
	ASSERT_EQ_INT("bzero[2]", buf[2], 0);
	ASSERT_EQ_INT("bzero[3] untouched", buf[3], 'X');
	/* n == 0 */
	buf[0] = 'Z';
	ft_bzero(buf, 0);
	ASSERT_EQ_INT("bzero n=0 no change", buf[0], 'Z');
}
```

### Task 1.11: `test_ft_memcpy`

```c
static void	test_ft_memcpy(void)
{
	char	dst[8] = {0};
	void	*r;

	r = ft_memcpy(dst, "hello", 6);
	ASSERT_EQ_PTR("memcpy ret", r, dst);
	ASSERT_EQ_STR("memcpy hello", dst, "hello");
	/* n == 0 */
	char	dst2[4] = "abc";
	ft_memcpy(dst2, "xyz", 0);
	ASSERT_EQ_STR("memcpy n=0 no change", dst2, "abc");
	/* n == 0 + NULL (設計書 §5.4) */
	r = ft_memcpy(NULL, NULL, 0);
	ASSERT_NULL("memcpy NULL NULL 0", r);
}
```

### Task 1.12: `test_ft_memmove`

```c
static void	test_ft_memmove(void)
{
	char	fwd[8] = "abcdef";
	char	bwd[8] = "abcdef";

	/* overlap: dst > src (後方コピー) */
	ft_memmove(fwd + 1, fwd, 4);
	ASSERT_EQ_STR("memmove overlap bwd", fwd, "aabcdf");
	/* overlap: dst < src (前方コピー) */
	ft_memmove(bwd, bwd + 1, 4);
	ASSERT_EQ_STR("memmove overlap fwd", bwd, "bcdeef");
	/* dst == src */
	char	same[4] = "abc";
	ft_memmove(same, same, 3);
	ASSERT_EQ_STR("memmove same", same, "abc");
	/* len == 0 */
	char	buf[4] = "xyz";
	ft_memmove(buf, "...", 0);
	ASSERT_EQ_STR("memmove len=0", buf, "xyz");
}
```

### Task 1.13: `test_ft_strlcpy`

```c
static void	test_ft_strlcpy(void)
{
	char	buf[10];
	size_t	r;

	memset(buf, 'X', sizeof(buf));
	r = ft_strlcpy(buf, "hello", 10);
	ASSERT_EQ_STR("strlcpy full", buf, "hello");
	ASSERT_EQ_INT("strlcpy ret full", r, 5);
	/* 切り詰め */
	memset(buf, 'X', sizeof(buf));
	r = ft_strlcpy(buf, "hello", 3);
	ASSERT_EQ_STR("strlcpy trunc", buf, "he");
	ASSERT_EQ_INT("strlcpy ret trunc", r, 5);
	/* dstsize == 0 */
	buf[0] = 'Z';
	r = ft_strlcpy(buf, "hello", 0);
	ASSERT_EQ_INT("strlcpy dstsize=0 no change", buf[0], 'Z');
	ASSERT_EQ_INT("strlcpy ret dstsize=0", r, 5);
	/* 空 src */
	r = ft_strlcpy(buf, "", 10);
	ASSERT_EQ_STR("strlcpy empty src", buf, "");
	ASSERT_EQ_INT("strlcpy ret empty", r, 0);
}
```

### Task 1.14: `test_ft_strlcat`

```c
static void	test_ft_strlcat(void)
{
	char	buf[10];
	size_t	r;

	strcpy(buf, "abc");
	r = ft_strlcat(buf, "de", 10);
	ASSERT_EQ_STR("strlcat normal", buf, "abcde");
	ASSERT_EQ_INT("strlcat ret normal", r, 5);
	/* 切り詰め: size 6、"abc" + "de" = "abcde" (ちょうど収まる) */
	strcpy(buf, "abc");
	r = ft_strlcat(buf, "defgh", 6);
	ASSERT_EQ_STR("strlcat trunc", buf, "abcde");
	ASSERT_EQ_INT("strlcat ret trunc", r, 8);
	/* dstsize == 0: dl=0, sl=3 → 戻り値 3 */
	r = ft_strlcat(buf, "xyz", 0);
	ASSERT_EQ_INT("strlcat dstsize=0", r, 3);
	/* dl >= dstsize: dst の長さが dstsize を超える (BSD 規定) */
	char	full[6] = "abcde";
	r = ft_strlcat(full, "xy", 3);  /* dstsize=3 < dl=5 */
	ASSERT_EQ_INT("strlcat dl>=dstsize", r, 3 + 2);
}
```

### Task 1.15: `test_ft_strchr`

```c
static void	test_ft_strchr(void)
{
	char	*r;
	const char	*s = "hello";

	r = ft_strchr(s, 'l');
	ASSERT_EQ_PTR("strchr found", r, &s[2]);
	/* \0 検索 */
	r = ft_strchr(s, '\0');
	ASSERT_EQ_PTR("strchr end", r, &s[5]);
	/* not found */
	r = ft_strchr(s, 'z');
	ASSERT_NULL("strchr not found", r);
	/* 空文字列で \0 検索 */
	const char	*e = "";
	r = ft_strchr(e, '\0');
	ASSERT_EQ_PTR("strchr empty \\0", r, e);
	/* 高位バイト (テスト設計書 §5.3) */
	const char	*hi = "abc\x80";
	r = ft_strchr(hi, (char)0x80);
	ASSERT_EQ_PTR("strchr high byte", r, &hi[3]);
}
```

### Task 1.16: `test_ft_strrchr`

```c
static void	test_ft_strrchr(void)
{
	const char	*s = "abcba";

	ASSERT_EQ_PTR("strrchr last 'b'", ft_strrchr(s, 'b'), &s[3]);
	ASSERT_EQ_PTR("strrchr end", ft_strrchr(s, '\0'), &s[5]);
	ASSERT_NULL("strrchr not found", ft_strrchr(s, 'z'));
}
```

### Task 1.17: `test_ft_strncmp`

```c
static void	test_ft_strncmp(void)
{
	ASSERT_EQ_INT("strncmp eq", ft_strncmp("abc", "abc", 3), 0);
	ASSERT_TRUE("strncmp lt", ft_strncmp("abc", "abd", 3) < 0);
	ASSERT_TRUE("strncmp gt", ft_strncmp("abd", "abc", 3) > 0);
	ASSERT_TRUE("strncmp shorter s1", ft_strncmp("ab", "abc", 5) < 0);
	ASSERT_EQ_INT("strncmp n=0", ft_strncmp("abc", "xyz", 0), 0);
	/* 高位バイト比較 (unsigned) */
	ASSERT_TRUE("strncmp unsigned",
		ft_strncmp("\xFF", "\x01", 1) > 0);
}
```

### Task 1.18: `test_ft_memchr`

```c
static void	test_ft_memchr(void)
{
	const char	*s = "abcdef";

	ASSERT_EQ_PTR("memchr found", ft_memchr(s, 'c', 6), &s[2]);
	ASSERT_NULL("memchr not found", ft_memchr(s, 'z', 6));
	ASSERT_NULL("memchr n=0", ft_memchr(s, 'a', 0));
	/* \0 含むバイナリ探索 */
	const char	bin[] = {1, 2, 0, 3, 4};
	ASSERT_EQ_PTR("memchr binary 0", ft_memchr(bin, 0, 5), &bin[2]);
}
```

### Task 1.19: `test_ft_memcmp`

```c
static void	test_ft_memcmp(void)
{
	ASSERT_EQ_INT("memcmp eq", ft_memcmp("abc", "abc", 3), 0);
	ASSERT_TRUE("memcmp lt", ft_memcmp("abc", "abd", 3) < 0);
	ASSERT_TRUE("memcmp gt", ft_memcmp("abd", "abc", 3) > 0);
	ASSERT_EQ_INT("memcmp n=0", ft_memcmp("abc", "xyz", 0), 0);
}
```

### Task 1.20: `test_ft_strnstr`

```c
static void	test_ft_strnstr(void)
{
	const char	*h = "hello world";

	/* 空 needle → haystack */
	ASSERT_EQ_PTR("strnstr empty needle", ft_strnstr(h, "", 11), h);
	/* needle 空 + len 0 */
	ASSERT_EQ_PTR("strnstr empty needle len0", ft_strnstr("aaa", "", 0), (void *)"aaa");
	/* found */
	ASSERT_EQ_PTR("strnstr found", ft_strnstr(h, "world", 11), &h[6]);
	/* len 不足 */
	ASSERT_NULL("strnstr len short", ft_strnstr("abcabc", "abc", 2));
	/* 境界 */
	ASSERT_EQ_PTR("strnstr boundary", ft_strnstr("abcabc", "abc", 3), (void *)"abcabc");
	/* needle が haystack より長い */
	ASSERT_NULL("strnstr needle longer", ft_strnstr("ab", "abc", 5));
	/* len 内で見つからない */
	ASSERT_NULL("strnstr not found", ft_strnstr(h, "zzz", 11));
}
```

### Task 1.21: `test_ft_atoi`

```c
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
```

### Task 1.22: `test_ft_calloc`

```c
static void	test_ft_calloc(void)
{
	int		*p;
	size_t	i;
	void	*z1, *z2;

	/* 通常 */
	p = (int *)ft_calloc(10, sizeof(int));
	ASSERT_NOT_NULL("calloc normal", p);
	i = 0;
	while (i < 10)
	{
		ASSERT_EQ_INT("calloc zero", p[i], 0);
		i++;
	}
	free(p);
	/* 0 ケース (subject 要件: free 可能な unique ポインタ) */
	z1 = ft_calloc(0, 10);
	ASSERT_NOT_NULL("calloc 0x10", z1);
	free(z1);
	z2 = ft_calloc(10, 0);
	ASSERT_NOT_NULL("calloc 10x0", z2);
	free(z2);
	/* overflow (設計書 §5.6) */
	ASSERT_NULL("calloc overflow SIZE_MAX*2",
		ft_calloc((size_t)-1, 2));
	ASSERT_NULL("calloc overflow boundary",
		ft_calloc(((size_t)-1) / 2 + 1, 2));
}
```

### Task 1.23: `test_ft_strdup`

```c
static void	test_ft_strdup(void)
{
	char	*d;
	char	src[] = "hello";

	d = ft_strdup(src);
	ASSERT_NOT_NULL("strdup non-null", d);
	ASSERT_EQ_STR("strdup content", d, "hello");
	ASSERT_TRUE("strdup distinct ptr", d != src);
	/* 独立性 */
	src[0] = 'X';
	ASSERT_EQ_INT("strdup independent", d[0], 'h');
	free(d);
	/* 空文字列 */
	d = ft_strdup("");
	ASSERT_NOT_NULL("strdup empty non-null", d);
	ASSERT_EQ_STR("strdup empty", d, "");
	free(d);
}
```

### Phase 1 完了時

`run_part1_tests()` は 23 個の `test_ft_*()` をすべて呼び出す。
Part 1 の ASSERT 総数目安: **約 100 個**。

---

## Phase 2: Part 2 テスト (11 タスク)

**対象ファイル**: `/Users/kota/dev/42-cursus/libft/test/test_part2.c`

先頭でヘッダ + `run_part2_tests()` を用意:

```c
#include "test_helpers.h"
#include "libft.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>

void	run_part2_tests(void)
{
	/* 各 test_ft_xxx を呼ぶ */
}
```

### Task 2.1: `test_ft_substr`

```c
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
```

### Task 2.2: `test_ft_strjoin`

```c
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
```

### Task 2.3: `test_ft_strtrim`

```c
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
```

### Task 2.4: `test_ft_split`

```c
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
	/* 先頭・末尾・連続 */
	r = ft_split(",,a,b,,", ',');
	ASSERT_EQ_INT("split merged size", split_size(r), 2);
	ASSERT_EQ_STR("split merged[0]", r[0], "a");
	ASSERT_EQ_STR("split merged[1]", r[1], "b");
	free_split(r);
	/* 空文字列 */
	r = ft_split("", ',');
	ASSERT_EQ_INT("split empty", split_size(r), 0);
	free_split(r);
	/* 全部区切り */
	r = ft_split(",,,", ',');
	ASSERT_EQ_INT("split all delims", split_size(r), 0);
	free_split(r);
	/* c == '\0' */
	r = ft_split("abc", '\0');
	ASSERT_EQ_INT("split c=0 size", split_size(r), 1);
	ASSERT_EQ_STR("split c=0 [0]", r[0], "abc");
	free_split(r);
}
```

### Task 2.5: `test_ft_itoa`

```c
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
```

### Task 2.6: `test_ft_strmapi`

```c
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
```

### Task 2.7: `test_ft_striteri`

```c
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
```

### Task 2.8-2.11: fd 出力系 (共通手法)

fd 取得ヘルパ:

```c
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
```

#### Task 2.8: `test_ft_putchar_fd`

```c
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
```

#### Task 2.9: `test_ft_putstr_fd`

```c
static void	test_ft_putstr_fd(void)
{
	FILE	*fp;
	int		fd;
	char	buf[64];

	fd = open_tmpfd(&fp);
	ft_putstr_fd("hello", fd);
	read_tmpfd(fp, buf, sizeof(buf));
	ASSERT_EQ_STR("putstr_fd", buf, "hello");
	/* NULL 安全 */
	fd = open_tmpfd(&fp);
	ft_putstr_fd(NULL, fd);
	read_tmpfd(fp, buf, sizeof(buf));
	ASSERT_EQ_STR("putstr_fd NULL", buf, "");
}
```

#### Task 2.10: `test_ft_putendl_fd`

```c
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
```

#### Task 2.11: `test_ft_putnbr_fd`

```c
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
```

### Phase 2 完了時

`run_part2_tests()` から 11 個を呼ぶ。Part 2 ASSERT 総数目安: **約 50 個**。

---

## Phase 3: Part 3 テスト (9 タスク)

**対象ファイル**: `/Users/kota/dev/42-cursus/libft/test/test_part3.c`

先頭:

```c
#include "test_helpers.h"
#include "libft.h"
#include <stdlib.h>
#include <string.h>

/* Part 3 共通ヘルパ (静的変数はケース毎にリセット) */
static int	g_iter_count;

static void	count_cb(void *c)
{
	(void)c;
	g_iter_count++;
}

static void	*f_strdup_wrap(void *c)
{
	return ((void *)strdup((char *)c));
}

void	run_part3_tests(void)
{
	/* ... */
}
```

### Task 3.1: `test_ft_lstnew`

```c
static void	test_ft_lstnew(void)
{
	char	content[] = "x";
	t_list	*n;

	n = ft_lstnew(content);
	ASSERT_NOT_NULL("lstnew non-null", n);
	ASSERT_EQ_PTR("lstnew content", n->content, content);
	ASSERT_NULL("lstnew next", n->next);
	free(n);
}
```

### Task 3.2: `test_ft_lstadd_front`

```c
static void	test_ft_lstadd_front(void)
{
	t_list	*lst;
	t_list	*a;
	t_list	*b;

	lst = NULL;
	a = ft_lstnew("a");
	ft_lstadd_front(&lst, a);
	ASSERT_EQ_PTR("add_front empty", lst, a);
	ASSERT_NULL("add_front empty next", lst->next);
	b = ft_lstnew("b");
	ft_lstadd_front(&lst, b);
	ASSERT_EQ_PTR("add_front head", lst, b);
	ASSERT_EQ_PTR("add_front new->next", lst->next, a);
	free(a);
	free(b);
}
```

### Task 3.3: `test_ft_lstsize`

```c
static void	test_ft_lstsize(void)
{
	t_list	*lst;

	ASSERT_EQ_INT("lstsize empty", ft_lstsize(NULL), 0);
	lst = ft_lstnew("a");
	ASSERT_EQ_INT("lstsize 1", ft_lstsize(lst), 1);
	ft_lstadd_front(&lst, ft_lstnew("b"));
	ft_lstadd_front(&lst, ft_lstnew("c"));
	ASSERT_EQ_INT("lstsize 3", ft_lstsize(lst), 3);
	/* 後始末 */
	while (lst)
	{
		t_list *next = lst->next;
		free(lst);
		lst = next;
	}
}
```

### Task 3.4: `test_ft_lstlast`

```c
static void	test_ft_lstlast(void)
{
	t_list	*a;
	t_list	*b;
	t_list	*c;

	ASSERT_NULL("lstlast NULL", ft_lstlast(NULL));
	a = ft_lstnew("a");
	ASSERT_EQ_PTR("lstlast single", ft_lstlast(a), a);
	b = ft_lstnew("b");
	c = ft_lstnew("c");
	a->next = b;
	b->next = c;
	ASSERT_EQ_PTR("lstlast tail", ft_lstlast(a), c);
	free(a);
	free(b);
	free(c);
}
```

### Task 3.5: `test_ft_lstadd_back`

```c
static void	test_ft_lstadd_back(void)
{
	t_list	*lst;
	t_list	*b;
	t_list	*c;

	lst = NULL;
	ft_lstadd_back(&lst, ft_lstnew("a"));
	ASSERT_EQ_INT("add_back empty size", ft_lstsize(lst), 1);
	b = ft_lstnew("b");
	ft_lstadd_back(&lst, b);
	ASSERT_EQ_INT("add_back size 2", ft_lstsize(lst), 2);
	c = ft_lstnew("c");
	ft_lstadd_back(&lst, c);
	ASSERT_EQ_INT("add_back size 3", ft_lstsize(lst), 3);
	ASSERT_EQ_PTR("add_back last", ft_lstlast(lst), c);
	while (lst)
	{
		t_list *next = lst->next;
		free(lst);
		lst = next;
	}
}
```

### Task 3.6: `test_ft_lstdelone`

```c
static int	g_del_calls;

static void	del_record(void *c)
{
	(void)c;
	g_del_calls++;
}

static void	test_ft_lstdelone(void)
{
	t_list	*a;
	t_list	*b;

	g_del_calls = 0;
	a = ft_lstnew("a");
	b = ft_lstnew("b");
	a->next = b;
	ft_lstdelone(a, del_record);
	ASSERT_EQ_INT("lstdelone del called once", g_del_calls, 1);
	/* b は生存している必要がある (subject 明示) */
	ASSERT_NOT_NULL("lstdelone next alive", b);
	ASSERT_EQ_STR("lstdelone next content", (char *)b->content, "b");
	free(b);
}
```

### Task 3.7: `test_ft_lstclear`

```c
static void	test_ft_lstclear(void)
{
	t_list	*lst;

	g_del_calls = 0;
	lst = ft_lstnew(strdup("a"));
	ft_lstadd_back(&lst, ft_lstnew(strdup("b")));
	ft_lstadd_back(&lst, ft_lstnew(strdup("c")));
	ft_lstclear(&lst, free);
	ASSERT_NULL("lstclear sets NULL", lst);
	/* 空リストに対しても安全 */
	ft_lstclear(&lst, free);
	ASSERT_NULL("lstclear idempotent", lst);
}
```

### Task 3.8: `test_ft_lstiter`

```c
static void	test_ft_lstiter(void)
{
	t_list	*lst;

	g_iter_count = 0;
	lst = ft_lstnew("a");
	ft_lstadd_back(&lst, ft_lstnew("b"));
	ft_lstadd_back(&lst, ft_lstnew("c"));
	ft_lstiter(lst, count_cb);
	ASSERT_EQ_INT("lstiter count", g_iter_count, 3);
	while (lst)
	{
		t_list *next = lst->next;
		free(lst);
		lst = next;
	}
	/* NULL / NULL f は no-op */
	g_iter_count = 0;
	ft_lstiter(NULL, count_cb);
	ASSERT_EQ_INT("lstiter NULL list", g_iter_count, 0);
}
```

### Task 3.9: `test_ft_lstmap`

```c
static void	test_ft_lstmap(void)
{
	t_list	*lst;
	t_list	*mapped;
	t_list	*cur;
	t_list	*m;

	lst = ft_lstnew(strdup("a"));
	ft_lstadd_back(&lst, ft_lstnew(strdup("b")));
	ft_lstadd_back(&lst, ft_lstnew(strdup("c")));
	mapped = ft_lstmap(lst, f_strdup_wrap, free);
	ASSERT_NOT_NULL("lstmap result", mapped);
	ASSERT_EQ_INT("lstmap size", ft_lstsize(mapped), 3);
	/* 独立性 (元とポインタが異なる) */
	cur = lst;
	m = mapped;
	while (cur && m)
	{
		ASSERT_EQ_STR("lstmap content eq", (char *)m->content, (char *)cur->content);
		ASSERT_TRUE("lstmap content distinct ptr", m->content != cur->content);
		cur = cur->next;
		m = m->next;
	}
	ft_lstclear(&lst, free);
	ft_lstclear(&mapped, free);
	ASSERT_NULL("lstmap lst cleared", lst);
	ASSERT_NULL("lstmap mapped cleared", mapped);
}
```

### Phase 3 完了時

`run_part3_tests()` から 9 個を呼ぶ。Part 3 ASSERT 総数目安: **約 35 個**。

---

## Phase 4: 実行・リーク検証

### Task 4.1: ビルドと実行

```sh
cd /Users/kota/dev/42-cursus/libft/test
make re
make run
```

**期待結果**:
- ビルド警告ゼロ (`-Werror` は外しているが、実際のコードで警告ゼロを目標)
- `=== RESULT: PASS=N FAIL=0 ===` と表示される
- 終了コード 0
- PASS 総数: **140 以上** (テスト設計書 §11 合格基準 3)

**FAIL が出た場合**: stderr に `FAIL <file>:<line> <label> got ... want ...` が出るので、該当テスト or 実装を修正。

### Task 4.2: メモリリーク検証

#### macOS:

```sh
cd /Users/kota/dev/42-cursus/libft/test
make leaks
```

**期待結果**: `Process N: 0 leaks for 0 total leaked bytes.`

`leaks` が SIP の影響で動作しない場合:

```sh
MallocStackLogging=1 leaks --atExit -- ./libft_test
```

#### Linux:

```sh
cd /Users/kota/dev/42-cursus/libft/test
make valgrind
```

**期待結果**: `All heap blocks were freed -- no leaks are possible`、`ERROR SUMMARY: 0 errors from 0 contexts`。

### Task 4.3: クリーンアップ確認

```sh
cd /Users/kota/dev/42-cursus/libft/test
make fclean
ls
```

`libft_test` と `*.o` が消えており、ソースファイル ( `test_*.c`, `test_*.h`, `Makefile`, `README.md`, `test_design.md`, `test_implementation.md`) のみが残ることを確認。

root の Makefile / libft.h / ft_*.c / libft.a / README.md は影響を受けていないことを確認:

```sh
cd /Users/kota/dev/42-cursus/libft
ls libft.a && make         # "Nothing to be done" が出ること
```

---

## 5. 合格基準チェックリスト (テスト設計書 §11 対応)

- [ ] `make run` で `FAIL=0` かつ終了コード 0
- [ ] `make leaks` (macOS) / `make valgrind` (Linux) でリーク 0 / エラー 0
- [ ] テスト総数 (PASS + FAIL) が **140 以上**
- [ ] 必須 regression ケース全網羅:
  - [ ] `ft_calloc(0, 0)` / `(0, N)` / `(N, 0)` すべて非 NULL
  - [ ] `ft_itoa(INT_MIN)` → `"-2147483648"`
  - [ ] `ft_putnbr_fd(INT_MIN, fd)` → `"-2147483648"`
  - [ ] `ft_memmove` overlap 両方向
  - [ ] `ft_split` 連続/先頭/末尾区切り + NULL 終端
  - [ ] `ft_lstdelone` 後に next 生存
  - [ ] `ft_lstclear` 後に `*lst == NULL`
  - [ ] `ft_lstmap` 完了後の独立性・leak 0
- [ ] root の Makefile / 提出ファイルに影響なし

---

## 6. 提出前の最終処理 (テスト設計書 §12 参照)

`test/` ディレクトリを 42 リポジトリに含めない推奨手順:

### 選択肢 A: test/ を削除

```sh
cd /Users/kota/dev/42-cursus/libft
rm -rf test/
```

### 選択肢 B: `.gitignore` で除外

```sh
cat > .gitignore << 'EOF'
*.o
libft.a
test/
.DS_Store
EOF
```

どちらの選択肢でも、提出リポジトリには以下のみが残ることを確認:

- `Makefile`, `libft.h`, `ft_*.c` × 43, `README.md`

---

## 7. トラブルシューティング

| 症状 | 原因 | 対処 |
|---|---|---|
| `make` で `../libft.a` が無い | root の libft.a 未ビルド | Makefile の `$(LIBFT)` ターゲットが自動的に `$(MAKE) -C ..` を呼ぶはず。手動なら `cd .. && make` |
| `FAIL` が stderr に山ほど出る | 実装バグ or テスト期待値ミス | stderr の `FAIL <file>:<line> <label>` から該当箇所特定 |
| `leaks` が "Process terminated before completion" を出す | SIP 干渉 | `MallocStackLogging=1 leaks ...` で再実行 |
| tmpfile が開けない | /tmp が書き込み不可 | `TMPDIR=/some/writable/path ./libft_test` |
| Linux で `ft_strlcpy` 実装がないと比較できない | テスト内で libc `strlcpy` は呼ばない設計 (テスト設計書 §9 オプション扱い) | 本書は libc 比較を必須化していないので問題なし |
| `test/` のファイルが norminette 警告を出す | norminette を test/ にかけている | `norminette libft.h ft_*.c` のように root の対象だけ指定する |
| 提出時に test/ が混入 | 提出前チェック漏れ | §6 手順に従う |
