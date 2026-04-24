# Libft テスト設計書

本書は libft のテスト戦略・テストケース・テスト基盤の設計を示す。
subject / 要件書 / 設計書に完全準拠。差分があれば上位文書が優先。

- subject: `/Users/kota/dev/42-cursus/libft/subject/en.subject.pdf`
- 要件書: `/Users/kota/dev/42-cursus/libft/docs/requirements.md`
- 設計書: `/Users/kota/dev/42-cursus/libft/docs/design.md`
- 実装手順書: `/Users/kota/dev/42-cursus/libft/docs/implementation.md`

---

## 1. 目的とスコープ

### 1.1 目的

- 完成した `libft.a` の **43 関数すべて** が subject 仕様通りに振る舞うことを検証する。
- メモリリーク・クラッシュがないことを確認する (subject II 要件)。
- defense (ピア評価) 時に自分の実装を示す材料として使える再現可能なテストを用意する。

### 1.2 スコープ

- **対象**: `/Users/kota/dev/42-cursus/libft/libft.a` が提供する 43 関数
- **対象外**:
  - 提出物としてのテストコード (subject II: 「テストは採点対象外、提出不要」)
  - 内部実装詳細 (ブラックボックステストを基本とする)
  - 性能ベンチマーク (subject 非要求)

### 1.3 subject との関係

subject Chapter II:
> "We encourage you to create test programs for your project, even though this work does not need to be submitted and will not be graded. ... during defence, you are free to use your tests and/or the tests of the peer you are evaluating."

テストは **推奨されているが提出対象外**。本書はこの前提に基づき、**リポジトリ root ではなく `test/` サブディレクトリ** にテスト資源を隔離する。

### 1.4 設計書 §10.2 との関係 (方針更新)

設計書 §10.2 は当初「`tests/` ディレクトリを作らない」方針だったが、ユーザー指示により **`test/` サブディレクトリでのローカル保持方式** に更新した。提出時には本書 §12 の手順で `test/` を削除するか `.gitignore` で除外し、「**リポジトリにコミットしない / 採点対象に含めない**」という設計書 §10.2 の本質は維持する。

---

## 2. 提出物との分離保証 (最重要)

### 2.1 subject の「未使用ファイル禁止」への対応

subject IV.1: *"Submitting unused files is not allowed"*。
subject VI 赤色警告: *"Place all your files at the root of your repository"*。

これらは **提出対象ファイル** (Makefile / libft.h / ft_*.c) に関する制約であり、テスト資源はそもそも提出対象外。ただし、リポジトリに test/ ディレクトリを残す場合は以下を徹底する:

### 2.2 分離規則

1. **テスト資源はすべて `test/` サブディレクトリ配下に配置**:
   - `test/test_design.md` (本書)
   - `test/Makefile` (テストビルド専用)
   - `test/test_main.c`, `test/test_part*.c`, `test/test_helpers.{c,h}`
2. **root の Makefile は test/ を一切参照しない**。`SRCS` にも、`.PHONY` にも含めない。
3. **root の Makefile から test/ を起動する場合は任意のオプショナルターゲット** (例: `make -C test run`) を手動で叩く形にする。subject 必須ルール (`all`, `clean`, `fclean`, `re`) はテストに触れない。
4. **提出時の推奨**: 42 リポジトリにコミットする前に `test/` を削除するか、`.gitignore` で除外する。本書の最終章 (§12) にチェックリストあり。
5. **norminette**: `norminette libft.h ft_*.c` のようにワイルドカード指定でテストを巻き込まない。test/ の中身は Norm チェック対象外 (採点対象外のため)。

---

## 3. ディレクトリ構造

### 3.1 テスト側レイアウト

```
libft/
├── (提出物: Makefile, libft.h, ft_*.c, README.md)  ← root、subject 管理下
├── libft.a                                          ← root ビルド生成物
├── docs/                                            ← 設計文書 (提出対象外)
└── test/                                            ← テスト資源 (本書のスコープ)
    ├── test_design.md        ← 本書
    ├── README.md             ← test/ の使い方 (簡易)
    ├── Makefile              ← テスト専用ビルド (../libft.a にリンク)
    ├── test_helpers.h        ← ASSERT マクロ、ユーティリティ
    ├── test_helpers.c        ← カウンタ実体、補助関数
    ├── test_main.c           ← ランナー
    ├── test_part1.c          ← Part 1 テストケース (23 関数分)
    ├── test_part2.c          ← Part 2 テストケース (11 関数分)
    └── test_part3.c          ← Part 3 テストケース (9 関数分)
```

