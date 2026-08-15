# extract_line

## 要件メモ

| 項目 | 内容 |
|------|------|
| ファイル名 | `get_next_line_utils.c` |
| プロトタイプ | `char *extract_line(char *leftover);` |
| 使える関数 | `malloc` |
| 再実装元 | なし（この課題専用のヘルパー） |
| bonus | − |

---

## 考え方

- `leftover` の中には「返すべき1行 + まだ次回に回す残り」が両方入っている状態。`extract_line` は **先頭から最初の `\n`（あれば含む）までだけ** を切り出して新しい文字列として返す係。
- `\n` が無い場合（＝ファイル末尾で改行なしに終わったケース）は、`leftover` 全体をそのまま1行として返す。

---

## メモリ図解

```
leftover = "hello\nworld"
             ^0123456789A (\nはインデックス5)

ft_strcount(leftover) = 6  ("hello\n" の長さ)
line = malloc(6 + 1)
コピー: h e l l o \n \0
戻り値: "hello\n"

------------------------------------------------

leftover = "hello"  (\n無し、ファイル終端)
ft_strcount(leftover) = 5
line = malloc(5 + 1)
コピー: h e l l o \0
戻り値: "hello"  (\nは付かない)
```

---

## 解答コード

```c
/* Norminette 準拠 */
int	ft_strcount(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	return (i);
}

char	*extract_line(char *leftover)
{
	char	*line;
	int		i;
	int		len;

	i = 0;
	len = ft_strcount(leftover);
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	while (leftover[i] != '\n' && leftover[i] != '\0')
	{
		line[i] = leftover[i];
		i++;
	}
	line[i] = leftover[i];
	if (leftover[i] == '\n')
		line[i + 1] = '\0';
	return (line);
}
```

**なぜそう書くか**

| コード | 理由 |
|--------|------|
| `ft_strcount` で先に必要な長さを数える | `malloc` は正確なサイズを渡さないと確保しすぎ／不足になる。1回スキャンしてからちょうどのサイズで確保する2パス方式。 |
| `if (s[i] == '\n') i++;`（`ft_strcount` 内） | `\n` を含めた長さで確保するため（戻り値の行に `\n` を含める仕様のため）。 |
| `line[i] = leftover[i];` の後に `if (leftover[i] == '\n') line[i + 1] = '\0';` | `\n` で止まった場合は `\n` 自体をコピーしてから次に `\0` を置く。`\0` で止まった場合は `line[i] = '\0'` がそのままコピーされるので、それ以上何もしなくてよい。 |
| `malloc` 失敗時は `NULL` を返す | 呼び出し元（`get_next_line`）で `leftover` を解放して安全に終了できるようにするため。 |

---

## ハマりポイント

### ❌ NG: よくある間違い

```c
char	*extract_line(char *leftover)
{
	int	len = ft_strlen(leftover);   /* \n の有無を考えず全長で確保 */
	char	*line = malloc(len + 1);
	...
	while (leftover[i] != '\n' && leftover[i] != '\0')
	{
		line[i] = leftover[i];
		i++;
	}
	line[i] = '\n';        /* leftoverに\nが無いのに強引に付けてしまう */
	line[i + 1] = '\0';
}
```

→ ファイル末尾で改行なしに終わる行に、存在しない `\n` を付け足してしまうバグ。件の仕様「ファイル末尾で `\n` が無ければ付けない」に違反する。`leftover[i]` が実際に `\n` かどうかを見てから付ける必要がある。

---

## 提出前チェック

- [ ] Norminette OK
- [ ] `"hello\nworld"` → `"hello\n"` を返す
- [ ] `"hello"`（`\n` 無し）→ `"hello"` をそのまま返す（`\n` を勝手に付けない）
- [ ] `malloc` 失敗時に `NULL` を返す
- [ ] メモリリークがない
