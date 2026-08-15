# push_swap コードリーディングガイド

> 提出用の説明は `README.md` にあります。こちらは**自分のコードを自分で読み解くための内部解説**です。
> 評価時に「ここ何してるの？」と聞かれて即答できる状態を目指した資料です。

---

## 0. 30秒サマリ

このプログラムがやることは、たった2行で言えます。

1. コマンドライン引数を `t_swap` の**双方向連結リスト**（スタック `a`）に変換する
2. スタックを操作しながら、実行した命令名を `write(1, "ra\n", 3)` のように**その場で標準出力へ吐く**

ソート結果そのものは誰にも見せません。**出力するのは命令列だけ**です。
だから「ソート関数」ではなく「命令を発行しながらリストを並べ替える関数」を読んでいる、という意識が大事です。

---

## 1. ファイルマップ（どこに何があるか）

| 層 | ファイル | 中身 |
| --- | --- | --- |
| **入口** | `main.c` | 全体の流れ。`setup_stack` → `run_algorithm` → `print_all_bench` → 解放 |
| **入力処理** | `args_parse.c` | 引数連結 / オプション判定 / 数値バリデーション |
| | `check_duplicate.c` | 重複と不正値のチェック |
| | `stack_utils.c` | 文字列 → 連結リスト生成、リスト解放 |
| **11命令** | `swap_a_b.c` | `sa` `sb` `ss` |
| | `push_a_b.c` | `pa` `pb` |
| | `rotate_a_b.c` | `ra` `rb` `rr` |
| | `rev_rotate_a_b.c` | `rra` `rrb` `rrr` |
| **アルゴリズム** | `simple_algorithm.c` | 選択ソート系 O(n²) |
| | `medium_algorithm.c` | チャンク分割 O(n√n) + `chunk_rank` / `pull_from_b` |
| | `chunk_utils.c` | `bring_chunk`（medium の中核） |
| | `complex_algorithm.c` | 基数ソート O(n log n) + `is_sorted` |
| | `ft_adaptive.c` | disorder による戦略の振り分け |
| **計測・補助** | `ft_disoder.c` | 転倒数による disorder 計算（マージソート応用） |
| | `bench_print.c` | `--bench` の出力 |
| | `stack_size.c` | リストの長さ |
| | `ft_strcmp.c` | オプション文字列比較（libft に無いので自作） |
| **ヘッダ** | `push_swap.h` | 構造体3つ + 全プロトタイプ |

`libft/` は 42 の既存ライブラリ。ここで実際に使っているのは
`ft_split` / `ft_atoi` / `ft_strlen` / `ft_strlcat` / `ft_bzero` / `ft_putstr_fd` / `ft_putnbr_fd` くらいです。

---

## 2. データ構造（`push_swap.h`）

### `t_swap` — スタックのノード

```c
typedef struct s_swap
{
    int             num;   // 実際の値（例: -42, 100）
    int             rank;  // 0〜n-1 の順位。medium / complex だけが使う
    struct s_swap   *pre;  // 前のノード
    struct s_swap   *next; // 次のノード
}   t_swap;
```

**`num` と `rank` の使い分けがこのコードの肝**です。

- `num` は生の値。負数もあるし、値の幅もバラバラ（例: `-2147483648` と `5`）。
- `rank` は「自分より小さい要素が何個あるか」＝ **0 から n-1 に圧縮した順位**。

`rank` があるおかげで、medium はチャンク境界を `0〜√n`, `√n〜2√n`… と整数で切れますし、
complex は `rank` をそのまま2進数として扱ってビット単位で振り分けられます。
生の `num` のままでは、負数や飛び飛びの値のせいでどちらも成立しません。

**スタックの向き**: `*a` が指すノードが**スタックの一番上（top）**です。`next` を辿ると下へ降ります。

```
*a → [2] ⇄ [4] ⇄ [5] ⇄ [1] ⇄ [3] → NULL
     top                      bottom
```

`pre` は `rra` / `rrb`（末尾を先頭に持ってくる）で末尾の1つ前を切り離すために必要です。

### `t_bench` — 命令カウンタ

`sa`〜`rrr` の11個 + `total`。命令を出力する関数が毎回 `bench->xx++; bench->total++;` します。
`--bench` を付けない場合も**カウントは常に行われて**おり、出力するかどうかだけが変わります。

### `t_ctx` — main が持つ全状態

```c
typedef struct s_ctx
{
    t_swap  *a;          // スタックa
    t_swap  *b;          // スタックb
    t_bench bench;       // カウンタ
    int     op;          // 0=未指定 1=simple 2=medium 3=complex 4=adaptive
    int     bench_flag;  // --bench が付いたか
    int     dis_flg;     // 1/2/3 = disorder の区分
    double  disorder;    // 0.0〜1.0
}   t_ctx;
```

引数を1個の構造体にまとめているのは、**Norm の「関数の引数は4つまで」**を守るためです。
main の先頭の `ft_bzero(&ctx, sizeof(t_ctx))` で全メンバをゼロ初期化しています（`a`/`b` も NULL になる）。