### 3.2 テストのビルド成果物

- `test/libft_test` (実行ファイル、`test/` 内に生成)
- `test/*.o` (ビルド中間物)

`test/Makefile` の `clean` / `fclean` でこれらを削除可能にする。root の `make fclean` と衝突しない (root Makefile は test/ に関知しない)。

---

## 4. テスト基盤設計

### 4.1 テスト方針

- **ブラックボックス中心**: 関数の入出力だけを検証。内部実装に依存しない。
- **自己完結**: 外部テストフレームワーク (Criterion, Unity, etc.) を使わず、C + libc のみで実装。
- **失敗時の情報密度**: assertion 失敗時はファイル名・行番号・関数名・期待値・実際値を 1 行に集約する。
- **全テスト実行**: 先頭で止めず最後まで走り、最後に `PASS=N FAIL=M` を表示する。
- **終了コード**: `g_fail == 0` のとき 0、そうでなければ 1 (CI やシェルパイプラインで活用可能)。

### 4.2 `test_helpers.h` の設計

> **注**: 以下で宣言する `g_pass`, `g_fail` は **テストランナー内限定のグローバル変数** であり、libft 本体 (提出対象) には一切含まれない。subject IV.1 のグローバル変数禁止は libft 本体にのみ適用される。test/ は採点対象外なので本書の設計に従う。

```c
#ifndef TEST_HELPERS_H
# define TEST_HELPERS_H

# include <stddef.h>

extern int	g_pass;
extern int	g_fail;

/* 整数比較 */
# define ASSERT_EQ_INT(label, actual, expected)    assert_eq_int(label, (long)(actual), (long)(expected), __FILE__, __LINE__)
/* 文字列比較 (strcmp ベース) */
# define ASSERT_EQ_STR(label, actual, expected)    assert_eq_str(label, (actual), (expected), __FILE__, __LINE__)
/* メモリブロック比較 */
# define ASSERT_EQ_MEM(label, a, b, n)             assert_eq_mem(label, (a), (b), (n), __FILE__, __LINE__)
/* ポインタ NULL / 非 NULL */
# define ASSERT_NULL(label, p)                     assert_null(label, (p), __FILE__, __LINE__)
# define ASSERT_NOT_NULL(label, p)                 assert_not_null(label, (p), __FILE__, __LINE__)
/* ポインタ一致 */
# define ASSERT_EQ_PTR(label, actual, expected)    assert_eq_ptr(label, (actual), (expected), __FILE__, __LINE__)
/* 真偽値 */
# define ASSERT_TRUE(label, cond)                  assert_true(label, (cond), __FILE__, __LINE__)

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

### 4.3 `test_helpers.c` の責務

- `g_pass`, `g_fail` カウンタ実体
- `assert_*` 関数: 結果によりカウンタを更新、失敗時に `fprintf(stderr, ...)` でログ

### 4.4 `test_main.c` の設計

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
	return (g_fail != 0);
}
```

### 4.5 `test/Makefile` の設計

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

**ポイント**:
- `-Werror` は外す (テスト側で libc への `printf(3)` 呼び出しや型変換があり、採点対象外のため緩める)。必要なら `-Wno-unused-result`, `-Wno-unused-parameter` も許容する。
- `-I ..` で `libft.h` を読める
- `$(LIBFT)` を依存に加えることで、root の `libft.a` が最新になるよう自動ビルド連携
- `make run` / `make leaks` / `make valgrind` を用意
- macOS で `leaks` が SIP の影響で動かない場合は `MallocStackLogging=1 leaks --atExit -- ./$(NAME)` を試す

### 4.6 Part ごとのテストファイル構造

各 `test_partN.c` は以下のパターン:

```c
#include "test_helpers.h"
#include "libft.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static void	test_ft_xxx(void)
{
	/* 代表ケース */
	ASSERT_EQ_INT("ft_xxx normal", ft_xxx(...), expected);
	/* エッジケース */
	ASSERT_EQ_INT("ft_xxx empty", ft_xxx(...), expected);
	/* ... */
}

void	run_partN_tests(void)
{
	test_ft_xxx();
	test_ft_yyy();
	/* ... */
}
```

