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
cc -Wall -Wextra -Werror main.c -L. -lftprintf -I. -o program
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

### 設計の根拠（Justification）

#### 1. フォーマット文字列の線形スキャン

フォーマット文字列を1文字ずつポインタで走査する方式を採用しました。

| 方式 | 説明 | 採用理由 |
|------|------|----------|
| **線形スキャン（採用）** | `while (*format)` でポインタを1ずつ進める | 追加メモリ不要、`%` 発見と同時に変換処理に移行できる |
| インデックス方式 | `format[i]` でアクセス | ポインタ演算と等価だが、ポインタ方式の方が 42 Norm 上でシンプル |
| `strchr` で `%` を探す | `strchr` で次の `%` の位置を取得 | 通常文字の一括書き出しには使えるが、変換処理との統合が複雑になる |

線形スキャンは O(n)（n = フォーマット文字列の長さ）で、状態を持たずに1パスで完結するため、printf の仕様に最も自然に対応します。

#### 2. va_list（可変長引数リスト）

引数リストを表すデータ構造として `va_list` を使います。

```
スタック上の引数レイアウト（概念図）
 ┌──────────┬──────────┬──────────┬───────┐
 │ format * │  arg1    │  arg2    │  ...  │
 └──────────┴──────────┴──────────┴───────┘
                ↑
            va_start でここを指すポインタを初期化
            va_arg  で型サイズ分だけ進む
```

`va_list` は ABI（呼び出し規約）に依存した実装が `<stdarg.h>` に隠蔽されており、移植性を保ちつつ可変引数を扱える唯一の標準的な方法です。代替として引数を配列・構造体で渡す設計も存在しますが、呼び出し側の書き方が `printf` の仕様から外れるため採用しません。

#### 3. if-else チェーンによるディスパッチ

変換指定子ごとの処理の振り分けに `if-else if` 連鎖を使っています。

| 方式 | メリット | デメリット | 採用可否 |
|------|----------|------------|----------|
| **if-else チェーン（採用）** | 追加の変数・配列が不要、Norminette 準拠 | 指定子が増えると行数が増える | ✓ |
| `switch-case` | コンパイラが jump table に最適化しやすい | 42 Norm は switch を禁止していない（が if-else と等価） | △ |
| 関数ポインタテーブル | O(1) ルックアップ | テーブル定義のためヘッダ or static 配列が必要、Norm 上で冗長 | △ |

今回の対応指定子は 8 種類と少ないため、線形探索（O(n)）の if-else でも実行速度に差はなく、最もシンプルな実装を選びました。

#### 4. 基数変換に再帰を使う理由

数値を任意の基数で出力するとき、桁は「下の桁から順に確定」しますが「出力は上の桁から」する必要があります。

```
例: 255 を 16進数に変換
  255 / 16 = 15 余り 15  → 'f'  ← 後に出力
   15 / 16 =  0 余り 15  → 'f'  ← 先に出力（再帰の底）
```

| 方式 | 説明 | トレードオフ |
|------|------|------------|
| **再帰（採用）** | 呼び出しスタックが「逆順バッファ」の役割を果たす | 追加配列ゼロ、コードが短い。桁数上限（32bit で最大 10 桁）があるのでスタックオーバーフローの懸念なし |
| 一時バッファに逆順格納 | `char buf[32]` に下位桁から詰め、最後に逆転して出力 | 配列確保が必要で Norminette の VLA 禁止を気にしなければ等価 |

`unsigned int` の 16 進表記は最大 8 桁なので再帰の深さは 8 以下であり、スタック消費量は無視できます。

#### 5. ポインタ出力に unsigned long を使う理由

`%p` はポインタを受け取りますが、ポインタをそのまま整数演算するには適切な整数型へキャストする必要があります。

```c
unsigned long addr = (unsigned long)va_arg(*ap, void *);
```

| 型 | 32bit | 64bit | 理由 |
|----|-------|-------|------|
| `unsigned int` | OK | NG（切り詰め） | 32bit なら 4 バイトだが 64bit では 8 バイトのポインタを格納できない |
| `uintptr_t` | OK | OK | 最も正確だが `<stdint.h>` の追加インクルードが必要 |
| **`unsigned long`（採用）** | OK | OK | 64bit Linux では `unsigned long` = 8 バイトでポインタサイズと一致。`<stdint.h>` 不要 |

対象プラットフォーム（64bit Linux / macOS）では `sizeof(unsigned long) == sizeof(void *)` が保証されるため、この型で十分です。

#### 6. 出力文字数の積算（戻り値設計）

各変換関数が出力した文字数を `int` で返し、呼び出し元の `ft_printf` が `count` に加算する設計です。

```c
count += ft_handle_conversion(*format, &ap);
count += write(1, format, 1);  // 通常文字も write の戻り値で加算
```

`write(2)` 自体が書き込んだバイト数を返すため、その戻り値をそのまま使うことで余計なカウンタ変数を各関数に持たせずに済みます。各変換関数が「自分が出力した文字数だけを返す」単一責任の設計となっており、組み合わせが容易です。

---

## Resources

- [printf(3) — Linux man page](https://linux.die.net/man/3/printf)
- [va_list / stdarg.h — cppreference](https://en.cppreference.com/w/c/variadic)
- [42 Norm](https://cdn.intra.42.fr/pdf/pdf/960/norme.en.pdf)
- [printfTester](https://github.com/Tripouille/printfTester)

### AI の使用について

- **バグ診断**: 型ミス・未定義動作・未使用変数などのコンパイルエラーの原因特定
- **README の作成支援**: 本ファイルの構成・記述
