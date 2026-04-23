# Rush02 — 数字を英単語に変換するプログラム 詳細解説

## プログラムの全体像

```
./a.out [辞書ファイル] <数字>
./a.out 1234567  →  one million two hundred thirty four thousand five hundred sixty seven
```

辞書ファイル（`numbers.dict`）を読み込み、数字を英語の読み方に変換する。

---

## ファイル構成

```
rush02/htakumi/ex00/
├── rush.h          ← 構造体定義・関数プロトタイプ
├── main.c          ← エントリーポイント・引数チェック
├── dict.c          ← 辞書ファイルの読み込み・解放
├── ft_split.c      ← 文字列を区切り文字で分割
├── lookup.c        ← 辞書の検索・単位の出力
├── convert.c       ← 変換メイン処理
├── convert_sub.c   ← 変換サブ処理（一の位・十の位・百の位）
├── output.c        ← 出力ユーティリティ・グループ分割
└── numbers.dict    ← 辞書データ
```

---

## rush.h — 構造体定義

```c
#ifndef RUSH_H          // RUSH_H が未定義なら以下を有効にする（二重インクルード防止）
# define RUSH_H         // RUSH_H を定義する

typedef struct s_entry  // キーと値のペアを表す構造体
{
    char  *key;         // 辞書のキー（例: "1000"）
    char  *value;       // 辞書の値（例: "thousand"）
}           t_entry;    // 型名を t_entry として使えるようにする

typedef struct s_dict   // 辞書全体を表す構造体
{
    t_entry  *entries;  // エントリ（キー・値ペア）の配列
    int       size;     // エントリの数
    char    **lines;    // ft_split で分割した生の行データ（free用に保持）
}           t_dict;     // 型名を t_dict として使えるようにする

#endif
```

**なぜ `lines` を持つか？**
`ft_split` で分割した文字列のポインタ配列は `free` が必要。
`entries[i].key` はその中のアドレスを指しているだけなので、
`lines` を別途保持してまとめて解放できるようにしている。

---

## main.c — エントリーポイント

### `is_number(char *str)` — 数字文字列か判定

```c
int  is_number(char *str)
{
    int  i;

    i = 0;
    if (str[0] == '\0')     // 空文字列なら数字ではない → 0を返す
        return (0);
    while (str[i] != '\0')  // 文字列の末尾まで繰り返す
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
            // '0'〜'9' 以外の文字があれば数字ではない
            return (0);
        i++;                // 次の文字へ
    }
    return (1);             // 全文字が数字 → 1（true）を返す
}
```

**ポイント:** `'0' <= c <= '9'` で ASCII 範囲チェック。`isdigit()` は使わず自前実装。

---

### `run_convert(char *dict_path, char *num_str)` — 変換の実行

```c
static int  run_convert(char *dict_path, char *num_str)
{
    t_dict  *dict;

    dict = load_dict(dict_path);    // 辞書ファイルを読み込む
    if (!dict)                      // 読み込み失敗なら
        return (dict_error());      // "Dict Error\n" を出力して 1 を返す
    if (convert(num_str, dict))     // 変換実行。失敗（返り値1）なら
    {
        free_dict(dict);            // メモリを解放して
        return (dict_error());      // "Dict Error\n" を出力して 1 を返す
    }
    free_dict(dict);                // 正常終了でもメモリを解放
    return (0);                     // 成功 → 0 を返す
}
```

---

### `main(int argc, char *argv[])` — 引数処理

```c
int  main(int argc, char *argv[])
{
    if (argc == 2 && is_number(argv[1]))
        // 引数1つ（数字のみ）の場合 → デフォルト辞書を使う
        return (run_convert("numbers.dict", argv[1]));
    if (argc == 3 && is_number(argv[2]))
        // 引数2つ（辞書ファイルパス + 数字）の場合
        return (run_convert(argv[1], argv[2]));
    return (put_error());           // それ以外 → "Error\n" を出力して 1 を返す
}
```

**使い方まとめ:**
| コマンド | argc | argv[1] | argv[2] |
|---------|------|---------|---------|
| `./a.out 42` | 2 | "42" | - |
| `./a.out numbers.dict 42` | 3 | "numbers.dict" | "42" |

---

## output.c — 出力ユーティリティ

### `put_error()` — 引数エラー出力

