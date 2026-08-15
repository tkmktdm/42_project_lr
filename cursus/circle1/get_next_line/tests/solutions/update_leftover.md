# update_leftover

## 要件メモ

| 項目 | 内容 |
|------|------|
| ファイル名 | `get_next_line_utils.c` |
| プロトタイプ | `char *update_leftover(char *leftover);` |
| 使える関数 | `malloc` |
| 再実装元 | なし（この課題専用のヘルパー） |
| bonus | − |

---

## 考え方

- `extract_line` が「今回返す1行」を切り出したのに対し、`update_leftover` は「次回に持ち越す残り（`\n` の次の文字から末尾まで）」を新しく確保して返す係。
- 残りが無い（`\n` の直後が `'\0'`、または `\n` そのものが無い）場合は `NULL` を返す。これにより `get_next_line` の次回呼び出し時、`static leftover` は `NULL` となり「まっさらな状態から読み直す」ことになる。

---

## メモリ図解

```
leftover = "hello\nworld"
p = strchr相当で\nの位置を探す → 5番目
p++  → "world" を指す
len = ft_strlen(p) = 5
right = malloc(5 + 1)
コピー: w o r l d \0
戻り値: "world"

------------------------------------------------

leftover = "hello\n"  (\nの後に何も無い)
p = \nの位置 → 5番目
p++          → "" (空文字列) を指す
len = ft_strlen(p) = 0
→ 戻り値: NULL  ("次に読むものはもう無い"を意味する)

------------------------------------------------

leftover = "hello"  (\n自体が無い)
p = NULL  (ft_strchr_gnl が見つけられない)
→ 戻り値: NULL
```

---

## 解答コード

```c
/* Norminette 準拠 */
char	*update_leftover(char *leftover)
{
	char	*p;
	char	*right;
	int		len;
	int		i;

	i = 0;
	p = ft_strchr_gnl(leftover, '\n');
	if (p == NULL)
		return (NULL);
	p++;
	len = ft_strlen(p);
	if (len == 0)
		return (NULL);
	right = malloc(sizeof(char) * (len + 1));
	if (!right)
		return (NULL);
	while (p[i] != '\0')
	{
		right[i] = p[i];
		i++;
	}
	right[i] = '\0';
	return (right);
}
```

**なぜそう書くか**

| コード | 理由 |
|--------|------|
| `p = ft_strchr_gnl(leftover, '\n'); if (p == NULL) return (NULL);` | `\n` が見つからない＝`leftover` 全体が今回の行として使い切られた、という状態なので持ち越す残りは無い。 |
| `len == 0` のとき `NULL` を返す | 空文字列をそのまま `static leftover` に入れると、次回呼び出しで「残りがある」と誤認して無駄な処理をしてしまう。`NULL` に正規化しておくことで `get_next_line` 側の判定がシンプルになる（`leftover == NULL` だけ見ればよい）。 |
| 新しい `malloc` で `right` を確保する | `leftover` はこの後 `get_next_line` 側で `free` されるため、その一部を指すポインタをそのまま使い回すと解放後アクセスになる。必ずコピーして独立させる。 |

---

## ハマりポイント

### ❌ NG: よくある間違い

```c
char	*update_leftover(char *leftover)
{
	char	*p = ft_strchr_gnl(leftover, '\n');

	if (!p)
		return (NULL);
	return (p + 1);   /* leftover の内部を指すポインタをそのまま返してしまう */
}
```

→ 呼び出し元の `get_next_line` は直後に `free(leftover)` するため、返した `p + 1` は解放済み領域を指すダングリングポインタになる。次回の呼び出しで use-after-free を踏む。必ず新しいメモリ領域にコピーしてから返す必要がある。

---

## 提出前チェック

- [ ] Norminette OK
- [ ] `"hello\nworld"` → `"world"` を返す
- [ ] `"hello\n"`（`\n` の後に何も無い）→ `NULL` を返す
- [ ] `"hello"`（`\n` が無い）→ `NULL` を返す
- [ ] 返り値は `leftover` から独立した新しいメモリ（use-after-freeにならない）
- [ ] メモリリークがない
