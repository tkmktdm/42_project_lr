*This project has been created as part of the 42 curriculum by htakumi.*

# get_next_line — ファイルディスクリプターから1行ずつ読む

## Description

`get_next_line` は、ファイルディスクリプターから**1行ずつ**読み取る関数を実装するプロジェクトです。
標準入力・通常ファイルのどちらに対しても、`read()` を必要な分だけ繰り返し呼び出しながら
`\n` が見つかるまで内容を蓄積し、1行ずつ返します。ファイル全体を一度に読み込むことはしません。

このプロジェクトを通して、**static変数**を使って関数呼び出しの間で状態（読み込みの続き = leftover）を
保持する方法と、**mallocの回数を抑えるためのバッファーの容量管理**を学びます。

### 関数仕様

| 関数              | プロトタイプ                     |
| ----------------- | -------------------------------- |
| `get_next_line` | `char *get_next_line(int fd);` |

- 戻り値: 読み込んだ1行（末尾に `\n`を含む。ファイル末尾で `\n`がない場合は含まない）
- 読むものがない/エラー時: `NULL`
- 使用可能な外部関数: `read`, `malloc`, `free`
- 禁止: `lseek`、グローバル変数、`libft`
- 実装しているのは**必須パートのみ**（複数fdの同時管理などのボーナスは未実装）

---

## Instructions

### ビルド

このプロジェクトに Makefile はありません。課題の指示どおり、`get_next_line.c` /
`get_next_line_utils.c` を利用側のファイルと一緒に直接 `cc` でコンパイルします。
`-D BUFFER_SIZE` の有無どちらでも動作する必要があるため、両方のパターンで
コンパイルできることを確認してください。

```bash
# -D BUFFER_SIZE なし（get_next_line.h内のデフォルト値 512 を使用）
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c -o test

# -D BUFFER_SIZE あり（例: 42）
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o test
```

### プロジェクトへの組み込み方

```c
#include "get_next_line.h"
#include <stdio.h>
#include <sys/fcntl.h> // open

int main(void)
{
    int   fd;
    char *line;

    fd = open("file.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

---

## アルゴリズムの説明と根拠

### 採用したアルゴリズム

`get_next_line` は呼ばれるたびに次の手順で1行を作って返す。

1. 「前回の続き（`leftover`, `static`変数）」に既に `\n` が含まれているか確認する。
2. 含まれていなければ、`\n` が見つかるか `read()` が `0`（EOF）を返すまで `read(fd, buf, BUFFER_SIZE)`
   を繰り返し呼び出し、読んだ内容を `leftover` に追記していく（`fill_leftover`）。
3. `leftover` の先頭から `\n` まで（含む）を1行として切り出し、呼び出し元に返す用の行にする（`extract_line`）。
4. `\n` より後ろの残りを次回用に `leftover` として保存し直す（`update_leftover`）。
5. `leftover` が空（`NULL`）になった時点でこれ以上読むものが無いと判断し、次回の呼び出しで `NULL` を返す。

`leftover` は関数呼び出しをまたいで保持する必要があるため `static` ローカル変数にしている
（グローバル変数は課題で禁止されているため、状態を持ち越す手段としてはこれ以外に選択肢が無い）。

### なぜこのアルゴリズムを選んだか（検討した代替案との比較）

| 案                                                                 | 問題点                                                                                                                                                                       |
| -------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| ファイル全体を一度に `read()` してから `\n` で分割する              | 課題PDFで明示的に禁止されている方針。ファイルが大きい場合にメモリを無駄に消費し、1回目の呼び出しだけが極端に遅くなる                                                       |
| `leftover` を使い捨てにする（前回の続きを保持しない）                | 1行が `BUFFER_SIZE` より長い場合、前回 `read()` で読みすぎた分をどこにも保持できず、行の一部を失う                                                                        |
| `leftover` を「今の内容＋新しい内容」ぴったりのサイズで毎回 `malloc` し直す | `realloc` が使用禁止関数のため、この方式では `read()` のたびに毎回コピー＋`malloc`が発生する。1行が長くバッファーが小さい場合（例: 20,000バイトの1行を `BUFFER_SIZE=10` で読む）に `malloc` が数千回発生し非効率 |
| **採用: `len`（実際の文字数）と `capacity`（確保済みの箱の大きさ）を分離し、足りない時だけ「必要量 × 2」で確保し直す（`grow_buf`）** | 動的配列で一般的な amortized doubling。`read()` の回数（＝ファイルサイズに比例）は変えられないが、`malloc` の回数を `read()` 回数の対数オーダーまで削減できる           |

### 計算量

- `read()` の呼び出し回数: ファイルサイズ ÷ `BUFFER_SIZE` にほぼ比例（アルゴリズム上これ以上は減らせない）
- `malloc` の呼び出し回数: 上記の「2倍確保」戦略により、`read()` 回数に対しておおよそ `log₂` オーダーに抑えられる
  （「容量が倍々に増えていく様子」の図解は後述の `append_buf` / `grow_buf` の解説を参照）
- `get_next_line()` 1回あたりの走査コスト: `leftover` の中を探す処理（`ft_strchr_gnl` / `extract_line` /
  `update_leftover`）はいずれもその時点の `leftover` の長さに比例する O(n)

---

## 技術選定

| 項目                   | 選択                                                                                | 理由                                                                                                                                       |
| ---------------------- | ------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------- |
| 使用できる関数         | `read`, `malloc`, `free` のみ                                                    | 課題PDFで許可されているのがこの3つだけ。`strchr` を含め他の標準ライブラリ関数は使えないため、必要な分は自前で再実装している（`ft_strchr_gnl` など） |
| ビルド方式             | Makefile無し、`get_next_line.c` / `get_next_line_utils.c` を `cc` で直接コンパイル | 課題PDFの指示どおり。単体ファイルの小さいプロジェクトなのでMakefileは要求されていない                                                        |
| 状態保持の方法         | `get_next_line` 内の `static char *leftover`（ローカルstatic変数1つ）              | グローバル変数が禁止されているため、呼び出しをまたいで状態を持ち越すには `static` ローカル変数以外に選択肢が無い                            |
| Norm対応のファイル分割 | ヘルパー関数を `get_next_line.c`（1個）と `get_next_line_utils.c`（5個）に分割     | 42 Normの「1ファイル5関数まで」制限のため（詳細は後述の「ファイル構成について」を参照）                                                      |

### マクロについて（`get_next_line.h`）

```c
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif

