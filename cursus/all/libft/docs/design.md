# Libft 設計書

`libft/subject/en.subject.pdf` (v19.2) および `libft/docs/requirements.md` に厳密準拠する実装設計。
差分があれば subject / requirements.md が優先。

---

## 1. 設計方針

### 1.1 準拠すべき制約 (subject / requirements.md より)

| 制約 | 出典 |
|---|---|
| Program Name: `libft.a` | IV (提出物表) |
| Files to Submit: `Makefile`, `libft.h`, `ft_*.c` | IV (提出物表) |
| Makefile ルール: `NAME`, `all`, `clean`, `fclean`, `re` | IV / II |
| コンパイルフラグ: `-Wall -Wextra -Werror` | II / IV.1 |
| コンパイラ: `cc` | II |
| 不要な再リンクをしてはならない | II |
| ライブラリ作成: `ar` 使用 / `libtool` 禁止 | IV.1 |
| 全ファイルを **リポジトリ root** に配置 | IV.1 / VI (赤色警告) |
| 未使用ファイルの提出不可 | IV.1 |
| グローバル変数禁止 | IV.1 |
| ヘルパー関数は `static` | IV.1 |
| `libft.a` は root に作成 | IV.1 |
| Norm 準拠 (違反で 0 点) | II |
| `restrict` 禁止 / `-std=c99` 禁止 | IV.2 (黄色コールアウト) |
| Part 1 関数は外部関数に依存してはならない | IV.2 |
| 文字分類関数の戻り値: 1 / 0 | IV.2 |
| `calloc`: `nmemb` or `size` が 0 → `free()` 可能な unique ポインタ | IV.2 |
| メモリリーク・クラッシュ禁止 | II |

### 1.2 設計原則

- **1 関数 = 1 ファイル**。subject の `ft_*.c` glob と 42 Norm 慣習に準拠。
- ファイル名は関数名そのまま (例: `ft_strlen.c`)。
- ヘッダは `libft.h` 1 つに集約 (subject 指定)。
- 全ファイル (`Makefile`, `libft.h`, 全 `ft_*.c`) はリポジトリ root 配置。
- 本 design.md は **ルートではなく `libft/docs/`** に置く。subject の「全ファイルを root に」は **提出対象ファイル** (Makefile / libft.h / ft_*.c) に関する制約であり、docs/ の設計文書は提出対象外。

### 1.3 mandatory のみ / bonus は対象外

v19.2 では Part 1〜3 すべてが Chapter IV "Mandatory part"。bonus 部はこのバージョンには存在しないため、`_bonus.{c/h}` ファイルおよび `bonus` Makefile ルールは **作成しない**。

---

## 2. リポジトリ構成

### 2.1 ファイルツリー (提出対象)

```
libft/
├── Makefile
├── libft.h
├── ft_isalpha.c
├── ft_isdigit.c
├── ft_isalnum.c
├── ft_isascii.c
├── ft_isprint.c
├── ft_strlen.c
├── ft_memset.c
├── ft_bzero.c
├── ft_memcpy.c
├── ft_memmove.c
├── ft_strlcpy.c
├── ft_strlcat.c
├── ft_toupper.c
├── ft_tolower.c
├── ft_strchr.c
├── ft_strrchr.c
├── ft_strncmp.c
├── ft_memchr.c
├── ft_memcmp.c
├── ft_strnstr.c
├── ft_atoi.c
├── ft_calloc.c
├── ft_strdup.c
├── ft_substr.c
├── ft_strjoin.c
├── ft_strtrim.c
├── ft_split.c
├── ft_itoa.c
├── ft_strmapi.c
├── ft_striteri.c
├── ft_putchar_fd.c
├── ft_putstr_fd.c
├── ft_putendl_fd.c
├── ft_putnbr_fd.c
├── ft_lstnew.c
├── ft_lstadd_front.c
├── ft_lstsize.c
├── ft_lstlast.c
├── ft_lstadd_back.c
├── ft_lstdelone.c
├── ft_lstclear.c
├── ft_lstiter.c
└── ft_lstmap.c
```

