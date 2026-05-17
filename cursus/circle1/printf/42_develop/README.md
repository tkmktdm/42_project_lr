*This project has been created as part of the 42 curriculum by htakumi.*

# ft_printf — printf 再実装

## Description

`ft_printf` は、C標準ライブラリの `printf()` を自前で再実装したライブラリです。
可変長引数（variadic functions）の仕組みを学ぶことを目的としており、
`libftprintf.a` として提供されます。

### 対応フォーマット指定子

| 指定子 | 説明                                                                  |
| ------ | --------------------------------------------------------------------- |
| `%c` | 1文字を出力                                                           |
| `%s` | 文字列を出力（NULL の場合は `(null)`）                              |
| `%p` | ポインタアドレスを `0x` 付き16進数で出力（NULL の場合は `(nil)`） |
| `%d` | 10進数の符号付き整数を出力                                            |
| `%i` | 10進数の符号付き整数を出力                                            |
| `%u` | 10進数の符号なし整数を出力                                            |
| `%x` | 16進数（小文字）で出力                                                |
| `%X` | 16進数（大文字）で出力                                                |
| `%%` | `%` 文字を出力                                                      |

---

## Instructions

### ビルド

```bash
# libftprintf.a をビルド
make

# オブジェクトファイルを削除
make clean

# オブジェクトファイルと libftprintf.a を削除
make fclean

# 再ビルド（fclean + all）
make re
```

### プロジェクトへの組み込み方

```bash
# libftprintf.a にリンクしてコンパイル
cc -Wall -Wextra -Werror main.c -L. -lftprintf -I includes -o program
```

```c
#include "ft_printf.h"

int main(void)
{
    int len;

    len = ft_printf("Hello, %s! Number: %d, Hex: %x\n", "world", 42, 255);
    ft_printf("printed %d chars\n", len);
    return (0);
}
```

---

## アルゴリズムとデータ構造の説明

### 全体の処理フロー

```
ft_printf(format, ...)
    │
    ├─ 通常文字 → write(1, &c, 1)
    │
    └─ '%' 検出 → ft_handle_conversion(次の文字, &ap)
                      │
                      ├─ 'c' → ft_print_char
                      ├─ 's' → ft_print_str
                      ├─ 'p' → ft_print_ptr
                      ├─ 'd','i' → ft_print_int
                      ├─ 'u' → ft_print_uint
                      ├─ 'x' → ft_print_hex(upper=0)
                      ├─ 'X' → ft_print_hex(upper=1)
                      └─ '%' → ft_print_percent
```

### 可変長引数（va_list）

`printf` は引数の数が実行時まで決まらないため、`<stdarg.h>` の仕組みを使います。

```c
va_list ap;
va_start(ap, format);   // format の次の引数からセット
va_arg(ap, int);        // 引数を1つ取り出す（型を指定）
va_end(ap);             // 解放
```

`va_arg` は呼ぶたびに「次の引数」を取り出します。型は呼び出し側が保証する必要があります。

### 基数変換（ft_putnbr_base）

`%x`, `%X`, `%u` の出力に使う汎用的な基数変換関数です。

```c
void ft_putnbr_base(unsigned int n, char *base)
{
    // base = "0123456789abcdef" なら16進、"0123456789" なら10進
    if (n >= ft_strlen(base))
        ft_putnbr_base(n / ft_strlen(base), base);
    write(1, &base[n % ft_strlen(base)], 1);
}
```

再帰で上の桁から順に出力します。`unsigned int` を使うことで `%u` の最大値（4294967295）も正しく扱えます。

### ポインタ出力（%p）

ポインタは 64bit システムでは 8 バイトなので `unsigned long` で受け取ります。

```c
unsigned long addr = (unsigned long)va_arg(ap, void *);
```

- `addr == 0` のとき → `(nil)` を出力（Linux の printf に合わせる）
- それ以外 → `"0x"` + 16進アドレスを出力

`unsigned long` 用の再帰出力ヘルパー `ft_putptr_hex` を `static` 関数として `ft_print_ptr.c` 内に定義しています。

### 戻り値（出力した文字数）

各変換関数は出力した文字数を `int` で返します。`ft_printf` はそれを `count` に加算して最終的な出力文字数を返します。

---

## Resources

- [printf(3) — Linux man page](https://linux.die.net/man/3/printf)
- [va_list / stdarg.h — cppreference](https://en.cppreference.com/w/c/variadic)
- [42 Norm](https://cdn.intra.42.fr/pdf/pdf/960/norme.en.pdf)
- [printfTester](https://github.com/Tripouille/printfTester)

### AI の使用について

- **バグ診断**: 型ミス・未定義動作・未使用変数などのコンパイルエラーの原因特定
- **README の作成支援**: 本ファイルの構成・記述
