# 例外条件の英文と日本語訳

問題の中身は分かっている前提で、**英語の subject のどこに例外条件が書いてあるか、何と書いてあるか**だけをまとめた。

> 英文は subject によくある言い回しを要約して再構成したもの。本番の文と一字一句同じではない。
> 本番では、ここにある**キーワード**が文中にあるかを探す読み方をする。

---

## 英語が読めなくても詰まないための読み方

1. **まず `Examples:` を見る**
   - subject の最後には必ず実行例がある。`cat -e` の `$` は改行
   - `./prog | cat -e` → `$` だけ、という例があれば「引数が違うときは改行だけ出す」という意味
   - 例外の大半は Examples を見れば分かる
2. **次に `Allowed functions` と `Expected files` を見る**（使える関数と提出ファイル名）
3. **本文では次の単語だけを探す**

| 探す単語 | 意味 | どう扱うか |
|----------|------|-----------|
| `not 1` / `not 2` / `is different from` / `incorrect` | 引数の数が違うとき | 多くの場合「改行だけ出す」 |
| `newline` / `\n` / `followed by` | 改行 | 最後に `\n` を付ける |
| `in the order` | 出てくる順番 | 並び順を変えない |
| `without doubles` / `no duplicates` | 重複なし | 同じ文字は1回だけ出す |
| `Doubles must be preserved` / `Duplications must remain` | 重複は残す | 同じ値を消さない |
| `null` | **0 のこと**（NULL ポインタではない） | lcm などで出てくる |
| `strictly positive` | 0 を含まない正の数 | 1 以上 |
| `positive (or zero)` | 0 以上 | |
| `in-place` | 新しく確保せず、渡された配列そのものを書き換える | malloc しない |
| `case remains unchanged` / `unaffected` | 大文字・小文字はそのまま | |
| `if it's a letter` | 文字がアルファベットのときだけ | 数字・記号は変えない |
| `will not be tested` / `You don't have to handle` / `will always be valid` / `Input is always coherent` | そのケースはテストされない | 対応しなくてよい |
| `Reproduce (exactly) the behavior of ...` | 標準関数と同じ動きにする | `man` で確認できる |

---

## Level 1

**first_word**
- `If the number of parameters is not 1, the program displays a newline.`
  → 引数が1個でなければ改行だけを出す
- `A "word" is defined as a part of a string delimited either by spaces/tabs, or by the start/end of the string.`
  → 単語はスペースかタブ、または文字列の端で区切られた部分（**タブも区切り文字**）

**fizzbuzz**
- `If the number is a multiple of 3, it prints 'fizz' instead. If ... a multiple of 5, 'buzz'. If ... both 3 and 5, 'fizzbuzz'.`
  → 倍数の数字が問題によって違うことがあるので、3 と 5 かどうかを必ず確認する

**ft_putstr / ft_strlen / ft_swap** — 例外なし

**ft_strcpy**
- `Reproduce the behavior of the function strcpy (man strcpy).`
  → strcpy と同じ動き。戻り値は s1

**repeat_alpha**
- `'a' becomes 'a', 'b' becomes 'bb', 'e' becomes 'eeeee', etc...`
- `Case remains unchanged.` → 大文字・小文字はそのまま
- `If the number of arguments is not 1, just display a newline.`

**rev_print / ulstr**
- `If the number of arguments is not 1, display a newline.`

**rot_13 / rotone**
- `'z' becomes 'm' and 'Z' becomes 'M'. Case remains unaffected.`（rotone は `'z' becomes 'a'`）
  → 端で一周する。大文字・小文字はそのまま
- `If the number of arguments is not 1, just display a newline.`

**search_and_replace**
- `If the number of arguments is not 3, just display a newline.`
- `If the second argument is not contained in the first one (the string) then the program simply rewrites the string followed by a newline.`
  → 置き換える文字が見つからなければ、文字列をそのまま出す
