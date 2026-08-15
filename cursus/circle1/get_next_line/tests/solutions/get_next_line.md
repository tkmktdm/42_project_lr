# get_next_line

## 要件メモ

| 項目 | 内容 |
|------|------|
| ファイル名 | `get_next_line.c` |
| プロトタイプ | `char *get_next_line(int fd);` |
| 使える関数 | `read`、`malloc`、`free` |
| 再実装元 | なし（fgetsに近い独自仕様） |
| bonus | ✓（複数fd対応・静的変数1個版は `get_next_line_bonus.c` に分離） |

---

## 考え方

- `read()` は「呼ぶたびに続きから」読める代わりに、`\n` の位置なんて気にしてくれない。だから **前回読みすぎた分（=まだ返していない続き）をどこかに保存しておく必要がある** → これが `static` 変数を使う理由。
- 設計は3段階に分解する。
  1. **足りるまで読む** (`fill_leftover`)：`leftover`（前回の残り）に `\n` が含まれるまで、または EOF になるまで `read()` を繰り返してバッファを継ぎ足す。
  2. **1行取り出す** (`extract_line`)：`leftover` の先頭から最初の `\n` まで（含む）をコピーして新しい文字列にする。
  3. **残りを更新する** (`update_leftover`)：`\n` の次の文字から末尾までを新しい `leftover` として保存し直す。
- なぜこの3分割か：`get_next_line` 自体は「状態管理と3つの処理を呼ぶ司令塔」に徹し、各処理は単一責任にすることでバグを追いやすくする。

### 用語メモ

- **static変数**: 関数を抜けても値が消えない変数。ここでは `leftover`（＝前回の `read()` で読みすぎて、まだ行として返していない文字列）を保持するために使う。
- **leftover（残り物）**: 直前までに読み込んだが、まだ呼び出し元に返していない文字列。次回の `get_next_line()` 呼び出しはここから読み始める。

---

## メモリ図解

`BUFFER_SIZE=5` でファイル `"AB\nCDEF\nG"` を読む場合：

```
1回目の get_next_line() 呼び出し
------------------------------------------------
static leftover = NULL

read() 1回目 → buf = "AB\nCD"
leftover = "AB\nCD"          ← \n を含むので読み込み終了

extract_line(leftover) → line = "AB\n"          ← これを return
update_leftover(leftover) → leftover = "CD"     ← 次回に持ち越す

呼び出し元は "AB\n" を受け取る
------------------------------------------------

2回目の get_next_line() 呼び出し
------------------------------------------------
static leftover = "CD"        ← 前回の続き

leftover に \n が無いので read() を継続
read() 2回目 → buf = "EF\nG"
leftover = "CD" + "EF\nG" = "CDEF\nG"   ← \n を含むので終了

extract_line(leftover) → line = "CDEF\n"
update_leftover(leftover) → leftover = "G"

呼び出し元は "CDEF\n" を受け取る
------------------------------------------------

3回目の get_next_line() 呼び出し
------------------------------------------------
static leftover = "G"

leftover に \n が無いので read() を継続
read() 3回目 → buf = "" (0バイト = EOF)
leftover = "G" のまま、byte_num <= 0 でループを抜ける

extract_line(leftover) → line = "G"          ← \nが無い最後の行
update_leftover(leftover) → NULL（続きが無いので）

呼び出し元は "G" を受け取る（\n無し = ファイル終端の合図）
------------------------------------------------

4回目の get_next_line() 呼び出し
------------------------------------------------
static leftover = NULL
read() → 0バイト（EOF）
leftover == NULL のため NULL を return
```

---

## 解答コード

```c
/* Norminette 準拠 */
#include "get_next_line.h"

static char	*append_buf(char *left, size_t *left_len, char *buf, int bytes)
{
	char	*tmp;

	tmp = left;
	left = ft_strjoin_n(left, *left_len, buf, (size_t)bytes);
	free(tmp);
	if (left)
		*left_len += (size_t)bytes;
	return (left);
}

static char	*fill_leftover(int fd, char *leftover)
{
	char	*buf;
	int		byte_num;
	size_t	left_len;

	left_len = ft_strlen(leftover);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	byte_num = 0;
	while (buf && (leftover == NULL || ft_strchr_gnl(leftover, '\n') == NULL))
	{
		byte_num = read(fd, buf, BUFFER_SIZE);
		if (byte_num <= 0)
			break ;
		buf[byte_num] = '\0';
		leftover = append_buf(leftover, &left_len, buf, byte_num);
	}
	if (!buf || byte_num < 0)
	{
		free(buf);
		free(leftover);
		return (NULL);
	}
	free(buf);
	return (leftover);
}

char	*get_next_line(int fd)
{
	static char	*leftover = NULL;
	char		*line;
	char		*new_g_leftover;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	leftover = fill_leftover(fd, leftover);
	if (leftover == NULL || leftover[0] == '\0')
	{
		free(leftover);
		leftover = NULL;
		return (NULL);
	}
	line = extract_line(leftover);
	if (!line)
	{
		free(leftover);
		leftover = NULL;
		return (NULL);
	}
	new_g_leftover = update_leftover(leftover);
	free(leftover);
	leftover = new_g_leftover;
	return (line);
}
```

