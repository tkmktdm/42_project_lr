*This project has been created as part of the 42 curriculum by tfujikaw, htakumi.*

# push_swap

## Description

`push_swap` は、2つのスタック（`a` と `b`）と限られた命令セットだけを使って、`a` に積まれた整数を昇順にソートする C プログラムです。

- 起動時、スタック `a` には重複のない整数（正・負を含む）がランダムな順序で積まれています。
- スタック `b` は空の状態からスタートします。
- 使えるのは `sa` `sb` `ss` `pa` `pb` `ra` `rb` `rr` `rra` `rrb` `rrr` の11命令のみです。
- ゴールは、これらの命令だけを使って `a` を昇順に並べ替え、実行した命令列を標準出力に1行ずつ出力することです。

単純に「ソートできればよい」わけではなく、**できるだけ少ない命令数でソートすること**が求められます。そのため本プロジェクトでは、入力データの乱雑さ（disorder）に応じて最適なアルゴリズムを選ぶ、4種類のソート戦略を実装しています。

## Instructions

### 必要環境

- `make`

### ビルド

```sh
make
```

- `libft` を先にビルドしてから `push_swap` 本体をリンクします。
- `clean` / `fclean` / `re` にも対応しています。

```sh
make clean   # オブジェクトファイルのみ削除
make fclean  # オブジェクトファイル + 実行ファイルを削除
make re      # fclean → all
```

### 実行方法

```sh
./push_swap [オプション] <整数のリスト>
```

引数は空白区切りの整数列です。1つの引数にまとめて渡しても（例: `"3 1 2"`）、複数の引数に分けて渡しても（例: `3 1 2`）どちらでも構いません。

```sh
$ ./push_swap 2 1 3 6 5 8
ra
pb
rra
pb
pb
ra
pb
sa
pa
pa
pa
pa
```

引数を1つも渡さなかった場合、プログラムは何も出力せずに終了します。

### 戦略選択オプション

| オプション     | 説明                                                  | 計算量クラス |
| -------------- | ----------------------------------------------------- | ------------ |
| `--simple`   | Simple アルゴリズムを強制使用                         | O(n²)       |
| `--medium`   | Medium アルゴリズムを強制使用                         | O(n√n)      |
| `--complex`  | Complex アルゴリズムを強制使用                        | O(n log n)   |
| `--adaptive` | disorder に応じて自動選択（**デフォルト動作**） | 入力による   |
| `--bench`    | ソート後、統計情報を標準エラーに出力                  | -            |

```sh
# simple アルゴリズムを強制
$ ./push_swap --simple 5 4 3 2 1

# bench モードで disorder・戦略・命令数の内訳を確認
$ ./push_swap --bench --adaptive 4 67 3 87 23 2>&1 1>/dev/null
[bench] disorder:  40.00%
[bench] strategy:  Adaptive / O(n²)
[bench] total_ops: 11
[bench] sa: 0  sb: 0  ss: 0  pa: 3  pb: 3
[bench] ra: 4  rb: 0  rr: 0  rra: 1  rrb: 0  rrr: 0
```

disorder は 40% で本来なら Medium 相当の区間ですが、要素数が5（6以下）のため n≤6 の例外処理で強制的に Simple が選ばれています（詳細は後述）。

### エラー処理

以下のような不正な入力に対しては、標準エラーに `Error` を出力します。

- 整数として解釈できない引数（文字列、空文字列、空白のみなど）
- `int` の範囲（`-2147483648` 〜 `2147483647`）を超える値
- 重複した値

```sh
$ ./push_swap 3 2 3
Error
$ ./push_swap ""
Error
```

### Bonus（checker）について

現時点では、自作の `checker` プログラム（bonus 部分）は未実装です。動作確認には、42 から配布された `checker_linux` バイナリを使用しています。

```sh
$ ./push_swap 3 2 1 0 | ./checker_linux 3 2 1 0
OK
```

## アルゴリズムの説明と選定理由

本プロジェクトでは、課題の要求どおり4種類のソート戦略をすべて1つのバイナリに実装し、`--simple` / `--medium` / `--complex` / `--adaptive` で切り替えられるようにしています。計算量は、実際に**生成される push_swap 命令の数**を基準に評価しています（C側の内部計算だけで完結し、命令を1つも生成しない処理はここには含めません）。

なお、Simple / Medium / Complexの各アルゴリズムは処理開始時に `is_sorted` で「スタック `a` がすでに昇順に並んでいるか」を判定し、並んでいる場合は命令を一切生成せずに即座に終了します。これは課題の「the program must display the smallest list of Push_swap operations possible」という要件（すでにソート済みの入力に対しては0命令が最小）を満たすためです。