---

## 3. 実行フロー（`main.c` を上から追う）

```
main()
 ├─ ft_bzero(&ctx)                    ← 全部ゼロクリア
 ├─ setup_stack(ac, av, &ctx)
 │    ├─ parse_options()              ← --simple 等を読み、数値が始まる位置 n を返す
 │    ├─ ac == 1 なら終了             ← 引数なし = 何も出力せず正常終了
 │    ├─ join_argv(av + n)            ← 残りの引数を空白区切り1本の文字列に連結
 │    ├─ check_duplicate(join)        ← 不正値 or 重複なら "Error"
 │    ├─ stack_init(join)             ← 文字列 → 連結リスト
 │    ├─ disorder_ratio(ctx.a)        ← 転倒数から乱雑度を算出
 │    └─ disorder_flg(disorder)       ← 1 / 2 / 3 に区分
 ├─ run_algorithm(&ctx)               ← ここで命令が stdout に流れる
 ├─ bench_flag なら print_all_bench() ← stderr へ統計
 └─ stack_free(a), stack_free(b)
```

### 押さえておくポイント

**① 引数を一度「1本の文字列」に潰している**

`join_argv` が `av[n]` 以降を空白でつないで `"3 1 2"` のような1本の文字列にします。
これにより `./push_swap 3 1 2` と `./push_swap "3 1 2"` を**同じコードパスで扱える**ようになります。
その代わり、この文字列は `ft_split` で3回パースされます（`check_duplicate` / `stack_init` / それぞれの内部）。
効率は良くありませんが、n ≤ 500 程度なら誤差です。

**② エラー時も `return (0)`**

`setup_stack` が失敗すると main は `return (0)` します。つまり**終了ステータスは常に 0** です。
`Error` は `write(2, ...)` で標準エラーに出るので、シェルからは
`./push_swap 1 1 2 2>&1 1>/dev/null` のように見ます。

**③ disorder は必ず計算される**

`--bench` の有無に関係なく `setup_stack` の中で毎回計算しています。
`--adaptive`（デフォルト）が `dis_flg` を必要とするからです。
ここは push_swap 命令を1つも発行しない、純粋な C 側の前処理です。

---

## 4. 引数処理を深掘り（`args_parse.c` / `check_duplicate.c`）

### `parse_options` — オプションを読む

```c
count = 1;                       // av[0] はプログラム名なので飛ばす
while (av[count] != NULL) {
    type = select_option(av[count]);   // 1..5、該当なしは 0
    if (type == 0) break;              // 数値が始まった → 終了
    ...
    count++;
}
return (count);                  // 「数値が始まるインデックス」を返す
```

戻り値 `count` は**数値列の開始位置**で、main はこれを `join_argv(av + n)` に使います。

排他ルールは2つ:

- `--bench` を2回 → `-1`（エラー）
- 戦略オプションを2つ（例: `--simple --medium`） → `-1`（エラー）
- `--bench --simple` のような組み合わせは OK

なお `--foo` のような未知のオプションは `select_option` で 0 が返るので**数値として扱われ**、
`is_valid_number` で弾かれて `Error` になります。結果的に正しい挙動です。

### `is_valid_number` — 数値バリデーション

```c
if (str[i] == '-') { neg = 1; i++; }
if (str[i] == '\0') return (0);          // "-" だけは不正
while (str[i]) {
    if (str[i] < '0' || str[i] > '9') return (0);
    value = value * 10 + (str[i] - '0');
    i++;
}
if ((!neg && value > 2147483647) || (neg && value > 2147483648)) return (0);
```

- `+` 記号は受け付けません（`+5` はエラー）
- 空文字列 `""` は `ft_split` の時点で消えるので、`check_duplicate` の `!arr[0]` で弾かれます
- 負数の上限が `2147483648` なのは `INT_MIN = -2147483648` を通すためです

> ⚠️ **既知の穴**: `value` は `long` ですが、桁数チェックを**ループの後**でしかしていません。
> 20桁以上を渡すと `long` 自体がオーバーフローし（C では未定義動作）、範囲チェックをすり抜けます。
> ```sh
> $ ./push_swap 18446744073709551616 1 2   # Error が出ずに素通りする
> ```
> 直すなら、ループ内で `if (value > 2147483648) return (0);` を毎桁チェックします。
> （42 のテスターはここまで見ないことが多いですが、聞かれたら説明できるようにしておくと安全です）

### `check_duplicate` — O(n²) の総当たり

`ft_split` した各要素について、`is_valid_number` と「後ろに同じ値がないか」を確認します。
`has_duplicate` が毎回 `ft_atoi` を呼ぶので厳密には O(n²) の atoi 呼び出しですが、
n ≤ 500 なら問題ありません。

戻り値の意味が **1 = OK / 0 = NG** で、関数名から受ける印象と逆なので読むとき注意してください。

### `stack_init` — 文字列 → 連結リスト