---

## 5. Part 1 テストケース

### 5.1 文字分類 (subject IV.2: 戻り値は 1 / 0)

| 関数 | ケース | 入力 | 期待値 |
|---|---|---|---|
| `ft_isalpha` | 大文字 | `'A'`, `'Z'` | 1 |
| | 小文字 | `'a'`, `'z'` | 1 |
| | 数字 | `'0'` | 0 |
| | 記号 | `'@'`, `' '` | 0 |
| | 範囲外 | `0`, `128`, `-1`, `256` | 0 |
| `ft_isdigit` | 数字 | `'0'`, `'5'`, `'9'` | 1 |
| | 非数字 | `'a'`, `'A'`, `' '` | 0 |
| | 範囲外 | `-1`, `128` | 0 |
| `ft_isalnum` | 英字 | `'a'`, `'Z'` | 1 |
| | 数字 | `'5'` | 1 |
| | 記号 | `'_'`, `'@'` | 0 |
| `ft_isascii` | ASCII | `0`, `127`, `'A'` | 1 |
| | 範囲外 | `128`, `-1`, `256` | 0 |
| `ft_isprint` | 印字可 | `' '` (32), `'~'` (126) | 1 |
| | 制御 | `31`, `127`, `0` | 0 |

**実装**: 各関数で上記入力すべてを 1 行の `ASSERT_EQ_INT` で網羅 (ループ可)。

### 5.2 ケース変換

| 関数 | ケース | 入力 | 期待値 |
|---|---|---|---|
| `ft_toupper` | 小文字 | `'a'`, `'z'` | `'A'`, `'Z'` |
| | 大文字 | `'A'` | `'A'` |
| | 非英字 | `'1'`, `'@'`, `0` | 入力と同じ |
| `ft_tolower` | 大文字 | `'A'`, `'Z'` | `'a'`, `'z'` |
| | 小文字 | `'a'` | `'a'` |
| | 非英字 | `'5'` | `'5'` |

### 5.3 文字列長・探索

**`ft_strlen`**
- 空文字列 `""` → 0
- 1 文字 `"a"` → 1
- 通常 `"hello"` → 5
- 改行含む `"a\nb"` → 3

**`ft_strchr`**
- 見つかる: `ft_strchr("hello", 'l')` → 最初の `'l'` を指す (位置 2)
- 末尾 `\0`: `ft_strchr("abc", '\0')` → 末尾 `'\0'` を指す (位置 3)
- 見つからない: `ft_strchr("abc", 'z')` → `NULL`
- 空文字列で `\0` 検索: `ft_strchr("", '\0')` → 先頭 `'\0'` を指す
- 高位バイト: `ft_strchr("abc\x80", (char)0x80)` → 該当位置

**`ft_strrchr`**
- 複数マッチ: `ft_strrchr("abcba", 'b')` → **後ろの** `'b'` (位置 3)
- `\0` 検索: `ft_strrchr("abc", '\0')` → 末尾 `'\0'` を指す
- 見つからない: `ft_strrchr("abc", 'z')` → `NULL`

**`ft_strncmp`**
- 一致: `ft_strncmp("abc", "abc", 3)` → 0
- `s1 < s2`: `ft_strncmp("abc", "abd", 3)` → `< 0`
- `s1 > s2`: `ft_strncmp("abd", "abc", 3)` → `> 0`
- `n` より短い文字列: `ft_strncmp("ab", "abc", 5)` → `< 0`
- `n == 0`: `ft_strncmp("abc", "xyz", 0)` → 0
- 高位バイト比較: `"\xFF"` vs `"\x01"` → `> 0` (unsigned 比較)

**`ft_memchr`**
- 見つかる: `ft_memchr("hello", 'l', 5)` → 位置 2
- n まで見つからない: `ft_memchr("hello", 'z', 5)` → `NULL`
- n == 0: `NULL`
- バイナリ: `\0` 含む領域で探索可

**`ft_memcmp`**
- 一致: 0
- バイト単位で差分あり: 差を返す (正/負)
- `n == 0`: 0

**`ft_strnstr`**
- `needle == ""`: haystack を返す
- needle 見つかる: 位置を返す
- len 内で見つからない: `NULL`
- needle が haystack より長い: `NULL`
- needle の一部だけが haystack に入る (len で切れる): `NULL`
- 境界: `ft_strnstr("abcabc", "abc", 3)` → 先頭一致 (位置 0)
- len 不足: `ft_strnstr("abcabc", "abc", 2)` → `NULL`
- needle 空 + len == 0: `ft_strnstr("aaa", "", 0)` → haystack (needle 空時は len 非考慮)