# ifndef GNL_NL
#  define GNL_NL '\n'
# endif
```

- どちらも `#ifndef` で囲んでいるのは、コンパイル時の `-D` オプションで外から値を上書きできる
  ようにするため。`#ifndef` が無いと、`-D BUFFER_SIZE=42` を付けてコンパイルしたときに
  「マクロの再定義」でエラーになるか、ヘッダ側の値で上書きされて指定した値が反映されなくなる。
- `BUFFER_SIZE` は課題要件で「`-D` の有無どちらでもコンパイルできること」が明示されているため
  必須。デフォルト値の `512` に特別な意味は無く、任意の値でよい（課題の指示どおり）。
- `GNL_NL` は課題側の要求ではなく、`'\n'` という文字リテラルをコード中に何度も直書きする代わりに
  名前を付けて1箇所にまとめた自主的な工夫。`extract_line` / `update_leftover` / `fill_leftover`
  内で使っている「改行文字」がこの1行を見ればすぐ分かる。
- ヘッダ先頭の二重インクルードガード `#ifndef GET_NEXT_LINE_H` / `#define GET_NEXT_LINE_H` も
  同じ仕組み（値を持たないマクロ）。こちらは同じヘッダファイルが複数回 `#include` されても、
  構造体やプロトタイプの再定義エラーにならないようにするためのもの。
- このプロジェクトに「引数を取るマクロ（function-like macro、例: `#define MAX(a,b) ...`）」は
  無い。すべて値（または何も持たない）だけの単純なマクロ（object-like macro）。

---

## ファイル構成と関数一覧

| ファイル                  | 関数                | 役割                                                      |
| ------------------------- | ------------------- | --------------------------------------------------------- |
| `get_next_line.c`       | `ft_strchr_gnl`   | 文字列中に `\n`（または任意の文字）があるか探す         |
| `get_next_line.c`       | `get_next_line`   | **本体**。1回の呼び出しで1行返す                    |
| `get_next_line_utils.c` | `fill_leftover`   | `\n`が見つかるまで `read()`を繰り返し蓄積する         |
| `get_next_line_utils.c` | `append_buf`      | 読んだ分を `leftover`に追記する（容量が足りるかで分岐） |
| `get_next_line_utils.c` | `grow_buf`        | 箱が足りないとき、新しい箱を確保して中身を移す            |
| `get_next_line_utils.c` | `extract_line`    | `leftover`から1行分を切り出す                           |
| `get_next_line_utils.c` | `update_leftover` | 次回用の残りを保存し直す                                  |