- `.c` ファイル総数: **43** (Part 1: 23 / Part 2: 11 / Part 3: 9)
- ヘッダ: 1 (`libft.h`)
- Makefile: 1
- 生成物: `libft.a` (root)
- 開発参照 (非提出): `subject/en.subject.pdf`, `docs/requirements.md`, `docs/design.md`

### 2.2 提出対象外の扱い

`subject/`, `docs/` は提出対象外。**Makefile では一切参照しない** (未使用ファイル扱いを避けるため、ビルド物も docs/ も touch しない)。

---

## 3. `libft.h` の設計

### 3.1 インクルードガード

```c
#ifndef LIBFT_H
# define LIBFT_H
```

42 Norm: マクロ名は **大文字**、ファイル名 + `_H`。インデントはスペース 1 つ(Norm 準拠)。

### 3.2 標準ヘッダの include

```c
# include <stddef.h>   /* size_t */
```

- `size_t` を使うため `<stddef.h>` が必要。
- `write` のプロトタイプは要らない (呼ぶのは `.c` 側、ヘッダで再宣言しない)。`.c` ファイル側で `<unistd.h>` を include する。
- `malloc`, `free` は `<stdlib.h>` → `.c` 側で include。
- ヘッダの責務は **公開プロトタイプと `t_list` 定義のみ** に限定。

### 3.3 `t_list` 構造体 (subject §IV.4 準拠)

```c
typedef struct s_list
{
    void            *content;
    struct s_list   *next;
}   t_list;
```

メンバ名・型・順序・スペーシングは subject 原文に一致。

### 3.4 公開プロトタイプ (要件書 §5.2 / §6 / §7 のとおり)

要件書 §6 / §7 の表に記載されたプロトタイプを一字一句そのまま宣言する。順序は Part 1 → Part 2 → Part 3。

**Part 1** (`ft_` プレフィックスを付けた libc 関数。libc man ページのプロトタイプに準じる)

```c
int     ft_isalpha(int c);
int     ft_isdigit(int c);
int     ft_isalnum(int c);
int     ft_isascii(int c);
int     ft_isprint(int c);
size_t  ft_strlen(const char *s);
void    *ft_memset(void *b, int c, size_t len);
void    ft_bzero(void *s, size_t n);
void    *ft_memcpy(void *dst, const void *src, size_t n);
void    *ft_memmove(void *dst, const void *src, size_t len);
size_t  ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t  ft_strlcat(char *dst, const char *src, size_t dstsize);
int     ft_toupper(int c);
int     ft_tolower(int c);
char    *ft_strchr(const char *s, int c);
char    *ft_strrchr(const char *s, int c);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
void    *ft_memchr(const void *s, int c, size_t n);
int     ft_memcmp(const void *s1, const void *s2, size_t n);
char    *ft_strnstr(const char *haystack, const char *needle, size_t len);
int     ft_atoi(const char *str);
void    *ft_calloc(size_t count, size_t size);
char    *ft_strdup(const char *s1);
```

注意事項:

- libc の man で `restrict` が付くもの (例: `memcpy`, `strlcpy` など) は **付けない**。subject IV.2 の黄色コールアウトで禁止。
- `isalpha` 等の man プロトタイプは `int c` なので、その型を踏襲。
- `strlcpy`, `strlcat` の第3引数は `size_t dstsize` (BSD 実装準拠)。

**Part 2** (要件書 §6 プロトタイプ)

```c
char    *ft_substr(char const *s, unsigned int start, size_t len);
char    *ft_strjoin(char const *s1, char const *s2);
char    *ft_strtrim(char const *s1, char const *set);
char    **ft_split(char const *s, char c);
char    *ft_itoa(int n);
char    *ft_strmapi(char const *s, char (*f)(unsigned int, char));
void    ft_striteri(char *s, void (*f)(unsigned int, char*));
void    ft_putchar_fd(char c, int fd);
void    ft_putstr_fd(char *s, int fd);
void    ft_putendl_fd(char *s, int fd);
void    ft_putnbr_fd(int n, int fd);
```

**Part 3** (要件書 §7 プロトタイプ、`t_list` 定義の後に置く)