```c
int  put_error(void)
{
    write(2, "Error\n", 6);  // stderr（fd=2）に "Error\n"（6バイト）を書く
    return (1);              // エラーコード 1 を返す
}
```

**なぜ fd=2 か？** fd=1 は stdout（標準出力）、fd=2 は stderr（標準エラー出力）。
エラーメッセージは stderr に出すのが慣習。

---

### `dict_error()` — 辞書エラー出力

```c
int  dict_error(void)
{
    write(2, "Dict Error\n", 11);  // stderr に "Dict Error\n"（11バイト）を書く
    return (1);                   // エラーコード 1 を返す
}
```

---

### `ft_strlen(char *str)` — 文字列長を計算

```c
int  ft_strlen(char *str)
{
    int  i;

    i = 0;
    while (str[i] != '\0')  // ヌル終端まで進む
        i++;
    return (i);             // カウントした文字数を返す
}
```

---

### `ft_putstr(char *str)` — 文字列出力

```c
void  ft_putstr(char *str)
{
    int  n;

    if (!str)                        // NULL ポインタなら
    {
        write(2, "Dict Error", 10);  // エラーメッセージを出力
        return ;
    }
    n = ft_strlen(str);              // 文字列長を計算
    write(1, str, n);                // stdout に n バイト書く
}
```

---

### `split_groups(char *num_str, char groups[][4])` — 数字を3桁ずつに分割

数字を後ろから3桁ずつグループに切り出す関数。

```c
int  split_groups(char *num_str, char groups[][4])
{
    int  len;    // 現在処理中の文字列の長さ
    int  i;      // 右端からの位置
    int  start;  // 今のグループの開始位置
    int  j;      // グループのインデックス

    len = ft_strlen(num_str);  // 例: "1234567" → len = 7
    i = len;                   // i = 7（末尾から始める）
    j = 0;                     // グループ0から始める
    while (i > 0)
    {
        start = 0;
        if (i >= 3)
            start = i - 3;     // 3桁以上残っている → 3桁前から
        // 例1: i=7 → start=4（"567"）
        // 例2: i=4 → start=1（"234"）
        // 例3: i=1 → start=0（"1"）
        len = 0;
        while (len < i - start)               // グループ内の文字をコピー
        {
            groups[j][len] = num_str[start + len];
            len++;
        }
        groups[j][len] = '\0';  // ヌル終端を追加
        j++;                    // 次のグループへ
        i = start;              // 次のループで残りを処理
    }
    return (j);                 // グループ数を返す
}
```

**具体例: "1234567" の場合**
```
groups[0] = "567"  ← 一の位グループ（ones）
groups[1] = "234"  ← 千の位グループ（thousands）
groups[2] = "1"    ← 百万の位グループ（millions）
戻り値: 3（グループ数）
```

**なぜ逆順か？** 単位（thousand, million…）のインデックスと対応させるため。
`groups[0]` = 単位なし、`groups[1]` = thousand、`groups[2]` = million…

---

## ft_split.c — 文字列分割

### `is_separator(char c, char *charset)` — 区切り文字か判定

```c
int  is_separator(char c, char *charset)
{
    int  i;

    i = 0;
    while (charset[i])          // charset の全文字を確認
    {
        if (c == charset[i])    // c が charset 内にあれば
            return (1);         // 区切り文字 → 1（true）
        i++;
    }
    return (0);                 // 区切り文字ではない → 0（false）
}
```

---

### `get_count(char *str, char *charset)` — 単語数を数える

```c
int  get_count(char *str, char *charset)
{
    int  word_count;
    int  i;

    i = 0;
    word_count = 0;
    while (str[i] != '\0')
    {
        if (!is_separator(str[i], charset)         // 現在の文字が区切りでなく
            && (i == 0 || is_separator(str[i - 1], charset)))
            // かつ（先頭 OR 前の文字が区切り）のとき
            word_count++;  // 新しい単語の始まり → カウント
        i++;
    }
    return (word_count);
}
```

**具体例: `"hello world"` を `" "` で分割**
- i=0: 'h' は区切りでない＋先頭 → `word_count=1`
- i=5: ' ' は区切り → スキップ
- i=6: 'w' は区切りでない＋前が区切り → `word_count=2`

---

### `get_word_size(char *str, char *charset)` — 各単語の長さを取得