呼び出し関係:

```
get_next_line()                          ← get_next_line.c
    │
    ├─ fill_leftover()                   ← get_next_line_utils.c
    │     ├─ ft_strchr_gnl()  (継続条件)  ← get_next_line.c（ファイルをまたいで呼ばれる）
    │     └─ append_buf()                ← get_next_line_utils.c
    │           └─ grow_buf()            ← get_next_line_utils.c
    │
    ├─ extract_line()                    ← get_next_line_utils.c
    │
    └─ update_leftover()                 ← get_next_line_utils.c
          └─ ft_strchr_gnl()             ← get_next_line.c
```

### なぜ `ft_strchr_gnl` だけ `get_next_line.c` にあるか

課題PDFは「ヘルパー関数は全部 `get_next_line_utils.c` に書くこと」と指示していますが、
42 Normには **1ファイルにつき関数は最大5個まで** という制限があります。ヘルパーだけで
6個（`ft_strchr_gnl`, `fill_leftover`, `append_buf`, `grow_buf`, `extract_line`,
`update_leftover`）あるため、全部を1ファイルに詰めるとNorm違反になります。

`ft_strchr_gnl` を `fill_leftover` のループ継続条件に直接埋め込んで関数自体を無くす案も
検討しましたが、それをやると①容量倍々管理のロジックが壊れる、②1関数25行のNorm制限を
超える、のどちらかになってしまいます。そのため `ft_strchr_gnl` だけを `get_next_line.c`
側に残し、`get_next_line_utils.c` を残り5関数ちょうど（Norm上限）に収めています。

---

## 関数ごとの詳細解説

### `get_next_line` — 本体（`get_next_line.c`）

```c
char *get_next_line(int fd)
{
    static char *leftover = NULL;
    char        *line;
    char        *new_g_leftover;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);                          // ① 不正な引数
    leftover = fill_leftover(fd, leftover);      // ② \n が来るまで／EOFまで読み込む
    if (leftover == NULL || leftover[0] == '\0')
    {
        free(leftover);
        leftover = NULL;
        return (NULL);                          // ③ 読むものがもう無い／エラー
    }
    line = extract_line(leftover);               // ④ 1行分を切り出す
    if (!line)
    {
        free(leftover);
        leftover = NULL;
        return (NULL);                          // ⑤ malloc失敗
    }
    new_g_leftover = update_leftover(leftover);  // ⑥ 次回用の残りを作り直す
    free(leftover);                              // ⑦ 古いバッファは不要になったのでfree
    leftover = new_g_leftover;                   // ⑧ 次回用に差し替え
    return (line);                               // ⑨ 呼び出し元に1行を返す
}
```

**メモリの所有権の移動**

| 時点     | 古い `leftover`                  | `line`                             | `new_g_leftover`           |
| -------- | ---------------------------------- | ------------------------------------ | ---------------------------- |
| ④の直後 | まだ生きている                     | 新しくmalloc（呼び出し元に渡す予定） | まだ無い                     |
| ⑥の直後 | まだ生きている                     | 呼び出し元行き                       | 新しくmalloc                 |
| ⑦の直後 | **free済み（ここで消える）** | 呼び出し元行き                       | 生きている                   |
| ⑧の直後 | （もう存在しない）                 | 呼び出し元行き                       | `leftover`の名前を引き継ぐ |

`line` だけが呼び出し元に渡り、`free` するのは**呼び出し元の責任**（呼び出し側で `free(line)`）。
それ以外の `leftover` 関連のバッファはすべて関数内部で管理し、必ずどこかで `free` される。

### `fill_leftover` — 読み込みループ（`get_next_line_utils.c`）

```c
char *fill_leftover(int fd, char *leftover)
{
    char        *buf;
    int         byte_num;
    t_leftover  info;

    info.len = 0;
    while (leftover && leftover[info.len] != '\0')
        info.len++;                              // (a) leftoverの現在の長さを数える
    info.capacity = info.len + 1;                 // (b) 箱の大きさ = 長さ+1（NUL分）
    buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    byte_num = 0;
    while (buf && (leftover == NULL || ft_strchr_gnl(leftover, '\n') == NULL))
    {                                              // (c) leftoverに\nが無い間ループ
        byte_num = read(fd, buf, BUFFER_SIZE);     // (d) 最大BUFFER_SIZEバイト読む
        if (byte_num <= 0)
            break ;                                // (e) EOF or エラー → 抜ける
        buf[byte_num] = '\0';
        leftover = append_buf(leftover, buf, byte_num, &info); // (f) leftoverに追記
    }
    free(buf);
    if (!buf || byte_num < 0)
    {
        free(leftover);
        return (NULL);                             // (g) mallocエラー or readエラー
    }
    return (leftover);
}
```