### 5.4 メモリ操作

**`ft_memset`**
- 通常: `char buf[5]; ft_memset(buf, 'A', 3);` → `buf[0..2] == 'A'`
- `len == 0`: 何も書き換えない
- バイナリ: `ft_memset(buf, 0xFF, 5)` で全バイト `0xFF`
- 戻り値: `b` ポインタ

**`ft_bzero`**
- 通常: 指定範囲を 0 化
- `n == 0`: 何もしない

**`ft_memcpy`**
- 通常: 非 overlap 領域のコピー
- `n == 0`: 何もしない (dst 変更なし)
- 戻り値: `dst`
- `n == 0` で NULL: `ft_memcpy(NULL, NULL, 0)` → クラッシュせず `NULL` を返す (設計書 §5.4 判断)

**`ft_memmove`**
- `dst < src`: 前方コピー
- `dst > src` (overlap): 後方コピー
  - 例: `char buf[] = "abcdef"; ft_memmove(buf+1, buf, 4);` → `"aabcdf"`
- `dst == src`: 変更なし
- `len == 0`: 変更なし

### 5.5 安全な文字列コピー

**`ft_strlcpy`**
- 通常: `ft_strlcpy(dst, "hello", 10)` → `dst=="hello"`、戻り値 5
- 切り詰め: `ft_strlcpy(dst, "hello", 3)` → `dst=="he"`、戻り値 5
- `dstsize == 0`: `dst` 変更なし、戻り値 5
- 空 src: `ft_strlcpy(dst, "", 10)` → `dst[0]=='\0'`、戻り値 0

**`ft_strlcat`**
- 通常: `dst="abc"`, `src="de"`, size=10 → `dst=="abcde"`、戻り値 5
- dst 長が dstsize に達する: dstsize 内に dst の `\0` が見つからないケース (BSD 規定 `dl >= dstsize`) → 戻り値 `dstsize + sl`、dst 変更なし
- 切り詰め: size 不足時、末尾に `\0` を置きつつ src の一部のみコピー
- `dstsize == 0`: 戻り値は `sl` (0 + sl)

### 5.6 変換・確保

**`ft_atoi`**
- 通常: `ft_atoi("42")` → 42
- 負数: `ft_atoi("-42")` → -42
- 符号 `+`: `ft_atoi("+42")` → 42
- 空白スキップ: `ft_atoi("   -42abc")` → -42
- `\t\n\v\f\r` スキップ: `ft_atoi("\t\n  42")` → 42
- 非数字終端: `ft_atoi("42abc")` → 42
- 空: `ft_atoi("")` → 0
- 数字なし: `ft_atoi("abc")` → 0
- 0 文字列: `ft_atoi("0")` → 0
- 二重符号: `ft_atoi("--42")` → 0 (man 準拠)

**注**: overflow ケース (例: `"99999999999999"`) は subject / man 上未定義で設計書 §5.6 が「defensive にしない」と判断。**テストには含めない**。

**`ft_calloc`**
- 通常: `ft_calloc(10, sizeof(int))` → 10 個の int、全 0、`free()` 可
- `count == 0` 単独: `ft_calloc(0, 10)` → `free()` 可能な unique ポインタ (subject 要件)
- `size == 0` 単独: `ft_calloc(10, 0)` → 同上
- `count == 0 && size == 0`: `ft_calloc(0, 0)` → 同上
- overflow (具体値): `ft_calloc(SIZE_MAX, 2)` → `NULL` (設計書 §5.6 の `size != 0 && count > SIZE_MAX / size` 判定)
- overflow 境界: `ft_calloc(SIZE_MAX / 2 + 1, 2)` → `NULL`
- 0 埋め確認: 返却直後に全バイトが 0

**`ft_strdup`**
- 通常: `ft_strdup("hello")` → 別アドレスで内容一致、`free()` 可
- 空文字列: `ft_strdup("")` → 1 バイト allocation、`""`
- ポインタ独立性: 元文字列を変更しても duplicate は変わらない

---

## 6. Part 2 テストケース

### 6.1 `ft_substr`