```c
int  *get_word_size(char *str, char *charset)
{
    int  index;
    int  i;
    int  word_count;
    int  *word_size;

    i = 0;
    word_count = get_count(str, charset);
    word_size = malloc(sizeof(int) * word_count);  // 単語数分の int 配列を確保
    while (i < word_count)          // 全要素を 0 で初期化
    {
        word_size[i] = 0;
        i++;
    }
    i = 0;
    index = 0;
    while (str[i] != '\0')
    {
        if (!is_separator(str[i], charset))
            word_size[index]++;         // 区切りでない → 現在の単語の長さ++
        else if (i > 0 && !is_separator(str[i - 1], charset))
            index++;                    // 区切り文字に入った → 次の単語へ
        i++;
    }
    return (word_size);
}
```

---

### `fill_words(char **words, ...)` — 単語を実際にコピー

```c
static void  fill_words(char **words, char *str, char *charset, int *word_size)
{
    int  index;      // 今何番目の単語か
    int  i;          // str 上の位置
    int  j;          // words[index] 上の書き込み位置
    int  is_new_word;

    index = 0;
    j = 0;
    i = -1;
    while (str[++i] != '\0')              // i を前置インクリメントして進む
    {
        if (!is_separator(str[i], charset))
        {
            is_new_word = (i == 0 || is_separator(str[i - 1], charset));
            if (is_new_word)
                // 新しい単語の先頭 → そのぶんのメモリを確保
                words[index] = malloc(sizeof(char) * (word_size[index] + 1));
            words[index][j] = str[i];    // 文字をコピー
            words[index][++j] = '\0';    // ヌル終端を更新（次の位置に先書き）
        }
        else if (i > 0 && !is_separator(str[i - 1], charset) && ++index)
            // 区切りに入った（前が非区切り）→ 次の単語へ
            j = 0;                       // 書き込み位置リセット
    }
}
```

---

### `ft_split(char *str, char *charset)` — メイン関数

```c
char  **ft_split(char *str, char *charset)
{
    char  **words;
    int    *word_size;

    // 単語数+1 個分のポインタ配列を確保（最後に NULL を入れるための +1）
    words = malloc(sizeof(char *) * (get_count(str, charset) + 1));
    word_size = get_word_size(str, charset);  // 各単語の長さを取得
    fill_words(words, str, charset, word_size);  // 実際にコピー
    words[get_count(str, charset)] = 0;  // 末尾に NULL を入れる
    free(word_size);                     // サイズ配列は不要になったので解放
    return (words);                      // 単語配列を返す
}
```

---

## dict.c — 辞書ファイルの読み込み

### `trim(char *str)` — 前後のスペースを除去

```c
char  *trim(char *str)
{
    int  i;
    int  j;

    i = 0;
    while (str[i] != '\0' && str[i] == ' ')
        i++;                          // 先頭のスペースをスキップ
    if (str[i] == '\0')
        return (str + i);             // 全部スペースなら空文字列を返す
    j = ft_strlen(str) - 1;
    while (j >= 0 && str[j] == ' ')
        j--;                          // 末尾のスペースをスキップ
    str[j + 1] = '\0';               // 末尾スペースの手前でヌル終端
    return (str + i);                 // 先頭スペースをスキップしたアドレスを返す
}
```

**ポイント:** 新しいメモリを確保せず、元の文字列の中でポインタを動かしている。

---

### `parse_line(char *line, t_entry *entry)` — 1行をパース

辞書の1行（`"1000: thousand"`）を key と value に分ける。

```c
static int  parse_line(char *line, t_entry *entry)
{
    int  colonp;      // コロン ':' の位置

    colonp = 0;
    while (line[colonp] != ':' && line[colonp] != '\0')
        colonp++;                  // ':' の位置を探す
    if (line[colonp] == '\0')
        return (0);                // ':' がなければ不正行 → 0（失敗）
    line[colonp] = '\0';           // ':' をヌル文字に書き換え → 文字列を2つに分割
    entry->key = trim(line);                  // 前半をトリムして key に
    entry->value = trim(line + colonp + 1);   // 後半をトリムして value に
    if (entry->key[0] == '\0' || entry->value[0] == '\0')
        return (0);                // key か value が空なら不正 → 0（失敗）
    return (1);                    // 成功 → 1
}
```

**具体例: `"1000: thousand"` の処理**
```
line = "1000: thousand"
colonp = 4（':'の位置）
line[4] = '\0' → "1000\0 thousand"
entry->key   = trim("1000") → "1000"
entry->value = trim(" thousand") → "thousand"
```