- **(a)(b)** `info`（`len`＝実際の文字数、`capacity`＝箱の大きさ）はこの関数が呼ばれる
  たびに新しく作り直す。`leftover` は前回 `update_leftover` で `len+1` バイトぴったりに
  mallocされているので、`capacity = len + 1` は「今実際に確保されている箱の大きさ」を正確に表す。
  `leftover` が `NULL`（初回呼び出し時）の場合は `info.len = 0` のままループが回らず、
  `capacity = 1` になる。これにより最初の `append_buf` は必ず「箱が足りない」と判定して
  `grow_buf` が呼ばれる（実質的な最初のmalloc）。
- **(c)** `leftover` にすでに `\n` が含まれていれば（前回の `read()` で複数行分読み込んでいた
  場合など）、`read()` を一切呼ばずに即座にループを抜けて `leftover` をそのまま返す。
- **(d)(e)** `read()` の戻り値は `> 0`＝読めたバイト数、`0`＝EOF、`< 0`＝エラー。
  `<= 0` ならとりあえずループを抜け、エラーかどうかは `(g)` で `byte_num < 0` を見て判別する。
- **(f)** 読んだ `buf` を `leftover` に追記する処理は `append_buf` / `grow_buf` に委譲する。
- **(g)** `buf` のmalloc失敗、または `read()` エラーのときだけ `leftover` を解放して `NULL` を
  返す。それ以外（EOFで正常終了、または `\n` が見つかって正常終了）は `leftover` をそのまま返す。

### `append_buf` / `grow_buf` — mallocを減らす仕組み（`get_next_line_utils.c`）

課題PDFの許可関数は `read`, `malloc`, `free` のみで **`realloc` は使えない**。1行が長くて
`read()` を何度も呼ぶ必要がある場合、毎回ぴったりのサイズで `malloc` し直すと `malloc` の回数が
`read()` の回数と同じだけ発生してしまい非効率。そこで「今の文字数(`len`)」と「確保済みの箱の
大きさ(`capacity`)」を分けて管理し、箱に余裕がある間は `malloc` せずに追記だけで済ませる。

```c
static char *append_buf(char *left, char *buf, int bytes, t_leftover *info)
{
    size_t i;
    size_t check_len;

    check_len = info->len + (size_t)bytes;    // 追記後に必要になる文字数
    if (check_len >= info->capacity)          // 箱に入りきらない（\0の1バイトも考慮してこのタイミングで成長）
        left = grow_buf(left, buf, (size_t)bytes, info);
    else                                       // 箱に余裕がある
    {
        i = -1;                                // (size_t)-1 は非常に大きい値
        while (++i != (size_t)bytes)           // 直後の ++i で 0 に戻る → 0 から bytes-1 まで回る
            left[info->len + i] = buf[i];      // 既存の末尾に直接書き込む（mallocなし）
        left[info->len + i] = '\0';
        info->len += i;
    }
    return (left);
}
```

```c
static char *grow_buf(char *left, char *buf, int bytes, t_leftover *info)
{
    size_t i;
    size_t new_capacity;
    char   *new_left;

    new_capacity = (info->len + (size_t)bytes) * 2;  // 必要量(len+bytes)の2倍を確保
    new_left = malloc(new_capacity);
    if (!new_left)
    {
        free(left);
        info->len = 0;      // 箱ごと消えたので len/capacity を両方リセット
        info->capacity = 0; // ここを古い値のままにすると次回「まだ余裕がある」と誤判定してNULLに書き込みクラッシュする
        return (NULL);
    }
    i = -1;
    while (++i != info->len)          // 古い内容(len文字分)をコピー
        new_left[i] = left[i];
    free(left);                       // 古い箱は不要になったので解放
    i = -1;
    while (++i != (size_t)bytes)      // 新しく読んだ分(bytes文字分)もコピー
        new_left[info->len + i] = buf[i];
    new_left[info->len + i] = '\0';
    info->len += (size_t)bytes;
    info->capacity = new_capacity;
    return (new_left);
}
```