| ケース | 入力 | 期待値 |
|---|---|---|
| 通常 | `("hello world", 6, 5)` | `"world"` |
| 末尾まで | `("hello", 0, 100)` | `"hello"` |
| start 超過 | `("abc", 10, 5)` | `""` (空文字列) |
| len == 0 | `("abc", 0, 0)` | `""` |
| 先頭 1 文字 | `("abc", 0, 1)` | `"a"` |

全ケースで戻り値 `free()` 後 leak 無しを検証。

### 6.2 `ft_strjoin`

| ケース | 入力 | 期待値 |
|---|---|---|
| 通常 | `("foo", "bar")` | `"foobar"` |
| 片方空 | `("", "abc")` | `"abc"` |
| 両方空 | `("", "")` | `""` |

### 6.3 `ft_strtrim`

| ケース | 入力 | 期待値 |
|---|---|---|
| 両側トリム | `("  hi  ", " ")` | `"hi"` |
| 全部 set | `("aaa", "a")` | `""` |
| set なし | `("abc", "")` | `"abc"` |
| 一部マッチ | `("xyabcyx", "xy")` | `"abc"` |
| 内部の set 文字は保持 | `(" a b ", " ")` | `"a b"` |

### 6.4 `ft_split`

subject は連続/先頭/末尾区切りの挙動を明示していない。本テストは **設計書 §6.4 の word_count 方針 (空単語は配列に含めない)** に基づく期待値を採用する。

| ケース | 入力 | 期待値 |
|---|---|---|
| 通常 | `("a,b,c", ',')` | `["a","b","c",NULL]` |
| 先頭区切り | `(",,a,b", ',')` | `["a","b",NULL]` |
| 末尾区切り | `("a,b,,", ',')` | `["a","b",NULL]` |
| 連続区切り | `("a,,b", ',')` | `["a","b",NULL]` |
| 空文字列 | `("", ',')` | `[NULL]` |
| 全部区切り | `(",,,", ',')` | `[NULL]` |
| c == '\0' | `("abc", '\0')` | `["abc",NULL]` |

**追加**: 返却配列全要素と配列自体の `free()` 後 leak 無しを検証。

### 6.5 `ft_itoa`

| ケース | 入力 | 期待値 |
|---|---|---|
| 0 | `0` | `"0"` |
| 正 | `42` | `"42"` |
| 負 | `-42` | `"-42"` |
| INT_MAX | `2147483647` | `"2147483647"` |
| INT_MIN | `-2147483648` | `"-2147483648"` |
| 境界 | `-1`, `1`, `10`, `-10`, `100` | 対応する文字列 |

### 6.6 `ft_strmapi`

**ヘルパ**: `static char upper(unsigned int i, char c) { (void)i; return (c >= 'a' && c <= 'z') ? c - 32 : c; }`

| ケース | 入力 | 期待値 |
|---|---|---|
| 通常 | `("hello", upper)` | `"HELLO"` |
| 空 | `("", upper)` | `""` |
| インデックス利用 | `("abc", idx_add)` | 位置依存の結果 |

### 6.7 `ft_striteri`

**ヘルパ**: `static void star(unsigned int i, char *c) { (void)i; if (*c == 'x') *c = '*'; }`

| ケース | 入力 | 期待値 |
|---|---|---|
| 書き換え | `"xyzxy"` + star | `"*yz*y"` |
| 空 | `""` + star | 変化なし、クラッシュなし |

### 6.8 fd 出力系 (`ft_putchar_fd`, `ft_putstr_fd`, `ft_putendl_fd`, `ft_putnbr_fd`)

**手法**: `tmpfile()` を open し、`fileno(fp)` で int fd を取り出し、そこへ書き込む。書き込み後 `fflush(fp)` + `rewind(fp)` で読み直し、`fread`/`fgets` で取得した内容を期待文字列と比較。`fclose(fp)` で後始末。

| 関数 | 入力 | 期待値 (ファイル内容) |
|---|---|---|
| `ft_putchar_fd` | `('A', fd)` | `"A"` |
| `ft_putstr_fd` | `("hello", fd)` | `"hello"` |
| `ft_putstr_fd` | `(NULL, fd)` | `""` (クラッシュせず) |
| `ft_putendl_fd` | `("hi", fd)` | `"hi\n"` |
| `ft_putnbr_fd` | `(0, fd)` | `"0"` |
| `ft_putnbr_fd` | `(-42, fd)` | `"-42"` |
| `ft_putnbr_fd` | `(INT_MIN, fd)` | `"-2147483648"` |