---

### `read_file(char *path, char *buf)` — ファイル読み込み

```c
static int  read_file(char *path, char *buf)
{
    int      fd;
    ssize_t  bytes;

    fd = open(path, O_RDONLY);   // ファイルを読み込み専用で開く
    if (fd == -1)                 // 開けなかった（ファイルなし等）→ 0（失敗）
        return (0);
    bytes = read(fd, buf, 65535); // 最大 65535 バイト読む
    close(fd);                    // ファイルを閉じる
    if (bytes == -1)              // 読み込み失敗 → 0（失敗）
        return (0);
    buf[bytes] = '\0';            // 読んだ末尾にヌル終端を付ける
    return (1);                   // 成功 → 1
}
```

**なぜ 65535 か？** バッファサイズ 65536 の最大インデックスは 65535。
`buf[bytes] = '\0'` でヌル終端するため、読み込みは 65535 バイトまでに制限。

---

### `load_dict(char *path)` — 辞書を読み込んで構造体に格納

```c
t_dict  *load_dict(char *path)
{
    t_dict  *dict;
    char     buf[65536];  // ファイル内容を一時的に格納するバッファ
    int      i;

    if (!read_file(path, buf))   // ファイル読み込み失敗 → NULL
        return (NULL);
    dict = malloc(sizeof(t_dict));   // 辞書構造体を確保
    if (!dict)
        return (NULL);
    dict->lines = ft_split(buf, "\n");         // 行ごとに分割
    dict->entries = malloc(sizeof(t_entry) * get_count(buf, "\n"));
    // 行数分の entry 配列を確保
    if (!dict->lines || !dict->entries)
        return (free_dict(dict), NULL);        // メモリ確保失敗 → 解放して NULL
    dict->size = get_count(buf, "\n");         // 行数（エントリ数）を記録
    i = 0;
    while (dict->lines[i] != NULL)
    {
        if (!parse_line(dict->lines[i], &dict->entries[i]))
            return (free_dict(dict), NULL);    // パース失敗 → 解放して NULL
        i++;
    }
    return (dict);  // 完成した辞書を返す
}
```

**処理の流れ:**
```
ファイル内容 → buf（文字列）
    ↓ ft_split(buf, "\n")
dict->lines = ["0: zero", "1: one", "2: two", ...]
    ↓ parse_line ×行数
dict->entries = [{key="0", value="zero"}, {key="1", value="one"}, ...]
```

---

### `free_dict(t_dict *dict)` — 辞書の解放

```c
void  free_dict(t_dict *dict)
{
    int  i;

    if (!dict)      // NULL なら何もしない（二重解放防止）
        return ;
    i = 0;
    if (dict->lines)
    {
        while (dict->lines[i] != NULL)
        {
            free(dict->lines[i]);   // 各行の文字列を解放
            i++;
        }
        free(dict->lines);          // ポインタ配列本体を解放
    }
    free(dict->entries);            // エントリ配列を解放
    free(dict);                     // 構造体本体を解放
}
```

**解放の順序:** 内側（各行の文字列）→ 外側（配列・構造体）の順で解放。
逆順にするとメモリリークやダングリングポインタになる。

---

## lookup.c — 辞書検索・単位出力

### `dict_lookup(t_dict *dict, char *key)` — キーで辞書を検索

```c
char  *dict_lookup(t_dict *dict, char *key)
{
    int  i;
    int  j;

    i = 0;
    while (i < dict->size)       // 全エントリを順番に確認
    {
        j = 0;
        while (dict->entries[i].key[j] == key[j] && key[j] != '\0')
            j++;                  // 文字が一致する間 j を進める
        if (dict->entries[i].key[j] == key[j])
            // 両方とも同じ位置で終わった（両方 '\0'）→ 完全一致
            return (dict->entries[i].value);
        i++;
    }
    return (NULL);  // 見つからなかった → NULL
}
```

**なぜ `strcmp` を使わないか？** 42Tokyo のルールで標準ライブラリ関数が制限されるため。

---

### `unit_exists(t_dict *dict, int idx)` — 単位が辞書に存在するか確認

単位とは thousand（idx=1）, million（idx=2）, billion（idx=3）… のこと。