`ft_split` の結果を先頭から `stack_append` で末尾に追加していきます。
`stack_append` は `head` と `tail` の両方を更新するので、**追加が O(1)**（末尾探索が不要）です。

---

## 5. 11命令の実装

4ファイルとも構造が同じです。**「実際の操作を行う `static` 関数」＋「出力とカウントを `report_op` に委譲する公開関数」**の2層。

```c
// bench_print.c — 全命令共通の「出力してカウントする」処理
void    report_op(char *label, int len, int *counter, t_bench *bench)
{
    write(1, label, len);   // 命令名を stdout へ
    (*counter)++;           // その命令専用のカウンタ（bench->pbなど）
    bench->total++;         // 合計カウンタ
}

// push_a_b.c
static int  push_a_b(t_swap **before, t_swap **after) { ...ポインタ付け替え...; return (1); }

void    push_pb(t_swap **a, t_swap **b, t_bench *bench)
{
    if (push_a_b(a, b) == 1)                    // 成功したときだけ
        report_op("pb\n", 3, &bench->pb, bench); // 出力 + カウント
}
```

以前は `write` + `bench->pb++` + `bench->total++` を4ファイル（`swap_a_b.c` / `push_a_b.c` / `rotate_a_b.c` / `rev_rotate_a_b.c`）にそれぞれ書いていましたが、
**同じ処理が11箇所重複していた**ため `report_op` に共通化しています（直近の "write fix" コミット）。
呼び出し側は「操作が成功したか」を判定して `report_op` を呼ぶだけになり、各ファイルはポインタ操作だけに専念できます。

この設計のおかげで、**空スタックや1要素に対する操作は命令を出力しません**。
（`sa` on 1要素、`pb` on 空スタックなど）`static` 関数が失敗（`return (0)`）を返すと `report_op` 自体が呼ばれないため、
これが「無駄な命令を出さない」保証になっています。

### 各操作の中身

| 関数 | やっていること |
| --- | --- |
| `swap_a_b` | ノードは動かさず、**`num` の値だけ交換**する |
| `push_a_b` | `before` の先頭ノードを切り離し、`after` の先頭に付け替える |
| `rotate_a_b` | 先頭を末尾へ。末尾は `while (last->next)` で毎回探索（O(n)） |
| `rev_rotate` | 末尾を先頭へ。`last->pre->next = NULL` で切り離すので `pre` が必須 |

> ⚠️ **`swap_a_b` の落とし穴**: 交換しているのは `num` だけで、**`rank` は交換していません**。
> 現状 `sa` を使うのは `simple_algorithm` だけで、simple は `rank` を一切使わないため問題は起きていません。
> ただし今後 medium / complex に `sa` / `sb` を足すなら、`rank` も一緒に swap しないと壊れます。

> 💡 **未使用の命令**: `sb` / `ss` / `rr` / `rrr` は実装済みですが、**どのアルゴリズムからも呼ばれていません**。
> 課題が11命令すべての実装を要求しているので置いてあります。
> `rr` / `rrr` を使えば a と b を同時に回して命令数を削れる余地があります（最適化の伸びしろ）。

> 🔍 **細かい点**: `rotate_a_b` は `first = *stack;` を NULL チェックより先に書いています。
> `stack` 自体は常に `&ctx->a` のような有効なアドレスなので実害はありませんが、順序としては逆が正しいです。

---

## 5.5 11命令を図で見る

口頭説明用に、各命令の前後をスタック図で並べておきます。スタックは**左がtop**です。

```
初期状態        a: 2 4 5 1 3   b: (空)
                top→2 4 5 1 3←bottom
```

**sa（swap a）— 上位2つを交換**
```
前: 2 4 5 1 3        後: 4 2 5 1 3
     ~~~                  ~~~
    2と4を交換
```

**pb（push b）— aの top を b の top へ**
```
前: a: 2 4 5 1 3   b: (空)
後: a: 4 5 1 3      b: 2
        ↑ aから抜けた2が bの topに乗る
```

**pa（push a）— bの top を a の top へ**（pbの逆方向）
```
前: a: 4 5 1 3      b: 2
後: a: 2 4 5 1 3    b: (空)
```

**ra（rotate a）— 先頭が最後尾に回る（上へシフト）**
```
前: 2 4 5 1 3
後: 4 5 1 3 2
    ↑先頭の2が末尾へ移動、他は1つずつ前にずれる
```

**rra（reverse rotate a）— 最後尾が先頭に回る（下へシフト）**
```
前: 2 4 5 1 3
後: 3 2 4 5 1
              ↑末尾の3が先頭へ移動
```

**rr / rrr** — `ra`+`rb` / `rra`+`rrb` を同時に実行。a・bの回転が両方成功したときのみ1回とカウントする（`rotate_a_b.c` の `check_a == 1 || check_b == 1`）。

図からわかる通り、`ra`と`rra`は逆演算、`pa`と`pb`も逆演算です。アルゴリズムは基本的に
「`pb`でbに逃がす → `ra`/`rra`で欲しい要素をtopへ寄せる → `pa`でaに戻す」の組み合わせだけで構成されています。

