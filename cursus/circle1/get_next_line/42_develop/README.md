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
    ├─ static変数 leftover に「前回読みすぎた残り」を保持
    │
    ├─ fill_leftover(fd, leftover)
    │     leftover に '\n' が見つかるまで read(fd, buf, BUFFER_SIZE) を繰り返す
    │     読んだ分は append_buf() で leftover に追記していく
    │
    ├─ leftover が空 / NULL → NULL を返す（読み込み終了）
    │
    ├─ extract_line(leftover)     → 先頭から '\n' まで（含む）を切り出して返す行にする
    ├─ update_leftover(leftover)  → '\n' より後ろを次回用の leftover として保存し直す
    │
    └─ 古い leftover を free して、新しい leftover に置き換える
```

### static変数（leftover）

`get_next_line` は呼ばれるたびに、前回の `read()` で読みすぎた分（次の行以降のデータ）を
`leftover` という `static` 変数に保持し続けます。これにより、2回目以降の呼び出しでも
「どこまで読んだか」を覚えておくことができます。

### バッファーサイズ（BUFFER_SIZE）

`read()` は一度に `BUFFER_SIZE` バイトずつファイルから読み込みます。
`BUFFER_SIZE` はコンパイル時に `-D BUFFER_SIZE=n` で指定でき、未指定の場合は
`get_next_line.h` 内のデフォルト値（512）が使われます。

```c
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif
```

`read()` 用の一時バッファーは `BUFFER_SIZE + 1` バイトで確保し、`read()` が `BUFFER_SIZE`
バイトいっぱいに読み込んだ場合でも、末尾に `'\0'` を書き込めるようにしています。

### leftoverの容量管理（`t_leftover` / `append_buf` / `grow_buf`）

`read()` のたびに単純に「今の内容＋新しい内容」ぴったりのサイズで `malloc` し直すと、
1行が長くバッファーサイズが小さい場合（例: 20,000バイトの1行を `BUFFER_SIZE=10` で読む場合）
`malloc` が数千回発生し、非効率になります。

そこで、`leftover` の「実際の文字数（`len`）」と「確保している箱の大きさ（`capacity`）」を
`t_leftover` 構造体で分けて管理し、箱に余裕がある間は追記だけで済ませる設計にしています。

```c
typedef struct s_leftover
{
	size_t	len;       // 今 leftover に入っている実際の文字数
	size_t	capacity;  // leftover として確保済みの箱の大きさ
}	t_leftover;
```

- `append_buf`: `len + 新しく読んだバイト数` が `capacity` に収まるなら、既存の箱にそのまま
  追記するだけ（`malloc`なし）。収まらないなら `grow_buf` に処理を委譲する。
- `grow_buf`: 必要な量の2倍の大きさで新しい箱を `malloc` し、古い内容と新しい内容を
  両方コピーしてから古い箱を `free` する。

この「容量に余裕を持たせて倍々に増やす」方式（動的配列の一般的な実装手法）により、
`read()` の回数自体は変わりませんが、`malloc` の回数を `read()` の回数（線形）から
おおよそ `log₂(read()の回数)` に減らすことができます。

### 補助関数

| 関数                | 役割                                                                   |
| ------------------- | ---------------------------------------------------------------------- |
| `ft_strchr_gnl`   | 文字列中に `\n` があるか探す                                         |
| `append_buf`      | `leftover` に新しく読んだ `buf` を追記する（容量が足りるかで分岐） |
| `grow_buf`        | `leftover` の箱が足りないとき、大きい箱を新しく確保して中身を移す    |
| `ft_strcount`     | `\n` まで（含む）の長さを数える                                      |
| `extract_line`    | `leftover` から `\n` まで（含む）を切り出して返す行にする          |
| `update_leftover` | `\n` より後ろの部分だけを次回用の `leftover` として残す            |
| `ft_strlen`       | 文字列全体の長さを数える（`NULL` の場合は0を返す）                   |

### ハマりやすいポイント

- `capacity`（箱の大きさ）と `len`（実際の文字数）は必ずセットで正しく管理する必要がある。
  `malloc` 失敗などで `leftover` が `NULL` に戻ったのに `capacity` だけ古い値のまま残っていると、
  次回「まだ余裕がある」と誤判定して `NULL` に書き込み、クラッシュする。
- `capacity` の初期値は、実際に確保されている箱の大きさ（`leftover`が `NULL`なら実質0、
  それ以外なら `len + 1`）を正直に反映させる必要がある。適当な固定値（`BUFFER_SIZE + 1`など）を
  入れると、まだ存在しない箱があるかのように誤認してクラッシュする。
- 新しい容量を「単純に2倍」するだけでは、一度に読む量が容量より大きい場合に不足することがある。
  `(必要な量) * 2` のように、必要量を基準にして確保する必要がある。

---

## Resources

- [get_next_line subject (42)](https://cdn.intra.42.fr/pdf/pdf/.../get_next_line.en.subject.pdf)
- [read(2) — man page](https://man7.org/linux/man-pages/man2/read.2.html)
- [42 Norm](https://cdn.intra.42.fr/pdf/pdf/960/norme.en.pdf)
- [static variables in C — cppreference](https://en.cppreference.com/w/c/language/storage_duration)
- [Dynamic array (growth strategy / amortized doubling) — Wikipedia](https://en.wikipedia.org/wiki/Dynamic_array)
- [francinette (42 peer-testing tool)](https://github.com/xicodomingues/francinette)

### AI の使用について

このプロジェクトでは、コードそのものは自分で書き、AI（Claude Code）は主に以下の用途で
壁打ち相手・デバッグ補助として使用しました。

- **概念の説明**: `read()` の挙動、`static` 変数がなぜ必要か、`BUFFER_SIZE` の役割、
  なぜファイル全体を一度に読んではいけないか、といった課題の前提となる考え方の説明
- **バグの原因調査**: `francinette`（ピア評価用の非公式テストツール）で発生した
  segmentation fault / タイムアウトについて、実際にコンパイル・実行・スタックトレースを取得して原因特定
- **設計方針の相談**: `malloc`回数を減らすための「容量を持たせて倍々に増やす」設計手法（動的配列の一般的な実装パターン）についての説明