---

## 7. Part 3 テストケース

### 7.1 `ft_lstnew`

- `content` がそのまま保持される (ポインタ一致)
- `next == NULL`
- `free(node)` のみ可能 (content は呼び出し側管理)

### 7.2 `ft_lstadd_front`

- 空リストに追加: `*lst` が `new`、`new->next == NULL`
- 既存リスト先頭に追加: `new->next == 旧 head`、`*lst == new`
- `lst == NULL` or `new == NULL`: クラッシュしない

### 7.3 `ft_lstsize`

- 空リスト (`NULL`): 0
- 1 要素: 1
- 3 要素: 3

### 7.4 `ft_lstlast`

- 空リスト (`NULL`): `NULL`
- 1 要素: その要素自身
- 3 要素: 末尾要素

### 7.5 `ft_lstadd_back`

- 空リストに追加: `*lst` が `new`
- 既存リスト末尾に追加: 末尾の `next == new`
- 3 要素リストに 1 つ追加後、`ft_lstsize` が 4

### 7.6 `ft_lstdelone`

- `del(content)` が呼ばれる (content の free 確認)
- ノード自体も `free` される
- **`next` は変更されない** (subject 明記): 隣接ノードを先に作っておき、`ft_lstdelone` 後にまだアクセス可能であることを確認

### 7.7 `ft_lstclear`

- 全ノードが free される
- 各 content に対して `del` が呼ばれる
- `*lst == NULL` になる (subject 明記)
- 空リスト (`*lst == NULL`) に対しても安全

### 7.8 `ft_lstiter`

- 全ノードの content に `f` が適用される
- `f` 呼び出し回数 == リストサイズ

**ヘルパ**: `static int g_iter_count = 0; static void count(void *c) { (void)c; g_iter_count++; }`

**注**: 各 ASSERT 前に `g_iter_count = 0;` で明示的にリセットすること。静的変数はケース間で必ず初期化し、複数ケースの累積による期待値乖離を防ぐ。

### 7.9 `ft_lstmap`

- 新しいリストが返る (元リストとポインタ独立)
- 各 new content が `f(old content)` の結果
- 新リストサイズ == 元リストサイズ
- `f = ft_strdup` 相当で確認し、valgrind/leaks でリーク 0

**失敗パステスト** (設計書 §7.9 の解放順検証):
- 理想: N 回目の `ft_lstnew` を失敗させ、「当該反復の `new_content` が `del` で解放」→「既存新リスト全体が `ft_lstclear(&new_head, del)` で解放」→「戻り値 NULL」→「leak 0」を確認。
- **実装難度**: C 標準では `malloc` の mock が困難なため、**本テストは実装困難なら省略可**。合格基準 (§11) には含めない。
- 代替: 正常系で leak 0 を確認することで、失敗時解放順の **間接証拠** とする。

---

## 8. メモリリーク・クラッシュテスト

### 8.1 目的

subject II 要件: *"your functions should not quit unexpectedly ... memory leaks will not be tolerated"*

### 8.2 実施方法

#### macOS (leaks ツール)

```sh
cd test
make leaks
```

内部で `leaks --atExit -- ./libft_test` を実行。

#### Linux (valgrind)

```sh
cd test
make valgrind
```

内部で `valgrind --leak-check=full --error-exitcode=1 ./libft_test` を実行。

### 8.3 期待結果

- **`leaks`**: `X leaks for Y total leaked bytes.` が `0 leaks for 0 total leaked bytes.` であること
- **`valgrind`**: `All heap blocks were freed -- no leaks are possible` かつ `ERROR SUMMARY: 0 errors from 0 contexts`

### 8.4 特に注目する関数

allocation を行う関数群 (成功時の解放を `main` 側で必ず行う):
- Part 1: `ft_calloc`, `ft_strdup`
- Part 2: `ft_substr`, `ft_strjoin`, `ft_strtrim`, `ft_split`, `ft_itoa`, `ft_strmapi`
- Part 3: `ft_lstnew`, `ft_lstmap` (lstmap は del を `free` として渡してクリア)

---

## 9. libc 比較テスト (オプション)

### 9.1 目的

`ft_X` と同名 libc `X` が同じ入力で同じ出力を返すことを確認する。