---

## 6. アルゴリズム4種

### 前提: `chunk_rank`（`medium_algorithm.c:15`）

medium と complex はどちらもこれを最初に呼びます。

```c
// 各ノードについて「自分より小さい値がいくつあるか」を数えて rank に入れる
```

二重ループなので O(n²) ですが、**push_swap 命令は1つも発行しない**内部計算です。
課題で評価されるのは命令数なので、ここのコストは計算量の議論には含めません。

結果として `rank` は必ず **0, 1, 2, …, n-1 の重複なしの並び**になります（重複値は入力時点で弾いてあるため）。

---

### 6-1. Simple — 選択ソート O(n²)

```
n-2 回繰り返す:
    最小値の位置を探す           (find_min_index, O(n))
    近い方向に回して先頭へ       (bring_min_to_top: ra または rra)
    pb で b へ積む
残った2要素を必要なら sa で整列
b の中身を全部 pa で a に戻す
```

**なぜ `n-2` 回なのか**: a に2要素だけ残した状態で止め、その2つは `sa` 1回で整列できるからです。
最小値を毎回 b に積んでいるので、b は上から昇順に積み上がり、そのまま `pa` で戻せば a が昇順になります。

**`bring_min_to_top` の工夫**: 最小値が上半分なら `ra`、下半分なら `rra` を使い、
回転回数を `min(index, size - index)` に抑えています。ここが「ほぼソート済みの入力に強い」理由です。

```c
if (min_index <= size / 2)  ra を min_index 回
else                        rra を (size - min_index) 回
```

---

### 6-2. Medium — チャンク分割 O(n√n)

登場人物: `chunk_rank` → `chunk_size` → `bring_chunk` → `pull_from_b`

**`chunk_size`（`medium_algorithm.c:39`）**

```c
if (n <= 3) return (n);
while (i * i <= n) i++;
return (i - 1);          // floor(sqrt(n))
```

チャンクの**サイズ**が √n なので、チャンクの**個数**も √n 個になります。

**`bring_chunk`（`chunk_utils.c:44`）** — a → b へ積む

```
chunk_start = 0, chunk_end = chunk_size
a が空になるまで:
    このチャンクに属する要素が a に何個あるか数える (count)
    count が 0 になるまで:
        先頭がチャンク内 → pb（count--）
        違う           → 対象が上半分なら ra、下半分なら rra
    次のチャンクへ (start = end, end += chunk_size)
```

rank の小さいチャンクから順に落としていくので、**b は大まかに降順**に積み上がります。
`find_chunk_index` で「一番近いチャンク内要素」の位置を見て回転方向を決めるのが効率化のポイントです。

**`pull_from_b`（`medium_algorithm.c:75`）** — b → a へ戻す

```
b が空になるまで:
    最大 rank の位置を探す (find_max_rank_index)
    近い方向に rb / rrb で回して先頭へ
    pa
```

常に「b の中の最大値」を a の先頭に載せるので、a は昇順に積み上がります。
b は既に大まかに降順なので最大 rank はたいてい先頭付近にあり、回転回数が少なくて済みます。

**手で追う例**: `./push_swap --medium 2 4 5 1 3`

| 状態 | a (rank) | b (rank) | 次の操作 |
| --- | --- | --- | --- |
| 初期 | 2(1) 4(3) 5(4) 1(0) 3(2) | — | chunk_size=2, チャンク [0,2) |
| | 4(3) 5(4) 1(0) 3(2) | 2(1) | `pb` |
| | 5(4) 1(0) 3(2) 4(3) | 2(1) | `ra` |
| | 1(0) 3(2) 4(3) 5(4) | 2(1) | `ra` |
| | 3(2) 4(3) 5(4) | 1(0) 2(1) | `pb` → チャンク [2,4) へ |
| | 4(3) 5(4) | 3(2) 1(0) 2(1) | `pb` |
| | 5(4) | 4(3) 3(2) 1(0) 2(1) | `pb` → チャンク [4,6) へ |
| | — | 5(4) 4(3) 3(2) 1(0) 2(1) | `pb`、ここから pull_from_b |
| | 5 | 4 3 1 2 | `pa` |
| | 4 5 | 3 1 2 | `pa` |
| | 3 4 5 | 1 2 | `pa` |
| | 3 4 5 | 2 1 | `rb`（最大 rank が下半分にあった） |
| | 2 3 4 5 | 1 | `pa` |
| | 1 2 3 4 5 | — | `pa` 完了 |

合計 13 命令（pb×5, ra×2, pa×5, rb×1）。実際に `--bench` で確認できます。

---

### 6-3. Complex — LSD 基数ソート O(n log n)

```c
int bit_size(int n)              // rank を表現するのに必要なビット数
{
    while ((1 << i) < n) i++;    // n=5 → 3ビット (rank は 0〜4)
    return (i);
}

int radix_pass(t_swap **a, t_swap **b, int bit, t_bench *bench)
{
    i = 0;
    while (i < bit) {                       // 各ビットについて
        count = stack_size(*a);
        while (count) {                     // a を1周
            if (((*a)->rank >> i) & 1) rotate_ra(a, bench);  // ビットが1 → a に残す
            else                       push_pb(a, b, bench); // ビットが0 → b へ
            count--;
        }
        while (*b) push_pa(a, b, bench);    // b を全部戻す
        i++;
    }
}
```