「必要な量ぴったり」ではなく「必要な量の2倍」を確保するのがポイント。これにより
`read()` の回数自体は変わらないが、`malloc`（＝`grow_buf` の呼び出し）の回数を
`read()` の回数（線形）からおおよそ `log₂(read()の回数)` まで減らせる（動的配列の一般的な
実装パターン）。

**図解：容量が倍々に増えていく様子（`BUFFER_SIZE=4` で20文字の行を読む場合のイメージ）**

```
1回目 read: "abcd"                    len=0→4   capacity=1→(0+4)*2=8
   [a b c d _ _ _ _]  capacity=8, len=4

2回目 read: "efgh"  → len+bytes=8 >= capacity(8) → grow_buf
   新capacity = (4+4)*2 = 16
   [a b c d e f g h _ _ _ _ _ _ _ _]  capacity=16, len=8

3回目 read: "ijkl"  → len+bytes=12 < capacity(16) → append_bufでそのまま追記（mallocなし）
   [a b c d e f g h i j k l _ _ _ _]  capacity=16, len=12

4回目 read: "mnop"  → len+bytes=16 >= capacity(16) → grow_buf
   新capacity = (12+4)*2 = 32
   [a b c d e f g h i j k l m n o p ...]  capacity=32, len=16

5回目 read: "qrst\n" → "\n"を含むのでこの回でループ終了（appendはする）
```

`read()` は5回呼ばれているが、実際に `malloc`（`grow_buf`）が発生したのは3回だけ
（1, 2, 4回目）。行がもっと長くなればなるほど、この差はさらに開く。

### `extract_line` — 1行を切り出す（`get_next_line_utils.c`）

```c
char *extract_line(char *leftover)
{
    char *line;
    int  i;
    int  len;

    len = 0;
    while (leftover[len] != '\0' && leftover[len] != GNL_NL)
        len++;                              // \n か \0 の手前まで数える
    if (leftover[len] == GNL_NL)
        len++;                              // \n も含めた長さにする
    line = malloc(sizeof(char) * (len + 1));
    if (!line)
        return (NULL);
    i = 0;
    while (leftover[i] != GNL_NL && leftover[i] != '\0')
    {
        line[i] = leftover[i];
        i++;
    }
    line[i] = leftover[i];                  // '\n' か '\0' 自体もコピー
    if (leftover[i] == GNL_NL)
        line[i + 1] = '\0';                 // \nの後ろにも終端を打つ
    return (line);
}
```

例1（`\n`あり）:

```
leftover = "BBB\nCC"
len を数える → len=4（"BBB\n"の4文字）
malloc(5) してコピー
  line[0]='B' line[1]='B' line[2]='B' line[3]='\n' line[4]='\0'
→ line = "BBB\n"
```

例2（ファイル末尾で `\n` なし）:

```
leftover = "XYZ"（これ以上readしてもEOF）
len = 3（\nにも\0にも達しないので3文字全部数える。leftover[3]=='\0'なのでlen++はしない）
malloc(4) してコピー
  line[0]='X' line[1]='Y' line[2]='Z' line[3]='\0'（\0自体もコピー）
→ line = "XYZ"（\nなし）← 課題の仕様どおり
```

### `update_leftover` — 次回用の残りを作る（`get_next_line_utils.c`）

```c
char *update_leftover(char *leftover)
{
    char *p;
    char *right;
    int  len;
    int  i;

    p = ft_strchr_gnl(leftover, GNL_NL);    // \n の位置を探す
    if (p == NULL)
        return (NULL);                       // \n が無い＝もう続きは無い
    p++;                                      // \n の次の文字から
    len = 0;
    while (p[len] != '\0')
        len++;
    if (len == 0)
        return (NULL);                       // \n の後ろに何も残っていない
    right = malloc(sizeof(char) * (len + 1));
    if (!right)
        return (NULL);
    i = 0;
    while (p[i] != '\0')
    {
        right[i] = p[i];
        i++;
    }
    right[i] = '\0';
    return (right);
}
```

```
leftover = "BBB\nCC"
p = "BBB\nCC" の中の '\n' の位置 → p は "\nCC" を指す
p++                              → p は "CC" を指す
len = 2
right = malloc(3) → "CC" をコピー → right = "CC"
```