**なぜそう書くか**

| コード | 理由 |
|--------|------|
| `static char *leftover = NULL;` | 呼び出しをまたいで「前回の続き」を覚えておく唯一の手段。 |
| `fd < 0 \|\| BUFFER_SIZE <= 0` を先にチェック | 不正な引数で `read()` を呼ぶと未定義動作になるため、早期リターンでガードする。 |
| `left_len` を都度計算せず `append_buf` の中で加算 | `ft_strjoin_n` の呼び出しごとに `ft_strlen(leftover)` を毎回計算すると `leftover` が伸びるにつれ O(n²) になる。長さを引数で持ち回すことで各連結を O(bytes) に抑える。 |
| `fill_leftover` のループ条件に `leftover == NULL` を含める | 初回呼び出し（`leftover` がまだ何もない）でも `ft_strchr_gnl(NULL, ...)` を呼んで落ちないようにするため。 |
| `byte_num <= 0` で `break` | `read()` が `0`（EOF）または `-1`（エラー）を返したら、それ以上読めないのでループを終了する。 |
| `leftover[0] == '\0'` を NULL 扱いにする | 空文字列の `leftover` は「もう返す内容がない」ことを意味するため、`NULL` と同じ終了条件にまとめる。 |

---

## ハマりポイント

### ❌ NG: よくある間違い

```c
/* 悪い例: read() のたびに leftover 全体を作り直す (O(n^2)) */
static char *fill_leftover_bad(int fd, char *leftover)
{
    char buf[BUFFER_SIZE + 1];
    int  byte_num;

    while ((byte_num = read(fd, buf, BUFFER_SIZE)) > 0)
    {
        buf[byte_num] = '\0';
        leftover = ft_strjoin(leftover, buf); /* 毎回 strlen(leftover) からやり直す */
        if (ft_strchr_gnl(leftover, '\n'))
            break ;
    }
    return (leftover);
}
```

→ `ft_strjoin` が内部で `ft_strlen(s1)` を計算する実装だと、`leftover` が育つほど毎回の連結コストが線形に増え、全体で二乗オーダーになる。`BUFFER_SIZE=1` かつ大きいファイルだと極端に遅くなる。`left_len` を引き回す `ft_strjoin_n` 方式ならこれを回避できる。

```c
/* 悪い例: read() のエラーと EOF を区別せず、static変数を解放しない */
char *get_next_line(int fd)
{
    static char *leftover;
    char        *buf = malloc(BUFFER_SIZE + 1);
    int         n = read(fd, buf, BUFFER_SIZE);
    ...
    if (n == -1)
        return (NULL); /* leftover を free もリセットもしていない → 次回呼び出しで壊れた状態のまま使われる/リークする */
}
```

→ エラー時は「その fd はもう使えない」ものとして `leftover` を `free` して `NULL` に戻さないと、メモリリークや二重解放の温床になる。

---

## 提出前チェック

- [ ] Norminette OK
- [ ] `-Wall -Wextra -Werror` でコンパイル通る（`-D BUFFER_SIZE` あり・なし両方）
- [ ] `make` が通る（`get_next_line.a` が生成される）
- [ ] `BUFFER_SIZE` が 1 / 42 / 9999 / 10000000 でも同じ結果になる
- [ ] ファイルからの読み込み・標準入力からの読み込みの両方で動く
- [ ] 改行なしで終わるファイルでも最後の行を正しく返す
- [ ] 空ファイル・空fd（`/dev/null`）で最初から `NULL` を返す
- [ ] 不正な fd（負の値、close済み）で `NULL` を返す
- [ ] malloc を使う箇所すべてでメモリリークがない（`leaks` / `valgrind` で確認）