**なぜこれでソートされるのか**: LSD（下位ビットから）基数ソートは**安定ソート**です。
下位ビットで分けた順序を保ったまま上位ビットで分け直すので、
全ビットを処理し終えた時点で完全に昇順になります。

- ビット0のパス後 → 偶数 rank が上、奇数 rank が下
- ビット1のパス後 → rank mod 4 の順
- …
- ビット `log2(n)` のパス後 → 完全に昇順

**命令数**: 1パスで `n` 回の `ra`/`pb` + 最大 `n` 回の `pa` ≒ 2n 命令。
それを `log2(n)` パス繰り返すので **約 2n·log2(n)**。n=100 なら 2×100×7 ≒ 1400、実測 1084 命令です。

**`rank` を使う理由がここで決定的**: 生の `num`（負数あり、値が飛び飛び）を2進数で見ても意味を成しません。
`rank` が 0〜n-1 の連続整数だからこそ、`log2(n)` ビットで全要素を区別でき、パス数が最小になります。

**`is_sorted`（`complex_algorithm.c:52`）** はこのファイルに同居していますが、
simple / medium / complex の3つすべてが冒頭で呼ぶ共通関数です。
すでに昇順なら**命令を1つも出さずに return** します（課題の「最小の命令列」要件を満たすため）。

---

### 6-4. Adaptive — ディスパッチャ（`ft_adaptive.c`）

これ自体はソートしません。**disorder を見て上の3つのどれかを呼ぶだけ**です。

```c
int disorder_flg(double n)
{
    if (n < 0.2)              return (1);   // → simple
    if (0.2 <= n && n < 0.5)  return (2);   // → medium
    if (n >= 0.5)             return (3);   // → complex
    return (0);
}
```

閾値 0.2 / 0.5 は課題 VI.3.3-4 が指定する区間の境界そのままです。
各区間にどれを割り当てたかの理由は `README.md` に書いてある通りで、要点は:

- ほぼ整列済み（< 0.2）: simple の「近い方向に回す」が効き、基数ソートの固定コスト（全ビット走査）より軽い
- 中程度（0.2〜0.5）: O(n²) は重すぎ、基数ソートはまだ割に合わない中間解
- ランダムに近い（≥ 0.5）: 基数ソートが最も命令数の伸びが緩やか

**実測（n=500 のランダム入力）**

| 戦略 | 命令数 |
| --- | --- |
| `--simple` | 32255 |
| `--medium` | 8259 |
| `--complex` | 6784 |
| `--adaptive` | 6784（complex を選択） |

**実測（n=5、`2 4 5 1 3`）**

| 戦略 | 命令数 |
| --- | --- |
| `--simple` | 10 |
| `--medium` | 13 |
| `--complex` | 25 |

小さい n では simple が最速です。基数ソートは `log2(n)` パスの固定コストがあるため、
n が小さいうちは不利になります。adaptive の設計が意味を持つのはこの逆転があるからです。

---

## 7. disorder の計算（`ft_disoder.c`）

disorder の定義は「**大小関係が逆転しているペアの数 ÷ 全ペア数**」です。

```
disorder = 転倒数 / (n × (n-1) / 2)
```

素朴に全ペアを比べると O(n²) ですが、ここでは**マージソートの過程で転倒数を数える**古典的テクニックを使い、
O(n log n) で同じ値を出しています。

**核心は `do_merge` の1行**（`ft_disoder.c:59`）:

```c
if (a->arr[i] <= a->arr[j])
    a->temp[k++] = a->arr[i++];
else {
    a->temp[k++] = a->arr[j++];
    inversions += (mid - i + 1);   // ← ここ
}
```

右側の要素 `arr[j]` を先に取り出したということは、
**左側に残っている `mid - i + 1` 個すべてが `arr[j]` より大きい**＝その個数だけ転倒ペアがある、
という意味です。マージ1回でまとめて数え上げられるのがこの手法の肝です。

`t_arrs`（`arr` と `temp` をまとめた構造体）が存在するのは、**Norm の引数4つ制限**を守るためです。
`do_merge(arr, temp, left, mid, right)` だと5引数になってしまうので、前2つを構造体に押し込んでいます。

呼び出し経路: `disorder_ratio`（リスト → 配列に変換）→ `calculate_disorder_fast`（配列をコピーして計測）。
元のスタックは壊しません（`arr_copy` を作ってからソートしている）。

---

## 8. ベンチ出力（`bench_print.c`）

すべて **fd 2（標準エラー）** に出します。命令列（stdout）と混ざらないようにするためです。
だから確認するときは `2>&1 1>/dev/null` と書きます。

**`print_disorder` の小数表示トリック**: `printf` が使えないので、

