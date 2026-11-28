# 暗記表（英語を読まずに解くため）

## 本番での読み方

英語の本文は読まない。見るのは次の3か所だけ。

```
Assignment name  : first_word        ← ① 問題名。この表で仕様を思い出す
Expected files   : first_word.c      ← ② 提出ファイル名。このとおりに作る
Allowed functions: write             ← ③ 使ってよい関数
--------------------------------------------------------------------------------
（英語の本文 … 読まない）

Examples:                            ← ④ 実行例。ここだけ見て、自分の記憶と合っているか確かめる

$> ./first_word "FOR PONY" | cat -e
FOR$                                 ← $ は改行
$> ./first_word | cat -e
$                                    ← 引数がないと改行だけ
```

**表の内容と実行例が違ったら、実行例のほうを正しいとする**（倍数の数字が違う、などの出題の変化に対応するため）。

## 覚える英単語は4つだけ

| 英語 | 意味 |
|------|------|
| `program` | main を書く問題 |
| `function` | 関数だけ書く問題（main は消して出す） |
| `newline` | 改行 |
| `null` | 0 |

## 表の見方

- **引数NG** の列：引数の数が違うときに出すもの。`\n` は改行だけ、という意味
- 「関数」の行は main を書かない

---

## Level 1

| 問題名 | 種類 | やること | 引数NG | 注意 |
|--------|------|----------|--------|------|
| first_word | program | 最初の単語を出す | `\n` | 区切りはスペースとタブ |
| fizzbuzz | program | 1〜100。3の倍数は fizz、5の倍数は buzz、15の倍数は fizzbuzz | − | 倍数の数字は実行例で確認する |
| ft_putstr | 関数 | 文字列を出力する | − | 改行は付けない |
| ft_strcpy | 関数 | s2 を s1 にコピーして s1 を返す | − | 最後に `\0` を付ける |
| ft_strlen | 関数 | 文字列の長さを返す | − | |
| ft_swap | 関数 | 2つの int を入れ替える | − | |
| repeat_alpha | program | a は1回、b は2回…と文字の順番の回数だけ繰り返す | `\n` | 大文字も同じ。記号はそのまま |
| rev_print | program | 文字列を逆順に出す | `\n` | |
| rot_13 | program | アルファベットを13文字ずらす | `\n` | z の次は a に戻る |
| rotone | program | アルファベットを1文字ずらす | `\n` | z→a、Z→A |
| search_and_replace | program | 文字 A を文字 B に置き換える | `\n` | A か B が2文字以上なら `\n` だけ |
| ulstr | program | 大文字と小文字を入れ替える | `\n` | |

## Level 2

| 問題名 | 種類 | やること | 引数NG | 注意 |
|--------|------|----------|--------|------|
| alpha_mirror | program | a↔z、b↔y のように反対側の文字に変える | `\n` | 大文字も同じ |
| camel_to_snake | program | `helloWorld` → `hello_world` | `\n` | |
| snake_to_camel | program | `hello_world` → `helloWorld` | `\n` | |
| do_op | program | `"1" "+" "2"` → `3`（+ − * / %） | `\n` | printf と atoi が使える |
| ft_atoi | 関数 | 文字列を int に変換する | − | 空白を飛ばす、符号は1個まで |
| ft_strcmp | 関数 | strcmp と同じ | − | |
| ft_strcspn | 関数 | strcspn と同じ | − | `man strcspn` で確認できる |
| ft_strspn | 関数 | strspn と同じ | − | `man strspn` で確認できる |
| ft_strpbrk | 関数 | strpbrk と同じ | − | 見つからなければ NULL |
| ft_strdup | 関数 | strdup と同じ | − | malloc を使う |
| ft_strrev | 関数 | 文字列をその場で逆にして返す | − | malloc しない |
| inter | program | 両方にある文字を、1つ目の順番で重複なしに出す | `\n` | |
| union | program | どちらかにある文字を、1つ目→2つ目の順で重複なしに出す | `\n` | |
| wdmatch | program | 1つ目の文字が2つ目の中に順番どおりあれば、1つ目を出す | `\n` | なければ `\n` だけ |
| is_power_of_2 | 関数 | 2のべき乗なら1、違えば0 | − | 0 は「違う」 |
| last_word | program | 最後の単語を出す | `\n` | 末尾に空白があってもよい |
| max | 関数 | 配列の最大値を返す | − | 長さ0なら0を返す |
| print_bits | 関数 | 8ビットを `00100110` のように出す | − | **改行なし** |
| reverse_bits | 関数 | ビットの並びを逆にして返す | − | |
| swap_bits | 関数 | 上位4ビットと下位4ビットを入れ替えて返す | − | |