`leftover` 全体が1行だけ（`\n` の後ろに何も無い、または `\n` 自体が無い）なら `NULL` を返し、
`get_next_line` 側でその `NULL` が次回の `leftover`（＝「もう読むものが無い」の目印）になる。

### `ft_strchr_gnl`（`get_next_line.c`）

```c
char *ft_strchr_gnl(char *s, int c)
{
    while (*s != '\0')
    {
        if ((unsigned char)*s == (unsigned char)c)
            return ((char *)s);
        s++;
    }
    if ((unsigned char)*s == (unsigned char)c)
        return ((char *)s);
    return (NULL);
}
```

標準の `strchr` の再実装。`\0` に達した後もう一度だけ比較しているのは、`c == '\0'` で
呼び出された場合に文字列の終端そのものを見つけられるようにするため（標準 `strchr` と同じ挙動）。

---

## エッジケースまとめ

| ケース                                                  | 挙動                                                                                                                                                                                                                             |
| ------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 空ファイル                                              | 1回目の呼び出しで即 `NULL`                                                                                                                                                                                                     |
| `\n` だけのファイル                                   | 各行が `"\n"` として返る（空行として扱われる）                                                                                                                                                                                 |
| 末尾に `\n` が無いファイル                            | 最後の行だけ `\n` 無しで返り、次回 `NULL`                                                                                                                                                                                    |
| `BUFFER_SIZE` が 1                                    | 1バイトずつしか読まないが、`grow_buf` の倍々戦略で最終的な `malloc` 回数は抑えられる                                                                                                                                         |
| `BUFFER_SIZE` が巨大（例: 10000000）                  | 1回の `read()` で複数行が一気に `leftover` に入ることがある → 2回目以降は `read()` を呼ばずに `leftover` 内の `\n` だけで返し続ける                                                                                   |
| 標準入力（`fd=0`）                                    | 通常ファイルと同じ `read()` ベースの処理でそのまま動く（`lseek` 未使用なので問題ない）                                                                                                                                       |
| 不正な `fd`（負の値・クローズ済みなど）               | 負の値は即 `NULL`。クローズ済みなど `read()` がエラー（`-1`）を返す場合も `NULL` を返しリークしない                                                                                                                      |
| `malloc` 失敗                                         | `leftover` を解放して `static leftover` を `NULL` に戻し `NULL` を返す（次回呼び出しは最初からやり直せる）                                                                                                               |
| 複数のファイルを順番に読む（1つ目を読み切ってから切替） | 前のファイルが終端で `leftover` が `NULL` に戻っているので、新しい `fd` でも正しく最初から読める                                                                                                                           |
| 複数の `fd` を交互に読む（読み切る前に切替）          | **非対応。** `leftover` は `static` 変数1個のみで `fd` ごとに区別していないため、別の `fd` に切り替えると前の続きが混ざって壊れる。これはボーナス要件（`fd` ごとに状態を分けて管理）で、このリポジトリでは未実装 |
| バイナリファイル                                        | 課題仕様上は未定義動作。`\0` を含む場合、文字列関数ベースのこの実装は `\0` を「文字列の終わり」として扱ってしまい、それ以降のデータを正しく扱えない                                                                          |

---

## Resources

- [read(2) — man page](https://man7.org/linux/man-pages/man2/read.2.html)
- [42 Norm](https://cdn.intra.42.fr/pdf/pdf/960/norme.en.pdf)
- [static variables in C — cppreference](https://en.cppreference.com/w/c/language/storage_duration)
- [Dynamic array (growth strategy / amortized doubling) — Wikipedia](https://en.wikipedia.org/wiki/Dynamic_array)
- [francinette (42 peer-testing tool)](https://github.com/xicodomingues/francinette)

### AI の使用について

主に、壁打ち相手・デバッグ補助、ドキュメント整備として使用しました。

- **概念の説明**: `read()` の挙動、`static` 変数がなぜ必要か、`BUFFER_SIZE` の役割、
  なぜファイル全体を一度に読んではいけないか、といった課題の前提となる考え方の説明
- **バグの原因調査**: `francinette`（ピア評価用の非公式テストツール）で発生した
  segmentation fault / タイムアウトについて、実際にコンパイル・実行・スタックトレースを取得して原因特定
- **設計方針の相談**: `malloc`回数を減らすための「容量を持たせて倍々に増やす」設計手法（動的配列の一般的な実装パターン）についての説明
- **README整備**
