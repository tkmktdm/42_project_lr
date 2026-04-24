# Libft 実装要件書

`libft/subject/en.subject.pdf` (Version 19.2) に厳密に基づく実装要件。
原文と齟齬があれば subject が優先。

---

## 1. プロジェクト概要 (Chapter I)

C の **非常に有用な (highly useful)** 標準関数にアクセスできない状況は面倒である。本プロジェクトはこれらの関数を自分で実装し、使い方を学ぶことで、今後の 42 の C 課題で価値を発揮する自作ライブラリを作ることを目的とする。

---

## 2. 共通ルール (Chapter II — Common Instructions)

- プロジェクトは **C** で書くこと。
- **Norm** に準拠すること。bonus ファイル/関数も Norm チェック対象で、Norm エラーがあれば **0 点**。
- 関数は予期せず終了してはならない (segfault, bus error, double free 等)。undefined behavior の場合を除き、クラッシュしたら評価は **0 点**、課題は機能していないとみなされる。
- ヒープ割当メモリは必要時に適切に **free** すること。メモリリーク不可。
- subject が要求する場合、`-Wall -Wextra -Werror` を付けて `cc` でソースをコンパイルする **Makefile** を提出すること。**不要な再リンクをしてはならない**。
- Makefile は最低でも `$(NAME)`, `all`, `clean`, `fclean`, `re` のルールを含むこと。
- **bonus** を提出するには、Makefile に `bonus` ルールを含め、main part では許可されないヘッダ・ライブラリ・関数を追加すること。bonus は `_bonus.{c/h}` ファイルに置く (subject が別途指定する場合を除く)。mandatory と bonus の評価は **別々** に行われる。
- プロジェクトが libft の使用を許可する場合、そのソースと Makefile を `libft` フォルダにコピーし、プロジェクトの Makefile はその libft の Makefile を使ってライブラリをビルドしてから本体をコンパイルすること。
- テストプログラムの作成は推奨されるが、提出は不要で採点対象外。これらのテストは **defense (評価)** の際に特に有用で、defense 中は自分のテストでも、評価するピアのテストでも自由に使ってよい。
- 成果物は **割り当てられた Git リポジトリ** に提出。リポジトリ内の内容のみが採点対象。Deepthought 採点はピア評価の後に行われ、いずれかのセクションでエラーが発生した時点で採点は停止する。

---

## 3. AI の利用方針 (Chapter III)

(ユーザーである学生に向けた方針が subject に記載されている。要点のみ抜粋)

- 基礎学習には本気の知的努力 — チャレンジ、反復、ピアラーニング — が必要。
- **Learner rules** (subject 原文 3 項目):
  - 割り当てられた課題にはまず自分で **reasoning (推論)** を適用すること。特に AI に頼る前に。
  - AI に直接答えを求めない。
  - 42 の AI に対するグローバルアプローチを学ぶこと。
- **Phase outcomes**: 技術とコーディングの基礎を得る / AI がこのフェーズでなぜ・どのように危険かを知る。
- 試験時は AI 使用不可 — 依存しすぎればすぐ気づくことになる。

---

## 4. Mandatory Part (Chapter IV)

### 4.0 提出物サマリ

| 項目 | 内容 |
|---|---|
| Program Name | `libft.a` |
| Files to Submit | `Makefile`, `libft.h`, `ft_*.c` |
| Makefile | `NAME`, `all`, `clean`, `fclean`, `re` |
| External Function | 各関数ごとに後述 |
| Libft authorized | n/a |
| Description | カリキュラムで役立つ関数のコレクションを作る |

### 4.1 技術的考慮事項

- **グローバル変数の宣言は厳格に禁止**。
- 複雑な関数を分割するためのヘルパー関数が必要なら、**`static`** として定義しスコープを適切なファイルに限定すること。
- 全ファイルはリポジトリの **root** に置くこと。
- 未使用ファイルの提出は **不可**。
- 全 `.c` ファイルは `-Wall -Wextra -Werror` でコンパイルできること。
- ライブラリの作成には **`ar` コマンド** を使用すること。**`libtool` の使用は厳格に禁止**。
- `libft.a` はリポジトリの **root** に作成すること。

---

## 5. Part 1 — Libc 関数の再実装 (IV.2)

libc の関数セットを再実装する。プロトタイプと挙動は **man ページに厳密に従う**。唯一の違いは名前で、**`ft_`** プレフィックスを付ける (例: `strlen` → `ft_strlen`)。

### 5.1 全般注意

- 一部の関数プロトタイプは C99 の **`restrict`** 修飾子を使うが、自作プロトタイプへの `restrict` 使用は **禁止**、`-std=c99` フラグでのコンパイルも **禁止**。
- 再実装する関数は **外部関数に依存してはならない**。
- **文字分類関数** (`isalpha`, `isdigit`, `isalnum`, `isascii`, `isprint`) の戻り値は:
  - マッチすれば **1**
  - マッチしなければ **0**