## Level 3

| 問題名 | 種類 | やること | 引数NG | 注意 |
|--------|------|----------|--------|------|
| add_prime_sum | program | n 以下の素数の合計を出す | **`0\n`** | 負の数や0でも `0` |
| epur_str | program | 単語の間をスペース1個にする | `\n` | 先頭と末尾に空白を出さない |
| expand_str | program | 単語の間をスペース3個にする | `\n` | 先頭と末尾に空白を出さない |
| ft_atoi_base | 関数 | n進数の文字列を int にする（16進まで） | − | 大文字も可。`-` は先頭だけ |
| ft_list_size | 関数 | リストの要素数を返す | − | |
| ft_range | 関数 | start から end までの配列を malloc して返す | − | 両端を含む |
| ft_rrange | 関数 | **end から start まで**の配列を返す | − | 向きが逆 |
| hidenp | program | 1つ目が2つ目の中に順番どおりあれば `1`、なければ `0` | `\n` | 1つ目が空なら `1` |
| lcm | 関数 | 最小公倍数を返す | − | どちらかが0なら0 |
| paramsum | program | 引数の個数を出す | − | 引数なしなら `0` |
| pgcd | program | 最大公約数を出す | `\n` | printf が使える |
| print_hex | program | 10進の数を16進（小文字）で出す | `\n` | 0 のときは `0` |
| str_capitalizer | program | 各単語の**最初**の文字を大文字、残りを小文字にする | `\n` | 引数が複数来る。1つ出すごとに改行 |
| rstr_capitalizer | program | 各単語の**最後**の文字を大文字、残りを小文字にする | `\n` | 引数が複数来る。1つ出すごとに改行 |
| tab_mult | program | `1 x 9 = 9` 〜 `9 x 9 = 81` の九九を出す | `\n` | |

## Level 4

| 問題名 | 種類 | やること | 引数NG | 注意 |
|--------|------|----------|--------|------|
| flood_fill | 関数 | 開始位置とつながった同じ文字を `F` で塗る | − | 上下左右のみ。`tab[y][x]` |
| fprime | program | 素因数分解して `2*2*3` のように出す | `\n` | 1 のときは `1` |
| ft_itoa | 関数 | int を文字列にして返す | − | INT_MIN に注意 |
| ft_list_foreach | 関数 | リストの各 data に関数 f を使う | − | |
| ft_list_remove_if | 関数 | cmp が **0 を返した**要素を消して free する | − | |
| ft_split | 関数 | 単語に分けて配列にして返す（最後は NULL） | − | 区切りはスペース・タブ・**改行** |
| rev_wrd | program | 単語の順番を逆にする | `\n` | |
| rostring | program | 最初の単語を最後に移す | `\n` | 間はスペース1個。引数が多くても1つ目だけ使う |
| sort_int_tab | 関数 | 配列を小さい順に並べる | − | 同じ値は消さない |
| sort_list | 関数 | cmp を使ってリストを並べ替え、先頭を返す | − | cmp が **0 以外なら正しい順番** |

---

## 練習方法

1. この表の「問題名」だけを見て、残りの列を口で言えるようにする
2. 解答を見ずに level1.md〜level4.md の問題を白紙から書く
3. [練習用 examshell](https://github.com/terminal-42s/42_examshell) で、英語の subject の「問題名・実行例だけ見て解く」練習をする