- Examples に `"zaz" "art" "zul"` → `$` がある
  → 2番目か3番目が**1文字でなければ**改行だけを出す（本文ではなく Examples で分かる例外）

---

## Level 2

**alpha_mirror**
- `'a' becomes 'z', 'Z' becomes 'A', 'd' becomes 'w', 'M' becomes 'N'`
- `The case is not changed.` / `If the number of arguments is not 1, display only a newline.`

**camel_to_snake / snake_to_camel**
- `takes a single string in lowerCamelCase format and converts it into snake_case format.`
  → 入力は正しい形式のものだけが来る
- `If the number of arguments is not 1, display a newline.`

**do_op**
- `If the number of parameters is incorrect, the program just displays a newline.`
- `You can assume the string have no mistakes or extraneous characters.` → 入力は正しいと考えてよい
- `Negative numbers, in input or output, will have one and only one leading '-'.` → 負の数の `-` は1個だけ
- `The result of the operation fits in an int.` → オーバーフローは考えなくてよい

**ft_atoi**
- `It works much like the standard atoi(const char *str) function, see the man.`
  → 先頭の空白を飛ばす、符号は1個まで、数字以外が来たら止める

**ft_strcmp / ft_strcspn / ft_strspn / ft_strpbrk / ft_strdup**
- `Reproduce exactly the behavior of the function ...`
  → 標準関数と同じ動き。本番で `man strcspn` などを見て確認できる

**ft_strrev**
- `reverses (in-place) a string. It must return its parameter.`
  → 新しく確保せずにその場で反転し、受け取った str を返す

**inter**
- `display, without doubles, the characters that appear in both strings, in the order they appear in the first one.`
  → 両方にある文字を、**1つ目の文字列での順番**で、重複なしに出す
- `If the number of arguments is not 2, the program displays \n.`

**union**
- `display, without doubles, the characters that appear in either one of the strings.`
  → どちらか一方にでもある文字を、重複なしに出す
- `The display will be in the order characters appear in the command line` → 1つ目→2つ目の順
- `If the number of arguments is not 2, the program displays \n.`

**wdmatch**
- `checks whether it is possible to write the first string with characters from the second string, while respecting the order`
- `If it's possible, the program displays the string, followed by a \n, otherwise it simply displays a \n.`
  → できなければ改行だけ。引数が2個でないときも改行だけ

**is_power_of_2**
- `returns 1 if its input is a power of 2, otherwise it returns 0.` → 0 は 2 のべき乗ではない

**last_word**
- first_word と同じ。末尾に空白があってもよい

**max**
- `If the array is empty, the function returns 0.` → **len が 0 なら 0 を返す**

**print_bits**
- `prints the binary representation of a byte, without a newline at the end.`
  → **最後に改行を付けない**

**reverse_bits / swap_bits**
- `reverses it, bit by bit` / `swaps its halves`
  → どちらも Examples の図（`0100 | 0001` → `0001 | 0100` など）を見るのが一番早い

---

## Level 3

**add_prime_sum**
- `If the number of arguments is not 1, or the argument is not a positive number, just display 0 followed by a newline.`
  → 引数が違う、または正の数でないときは **`0` を出す**（改行だけではない）

**epur_str**
- `displays this string with exactly one space between words, with no spaces or tabs either at the beginning or the end, followed by a \n.`
  → 単語の間はスペース1個、先頭と末尾には空白を出さない
- `If the number of arguments is not 1, or if there are no words to display, the program displays \n.`

**expand_str**
- epur_str と同じで、`exactly three spaces between each word`（単語の間はスペース3個）

**ft_atoi_base**
- `base can't be over 16` / `digits: 0123456789abcdef (and uppercase ABCDEF)`
  → 基数は16まで。大文字も受け付ける
- `Minus sign ('-') is interpreted only if it is the first character of the string.`
  → `-` は先頭にあるときだけ有効