- **`calloc`** は man ページと挙動が異なる場合がある。ルール: `nmemb` か `size` が **0** の場合、`free()` に渡せる unique なポインタ値を返すこと。

### 5.2 対象関数一覧 (23 関数)

`malloc` 不使用のもの:

- `isalpha`
- `isdigit`
- `isalnum`
- `isascii`
- `isprint`
- `strlen`
- `memset`
- `bzero`
- `memcpy`
- `memmove`
- `strlcpy`
- `strlcat`
- `toupper`
- `tolower`
- `strchr`
- `strrchr`
- `strncmp`
- `memchr`
- `memcmp`
- `strnstr`
- `atoi`

`malloc()` を使って実装するもの:

- `calloc`
- `strdup`

### 5.3 glibc に関する注意 (subject 原文位置: Part 1 末尾)

`strlcpy`, `strlcat`, `bzero` 等は glibc にデフォルトで含まれない。システム標準と比較テストするには `<bsd/string.h>` を include し `-lbsd` フラグでコンパイルする必要がある場合がある。これは glibc 固有の挙動で、興味があれば glibc と BSD libc の差分を調べてみるとよい。

---

## 6. Part 2 — 追加関数 (IV.3)

libc に含まれない、または別形で存在する関数群。Part 1 の関数は Part 2 の実装に役立つ場合がある。

### 6.1 `ft_substr`

| 項目 | 内容 |
|---|---|
| Prototype | `char *ft_substr(char const *s, unsigned int start, size_t len);` |
| Files to Submit | - |
| Parameters | `s`: substring を作る元の文字列 / `start`: `s` 内での substring の開始インデックス / `len`: substring の最大長 |
| Return Value | substring。allocation が失敗したら NULL |
| External Function | `malloc` |
| Description | `malloc(3)` でメモリを確保し、文字列 `s` から substring を返す。substring は index `start` から始まり、最大長 `len` を持つ |

### 6.2 `ft_strjoin`

| 項目 | 内容 |
|---|---|
| Prototype | `char *ft_strjoin(char const *s1, char const *s2);` |
| Files to Submit | - |
| Parameters | `s1`: prefix となる文字列 / `s2`: suffix となる文字列 |
| Return Value | 新しい文字列。allocation が失敗したら NULL |
| External Function | `malloc` |
| Description | `malloc(3)` でメモリを確保し、`s1` と `s2` を連結した新しい文字列を返す |

### 6.3 `ft_strtrim`

| 項目 | 内容 |
|---|---|
| Prototype | `char *ft_strtrim(char const *s1, char const *set);` |
| Files to Submit | - |
| Parameters | `s1`: トリム対象の文字列 / `set`: 除去対象の文字集合を含む文字列 |
| Return Value | トリム済みの文字列。allocation が失敗したら NULL |
| External Function | `malloc` |
| Description | `malloc(3)` でメモリを確保し、`s1` の先頭と末尾から `set` に含まれる文字を除去したコピーを返す |

### 6.4 `ft_split`

| 項目 | 内容 |
|---|---|
| Prototype | `char **ft_split(char const *s, char c);` |
| Files to Submit | - |
| Parameters | `s`: 分割対象の文字列 / `c`: 区切り文字 |
| Return Value | 分割された新しい文字列の配列。allocation が一つでも失敗したら NULL。返された領域 (呼び出し側が利用後に) は次の手順で解放する: 1) 配列内の各文字列を `free()`、2) 配列自体を `free()` |
| External Function | `malloc`, `free` |
| Description | `malloc(3)` でメモリを確保し、`s` を文字 `c` を区切りとして分割した文字列配列を返す。配列内の各文字列は独立に allocate される。ポインタ配列自体も動的に allocate される。返される配列は **NULL 終端** であること |

### 6.5 `ft_itoa`

| 項目 | 内容 |
|---|---|
| Prototype | `char *ft_itoa(int n);` |
| Files to Submit | - |
| Parameters | `n`: 変換対象の整数 |
| Return Value | 整数を表す文字列。allocation が失敗したら NULL |
| External Function | `malloc` |
| Description | `malloc(3)` でメモリを確保し、引数の整数を表す文字列を返す。**負数も扱うこと** |

### 6.6 `ft_strmapi`

| 項目 | 内容 |
|---|---|
| Prototype | `char *ft_strmapi(char const *s, char (*f)(unsigned int, char));` |
| Files to Submit | - |
| Parameters | `s`: イテレート対象の文字列 / `f`: 各文字に適用する関数 |
| Return Value | `f` を連続適用して作った文字列。allocation が失敗したら NULL |
| External Function | `malloc` |
| Description | 文字列 `s` の各文字に `f` を適用する。`f` の第一引数としてインデックス、第二引数として文字自体を渡す。`f` の適用結果を格納する新しい文字列を `malloc(3)` で作る |

