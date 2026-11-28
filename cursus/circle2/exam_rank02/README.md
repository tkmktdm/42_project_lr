# Exam Rank 02 対策

## 試験の形式（一般的な形）

### 当日の流れ

1. intra で**事前に登録**しておく（登録していないと受けられない）
2. 開始10分ほど前から受付。**遅刻すると受けられない**ことがある
3. 試験用アカウントでログインする（ユーザー名・パスワードとも `exam` という例が多い。画面の案内に従う）
   - 自分の intra アカウントでログインしないこと
4. ターミナルで `examshell` を起動し、intra のログイン名とパスワードを入力する
   - 開始から10分以内に起動するよう指示がある
5. 制限時間は **3時間**

### ディレクトリと提出

```
~/subjects/<問題名>/   ← 問題文（subject.en.txt など）
~/rendu/               ← 提出用の git リポジトリ
```

```bash
mkdir -p ~/rendu/first_word
vim ~/rendu/first_word/first_word.c
cd ~/rendu
git add . && git commit -m "first_word" && git push   # ← push を忘れない
# examshell の画面に戻って
grademe
```

- examshell の中ではいくつかのコマンドしか使えない（`grademe` など）。ファイルの編集や git 操作は**別のターミナル**で行う
- `grademe` を実行すると自動採点され、数十秒〜数分で結果が出る

### 出題と採点

- Level 1 → 2 → 3 → 4 の順に、**1問ずつランダム**に出題される
- 正解すると次のレベルへ進む（1レベル約25点。Level 4 までクリアすれば 100 点）
- **4問すべてクリアで合格**という体験記が多い（42Tokyo での最新の扱いは確認すること）
- 不正解でも点数は減らないが、同じレベルの**別の問題**が出ることが多い。
  次に提出できるまでの**待ち時間が失敗するたびに延びる**ので、何度も落とすと時間切れになる

### 環境の制約

- **インターネット、自分のメモ、AI 補完は使えない**。`man` は使えることが多い
- エディタは vim / emacs。**VS Code は使えない**ので vim の基本操作に慣れておく
- Norminette のチェックはない。ただし **`-Wall -Wextra -Werror` で通らないと0点**
- 使える関数は問題ごとに `Allowed functions` で指定される（主に `write`、`malloc`、`free`）
- 「program」問題は `main` を書く。「function」問題は関数だけ提出（main は書かない）

### 問題文の言語

- 本科の Exam Rank 02 で **日本語の問題文が用意されているという情報は見つからなかった**。
  英語で出る前提で準備するのが安全（examshell の練習ツールには英語・フランス語の切り替えしかない）
- 試験ガイドが英語だったという 42Tokyo の体験記はある
- 手元の `piscine/exam03/LastExamSubjects_JP` は非公式に配布された訳で、問題の中身も本科の Rank 02 とは違う
  （fizzbuzz の倍数が 4 と 7 になっているなど）。日本語の問題文がある根拠にはならない
- 不安なら 42Tokyo の Slack やスタッフに「Rank 02 の問題文に日本語版はあるか」を聞いてみるとよい
- **英語を読まずに解くための暗記表は [cheatsheet_ja.md](cheatsheet_ja.md)**（まずはこれ）
- 全問題の例外条件の英文と日本語訳は [exceptions_en_ja.md](exceptions_en_ja.md) にまとめてある

#### subject でよく出る英語

| 英語 | 意味 |
|------|------|
| `Assignment name` / `Expected files` | 問題名 / 提出するファイル名 |
| `Allowed functions` | 使ってよい関数（ここにない関数は使えない） |
| `Write a program that ...` | main を含むプログラムを書く |
| `Write a function that ...` / `Your function must be declared as follows:` | 関数だけを書く / プロトタイプの指定 |
| `If the number of arguments is not 1, display a newline.` | 引数が1個でなければ改行だけを出力する |
| `followed by a newline` | 最後に改行を出力する |
| `A word is a section of string delimited by spaces/tabs or by the start/end of the string.` | 単語は空白・タブ・文字列の端で区切られた部分 |
| `display` / `return` | 出力する / 戻り値で返す |
| `in the order they appear` / `without doubles` | 出てきた順に / 重複なしで |
| `You don't have to handle ...` / `will not be tested` | …には対応しなくてよい / テストされない |
| `ascending order` / `descending order` | 昇順 / 降順 |
| `the string will only contain lowercase letters` | 小文字だけが渡される |
| `reversed` / `consecutive` / `leading` / `trailing` | 逆順 / 連続した / 先頭の / 末尾の |

### 本番で落ちやすいところ

- ファイル名・ディレクトリ名のタイポ（`rendu/ft_strlen/ft_strlen.c` の形になっているか）
- `git push` を忘れたまま `grademe` する
- 関数問題で `main` を残したまま提出する
- 引数の数が違うとき・空文字列を渡したときの処理が抜けている

### 練習ツール

本番の examshell を再現したツールで、同じ流れで練習しておくと当日あわてない。

- [terminal-42s/42_examshell](https://github.com/terminal-42s/42_examshell)

### 参考

- [42 Tokyoの校舎へ。「Exam Rank 02」をクリア（2022年の体験記）](https://note.com/hovinci/n/n2eba3b7769a6)

> ⚠ 問題セットはキャンパスや時期によって変わることがあります。最新の内容は
> 42Tokyo の intra や Slack で、直前に受けた人に確認してください。

## 出題範囲（よく知られている問題セット）

| Level | 問題 |
|-------|------|
| 1 | first_word, fizzbuzz, ft_putstr, ft_strcpy, ft_strlen, ft_swap, repeat_alpha, rev_print, rot_13, rotone, search_and_replace, ulstr |
| 2 | alpha_mirror, camel_to_snake, do_op, ft_atoi, ft_strcmp, ft_strcspn, ft_strdup, ft_strpbrk, ft_strrev, ft_strspn, inter, is_power_of_2, last_word, max, print_bits, reverse_bits, snake_to_camel, swap_bits, union, wdmatch |
| 3 | add_prime_sum, epur_str, expand_str, ft_atoi_base, ft_list_size, ft_range, ft_rrange, hidenp, lcm, paramsum, pgcd, print_hex, rstr_capitalizer, str_capitalizer, tab_mult |
| 4 | flood_fill, fprime, ft_itoa, ft_list_foreach, ft_list_remove_if, ft_split, rev_wrd, rostring, sort_int_tab, sort_list |

解答: [level1.md](level1.md) / [level2.md](level2.md) / [level3.md](level3.md) / [level4.md](level4.md)

## 共通の注意（ここで落ちる人が多い）

1. **program 問題で引数の数が違うときは `\n` だけ出力する**（ほぼ全問共通）
2. 出力の最後の `\n` を忘れない
3. 関数問題に `main` を残したまま提出しない
4. ファイル名・関数名・ディレクトリ名は1文字でも違うと0点
5. 練習するときは毎回 `cc -Wall -Wextra -Werror` でコンパイルし、空文字列 `""`・引数なし・引数が多すぎる場合を必ず試す