```c
scaled = (int)(disorder_result * 10000 + 0.5);  // 0.4 → 4000（+0.5 は四捨五入）
int_part  = scaled / 100;                        // 40
frac_part = scaled % 100;                        // 0
// frac_part < 10 なら "0" を先に出す（例: 40.05% の 05）
```

整数部と小数部を分けて `ft_putnbr_fd` で出し、`40.00%` の形にしています。

**`print_strategy`** は `op` を優先し、`op == 0`（オプション未指定）のときだけ `dis_flg` を見て
`Adaptive / O(...)` と表示します。

---

## 9. 読む順番のおすすめ

コードを初めて通しで読むなら、この順で追うと理解が積み上がります。

1. **`push_swap.h`** — 構造体3つを頭に入れる（特に `num` と `rank` の違い）
2. **`main.c`** — 全体の流れを掴む
3. **`push_a_b.c`** — 「操作 + 出力 + カウント」の2層構造のパターンを1つ理解する（他3ファイルは同じ形）
4. **`rev_rotate_a_b.c`** — `pre` ポインタが何のためにあるか納得する
5. **`simple_algorithm.c`** — 一番シンプルなソート。「命令を発行しながら並べ替える」感覚を掴む
6. **`args_parse.c` → `check_duplicate.c` → `stack_utils.c`** — 入力がどうリストになるか
7. **`medium_algorithm.c` + `chunk_utils.c`** — `rank` の意味がここで分かる
8. **`complex_algorithm.c`** — 基数ソート。`rank` があるから成立する、と繋げる
9. **`ft_disoder.c`** — 転倒数。上のソートとは独立した計測ロジック
10. **`ft_adaptive.c` + `bench_print.c`** — 全部を束ねる部分

---

## 10. 動かして確かめるコマンド集

```sh
make                                    # ビルド（libft も一緒に）

# 基本
./push_swap 2 1 3 6 5 8

# ソート結果が正しいか（42配布のチェッカー）
./push_swap 5 3 9 1 7 2 | ./checker_Mac 5 3 9 1 7 2      # → OK

# 戦略ごとの命令数を比較
N=$(python3 -c "import random;a=list(range(1,101));random.shuffle(a);print(' '.join(map(str,a)))")
for o in --simple --medium --complex --adaptive; do
    printf "%-11s " $o
    ./push_swap --bench $o $N 2>&1 1>/dev/null | grep total_ops
done

# ソート済み入力なら命令ゼロ
./push_swap 1 2 3 4 5 | wc -l           # → 0

# エラーケース
./push_swap 3 2 3                       # 重複    → Error
./push_swap ""                          # 空      → Error
./push_swap abc                         # 非数値  → Error
./push_swap 2147483648                  # 範囲外  → Error
./push_swap --simple --medium 3 1 2     # 排他違反 → Error

# メモリリークチェック（Linux 環境で）
valgrind --leak-check=full ./push_swap 5 3 9 1 7 2 > /dev/null
```

---

## 11. 今後の課題・改善の余地

自分で把握しておくべき「まだやっていないこと」「直せるところ」のリストです。

| 項目 | 内容 |
| --- | --- |
| **bonus 未実装** | 自作の `checker` が無く、42配布の `checker_Mac` に依存している |
| **`is_valid_number` の桁溢れ** | 20桁以上の入力で `long` がオーバーフローし、チェックをすり抜ける（§4 参照） |
| **`rr` / `rrr` が未使用** | a と b を同時に回せば命令数を削れる余地がある |
| **`swap_a_b` が `rank` を交換しない** | 今は無害だが、medium/complex に `sa` を足すと壊れる（§5 参照） |
| **`ft_split` を3回呼んでいる** | `join_argv` した文字列を `check_duplicate` と `stack_init` が別々にパースしている |
| **`stack_init` の malloc 失敗時** | 途中まで作ったリストを解放せず NULL を返す（リーク） |
| **`chunk_rank` が O(n²)** | 命令数には影響しないが、n が大きいと実行時間に効く |
| **`bring_chunk` の内部コスト** | `count_in_chunk` / `find_chunk_index` を毎ループ呼ぶため C 側の計算量は重め |

---

## 12. 弁論想定問答

レビューで聞かれそうな質問と、コードの根拠つきの回答例です。「なぜ」を聞かれたら、まずここを思い出してください。

### 全体設計

**Q. なぜ4つもアルゴリズムを実装したのか？1つの賢いアルゴリズムで統一しないのか？**
> 課題要件（VI.3.3）が O(n²) / O(n√n) / O(n log n) の3クラスをそれぞれ実装し、
> disorder（乱雑度）に応じて切り替える adaptive を作ることを求めているため。
> 実測（§6-4）でも、n が小さいときは simple が最速、ランダムに近いときは complex が最速、
> と「常に同じアルゴリズムが最善」ではないことが確認できる。この逆転現象こそが adaptive の存在理由。