### 6.7 `ft_striteri`

| 項目 | 内容 |
|---|---|
| Prototype | `void ft_striteri(char *s, void (*f)(unsigned int, char*));` |
| Files to Submit | - |
| Parameters | `s`: イテレート対象の文字列 / `f`: 各文字に適用する関数 |
| Return Value | None |
| External Function | None |
| Description | 引数の文字列の各文字に `f` を適用し、第一引数としてインデックスを渡す。各文字は **アドレスで** `f` に渡され、必要に応じて変更可能 |

### 6.8 `ft_putchar_fd`

| 項目 | 内容 |
|---|---|
| Prototype | `void ft_putchar_fd(char c, int fd);` |
| Files to Submit | - |
| Parameters | `c`: 出力する文字 / `fd`: 書き込み先のファイルディスクリプタ |
| Return Value | None |
| External Function | `write` |
| Description | 指定された file descriptor に文字 `c` を出力する |

### 6.9 `ft_putstr_fd`

| 項目 | 内容 |
|---|---|
| Prototype | `void ft_putstr_fd(char *s, int fd);` |
| Files to Submit | - |
| Parameters | `s`: 出力する文字列 / `fd`: 書き込み先のファイルディスクリプタ |
| Return Value | None |
| External Function | `write` |
| Description | 指定された file descriptor に文字列 `s` を出力する |

### 6.10 `ft_putendl_fd`

| 項目 | 内容 |
|---|---|
| Prototype | `void ft_putendl_fd(char *s, int fd);` |
| Files to Submit | - |
| Parameters | `s`: 出力する文字列 / `fd`: 書き込み先のファイルディスクリプタ |
| Return Value | None |
| External Function | `write` |
| Description | 指定された file descriptor に文字列 `s` を出力し、その後に改行を続ける |

### 6.11 `ft_putnbr_fd`

| 項目 | 内容 |
|---|---|
| Prototype | `void ft_putnbr_fd(int n, int fd);` |
| Files to Submit | - |
| Parameters | `n`: 出力する整数 / `fd`: 書き込み先のファイルディスクリプタ |
| Return Value | None |
| External Function | `write` |
| Description | 指定された file descriptor に整数 `n` を出力する |

---

## 7. Part 3 — 連結リスト (IV.4)

メモリと文字列操作関数は有用。さらにリスト操作も有用であることを学ぶ。`libft.h` に次の構造体宣言を追加する:

```c
typedef struct s_list
{
    void            *content;
    struct s_list   *next;
}   t_list;
```

メンバ:

- `content`: ノードに格納されるデータ。`void *` により任意型を格納可能。
- `next`: 次ノードのアドレス。現ノードが末尾なら `NULL`。

### 7.1 `ft_lstnew`

| 項目 | 内容 |
|---|---|
| Prototype | `t_list *ft_lstnew(void *content);` |
| Files to Submit | - |
| Parameters | `content`: 新ノードに格納するコンテンツ |
| Return Value | 新ノードへのポインタ |
| External Function | `malloc` |
| Description | `malloc(3)` でメモリを確保し、新ノードを返す。メンバ `content` は引数 `content` で初期化、`next` は `NULL` で初期化 |

### 7.2 `ft_lstadd_front`

| 項目 | 内容 |
|---|---|
| Prototype | `void ft_lstadd_front(t_list **lst, t_list *new);` |
| Files to Submit | - |
| Parameters | `lst`: リスト先頭ノードへのポインタのアドレス / `new`: 追加するノードへのポインタのアドレス |
| Return Value | None |
| External Function | None |
| Description | ノード `new` をリストの **先頭** に追加する |

### 7.3 `ft_lstsize`

| 項目 | 内容 |
|---|---|
| Prototype | `int ft_lstsize(t_list *lst);` |
| Files to Submit | - |
| Parameters | `lst`: リストの先頭 |
| Return Value | リストの長さ |
| External Function | None |
| Description | リスト内のノード数を数える |

### 7.4 `ft_lstlast`

| 項目 | 内容 |
|---|---|
| Prototype | `t_list *ft_lstlast(t_list *lst);` |
| Files to Submit | - |
| Parameters | `lst`: リストの先頭 |
| Return Value | リストの末尾ノード |
| External Function | None |
| Description | リストの末尾ノードを返す |

### 7.5 `ft_lstadd_back`