**ft_range / ft_rrange**
- `fill it with consecutive values that begin at start and end at end (Including start and end !)`
  → start と end を**両方含む**
- rrange は `begin at end and end at start` → 向きが逆（ここが一番の引っかけ）

**hidenp**
- `s1 is hidden in s2 if it's possible to find each character from s1 in s2, in the same order`
- `Also, the empty string is hidden in any string.` → **空文字列は必ず `1`**
- `If the number of parameters is not 2, the program displays a newline.`

**lcm**
- `If either a or b is null, lcm is equal to 0.`
  → ここの **null は「0」**の意味。a か b が 0 なら 0 を返す

**paramsum**
- `displays the number of arguments passed to it` → 引数なしなら `0`

**pgcd**
- `two strings representing two strictly positive integers that fit in an int.`
  → 1 以上の数だけが渡される
- `If the number of parameters is not 2, display a newline.`

**print_hex**
- `takes a positive (or zero) number expressed in base 10, and displays it in base 16 (lowercase letters)`
  → 0 も来るので `0` を出せるようにする。**小文字**で出す
- `If the number of parameters is not 1, the program displays a newline.`

**str_capitalizer / rstr_capitalizer**
- `takes one or more strings and, for each argument, puts the first (rstr: last) character of each word (if it's a letter) in uppercase and the rest in lowercase, then displays the result followed by a \n.`
  → **引数は複数来る**。1つ出すごとに改行。アルファベットでなければそのまま
- `If there are no parameters, display \n.`

**tab_mult**
- `The parameter will always be a strictly positive number that fits in an int, and said number times 9 will also fit in an int.`
  → 入力のチェックは不要
- `If there are no parameters, the program displays \n.`

---

## Level 4

**flood_fill**
- `A zone is a group of the same characters delimitated horizontally and vertically by other characters or the array boundary.`
- `The flood_fill function won't fill diagonally.` → **斜めには塗らない**
- 塗る文字は `'F'`

**fprime**
- `displays its prime factors ... in ascending order and separated by '*'`
  → 小さい順に、`*` でつなぐ
- `If the number of parameters is not 1, the program displays a newline.`
- `The input, when there is one, will be valid.` → 入力のチェックは不要

**ft_itoa**
- `converts the integer to a null-terminated string` → **INT_MIN も渡される**と考えておく

**ft_list_foreach**
- `applies a function given as argument to the information within each of the list's elements.` → 各 data に f を適用する

**ft_list_remove_if**
- `removes from the passed list any element the data of which is "equal" to the reference data.`
- `cmp takes two void* and returns 0 when both parameters are equal.` → **0 が「等しい」**
- 外した要素は free する

**ft_split**
- `A "word" is defined as a part of a string delimited either by spaces/tabs/new lines, or by start/end of the string.`
  → **改行も区切り文字**（first_word などとの違い）
- `returns them as a NULL-terminated array of strings` → 最後の要素は NULL

**rev_wrd**
- `If the number of parameters is different from 1, the program will display '\n'.`
- `there won't be any "additional" spaces` → 余分な空白は来ない（単語の間はいつもスペース1個）

**rostring**
- `rotating it one word to the left. Thus, the first word becomes the last, and others stay in the same order.`
- `Words will be separated by only one space in the output.` → 出力ではスペース1個
- `If there's less than one argument, the program displays \n.`
  → 引数が**2個以上でも1つ目だけを処理**する

**sort_int_tab**
- `sorts (in-place) ... in ascending order. Doubles must be preserved.`
  → その場で昇順に並べる。同じ値は消さない
- `Input is always coherent.` → 入力のチェックは不要

**sort_list**
- `using the function pointer cmp to select the order to apply`
- `cmp always returns a value different from 0 if a and b are correctly ordered, 0 otherwise.`
  → **0 以外が返ったら正しい順番**（ft_list_remove_if の cmp と意味が逆なので注意）
- `Duplications must remain.` → 同じ値を消さない