### Simple algorithm — O(n²)（選択ソートの応用）

`simple_algorithm.c`

スタック `a` の中から最小値を探し（`find_min_index`）、`ra` / `rra` で最小値を先頭に回転させてから `pb` で `b` へ積む、という操作を要素数-2回繰り返します。最後に残った2要素を必要なら `sa` で整列し、`b` に積んだ要素を先頭から順に `pa` で `a` へ戻します。

「最小値を探す（O(n)）→ 先頭に回転（最大O(n)）」をn回繰り返すため、生成される命令数は O(n²) になります。

### Medium algorithm — O(n√n)（チャンク分割）

`chunk_utils.c`（`chunk_size` / `bring_chunk`）、`medium_algorithm.c`（`chunk_rank` / `pull_from_b`）

1. `chunk_rank` で各要素に「自分より小さい要素がいくつあるか」という順位（rank）を付与します。
2. `chunk_size` で `√n` に相当するチャンクサイズを決定します。
3. `bring_chunk` で、rank の値が小さいチャンクから順に `b` へ積んでいきます（回転方向は要素の位置に応じて `ra` / `rra` を使い分け、移動距離を最小化します）。
4. `pull_from_b` で、`b` の中から常に最大の rank を持つ要素を選んで `a` へ戻します。

`√n` 個のチャンクをそれぞれ O(n) の操作で処理するため、生成される命令数は O(n√n) になります（rank 付け自体は命令を生成しない C 内部の計算です）。

### Complex algorithm — O(n log n)（基数ソートの応用）

`complex_algorithm.c`

1. `chunk_rank` で各要素に rank（0〜n-1 の順位）を付与します。
2. rank を2進数として見て、下位ビットから順に「そのビットが1なら `ra` で待避、0なら `pb` で `b` へ積む」という処理を行い（`radix_pass`）、各ビットの処理後に `b` の中身をすべて `pa` で `a` に戻します。
3. これを rank を表現するのに必要なビット数（`bit_size(n)`、およそ `log2(n)`）回繰り返します。

LSD 基数ソートと同じ考え方で、1回のビット処理が O(n)、それを `log2(n)` 回繰り返すため、生成される命令数は O(n log n) になります。

### Adaptive algorithm — 学習者独自設計

`ft_adaptive.c`

上記3つの戦略は、課題が要求する複雑さクラスをそれぞれ厳密に満たしています。Adaptive アルゴリズムは、この3つを **disorder の値に応じて呼び分けるディスパッチャ**として実装しました。

```
disorder < 0.2        → Simple  （O(n²)）
0.2 ≤ disorder < 0.5   → Medium  （O(n√n)）
disorder ≥ 0.5         → Complex（O(n log n)）
```

**なぜこの区間にこのアルゴリズムなのか（選定理由）**

閾値 0.2 / 0.5 は課題（VI.3.3-4）が各 disorder 区間に課す計算量目標の境界値であり、その値をそのまま採用しています。そのうえで、各区間にどの戦略を割り当てるかは以下の理由で決定しました。

- **disorder < 0.2 → Simple（O(n²)）**
  ほぼ整列済みの入力では、各要素が本来の位置の近くに存在します。最小値抽出＋近い方向への回転（`ra` / `rra` の使い分け）は、わずかな回転で要素を所定位置へ運べるため、O(n²) クラスでも実際に生成される命令数は小さく収まります。実装が単純で1要素あたりの無駄な命令が少なく、この領域では基数ソートの固定オーバーヘッド（全ビット走査）よりも軽量に済みます。
- **0.2 ≤ disorder < 0.5 → Medium（O(n√n)）**
  中程度に乱れた入力では、O(n²) は命令数が増えすぎる一方、基数ソートのオーバーヘッドはまだ見合いません。`√n` チャンク分割は「`b` へ退避 → `b` から戻す」の2段階で命令数を O(n√n) に抑えられ、実装の単純さと性能のバランスが取れた中間解になります。
- **disorder ≥ 0.5 → Complex（O(n log n)）**
  完全ランダムに近い入力では O(n²)・O(n√n) は命令数が急増します。基数ソートは命令数の増加が最も緩やかで、乱雑度に依らず `log₂(n)` パスで確実にソートできるため、この領域で最良の選択になります。

各分岐が呼び出す Simple / Medium / Complex は上記の通りそれぞれ独立に O(n²) / O(n√n) / O(n log n) を満たすため、disorder に応じてこの3つを振り分けるだけで、課題が要求する「disorder の区間ごとの計算量目標」を自動的に満たす設計になっています。

**要素数が少ない場合（n ≤ 6）の例外処理**