```c
int  unit_exists(t_dict *dict, int idx)
{
    char  *unit_key;
    int    k;
    int    result;

    if (idx == 0)           // idx=0 は単位なし（ones）→ 常に存在する
        return (1);
    unit_key = malloc(idx * 3 + 2);
    // idx=1 → 4バイト（"1000\0"）, idx=2 → 7バイト（"1000000\0"）
    if (!unit_key)
        return (0);
    unit_key[0] = '1';      // "1" から始める
    k = 0;
    while (k++ < idx * 3)
        unit_key[k] = '0';  // idx * 3 個の '0' を追加
    // idx=1: "1" + "000" = "1000"
    // idx=2: "1" + "000000" = "1000000"
    unit_key[k] = '\0';     // ヌル終端
    result = (dict_lookup(dict, unit_key) != NULL);  // 辞書に存在するか確認
    free(unit_key);
    return (result);
}
```

---

### `print_unit(t_dict *dict, int idx)` — 単位を出力

```c
int  print_unit(t_dict *dict, int idx)
{
    char  *unit_key;
    char  *unit;
    int    k;

    if (idx == 0)        // idx=0 は単位なし → 何も出力しない
        return (0);
    unit_key = malloc(idx * 3 + 2);  // 単位のキー文字列を作成（unit_exists と同じ）
    if (!unit_key)
        return (1);
    unit_key[0] = '1';
    k = 0;
    while (k++ < idx * 3)
        unit_key[k] = '0';
    unit_key[k] = '\0';
    unit = dict_lookup(dict, unit_key);  // 辞書から単位の単語を取得
    free(unit_key);
    if (!unit)
        return (1);          // 見つからなかった → エラー
    ft_putstr(" ");          // スペースを出力
    ft_putstr(unit);         // 単位を出力（例: "thousand", "million"）
    return (0);
}
```

---

## convert_sub.c — 変換サブ処理

### `is_zero(char *str)` — すべて '0' かどうか判定

```c
int  is_zero(char *str)
{
    while (*str == '0')
        str++;                // '0' をスキップしながら進む
    return (*str == '\0');    // 最後まで '0' だったか確認
}
```

例: `"0"` → 1（ゼロ）、`"00"` → 1、`"01"` → 0、`"123"` → 0

---

### `convert_ones(char *group, t_dict *dict)` — 一の位を出力

```c
int  convert_ones(char *group, t_dict *dict)
{
    char  *word;

    if (group[0] == '0')     // 0 なら何も出力しない（成功扱い）
        return (0);
    word = dict_lookup(dict, group);  // 辞書から単語を取得
    if (!word)
        return (1);          // 辞書にない → エラー
    ft_putstr(word);         // 単語を出力（例: "five"）
    return (0);
}
```

---

### `convert_tens(char *group, t_dict *dict)` — 十の位を出力

```c
int  convert_tens(char *group, t_dict *dict)
{
    char  list[3];   // 十の位のキー（例: "20\0"）
    char  *word;

    if (group[0] == '1')
        // 10〜19 は特殊（eleven, twelve, thirteen...）→ そのまま辞書検索
        return (convert_ones(group, dict));
    if (group[0] != '0')
    {
        // 20〜99
        list[0] = group[0];   // 十の位の文字（例: '3'）
        list[1] = '0';        // 一の位を '0' にして "30", "40"... を作る
        list[2] = '\0';
        word = dict_lookup(dict, list);  // 例: "30" → "thirty"
        if (!word)
            return (1);
        ft_putstr(word);      // 例: "thirty" を出力
        if (group[1] != '0')
        {
            ft_putstr(" ");             // スペースを出力
            return (convert_ones(&group[1], dict));  // 一の位を出力
        }
        return (0);
    }
    // 一の位のみ（例: group = "05" → group[1] = '5'）
    return (convert_ones(&group[1], dict));
}
```

**具体例:**
| group | 出力 |
|-------|------|
| "15" | "fifteen"（10台として辞書検索）|
| "30" | "thirty" |
| "37" | "thirty seven" |
| "07" | "seven" |

---

### `print_hundreds(char *group, t_dict *dict)` — 百の位を出力

```c
int  print_hundreds(char *group, t_dict *dict)
{
    char  list[2];    // 百の位のキー（例: "3\0"）
    char  *word;
    char  *hundred;

    list[0] = group[0];   // 百の位の文字（例: '3'）
    list[1] = '\0';
    word = dict_lookup(dict, list);       // 例: "3" → "three"
    hundred = dict_lookup(dict, "100");   // "hundred" を取得
    if (!word || !hundred)
        return (1);
    ft_putstr(word);     // 例: "three"
    ft_putstr(" ");      // スペース
    ft_putstr(hundred);  // "hundred"
    if (group[1] != '0' || group[2] != '0')
        ft_putstr(" ");  // 後に十の位・一の位が続く場合はスペース
    return (0);
}
```

