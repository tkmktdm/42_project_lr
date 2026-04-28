*This project has been created as part of the 42 curriculum by htakumi.*

# libft

## Description

libft は、C標準ライブラリの関数群を自前で再実装したカスタムCライブラリです。
42のカリキュラムを通じて繰り返し使う汎用的な関数をまとめることが目的です。

ライブラリは3つのパートに分かれています：

- **Part 1** — 標準libcの再実装（`ft_strlen`、`ft_memcpy`、`ft_atoi` など）
- **Part 2** — libcにない追加のユーティリティ関数（`ft_substr`、`ft_split`、`ft_itoa` など）
- **Part 3（Bonus）** — 連結リスト操作関数（`ft_lstnew`、`ft_lstadd_back`、`ft_lstmap` など）

## Instructions

### コンパイル

```bash
# ライブラリをビルド（必須パート）
make

# bonus（連結リスト関数）を含めてビルド
make bonus

# オブジェクトファイルの削除
make clean

# オブジェクトファイルとライブラリの削除
make fclean

# 再ビルド
make re
```

### 使い方

ヘッダをインクルードし、ライブラリとリンクしてコンパイルします：

```bash
cc -Wall -Wextra -Werror main.c -L. -lft -I. -o program
```

```c
#include "libft.h"

int main(void)
{
    char *s = ft_strdup("hello");
    ft_putstr_fd(s, 1);
    free(s);
    return (0);
}
```

## Resources

- [C標準ライブラリリファレンス (cppreference)](https://en.cppreference.com/w/c)
- [man pages](https://linux.die.net/man/3/)
- [42 Norm](https://cdn.intra.42.fr/pdf/pdf/960/norme.en.pdf)

### AI の使用について

- 仕様書作成やテスト生成の補助ツールとして使用しました