**Q. `main.c` の処理順序を一言で説明すると？**
> `setup_stack`（引数パース→重複/範囲チェック→リスト化→disorder計算）→
> `run_algorithm`（opに応じて4アルゴリズムのどれかを実行、命令をstdoutへ即時出力）→
> `--bench`ならstderrへ統計出力→`stack_free`で後始末。（§3の図を参照）

**Q. なぜ引数を一度1本の文字列に結合（`join_argv`）しているのか？**
> `./push_swap 3 1 2` と `./push_swap "3 1 2"` を同じ `ft_split` ベースの処理で扱えるようにするため。
> 引数がシェルで複数トークンに分かれていても、クォートで1トークンになっていても結果が同じになる。

### データ構造

**Q. `num` と `rank` を分けているのはなぜ？1つのフィールドで足りないのか？**
> `num` は生の値（負数・飛び飛びの値を含む）。`rank`は「自分より小さい要素の個数」＝0〜n-1に圧縮した順位。
> medium はチャンク境界を整数区間で切りたい、complex は順位をビット単位で見たい。
> どちらも「隙間のない連続した0〜n-1の整数」が必要で、生の`num`のままでは負数や飛び飛びの値のせいで成立しない。

**Q. 双方向連結リスト（`pre`/`next`）にした理由は？配列じゃダメなのか？**
> `pa`/`pb`（先頭同士のつけ替え）はポインタ操作だけでO(1)。配列だと毎回シフトが必要でO(n)になる。
> `pre`は`rra`/`rrb`（末尾を先頭に持ってくる）のときに「末尾の1つ前」を切り離すために必須
> （`last->pre->next = NULL`、`rev_rotate_a_b.c:26`）。

**Q. `t_ctx`のような構造体にまとめている理由は？**
> Normの「関数の引数は4つまで」制限のため。stateをバラバラの変数で持つと`main`から呼ぶ関数の引数が
> すぐ4つを超えてしまう。同じ理由で`t_arrs`（`ft_disoder.c`）や`t_bench`も存在する。

### 引数処理

**Q. `check_duplicate`が先で`stack_init`が後、なぜ2回パースしているのか非効率では？**
> その通りで非効率だが、n≤500程度なら実行時間に影響しない（§11の改善余地に記載）。
> 設計としては「バリデーション」と「構築」を関数の責務として分離した結果。

**Q. `is_valid_number`が`+5`を弾く理由、`INT_MIN`はどう通しているか？**
> 課題の入力形式に`+`は含まれないため未対応（弾いて`Error`）。
> `INT_MIN = -2147483648`を通すために、負数のときだけ上限チェックを`2147483648`にしている
> （`neg`フラグで分岐、`args_parse.c:83`）。

**Q. オプションと数値の順序に制約はあるか？**
> `parse_options`は`av[1]`から順に見て、`select_option`が0を返した（＝オプションでなくなった）時点で
> ループを抜ける。つまり**オプションは先頭にまとめる必要がある**。数値の後にオプションを書くと、
> オプション文字列がそのまま数値としてパースされて`Error`になる。

### アルゴリズム

**Q. simpleが「選択ソート」だと言える根拠は？**
> 毎回「未整列部分から最小値を探す」→「スタックの外（b）に置く」を繰り返す構造が選択ソートそのもの。
> `find_min_index`で全走査しながら最小を探す部分がO(n)、それをn-2回繰り返すのでO(n²)。

**Q. mediumの√nチャンクは、要素数が√nの倍数でなくても機能するか？**
> する。`chunk_size`は`floor(sqrt(n))`を返すだけで、`bring_chunk`は最後のチャンクが半端な個数でも
> `count_in_chunk`で実際にある個数だけループするため問題ない。

**Q. complexがO(n log n)である根拠を数式で説明すると？**
> `bit_size`が返すビット数は`ceil(log2(n))`。各ビットのパス（`radix_pass`内の1回のwhileループ）は
> 全要素を1回ずつ`ra`か`pb`するのでO(n)。これを`log2(n)`回繰り返すので合計O(n log n)。
> 実測でもn=100で約1400命令、n×log2(n)の理論値と近い（§6-3）。

**Q. なぜradix sortは`rank`のビットで振り分けても正しくソートできるのか？**
> LSD基数ソートは安定ソート（同じキーの相対順序を保つ）だから。下位ビットで振り分けた結果の順序を
> 保ったまま次のビットで振り分け直すことを繰り返すと、全ビット処理後には辞書式に完全昇順になる。
> `rank`が0〜n-1の一意な整数なので、ビット表現がそのまま大小関係と一致する。

**Q. simple/medium/complexの冒頭で`is_sorted`を呼んでいるのはなぜ？**
> 課題が「最小の命令列」を要求しているため。すでに昇順ならアルゴリズムを実行せず即returnし、
> 命令を1つも出力しない。

### disorder / adaptive

**Q. disorderの計算にマージソートを使う理由は？O(n²)の総当たりではダメなのか？**
> 総当たり（全ペア比較）でもdisorderの値自体は正しく計算できるが、O(n²)。マージソートの過程で
> 転倒数を数える手法ならO(n log n)で同じ値が出せる（`do_merge`内の`inversions += (mid - i + 1)`が肝）。
> n=500でも一瞬で終わる、というのがこの実装を選んだ理由。