**具体例:** group = "347"
→ `"three hundred "` を出力（その後 "forty seven" が続く）

---

### `validate_units(char (*groups)[4], int top, t_dict *dict)` — 単位の検証

```c
int  validate_units(char (*groups)[4], int top, t_dict *dict)
{
    int  i;
    int  k;

    i = top;               // 最上位グループから確認
    while (i >= 0)
    {
        k = -1;
        while (groups[i][++k] == '0')
            ;              // 先頭の '0' をスキップ
        if (groups[i][k] && !unit_exists(dict, i))
            // そのグループが 0 でない（有効な数字がある）のに
            // 対応する単位が辞書にない → エラー
            return (1);
        i--;
    }
    return (0);  // 全グループの単位が辞書にある → 成功
}
```

---

## convert.c — 変換メイン処理

### `top_group_idx(char (*groups)[4], int i)` — 最上位の非ゼログループを探す

```c
static int  top_group_idx(char (*groups)[4], int i)
{
    int  k;

    k = -1;
    while (groups[i][++k] == '0')
        ;              // 現在のグループの先頭 '0' をスキップ
    while (i > 0 && !groups[i][k])
    // groups[i][k] が '\0'（= グループが "0" や "00" や "000" など全0）なら
    {
        i--;           // 一つ下のグループへ
        k = -1;
        while (groups[i][++k] == '0')
            ;          // そちらも先頭 '0' をスキップ
    }
    return (i);        // 最上位の非ゼログループのインデックスを返す
}
```

**例: "1000000" → groups = ["000", "000", "1"]**
- i=2（最初は最上位グループ）
- groups[2] = "1" → k=0 で '1' → ゼロでないのでそのまま
- return 2

---

### `convert_hundreds(char *group, int len, t_dict *dict, int unit_idx)` — グループを変換して出力

```c
int  convert_hundreds(char *group, int len, t_dict *dict, int unit_idx)
{
    if (len == 3 && group[0] != '0')
        // 3桁かつ百の位が 0 でない → 百の位を出力
        if (print_hundreds(group, dict))
            return (1);
    if (len >= 2)
    {
        // 2桁以上 → 十の位・一の位を出力（後ろから2文字）
        if (convert_tens(&group[len - 2], dict))
            return (1);
    }
    else if (group[0] != '0')
    {
        // 1桁かつ 0 でない → 一の位のみ
        if (convert_ones(group, dict))
            return (1);
    }
    return (print_unit(dict, unit_idx));  // 単位を出力（thousand, million など）
}
```

**具体例: group="347", len=3, unit_idx=1**
```
print_hundreds("347", dict) → "three hundred "
convert_tens("47", dict)    → "forty seven"
print_unit(dict, 1)         → " thousand"
合計: "three hundred forty seven thousand"
```

---

### `convert_groups(char (*groups)[4], int i, t_dict *dict)` — 下位グループを変換

```c
static int  convert_groups(char (*groups)[4], int i, t_dict *dict)
{
    int  k;

    while (i-- > 0)     // 上位から 1 つ下のグループから順に処理
    {
        k = -1;
        while (groups[i][++k] == '0')
            ;            // 先頭の '0' をスキップ
        if (groups[i][k])  // グループが全て 0 でない場合のみ出力
        {
            ft_putstr(" ");   // グループ間のスペース
            if (convert_hundreds(groups[i], ft_strlen(groups[i]), dict, i))
                return (1);
        }
    }
    return (0);
}
```

---

### `handle_zero(t_dict *dict)` — 0 を出力

```c
static int  handle_zero(t_dict *dict)
{
    char  *zero;

    zero = dict_lookup(dict, "0");   // "0" → "zero" を辞書から取得
    if (!zero)
        return (1);                  // 辞書に "0" がない → エラー
    ft_putstr(zero);                 // "zero" を出力
    ft_putstr("\n");                 // 改行
    return (0);
}
```

---

### `convert(char *num_str, t_dict *dict)` — 変換のメイン処理