`main.c`（`build_stack`）で、スタックの要素数が6以下のときはdisorderの値にかかわらず強制的にSimpleを選択します。

```c
if (stack_size(ctx->a) <= 6)
	ctx->dis_flg = 1;
```

- disorderが高くても（≥0.5でも）、この場合はSimpleが選ばれます。
- **理由**: Simpleは入力サイズにかかわらず常に正しくソートできるため、disorderを無視しても正当性は損なわれません。一方Medium/Complexはチャンク分割や複数回のビット走査といった固定オーバーヘッドを持つため、nが小さいとその固定コストがSimpleのO(n²)実コストを上回ってしまい、かえって命令数が増えます。
- n≤6という閾値は、Simpleの最悪計算量O(n²)（最大36回程度の走査・回転）が、Medium/Complexの固定オーバーヘッドより明らかに小さく収まる範囲として設定しました。

**計算量（Push_swap モデルにおける upper bound）**

| 区間                  | 内部手法                   | 時間（生成命令数） | 空間                               |
| --------------------- | -------------------------- | ------------------ | ---------------------------------- |
| disorder < 0.2        | Simple（選択ソート）       | O(n²)             | O(1)（スタックのポインタ操作のみ） |
| 0.2 ≤ disorder < 0.5 | Medium（√n チャンク分割） | O(n√n)            | O(1)                               |
| disorder ≥ 0.5       | Complex（LSD 基数ソート）  | O(n log n)         | O(1)                               |

いずれの戦略も、既存のスタック（連結リスト）を直接操作するのみで、要素数に比例した追加バッファは確保していません。

### Disorder（乱雑度）の計算

`ft_disoder.c`

課題定義どおり、「全ペアのうち、大小関係が逆転しているペアの割合」を disorder としています。

```
disorder = (逆転しているペアの数) / (全ペアの数)
```

素朴に実装すると全ペア総当たりで O(n²) になりますが、本実装ではマージソートを応用した「転倒数（inversion count）」の計算（`calculate_disorder_fast`）を用いており、O(n log n) で同じ値を求めています。この計算は、いかなる push_swap 命令も実行する前（ソート処理に入る前）に行われます。

## Contributors

本プロジェクトは 2 名（tfujikaw, htakumi）による共同作業です。両名が要件定義・実装・デバッグ・動作確認のすべての工程に関わり、以下のような形で協力して開発を進めました。

- スタック操作命令（`sa` / `sb` / `ss` / `pa` / `pb` / `ra` / `rb` / `rr` / `rra` / `rrb` / `rrr`）の実装（tfujikaw）
- Simple / Medium / Complex / Adaptive の4アルゴリズムの設計・実装（tfujikaw, htakumi）
- Disorder（乱雑度）計算ロジックの実装（tfujikaw, htakumi）
- 引数パース・エラーハンドリングの実装（tfujikaw, htakumi）
- ベンチマーク機能（`--bench`）の実装（tfujikaw）
- 上記すべての動作確認・デバッグ（htakumi）

両名とも、実装したすべての機能について説明・弁明できる状態にあります。

## Resources

### 参考資料

- [選択ソート](https://e-words.jp/w/選択ソート.html)
- [選択ソート](https://www.codereading.com/algo_and_ds/algo/selection_sort.html)
- [チャンク分割ソート](https://qiita.com/MoriP-K/items/54ee96dc634148cf40a8)
- [基数ソート](https://tukumolog.com/radix-sort-introduction/)
- [基数ソート](https://e-words.jp/w/基数ソート.html)
- [基数ソート](https://www.hello-algo.com/ja/chapter_sorting/radix_sort/#11102)
- [Big-O notation — Wikipedia](https://en.wikipedia.org/wiki/Big_O_notation)
- [Radix sort — Wikipedia](https://en.wikipedia.org/wiki/Radix_sort)
- [Inversion (discrete mathematics) — Wikipedia](https://en.wikipedia.org/wiki/Inversion_(discrete_mathematics))（転倒数・disorder の計算根拠）
- [Selection sort — Wikipedia](https://en.wikipedia.org/wiki/Selection_sort)

### AI の利用について

- AIを使用する際は直接的なコードは書かせずに、段階的なヒントをもとに実装いたしました。
- **課題仕様との照合**: 課題PDFの要求事項と実装を突き合わせ、README.md の未作成やbonus未実装といった不足点を洗い出し
- **本 README.md のドラフト作成**: 上記の照合結果と実装内容をもとに、課題が要求する構成（Description / Instructions / Resources 等）でのドラフト作成

いずれの提案も、学習者自身がコードを読んで内容を理解した上で採用しています。