```c
t_list  *ft_lstnew(void *content);
void    ft_lstadd_front(t_list **lst, t_list *new);
int     ft_lstsize(t_list *lst);
t_list  *ft_lstlast(t_list *lst);
void    ft_lstadd_back(t_list **lst, t_list *new);
void    ft_lstdelone(t_list *lst, void (*del)(void *));
void    ft_lstclear(t_list **lst, void (*del)(void *));
void    ft_lstiter(t_list *lst, void (*f)(void *));
t_list  *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
```

### 3.5 ヘッダ全体のレイアウト

> 以下のコードブロックの表示はスペース区切りだが、**実装時は 42 Norm に従い、インデントにはタブ (`\t`) を使用する**。スペースとの混在禁止。

```c
#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>

typedef struct s_list
{
    void            *content;
    struct s_list   *next;
}   t_list;

/* --- Part 1: libc functions --- */
int     ft_isalpha(int c);
/* ... 23 関数 ... */

/* --- Part 2: additional functions --- */
char    *ft_substr(char const *s, unsigned int start, size_t len);
/* ... 11 関数 ... */

/* --- Part 3: linked list --- */
t_list  *ft_lstnew(void *content);
/* ... 9 関数 ... */

#endif
```

Norm ルール: `# include` (# の後にスペース) を使う。

---

## 4. `Makefile` の設計

### 4.1 必須ルール (subject II / IV)

- `$(NAME)` (= `all` と同値の成果物生成ルール)
- `all`
- `clean`
- `fclean`
- `re`

### 4.2 再リンク抑制の要件

subject II: "your Makefile must not perform unnecessary relinking"

対応:
- `$(NAME)` は `$(OBJS)` に依存
- 各 `.o` は対応する `.c` と `libft.h` に依存 (ヘッダ変更時のみ全 `.o` 再コンパイル)
- オブジェクトファイルが既に最新であれば `ar` も実行されない (make が "up to date" と判定)

### 4.3 `ar` の使用 (subject IV.1)

`ar rcs $(NAME) $(OBJS)` を使う。`libtool` は使わない。

### 4.4 Makefile 全体

```makefile
NAME    = libft.a

CC      = cc
CFLAGS  = -Wall -Wextra -Werror
AR      = ar rcs
RM      = rm -f

HEADER  = libft.h

SRCS_PART1 = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
             ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
             ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
             ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
             ft_atoi.c ft_calloc.c ft_strdup.c

SRCS_PART2 = ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
             ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
             ft_putendl_fd.c ft_putnbr_fd.c

SRCS_PART3 = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
             ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
             ft_lstmap.c

SRCS    = $(SRCS_PART1) $(SRCS_PART2) $(SRCS_PART3)
OBJS    = $(SRCS:.c=.o)

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

### 4.5 Makefile 設計上のチェック項目

- [x] `NAME`, `all`, `clean`, `fclean`, `re` 全て存在
- [x] `-Wall -Wextra -Werror` でコンパイル
- [x] `cc` を使用
- [x] `ar` を使用 (`libtool` 不使用)
- [x] `$(NAME)` 生成場所はカレントディレクトリ (= リポジトリ root)
- [x] 未使用ファイルをビルドに含めない (SRCS に全 43 本を明示列挙)
- [x] `.PHONY` 指定で phony target 保証
- [x] ヘッダ変更時に全 `.o` 再コンパイル、個別 `.c` 変更時は該当 `.o` のみ
- [x] 一度ビルド後に `make` を再実行しても再リンクしない

---

## 5. 関数実装方針 (Part 1)

### 5.1 Part 1 全般

- subject IV.2: **外部関数に依存してはならない**。libc の関数呼び出し禁止。他の `ft_*` 関数の呼び出しも避け、原則として自己完結で実装する (文字分類の小物を除く)。
- man ページの挙動に一致させる。
- `const` は man に合わせて付ける (ただし `restrict` は外す)。

### 5.2 文字分類・変換 (7 関数)

| 関数 | 実装方針 |
|---|---|
| `ft_isalpha` | `('A' <= c && c <= 'Z') \|\| ('a' <= c && c <= 'z')` → 1/0 |
| `ft_isdigit` | `'0' <= c && c <= '9'` → 1/0 |
| `ft_isalnum` | isalpha と isdigit の条件式を **ファイル内に直書き** する。subject の「外部関数禁止」は libc 関数を指し、同じ libft 内の呼び出しは禁止対象外だが、各関数を自己完結にしておく方針 (§5.7 参照) |
| `ft_isascii` | `0 <= c && c <= 127` → 1/0 |
| `ft_isprint` | `' ' <= c && c <= '~'` (32〜126) → 1/0 |
| `ft_toupper` | `'a' <= c && c <= 'z'` なら `c - 32`、そうでなければ `c` そのまま |
| `ft_tolower` | `'A' <= c && c <= 'Z'` なら `c + 32`、そうでなければ `c` そのまま |

要件書 §5.1: 文字分類は **1 or 0**。man の libc `isalpha` は非 0 を返すだけでよいが、subject が 1 を厳密指定。

### 5.3 文字列長・探索 (7 関数)

| 関数 | 実装方針 |
|---|---|
| `ft_strlen` | `'\0'` まで単純に走査、カウントを返す |
| `ft_strchr` | `s` を `'\0'` を含めて走査。`c` は `(unsigned char)` にキャストして比較 (`'\0'` 指定時も見つかる必要があるので末尾を含む) |
| `ft_strrchr` | 後方からマッチ、または順方向走査で最後にマッチした位置を保持 |
| `ft_strncmp` | `n` まで走査。不一致発生時は `(unsigned char)s1[i] - (unsigned char)s2[i]` を返す。`'\0'` 到達で途中終了 |
| `ft_strnstr` | `len` の範囲内で `needle` を検索。`needle` が空文字列なら `haystack` を返す。`haystack` の長さが `needle` 長 + 現在位置を超えない場合のみ比較 |
| `ft_memchr` | `(unsigned char*)s` として `n` バイト走査、`(unsigned char)c` と比較 |
| `ft_memcmp` | `n` バイトを `unsigned char` として比較、差を返す |

### 5.4 メモリ操作 (4 関数)

| 関数 | 実装方針 |
|---|---|
| `ft_memset` | `(unsigned char *)b` に `(unsigned char)c` を `len` バイト書き込む。`b` を返す |
| `ft_bzero` | `ft_memset(s, 0, n)` 相当を自己実装 (外部依存不可なのでループ直書き or 内部で同じ処理) |
| `ft_memcpy` | `n == 0` なら何もせず `dst` を返す。`n > 0` で `dst == NULL && src == NULL` は undefined behavior 領域 (man 準拠で未定義のまま許容)。overlap は考慮しない (memmove の役割) |
| `ft_memmove` | `dst < src` なら先頭から、`dst > src` なら末尾から (overlap を正しく扱う) |

### 5.5 安全な文字列コピー (2 関数)

| 関数 | 実装方針 |
|---|---|
| `ft_strlcpy` | `src` 長を測り、`dstsize > 0` なら `min(srclen, dstsize-1)` バイトコピーしてヌル終端。戻り値は **src の長さ** |
| `ft_strlcat` | 既存 `dst` の長さ `dl` と `src` 長 `sl` を取得。`dl >= dstsize` なら何もせず `dstsize + sl` を返す (BSD 規定)。そうでなければ残り容量にコピーしてヌル終端、戻り値 `dl + sl` |

### 5.6 変換・確保 (3 関数)

| 関数 | 実装方針 |
|---|---|
| `ft_atoi` | 空白スキップ (`' '`, `\t`, `\n`, `\v`, `\f`, `\r`)、符号 1 文字、数字を積み上げる。**man 挙動に従い overflow は未定義** (42 では INT_MIN/INT_MAX での挙動を問われる場合があるが、atoi の man は overflow 未定義なので defensive にしない判断もアリ)。設計としてはシンプルな累積版を採用 |
| `ft_calloc` | `count * size` バイト確保 → 0 埋め。subject 要件: `count == 0 \|\| size == 0` の時も `free()` に渡せる unique ポインタを返す (= `malloc(0)` 相当でよい)。掛け算のオーバーフロー検出として `size != 0 && count > SIZE_MAX / size` で判定し、true なら NULL 返却 (これは subject 非要求だが defensive)。`ft_calloc.c` 内で `<stdlib.h>` (malloc) と `<limits.h>` (SIZE_MAX) を include |
| `ft_strdup` | `ft_strlen` 相当で長さ取得 → `malloc` → ヌル終端までコピー |

### 5.7 Part 1 の外部依存方針の最終整理

要件書 §5.1: 「再実装する関数は **外部関数に依存してはならない**」。
解釈: libc の呼び出しは禁止。**`ft_calloc` / `ft_strdup` は malloc を呼ぶが**、これは subject の表で許可されている (「In order to implement the two following functions, you will use malloc()」)。

Part 1 の各関数内で他の Part 1 関数 (例: `ft_strlen`) を呼ぶことは subject 原文上は禁止されていないが、安全側に倒して **各関数は自己完結** で書く (1 関数が失敗すると連鎖しないメリット / Norm 上も問題なし)。

---

## 6. 関数実装方針 (Part 2)

### 6.1 `ft_substr`

- `s == NULL` → NULL 返却 (defensive)
- `start >= ft_strlen(s)` → 空文字列 `""` を malloc して返す (NULL ではない)
- 実際に copy する長さは `min(len, strlen(s) - start)`
- `malloc` 失敗時 NULL

### 6.2 `ft_strjoin`

- `s1 == NULL \|\| s2 == NULL` → NULL (defensive)
- `ft_strlen(s1) + ft_strlen(s2) + 1` を malloc
- s1 をコピーして、続いて s2 をコピー、末尾にヌル終端

### 6.3 `ft_strtrim`

- `s1 == NULL \|\| set == NULL` → NULL
- `set` に含まれる文字かを判定する `static` ヘルパ関数を用意 (in_set)
- 前方から最初の非 set 文字位置 `i`、後方から最後の非 set 文字位置 `j` を探す
- `j < i` (全部 set) → 空文字列を返す
- それ以外は `j - i + 1` を malloc してコピー

### 6.4 `ft_split`

- `s == NULL` → NULL
- 出力単語数を数える `static` ヘルパ関数 (word_count) を用意
- `malloc((count + 1) * sizeof(char *))` で配列確保
- 各単語について **`ft_substr` を呼んで** コピー (Part 2 間での再利用方針、§6.12 参照)。末尾要素は NULL
- **任意のステップで malloc が失敗した場合**、それまでに確保した配列要素を全 `free()` してから NULL を返す (リーク防止)
- 返却配列は **NULL 終端**

### 6.5 `ft_itoa`

- `n == INT_MIN` の特別扱いが必要 (`-INT_MIN` はオーバーフロー)
- 桁数を数える `static` 関数 (num_len)。`n == 0` 時は桁数 1
- `malloc(num_len + 1 + (n < 0 ? 1 : 0))`
- 負数の符号を書き、絶対値を末尾から書き込む

### 6.6 `ft_strmapi`

- `s == NULL \|\| f == NULL` → NULL
- `ft_strlen(s) + 1` を malloc
- 各 index について `f(i, s[i])` を代入、末尾ヌル終端

### 6.7 `ft_striteri`

- `s == NULL \|\| f == NULL` → 何もしないで return
- 各 i について `f(i, &s[i])` を呼ぶ (アドレス渡し)

### 6.8 `ft_putchar_fd`

- `write(fd, &c, 1)` を呼ぶだけ

### 6.9 `ft_putstr_fd`

- `s == NULL` は defensive に return
- `ft_strlen(s)` を計算して `write(fd, s, len)` (または逐次 putchar_fd でも可、設計は前者を採用)

### 6.10 `ft_putendl_fd`

- `ft_putstr_fd(s, fd); ft_putchar_fd('\n', fd);`

### 6.11 `ft_putnbr_fd`

- `n == INT_MIN` 特別扱い (文字列 `-2147483648` をハードコードせず、再帰で `-(n/10)` を呼ぶと overflow するので、`long long` に昇格 or 最初に符号処理 + 絶対値を unsigned で扱う)
- 負数なら `'-'` を出し、絶対値を再帰出力

### 6.12 Part 2 での内部 `ft_*` 利用方針

Part 1 と違い Part 2 は内部で `ft_strlen` 等を使ってよい (subject は外部依存禁止を Part 1 のみに明示)。設計としては積極的に再利用する:
- `ft_substr`, `ft_strjoin`, `ft_strtrim`, `ft_itoa`, `ft_strmapi`, `ft_strdup` 内で `ft_strlen`
- `ft_split` 内で `ft_substr`
- `ft_putendl_fd` 内で `ft_putstr_fd`, `ft_putchar_fd`
- `ft_putstr_fd` 内で `ft_strlen`

---

## 7. 関数実装方針 (Part 3)

### 7.1 `ft_lstnew`

- `malloc(sizeof(t_list))`
- `content = content`, `next = NULL`
- malloc 失敗時 NULL

### 7.2 `ft_lstadd_front`

- `lst == NULL \|\| new == NULL` → return (defensive)
- `new->next = *lst; *lst = new;`

### 7.3 `ft_lstsize`

- `lst == NULL` → 0
- イテレートしてカウント

### 7.4 `ft_lstlast`

- `lst == NULL` → NULL
- `next == NULL` のノードまで進む

### 7.5 `ft_lstadd_back`

- `lst == NULL \|\| new == NULL` → return
- `*lst == NULL` なら `*lst = new`
- それ以外は `ft_lstlast(*lst)->next = new`

### 7.6 `ft_lstdelone`

- `lst == NULL \|\| del == NULL` → return
- `del(lst->content)` を呼び、その後 `free(lst)`
- **`lst->next` は絶対に free しない** (subject 明記)

### 7.7 `ft_lstclear`

- `lst == NULL \|\| *lst == NULL \|\| del == NULL` → return
- 先頭から順に `ft_lstdelone(current, del)` を呼んで全ノードを free
- 最後に `*lst = NULL`

### 7.8 `ft_lstiter`

- `lst == NULL \|\| f == NULL` → return
- 各ノードの `content` に `f` を適用

### 7.9 `ft_lstmap`

- `lst == NULL \|\| f == NULL` → NULL (del は呼び出さない場合もあるので単独 NULL チェック不要)
- 新リスト頭を `new_head = NULL` で初期化
- 各ノードについて:
  - `new_content = f(node->content)` で新 content を取得
  - `new_node = ft_lstnew(new_content)` で新ノードを作る
  - **新ノードの malloc が失敗した場合**:
    1. `del(new_content)` で **この反復で取得済みの new_content を先に解放**
    2. `ft_lstclear(&new_head, del)` で新リスト全体を解放 (各ノードの content も `del` で free される)
    3. `NULL` を返す
  - 成功したら `ft_lstadd_back(&new_head, new_node)` で新リスト末尾に追加
- 最後まで走り終えたら `new_head` を返す

### 7.10 Part 3 での内部 `ft_*` 利用方針

- `ft_lstadd_back` が `ft_lstlast` を呼ぶ
- `ft_lstclear` が `ft_lstdelone` を呼ぶ
- `ft_lstmap` が `ft_lstnew`, `ft_lstadd_back`, `ft_lstclear` を呼ぶ

これらは libft 内部参照なので、ar アーカイブ内で解決される。

---

## 8. エッジケース・エラーハンドリング方針

| ケース | 方針 |
|---|---|
| 入力ポインタ NULL | defensive に早期リターン (NULL / void) |
| malloc 失敗 | NULL を返す (および途中確保物の解放) |
| `ft_split` 途中 malloc 失敗 | 既に確保した要素を free してから NULL |
| `ft_lstmap` 途中 malloc 失敗 | `del` で content 解放しつつ新リストを `ft_lstclear` |
| INT_MIN (`ft_itoa`, `ft_putnbr_fd`, `ft_atoi`) | `long` 昇格または unsigned 経由で扱う |
| `ft_memcpy` の overlap | 仕様外 (memmove の責務) |
| `ft_strnstr` で needle が空 | haystack を返す (man 準拠) |
| `ft_atoi` の overflow | man atoi 準拠で未定義。defensive なしの単純実装 |
| `ft_calloc(0, 0)` | subject 要件: `free()` 可能な unique ポインタ (malloc(0) に委譲 or 1 バイト確保) |

---

## 9. 42 Norm 準拠方針

Norm (norminette) の主な制約:

- 関数は **25 行以内** (本体、シグネチャとブレース除く)
- 1 ファイルあたり関数数 **5 個以下**
- 1 行 **80 字以内** (タブ幅 4 で計算)
- 関数の引数は **4 個以下**
- 1 関数内の変数宣言は **関数先頭**
- `for` 文・三項演算子は使い方に制限 (norminette のバージョンに依存、現行では `for` 禁止ではないが 42 では `while` 推奨)
- 1 ファイルあたりのグローバル変数・構造体・typedef の数に制限
- インデントはタブ (文字)、スペースとの混在禁止
- 関数の戻り値型と関数名の間で改行 (型を 1 行目、名前と引数を 2 行目) — **関数定義 (`.c` 内) に適用**、ヘッダのプロトタイプは 1 行宣言でよい
- ブレースは新行
- 複数宣言の単一 `;` 禁止 (1 行 1 宣言)

設計上の対応:

- 1 関数 1 ファイル方針なので関数数上限は自然にクリア
- 25 行に収まりにくい関数 (`ft_split`, `ft_itoa`, `ft_lstmap` 等) は **`static` ヘルパ** に分割
- 変数宣言はすべて関数先頭
- `for` は使わず `while` 統一
- ヘッダは `# include`, `# define` (`#` 直後にスペース) でインデント

### 9.1 `static` ヘルパを置くファイル例

| 主関数 | ヘルパ (同一ファイル内に `static`) |
|---|---|
| `ft_split` | `static size_t word_count(char const *s, char c);` / `static char *word_dup(char const *s, char c, size_t *i);` / クリーンアップ用 `static void free_split(char **arr, size_t n);` |
| `ft_itoa` | `static size_t num_len(int n);` |
| `ft_strtrim` | `static int in_set(char c, char const *set);` |
| `ft_putnbr_fd` | `static void put_uint(unsigned int n, int fd);` |
| `ft_lstmap` | `static void cleanup(t_list *new_head, void (*del)(void *));` (ft_lstclear を呼ぶラッパ) |

すべて **同一 `.c` 内の `static`** なのでスコープ漏れなし (subject IV.1 準拠)。

---

## 10. ビルド・動作確認手順

### 10.1 ビルド

```sh
$ make           # libft.a を生成
$ make clean     # .o 削除
$ make fclean    # .o + libft.a 削除
$ make re        # fclean + all
```

期待挙動:

- `make` 2 回目で `make: Nothing to be done for 'all'.` と出る (再リンクしない)
- `libft.h` の timestamp を変えると全 `.o` が再コンパイル
- `ft_strlen.c` の timestamp を変えると `ft_strlen.o` のみ再コンパイル → `libft.a` 再生成

### 10.2 テスト (任意、提出対象外)

subject II: テスト作成は推奨だが提出不要・採点対象外。subject IV.1 の「未使用ファイル提出不可」に触れないよう、**本設計では `tests/` ディレクトリを作らない**。defense (ピア評価) 時にはピアのテスト、または自作の簡易ドライバをその場で用意する前提。どうしてもローカルでテストを保持したい場合は、`git` 追跡外の場所 (リポジトリ外、または `.gitignore` 追加) に置き、リポジトリには絶対にコミットしない。

### 10.3 Norm チェック

```sh
$ norminette *.c libft.h
```

- エラーがあれば評価 0 点 (subject II)
- bonus も含まれるが v19.2 では bonus なし → 全 .c + libft.h が対象

### 10.4 リーク・クラッシュチェック (ローカル)

```sh
$ cc -Wall -Wextra -Werror main.c libft.a -o test
$ valgrind --leak-check=full ./test    # Linux
$ leaks --atExit -- ./test             # macOS
```

subject II: メモリリーク・クラッシュは不可。全関数をテストドライバから呼んで確認する。

---

## 11. README 設計 (Chapter V 準拠)

`README.md` (リポジトリ root) の構造:

```markdown
*This project has been created as part of the 42 curriculum by <login1>[, <login2>[, <login3>[...]]].*

## Description
...プロジェクトの目標と概要...

## Instructions
...make のビルド・インストール・使い方...

## Resources
...参考資料 (man ページ, 42 intranet 等)...
### AI usage
...AI をどのタスクにどの程度使ったかの記述...

## Library details
...作成したライブラリの関数一覧と詳細...
```

必須要素 (要件書 §8):

- 1 行目は斜体で `*This project has been created as part of the 42 curriculum by <login1>[, <login2>[...]]].*`
- Description / Instructions / Resources セクション
- Resources 内に **AI をどのタスクのどの部分にどう使ったか** の記述
- **ライブラリの詳細な説明** (追加要求)
- 推奨言語: 英語 (キャンパス主要言語でも可)

---

## 12. 実装順序 (推奨)

subject の順序に従い、Part 1 → Part 2 → Part 3 で実装することで **依存関係の後退が発生しない**:

1. **Part 1 - group A (自己完結な簡単なもの)**: isalpha, isdigit, isalnum, isascii, isprint, toupper, tolower, strlen, bzero, memset
2. **Part 1 - group B (基本メモリ・文字列)**: memcpy, memmove, memchr, memcmp, strchr, strrchr, strncmp, strnstr, strlcpy, strlcat
3. **Part 1 - group C (変換・確保)**: atoi, calloc, strdup
4. **Part 2 (Part 1 に依存)**: substr, strjoin, strtrim, split, itoa, strmapi, striteri, putchar_fd, putstr_fd, putendl_fd, putnbr_fd
5. **Part 3 (独立に近い)**: lstnew → lstadd_front → lstsize → lstlast → lstadd_back → lstdelone → lstclear → lstiter → lstmap

各ステップで該当 `.c` を書き、`Makefile` の SRCS に追加し、`libft.h` に宣言を追加し、`make` が通ることを確認してから次に進む。

---

## 13. 設計チェックリスト (subject / requirements 完全準拠確認)

### 13.1 ファイル

- [x] `libft.a` ルート生成
- [x] `Makefile` / `libft.h` / `ft_*.c` のみ提出 (43 + 2 = 45 ファイル)
- [x] subject / docs / tests 等は **提出対象外**、Makefile 非参照
- [x] 未使用ファイルなし

### 13.2 Makefile

- [x] ルール: `NAME`, `all`, `clean`, `fclean`, `re`
- [x] `-Wall -Wextra -Werror`
- [x] `cc` 使用
- [x] `ar` 使用、`libtool` 不使用
- [x] 不要な再リンクなし (依存関係明示)
- [x] bonus ルール **作成しない** (v19.2 に bonus なし)

### 13.3 ヘッダ

- [x] `typedef struct s_list { void *content; struct s_list *next; } t_list;` を含む
- [x] 全 43 関数のプロトタイプ宣言 (要件書プロトタイプと一字一句一致)
- [x] include ガード

### 13.4 関数

- [x] Part 1: 23 関数 (`ft_` プレフィックス、外部依存なし、文字分類は 1/0)
- [x] Part 2: 11 関数 (許可された外部関数のみ)
- [x] Part 3: 9 関数 (`t_list` 使用、`ft_lstdelone` は next を free しない)
- [x] `ft_calloc`: 0 入力で `free()` 可能 unique ポインタ
- [x] グローバル変数なし
- [x] ヘルパは `static`
- [x] メモリリークなし (途中失敗時の解放含む)
- [x] クラッシュなし (NULL 入力防御)

### 13.5 Norm

- [x] 全関数 25 行以内 (ヘルパで分割)
- [x] `restrict` なし
- [x] `-std=c99` で **コンパイルしない** (subject 禁止)
- [x] インデント・改行・命名が Norm 準拠
