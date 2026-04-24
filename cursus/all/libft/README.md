*This project has been created as part of the 42 curriculum by kokubo.*

## 概要 (Description)

Libft は 42 カリキュラム最初のプロジェクトで、C 標準ライブラリの一部と
追加のユーティリティ関数をゼロから実装した自作ライブラリ (`libft.a`) を
作成するもの。以降の C 課題 (get_next_line, ft_printf, push_swap, minishell
など) で継続的に再利用される基盤となる。

**実装規模**: 43 関数 + `t_list` 構造体 + 自作 `Makefile`。

- Part 1 — libc 関数の再実装: **23 関数**
- Part 2 — 追加ユーティリティ: **11 関数**
- Part 3 — 単方向連結リスト: **9 関数**

## ビルドと使い方 (Instructions)

リポジトリ root で `make` すると `libft.a` が生成される:

```sh
make          # libft.a を生成
make clean    # .o を削除
make fclean   # .o と libft.a を削除
make re       # fclean + all
```

他プロジェクトから使うには、`libft.a` をリンクしヘッダを include する:

```sh
cc -Wall -Wextra -Werror your_main.c libft.a -o your_program
```

```c
#include "libft.h"
```

**コンパイルフラグ**: `cc -Wall -Wextra -Werror` (subject 準拠)
**ライブラリ作成**: `ar rcs` (`libtool` 不使用)
**グローバル変数**: ゼロ (subject IV.1 準拠)
**Norm**: 44 ファイルすべて `norminette` 合格済み

## 参考資料 (Resources)

- C 標準ライブラリの man ページ (`man 3 strlen`, `man 3 memcpy`, `man 3 atoi` 他)
- BSD `strlcpy` / `strlcat` の仕様 (glibc には含まれないため挙動確認時は
  `<bsd/string.h>` と `-lbsd` が参考になる)
- 42 intranet の Libft プロジェクトページ (subject v19.2)

### AI の利用について (AI usage)

本プロジェクトでは Anthropic Claude (Opus 4.7) を **設計・検証の足場** と
して活用した。具体的な使用箇所は以下:

1. **要件抽出**: subject PDF (英語) の読解と日本語要件書 (`docs/requirements.md`) への整理
2. **アーキテクチャ設計**: `libft.h` / `Makefile` / 関数分割方針 (`docs/design.md`)
3. **実装手順化**: 48 タスクに分解した Plan 実行可能な手順書 (`docs/implementation.md`)
4. **クロス検証**: subject ⇔ 要件書 ⇔ 設計書 ⇔ 実装手順書の不一致チェック (検証エージェントの反復実行)
5. **Norm 対応**: 42 ヘッダの自動生成・関数分割支援
6. **テスト設計**: ブラックボックステストケースの整理 (`test/test_design.md` / `test/test_implementation.md`)

**実装コードそのもの**・**バグ調査**・**最終責任** は著者 (kokubo) が負い、
AI 出力はスキャフォールドとレビュー目的で使用した。ユーザー (著者) が
常に唯一の意思決定者である方針で進めた。

## ライブラリ詳細 (Library details)

### Part 1 — libc 関数の再実装 (23 関数)

subject 原文通り、man ページの挙動に厳密に従う。プレフィックスは `ft_`、
`restrict` は使用しない (subject IV.2)。**外部関数依存なし**
(`ft_calloc` / `ft_strdup` のみ `malloc` を使用)。

| 分類 | 関数 |
|---|---|
| 文字分類 (戻り値 1/0) | `ft_isalpha` `ft_isdigit` `ft_isalnum` `ft_isascii` `ft_isprint` |
| 大小変換 | `ft_toupper` `ft_tolower` |
| 文字列長・探索 | `ft_strlen` `ft_strchr` `ft_strrchr` `ft_strncmp` `ft_strnstr` `ft_memchr` `ft_memcmp` |
| メモリ操作 | `ft_memset` `ft_bzero` `ft_memcpy` `ft_memmove` (overlap 対応) |
| 安全なコピー (BSD) | `ft_strlcpy` `ft_strlcat` (意図した長さを返す) |
| 変換・確保 | `ft_atoi` `ft_calloc` (0 入力で `free()` 可能な unique ポインタ) `ft_strdup` |

### Part 2 — 追加関数 (11 関数)

| 分類 | 関数 |
|---|---|
| 文字列生成 | `ft_substr` `ft_strjoin` `ft_strtrim` `ft_split` (NULL 終端、途中 malloc 失敗時はリーク無しで NULL 返却) `ft_itoa` (INT_MIN 対応) |
| 文字列マッピング | `ft_strmapi` (値) `ft_striteri` (アドレス渡し) |
| fd 出力 | `ft_putchar_fd` `ft_putstr_fd` `ft_putendl_fd` `ft_putnbr_fd` (INT_MIN 対応) |

### Part 3 — 連結リスト (9 関数)

subject §IV.4 に指定された `t_list` 構造体を使用:

```c
typedef struct s_list
{
    void            *content;
    struct s_list   *next;
}   t_list;
```

| 関数 | 概要 |
|---|---|
| `ft_lstnew` | 新規ノード作成 |
| `ft_lstadd_front` | 先頭追加 |
| `ft_lstadd_back` | 末尾追加 |
| `ft_lstsize` | 要素数カウント |
| `ft_lstlast` | 末尾取得 |
| `ft_lstdelone` | 単ノード解放 (**next は解放しない**) |
| `ft_lstclear` | 全解放 + `*lst = NULL` 化 |
| `ft_lstiter` | 各 content に `f` を適用 |
| `ft_lstmap` | `f` で写像した新リスト生成 (途中失敗時に部分結果を `del` で解放) |

### 遵守事項 (Constraints)

- C で記述、`cc -Wall -Wextra -Werror` でコンパイル
- 42 Norm 準拠 (`norminette` 全ファイル OK)
- グローバル変数ゼロ、ヘルパーは `static`
- メモリリーク無し (macOS `leaks` / Linux `valgrind` で検証可)
- `ar rcs` でアーカイブ作成 (`libtool` 不使用)
- プロトタイプに `restrict` なし、`-std=c99` 不使用

## 開発時の補足情報

提出対象ではないが、開発中に作成した資料は以下のディレクトリに置かれている
(42 提出時は削除または `.gitignore` で除外する):

| ディレクトリ | 内容 |
|---|---|
| `subject/` | subject PDF (42 支給) |
| `docs/` | `requirements.md` (日本語要件書) / `design.md` (アーキテクチャ設計) / `implementation.md` (48 タスク実装手順書) |
| `test/` | `test_design.md` (テスト設計) / `test_implementation.md` (50 タスク実装手順書) / テスト実装 (`test_*.c`, `test_helpers.{c,h}`, `Makefile`) |

### テストの実行 (任意、提出対象外)

```sh
cd test
make run           # 全テスト実行
make leaks         # macOS のリーク検証
make valgrind      # Linux のリーク検証
```

現在の実装は **PASS=231 / FAIL=0 / リーク 0 バイト** を達成。

### 提出前のチェックリスト

- [ ] root に `Makefile`, `libft.h`, `ft_*.c` × 43, `README.md` のみが残る
- [ ] `subject/`, `docs/`, `test/` は削除するか `.gitignore` で除外
- [ ] `make re` が警告ゼロで成功、`libft.a` が root に生成される
- [ ] `norminette libft.h ft_*.c` が全ファイル OK
- [ ] 自分のテストまたは peer のテストでリークが出ない