```c
int  convert(char *num_str, t_dict *dict)
{
    char  (*groups)[4];  // 3桁グループの配列（各グループは最大4文字 "999\0"）
    int    i;

    if (is_zero(num_str))
        return (handle_zero(dict));   // 全部 0 なら "zero" を出力
    groups = malloc((ft_strlen(num_str) / 3 + 1) * sizeof(*groups));
    // グループ数 = 桁数/3 + 1（切り上げ）分のメモリを確保
    if (!groups)
        return (1);
    i = top_group_idx(groups, split_groups(num_str, groups) - 1);
    // 1. split_groups: 数字を3桁グループに分割し、グループ数を返す
    // 2. -1: 最上位グループのインデックス（0起算）
    // 3. top_group_idx: 最上位の非ゼログループのインデックスを返す
    if (validate_units(groups, i, dict)
        || convert_hundreds(groups[i], ft_strlen(groups[i]), dict, i)
        || convert_groups(groups, i, dict))
    // 1. validate_units: 全グループの単位が辞書に存在するか確認
    // 2. convert_hundreds: 最上位グループを変換・出力
    // 3. convert_groups: 残りのグループを変換・出力
    {
        free(groups);
        return (1);
    }
    free(groups);
    ft_putstr("\n");   // 最後に改行
    return (0);
}
```

---

## 全体の処理フロー（具体例）

### 入力: `./a.out 1234567`

```
main()
  └── run_convert("numbers.dict", "1234567")
        ├── load_dict("numbers.dict")
        │     ├── read_file() → buf = "0: zero\n1: one\n..."
        │     ├── ft_split(buf, "\n") → lines = ["0: zero", "1: one", ...]
        │     ├── parse_line × 行数 → entries = [{key="0", value="zero"}, ...]
        │     └── return dict
        └── convert("1234567", dict)
              ├── is_zero("1234567") → false
              ├── split_groups("1234567", groups)
              │     groups[0] = "567"  ← ones
              │     groups[1] = "234"  ← thousands
              │     groups[2] = "1"    ← millions
              │     return 3
              ├── top_group_idx(groups, 2) → 2
              ├── validate_units(groups, 2, dict) → OK
              ├── convert_hundreds("1", 1, dict, 2)
              │     → convert_ones("1", dict) → "one"
              │     → print_unit(dict, 2) → " million"
              │     出力: "one million"
              ├── convert_groups(groups, 2, dict)
              │     i=1: convert_hundreds("234", 3, dict, 1)
              │           → print_hundreds("234", dict) → "two hundred "
              │           → convert_tens("34", dict) → "thirty four"
              │           → print_unit(dict, 1) → " thousand"
              │           出力: " two hundred thirty four thousand"
              │     i=0: convert_hundreds("567", 3, dict, 0)
              │           → print_hundreds("567", dict) → "five hundred "
              │           → convert_tens("67", dict) → "sixty seven"
              │           → print_unit(dict, 0) → ""（単位なし）
              │           出力: " five hundred sixty seven"
              └── ft_putstr("\n")

最終出力: "one million two hundred thirty four thousand five hundred sixty seven\n"
```

---

## 重要な設計ポイント

### 1. グループのインデックスと単位の対応

```
groups[0] → idx=0 → 単位なし（ones）
groups[1] → idx=1 → "1000" → "thousand"
groups[2] → idx=2 → "1000000" → "million"
groups[3] → idx=3 → "1000000000" → "billion"
```

`unit_key` を `"1" + "0" × (idx*3)` で動的に生成して辞書を引く。

### 2. メモリ管理の責任分担

| データ | 確保場所 | 解放場所 |
|--------|---------|---------|
| `dict` 構造体 | `load_dict` | `free_dict` |
| `dict->lines[i]` | `ft_split` の中 | `free_dict` |
| `dict->lines` | `ft_split` | `free_dict` |
| `dict->entries` | `load_dict` | `free_dict` |
| `groups` | `convert` | `convert` |
| `unit_key` | `unit_exists`/`print_unit` | 同関数内 |

### 3. エラー時の即時解放パターン

```c
// Cの慣用句: カンマ演算子で解放 + NULL 返却を1行で
return (free_dict(dict), NULL);
// これは以下と同等:
// free_dict(dict);
// return (NULL);
```

### 4. 辞書の柔軟性

`numbers.dict` を別の辞書ファイルに差し替えると他言語の数字読み上げにも対応できる設計。
（例: フランス語の辞書を作ればフランス語で出力できる）
