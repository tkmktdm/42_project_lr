# BSQ — Big SQuare

## 要件メモ

| 項目 | 内容 |
|------|------|
| 実行ファイル名 | `bsq` |
| 引数 | ファイルパス 1 つ以上 / 引数なし → stdin |
| 使える関数 | `open` `close` `read` `write` `malloc` `free` `exit` |
| libft | 使用不可（自分で実装） |
| コンパイル | `cc -Wall -Wextra -Werror` |

---

## マップフォーマット

```
9.ox        ← 1行目：行数(9) + 空セル(.) + 障害物(o) + 塗りつぶし(x)
o...o.o...
...o..oo.o
..o..o....
......o...
o..ooo..oo
.o...o..o.
..o.o..ooo
......o...
...o..o...
```

### 1行目の構造

```
9  .  o  x
↑  ↑  ↑  ↑
行数 空 障害 塗り
```

- 行数は正の整数（`0` は無効）
- 3文字はすべて異なり、表示可能文字（ASCII > 32）
- 1行目の直後から `行数` 行がマップ本体

---

## エラー条件（`map error\n` を出力）

| 状況 | 説明 |
|------|------|
| 1行目が正の整数で始まらない | `0xxx`, `abc`, 空行 |
| 1行目の文字が3つない / 重複 / 非表示文字 | |
| マップ行数が宣言値と違う | 少ない・多い |
| 行の長さがバラバラ | |
| 指定3文字以外の文字が含まれる | |
| 行が1列もない | `cols == 0` |

---

## アルゴリズム：動的計画法（DP）

### 考え方

`dp[i][j]` = 「右下隅が (i, j) の最大正方形のサイズ」

```
マップ（. = 空, o = 障害物）:
. . . .
. . o .
. . . .
. . . .

dp テーブル:
1 1 1 1
1 2 0 1
1 2 1 1
1 2 2 2  ← dp[3][3]=2 が最大
```

### 漸化式

```
if grid[i][j] == 障害物:
    dp[i][j] = 0
else if i == 0 or j == 0:
    dp[i][j] = 1
else:
    dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1
```

### なぜこの式か

正方形のサイズを 1 増やすには「上・左・左上」の 3 方向すべてが確保できていないといけない。

```
  左上  上
  ┌───┬─┐
  │   │ │  ← dp[i-1][j-1] と dp[i-1][j] が min 以上確保
  ├───┼─┤
  │ 左│★│  ← dp[i][j-1] が min 以上確保
  └───┴─┘
```

3方向の min が `k` なら、右下を (i,j) とする `(k+1)×(k+1)` 正方形が作れる。

### メモリ図解

```
alloc_dp(rows=4, cols=4):

dp (int**)
┌─────┐
│ dp[0]│ → [1][1][1][1]
│ dp[1]│ → [1][2][0][1]
│ dp[2]│ → [1][2][1][1]
│ dp[3]│ → [1][2][2][2]
└─────┘
               ↑
          max=2, mr=3, mc=3
```

### 同サイズの正方形が複数ある場合

> 「最も上、次に最も左」を優先

DP を左上→右下の順（行優先）でスキャンし、更新条件を `dp[i][j] > best`（厳密な `>`）にする。
→ 最初に見つかったもの（最も上、同列なら左）が保持される。

---

## 正方形の塗りつぶし

右下隅 `(mr, mc)` とサイズ `size` が分かれば：

```
左上 = (mr - size + 1, mc - size + 1)

for r in [mr-size+1 .. mr]:
    for c in [mc-size+1 .. mc]:
        grid[r][c] = full_char
```

---

## ファイル構成

```
bsq/htakumi/
├── bsq.h       — 構造体 t_map、全プロトタイプ
├── main.c      — エントリポイント、ファイル処理ループ
├── read.c      — read_fd: fdを全部読んでchar*に
├── parse.c     — split, parse_header, validate_row, set_grid
├── solve.c     — alloc_dp, fill_dp, mark_square
├── output.c    — print_map (write だけで出力)
└── utils.c     — ft_strlen, ft_strdup_n, free_split, free_map, free_dp
```

---

## 解答コード：主要部抜粋

### parse_header（1行目の解析）

