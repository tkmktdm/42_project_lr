*This project has been created as part of the 42 curriculum by htakumi.*

# get_next_line — ファイルディスクリプターから1行ずつ読む

## Description

`get_next_line` は、ファイルディスクリプターから**1行ずつ**読み取る関数を実装するプロジェクトです。
標準入力・通常ファイルのどちらに対しても、`read()` を繰り返し呼び出しながら
`\n` が見つかるまでバッファーを蓄積し、1行を返します。

このプロジェクトを通して、**static変数**を使って関数呼び出し間で状態（読み込みの続き=leftover）を
保持する方法を学びます。

### 関数仕様

| 関数 | プロトタイプ |
|------|--------------|
| `get_next_line` | `char *get_next_line(int fd);` |

- 戻り値: 読み込んだ1行（末尾に`\n`を含む。ファイル末尾で`\n`がない場合は含まない）
- 読むものがない/エラー時: `NULL`
- 使用可能な外部関数: `read`, `malloc`, `free`

---

## Instructions

### ビルド

```bash
# get_next_line.a をビルド（BUFFER_SIZEはデフォルト512）
make

# BUFFER_SIZEを指定してビルド
make re BUFFER_SIZE=42

# オブジェクトファイルを削除
make clean

# オブジェクトファイルと get_next_line.a を削除
make fclean

# 再ビルド
make re
```

### 動作確認（直接コンパイルする場合）

評価時は以下のように直接コンパイルされる想定です（`-D BUFFER_SIZE` の有無どちらでも動作します）。

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o test
```

### プロジェクトへの組み込み方

```c
#include "get_next_line.h"

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

## アルゴリズムとデータ構造の説明

### 全体の処理フロー

```
get_next_line(fd)
    │
    ├─ static変数 g_leftover に「前回読みすぎた残り」を保持
    │
    ├─ g_leftover に '\n' が含まれるまで read() を繰り返す
    │     read(fd, buf, BUFFER_SIZE)
    │     g_leftover = ft_strjoin(g_leftover, buf)   ← 結合して蓄積
    │
    ├─ g_leftover が空 / NULL → NULL を返す（読み込み終了）
    │
    ├─ extract_line(g_leftover)     → '\n' まで（含む）を切り出して返す
    ├─ update_leftover(g_leftover)  → '\n' より後ろを次回用に保存
    │
    └─ free(古い g_leftover) して new_leftover に置き換える
```

### static変数（g_leftover）

`get_next_line` は呼ばれるたびに、前回の `read()` で読みすぎた分（次の行以降のデータ）を
`g_leftover` という `static` 変数に保持し続けます。これにより、2回目以降の呼び出しでも
「どこまで読んだか」を覚えておくことができます。

### バッファサイズ（BUFFER_SIZE）

`read()` は一度に `BUFFER_SIZE` バイトずつファイルから読み込みます。
`BUFFER_SIZE` はコンパイル時に `-D BUFFER_SIZE=n` で指定でき、未指定の場合は
`get_next_line.h` 内のデフォルト値（512）が使われます。

```c
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif
```

`buf` 配列は `BUFFER_SIZE + 1` で確保し、`read()` が `BUFFER_SIZE` バイトいっぱいに読み込んだ
場合でも、末尾に `'\0'` を書き込めるようにしています（これを `BUFFER_SIZE` のままにすると
配列外書き込みになり、`BUFFER_SIZE` が大きい値のときにクラッシュします）。

### 補助関数

| 関数 | 役割 |
|------|------|
| `ft_strchr_gnl` | 文字列中に `\n` があるか探す |
| `ft_strjoin` | `leftover` と新しく読んだ `buf` を結合する |
| `ft_strcount` | `\n` まで（含む）の長さを数える |
| `extract_line` | `leftover` から `\n` まで（含む）を切り出して返す行にする |
| `update_leftover` | `\n` より後ろの部分だけを次回用の `leftover` として残す |
| `ft_strlen` | 文字列全体の長さを数える（`NULL` の場合は0を返す） |

### ハマりやすいポイント

- `ft_strjoin` の初回呼び出しは `leftover == NULL`。このとき `ft_strlen(NULL)` が `0` を返すように
  しておくことで、特別な分岐なしに `buf` の内容だけがコピーされるようにしている。
- `BUFFER_SIZE`が大きい値（複数行を一度に読み込む場合）でも、`ft_strjoin`には文字列全体の長さ
  （`ft_strlen`）を使う必要がある。`\n`までの長さしか数えない`ft_strcount`を使うと、
  2行目以降のデータが結合時に欠落してしまう。

---

## Resources

- [get_next_line subject (42)](https://cdn.intra.42.fr/pdf/pdf/.../get_next_line.en.subject.pdf)
- [read(2) — man page](https://man7.org/linux/man-pages/man2/read.2.html)
- [42 Norm](https://cdn.intra.42.fr/pdf/pdf/960/norme.en.pdf)
- [static variables in C — cppreference](https://en.cppreference.com/w/c/language/storage_duration)

### AI の使用について

- **ヘッダーファイルの整合性チェック**: `get_next_line.h` のプロトタイプ宣言と実装（`static`の有無）の
  不一致、不要な `#include` の指摘
- **コンパイルエラー・バグの原因調査**: `BUFFER_SIZE` マクロの二重定義、`buf[BUFFER_SIZE]` の
  配列外書き込み（AddressSanitizerで検証）、`ft_strjoin` のNULL処理ミスなどの原因特定
- **Norminetteエラーの修正方針の相談**: `TOO_MANY_LINES`、`GLOBAL_VAR_NAMING`、`TOO_MANY_FUNCS`
  などの指摘に対する修正案の提示（最終的な修正は自分で実施）