**Q. 閾値0.2と0.5はどうやって決めたのか？**
> 課題VI.3.3-4がそのまま指定している境界値（low<0.2、medium 0.2〜0.5、high≥0.5）。
> 各区間にどのアルゴリズムを割り当てるかは自由だが、計算量クラスの上限だけは守る必要がある。

**Q. `main.c`で`stack_size(*a) <= 6`のとき強制的に`dis_flg = 1`にしているのはなぜ？**
> 要素数が少ないと、たとえdisorderの値が高くても基数ソート（complexの固定コストであるlog2(n)パス）は
> 割に合わない。実測（§6-4のn=5の例）でもsimpleが最速。小規模入力を常にsimpleで捌くための最適化。

### メモリ・エラー処理

**Q. メモリリークはどう検証したか？**
> `valgrind --leak-check=full`（Linux）または`leaks`（Mac）で`stack_free(ctx.a)`/`stack_free(ctx.b)`後に
> 未解放ブロックがないか確認（§10のコマンド集）。`stack_init`の`malloc`失敗時は例外的にリークする経路が
> 残っている（§11）。

**Q. エラー時になぜexit codeを変えず`return (0)`なのか？**
> 課題が終了コードを明示的に要求していないため。`Error`はstderrへの出力（`write(2, "Error\n", 6)`）だけで
> 判定する設計。

---

## 13. ライブコーディング想定問題

42のライブコーディング試験で聞かれそうな「機能追加」系の問題と、このコードベースに対する解答例を記録しておきます。ここも提出物には含めない自分用の練習ノートです。

### お題: quiet モード — 操作列を出さず、合計命令数だけ出力する

**要件**: 通常は `sa` `pb` … を1行ずつ標準出力するが、quiet モードでは個々の命令名を出さず、合計命令数だけを1行出力する。

**解答**

1. `t_bench` にフラグを1つ追加する

```c
/* push_swap.h */
typedef struct s_bench
{
    ...
    int    quiet;   // 1 なら操作列を出力しない
}    t_bench;
```

2. `report_op` の出力部分だけ条件分岐で止める（カウントは今まで通り行う）

```c
/* bench_print.c */
void    report_op(char *label, int len, int *counter, t_bench *bench)
{
    if (!bench->quiet)
        write(1, label, len);
    (*counter)++;
    bench->total++;
}
```

3. `main.c` の `run_algorithm` の後に合計だけ出す

```c
if (ctx.bench.quiet == 1)
{
    ft_putnbr_fd(ctx.bench.total, 1);
    write(1, "\n", 1);
}
```

**なぜこの3箇所だけで済むか**

- 11命令はすべて `report_op` を経由して出力している（§5参照）ので、出力を止める変更点はここ1箇所だけで全命令に効く。
- `bench->total` は `--bench` の有無に関わらず常にカウントされているので、quiet モードでも合計はすでに正しく積み上がっている。数え直す処理は不要。
- `ft_bzero(&ctx, sizeof(t_ctx))` により `quiet` はデフォルト0なので、既存の動作（1行ずつ出力する通常モード）は変更されない。

**この解答だけでは足りない点**

上のコードだけでは `bench.quiet` を1にする手段がありません。実際の試験では「`--quiet` オプションを追加せよ」まで含めて要求される可能性が高いです。追加するなら:

```c
/* args_parse.c: select_option に1行追加 */
if (ft_strcmp(av, "--quiet") == 0)
    return (6);
```

現在の `parse_options(char **av, int *op, int *bench_flag)` は `t_ctx` 全体ではなく個別のポインタしか受け取っていないため、そのままでは新しい `type == 6` を `bench.quiet` に書き込めません。素直に直すなら

- 第4引数に `int *quiet` を追加して呼び出し側 (`main.c`) で `ctx->bench.quiet` に渡す、または
- `parse_options` の戻り値（数値列の開始位置）を使って `main.c` 側で `av` をもう一度舐めて `--quiet` の有無を判定する

のどちらかになります。試験本番では、この「`parse_options` が `t_ctx` を直接触れない設計になっている」という制約に自分で気づけるかがポイントです。

---

## 付録: 用語ミニ辞典

| 用語 | 意味 |
| --- | --- |
| **rank** | 「自分より小さい要素の個数」＝ 0〜n-1 の順位。値の圧縮 |
| **disorder** | 逆転しているペアの割合。0.0 = 完全ソート済み、1.0 に近い = 完全逆順 |
| **転倒数 (inversion)** | `i < j` かつ `a[i] > a[j]` となるペアの個数 |
| **チャンク** | rank を √n 個ずつに区切ったグループ |
| **LSD 基数ソート** | 最下位ビット (Least Significant Digit) から順に振り分ける基数ソート |
| **Norm** | 42 のコーディング規約。関数25行以内、引数4つ以内、変数5つ以内など |