```c
static int	parse_header(char *line, t_map *map)
{
	int	i;

	i = 0;
	map->rows = 0;
	while (line[i] >= '0' && line[i] <= '9')
	{
		map->rows = map->rows * 10 + (line[i] - '0');
		i++;
	}
	if (i == 0 || map->rows <= 0)
		return (-1);
	// i の位置から3文字が存在し、4文字目が '\0' でなければ無効
	if (!line[i] || !line[i + 1] || !line[i + 2] || line[i + 3])
		return (-1);
	map->empty = line[i];
	map->obst  = line[i + 1];
	map->full  = line[i + 2];
	// 重複チェック・表示可能チェック
	...
	return (0);
}
```

**ポイント**: 数字を貪欲に読んで止まった位置から3文字を取る。`line[i + 3]` が非ゼロなら余分な文字あり→エラー。

### fill_dp（DP テーブル構築 + 最大位置追跡）

```c
static void	fill_dp(t_map *map, int **dp, int *mr, int *mc)
{
	int	i;
	int	j;
	int	best;

	best = 0;
	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			if (map->grid[i][j] == map->obst)
				dp[i][j] = 0;
			else if (i == 0 || j == 0)
				dp[i][j] = 1;
			else
				dp[i][j] = ft_min(dp[i-1][j],
					ft_min(dp[i][j-1], dp[i-1][j-1])) + 1;
			if (dp[i][j] > best)   // 厳密な > で上・左優先
			{
				best = dp[i][j];
				*mr = i;
				*mc = j;
			}
			j++;
		}
		i++;
	}
}
```

### read_fd（ファイルを全部読む）

```c
// realloc が使えないので「手動再確保」
while ((n = read(fd, buf, 4096)) > 0)
{
    tmp = malloc(total + n + 1);  // 新サイズで確保
    ft_memcpy_s(tmp, content, total);  // 旧データをコピー
    ft_memcpy_s(tmp + total, buf, n);  // 新データを追記
    tmp[total + n] = '\0';
    free(content);  // 旧バッファを解放
    content = tmp;
    total += n;
}
```

---

## ハマりポイント

### ❌ 末尾の改行処理

ファイルは通常 `\n` で終わる。`split_content` は末尾 `\n` の後に空文字列を追加しない：

```c
// fill_lines の末尾処理
if (*start)  // '\0' なら追加しない → 末尾 '\n' 後の空文字列を無視
    res[i++] = ft_strdup_n(start, s - start);
```

→ これがないと `n_lines != map->rows + 1` でエラーになる。

### ❌ grid の NULL 初期化を忘れる

`set_grid` の途中でエラーが起きると `free_map` が呼ばれる。
`grid[j..rows]` が未初期化だと `free_split(grid)` が不正なポインタを解放する。

```c
// malloc 直後に全部 NULL 初期化
i = 0;
while (i <= map->rows)
    map->grid[i++] = NULL;
```

→ `free_split` は `NULL` で止まるので安全。

### ❌ 複数ファイルの区切り

```c
// 最初のファイル以外の前に空行を入れる
if (!is_first)
    write(1, "\n", 1);
```

→ 「間に1行」なので最後には空行が入らない。

### ❌ `dp[mr][mc] == 0` のときに mark を呼ばない

全マスが障害物のとき `best == 0` のまま。この状態で `mark_square` を呼ぶと
サイズ 0 の正方形を塗ろうとする（実害はないが意図しない動作）。

```c
if (dp[mr][mc] > 0)
    mark_square(map, dp[mr][mc], mr, mc);
```

---

## 提出前チェック

- [ ] Norminette OK（関数 25 行以内、変数 5 個以内）
- [ ] `-Wall -Wextra -Werror` でコンパイル通る
- [ ] `make re` で一から再ビルドできる
- [ ] `make` を 2 回実行して `Nothing to be done for 'all'`（再リンクなし）
- [ ] 引数なしで stdin から読み込める
- [ ] 複数ファイルを引数に取り、間に空行が 1 行入る
- [ ] 無効なファイルで `map error` が出る
- [ ] 全マスが障害物のときマップがそのまま出力される
- [ ] 全マスが空のとき全体が塗りつぶされる（単純確認）