| 項目 | 内容 |
|---|---|
| Prototype | `void ft_lstadd_back(t_list **lst, t_list *new);` |
| Files to Submit | - |
| Parameters | `lst`: リスト先頭ノードへのポインタのアドレス / `new`: 追加するノードへのポインタのアドレス |
| Return Value | None |
| External Function | None |
| Description | ノード `new` をリストの **末尾** に追加する |

### 7.6 `ft_lstdelone`

| 項目 | 内容 |
|---|---|
| Prototype | `void ft_lstdelone(t_list *lst, void (*del)(void *));` |
| Files to Submit | - |
| Parameters | `lst`: 解放対象のノード / `del`: コンテンツ削除に使う関数のアドレス |
| Return Value | None |
| External Function | `free` |
| Description | 引数のノードを取り、そのコンテンツを関数 `del` を使って解放する。ノード自体も free するが、**次ノードは free しない** |

### 7.7 `ft_lstclear`

| 項目 | 内容 |
|---|---|
| Prototype | `void ft_lstclear(t_list **lst, void (*del)(void *));` |
| Files to Submit | - |
| Parameters | `lst`: ノードへのポインタのアドレス / `del`: ノードのコンテンツを削除するのに使う関数のアドレス |
| Return Value | None |
| External Function | `free` |
| Description | 指定されたノードとそれに続く全ノードを、`del` と `free(3)` を使って削除・解放する。最後にリストへのポインタを `NULL` にする |

### 7.8 `ft_lstiter`

| 項目 | 内容 |
|---|---|
| Prototype | `void ft_lstiter(t_list *lst, void (*f)(void *));` |
| Files to Submit | - |
| Parameters | `lst`: ノードへのポインタのアドレス / `f`: 各ノードのコンテンツに適用する関数のアドレス |
| Return Value | None |
| External Function | None |
| Description | リスト `lst` をイテレートし、各ノードのコンテンツに関数 `f` を適用する |

### 7.9 `ft_lstmap`

| 項目 | 内容 |
|---|---|
| Prototype | `t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));` |
| Files to Submit | - |
| Parameters | `lst`: ノードへのポインタのアドレス / `f`: 各ノードのコンテンツに適用する関数のアドレス / `del`: 必要ならノードのコンテンツを削除するのに使う関数のアドレス |
| Return Value | 新しいリスト。allocation が失敗したら NULL |
| External Function | `malloc`, `free` |
| Description | リスト `lst` をイテレートし、各ノードのコンテンツに `f` を適用し、`f` の連続適用の結果から新しいリストを作る。`del` 関数は必要ならノードのコンテンツを削除するのに使う |

---

## 8. README 要件 (Chapter V)

Git リポジトリの root に `README.md` を置く。目的は、プロジェクトを知らない人 (peer, staff, recruiter など) がプロジェクトの概要・実行方法・追加情報の参照先を素早く理解できるようにすること。

`README.md` に最低限含めること:

- **1 行目は必ず斜体** で、次の文言:
  *This project has been created as part of the 42 curriculum by <login1>[, <login2>[, <login3>[...]]].*
- **Description** セクション: プロジェクトのゴールと概要を明確に提示。
- **Instructions** セクション: コンパイル・インストール・実行に関する情報。
- **Resources** セクション: トピックに関連する参考資料 (ドキュメント、記事、チュートリアル等)、および **AI をどのタスク/どの部分にどう使ったか** の記述。
- **プロジェクトに応じて追加のセクションが必要になる場合あり** (usage examples, feature list, technical choices 等)。

subject 原文: *"Any required additions will be explicitly listed below."* (以下に明示的な追加要求を列挙する)。本プロジェクトでの追加要求は次のとおり:

- **このプロジェクトで作成したライブラリの詳細な説明も含めること**。

言語は英語が推奨。代替としてキャンパスの主要言語も可。

---

## 9. 提出とピア評価 (Chapter VI)

- 課題は通常通り **Git リポジトリ** に提出。リポジトリ内のもののみがピア評価の対象。ファイル名を再確認すること。
- **全ファイルはリポジトリの root に置くこと** — subject 原文では赤色警告枠で強調: *"Place all your files at the root of your repository."*
- 評価中、プロジェクトの **軽微な修正** を求められることがある。挙動の小変更、数行の書き換え、簡単な追加機能など。数分で実現可能な範囲 (特定の時間枠が定められている場合を除く)。
- この修正ステップは全プロジェクトで発生するとは限らないが、評価ガイドラインに記載があれば対応できるように準備しておくこと。
- 修正は任意の開発環境で実施可能で、プロジェクトの特定の部分の理解度を確認するためのもの。関数/スクリプトの小更新、表示の変更、データ構造の調整などがあり得る。
- 詳細 (スコープ、ターゲット等) は評価ガイドラインに記載され、同じプロジェクトでも評価ごとに異なる場合がある。