### 9.2 注意点

- **compliance 保証対象外のケース**:
  - `ft_calloc(0, 0)`: subject 要件 (unique free 可能) を優先、libc 挙動には従わない
  - `ft_atoi` overflow: man 上未定義、libc との一致は要求されない
  - `ft_memcpy(NULL, NULL, 0)`: man 上 UB、libc との一致は要求されない
- **macOS と Linux で挙動差があるもの**:
  - `strlcpy`, `strlcat`, `bzero`: glibc にはデフォルトで無く、比較対象は `<bsd/string.h>` + `-lbsd` が必要 (要件書 §5.3)。
- **比較は検証の補助手段**。subject 仕様との差異が libc との差異と同じとは限らない。

### 9.3 実装例

```c
static void	compare_strlen(const char *s)
{
	ASSERT_EQ_INT("strlen", (long)ft_strlen(s), (long)strlen(s));
}

static void	test_compare_strlen(void)
{
	compare_strlen("");
	compare_strlen("a");
	compare_strlen("hello, world!");
}
```

### 9.4 スコープ

本設計では **オプション扱い**。実装に余裕があれば `test_compare.c` を追加し、libc 比較セクションを走らせる。本書の合格基準 (§11) には含めない。

---

## 10. 実行手順

### 10.1 フルテスト実行

```sh
cd /Users/kota/dev/42-cursus/libft/test
make run
```

出力例:
```
...
=== RESULT: PASS=187 FAIL=0 ===
```

終了コード: FAIL==0 なら 0、それ以外は 1。

### 10.2 リークチェック

```sh
cd /Users/kota/dev/42-cursus/libft/test
make leaks        # macOS
make valgrind     # Linux
```

### 10.3 クリーンアップ

```sh
cd /Users/kota/dev/42-cursus/libft/test
make fclean
```

### 10.4 root の Makefile は変更しない

root の Makefile は Phase 0 で作成したまま変更しない。テストを走らせる際は必ず `cd test && make ...` の形式を使う。

---

## 11. 合格基準

テストが「成功」となる条件:

1. **`test/make run`** の結果が `FAIL=0` かつ終了コード 0
2. **`test/make leaks`** (または `valgrind`) の結果が `0 leaks / 0 bytes` / `0 errors`
3. テスト総数が十分に広範囲 (目安: **140 ケース以上**、全 43 関数を少なくとも 1 ケース以上)
4. 以下の最重要ケースを必ず含む (regression 防止):
   - `ft_calloc(0, 0)` が `free()` 可能な非 `NULL` を返す
   - `ft_itoa(INT_MIN)` が `"-2147483648"`
   - `ft_putnbr_fd(INT_MIN, fd)` が同じく `-2147483648` を出す
   - `ft_memmove` の overlap 両方向
   - `ft_split` の連続区切り + NULL 終端
   - `ft_lstdelone` 後に next が生存
   - `ft_lstclear` 後に `*lst == NULL`
   - `ft_lstmap` 完了後のリスト独立性と leak なし

---

## 12. 提出物との境界保証チェックリスト

本書に従って test/ を運用する際、42 提出前に以下を確認すること:

- [ ] root の `Makefile` に test/ への参照が **一切ない**
- [ ] `make` (root) 実行時、test/ 配下のファイルが **一切コンパイルされない**
- [ ] `make clean` / `make fclean` (root) で test/ 配下のファイルが触られない
- [ ] `norminette libft.h ft_*.c` が root の 44 ファイルのみを検査
- [ ] 提出前に `test/` ディレクトリを **削除する** か、`.gitignore` に `test/` を追加
- [ ] 提出リポジトリには `Makefile`, `libft.h`, `ft_*.c` × 43, `README.md` のみを置く
- [ ] libft.a の生成先は root のみ (test/ には生成されない)

### 12.1 `.gitignore` 推奨エントリ (test/ を残したまま提出する場合)

```
# Build artifacts
*.o
libft.a

# Test directory (not graded, not submitted)
test/

# OS-specific
.DS_Store
```

---

## 13. 本書の更新ポリシー

- subject / 要件書 / 設計書が改訂されたら本書も見直す
- 新たに合格基準を破るバグが見つかったら、§11 のリストに該当ケースを追加し、テストを追加する
- 本書は **テストの仕様**、実装 (`test_*.c`) は本書に従って書く
