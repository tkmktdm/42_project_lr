# ft_strchr_gnl

## 要件メモ

| 項目 | 内容 |
|------|------|
| ファイル名 | `get_next_line_utils.c` |
| プロトタイプ | `char *ft_strchr_gnl(char *s, int c);` |
| 使える関数 | なし |
| 再実装元 | `strchr`（man 3 strchr） |
| bonus | − |

---

## 考え方

- `get_next_line` は「`leftover` の中に `\n` が来たかどうか」を毎回チェックする必要がある。標準の `strchr` と同じ動きをする自前版があれば十分。
- 名前に `_gnl` サフィックスを付けているのは、libft の `ft_strchr` と衝突させないため（この課題では libft の使用が禁止されているので、完全に独立した実装として用意している）。

---

## メモリ図解

```
s = "hello\0"
ft_strchr_gnl(s, 'l') →  'h' 'e' [l] 'l' 'o' '\0'
                                 ^ ここのポインタを返す

ft_strchr_gnl(s, '\0') → 'h' 'e' 'l' 'l' 'o' [\0]
                                             ^ 終端文字自体も検索対象になる
```

---

## 解答コード

```c
/* Norminette 準拠 */
char	*ft_strchr_gnl(char *s, int c)
{
	while (*s != '\0')
	{
		if ((unsigned char)*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}
```

**なぜそう書くか**

| コード | 理由 |
|--------|------|
| `(unsigned char)` にキャストして比較 | `char` の符号は環境依存（signed/unsignedどちらもあり得る）。`int c` との比較を標準ライブラリ同様に符号なしで揃えることで移植性を保つ。 |
| ループの後にもう一度 `'\0'` との比較を行う | `c == '\0'` で呼ばれた場合、終端文字そのものを探して返せるようにするため（標準の `strchr` と同じ仕様）。 |

---

## ハマりポイント

### ❌ NG: よくある間違い

```c
char	*ft_strchr_gnl(char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)          /* char と int を符号込みで直接比較 */
			return (s);
		s++;
	}
	return (NULL);            /* '\0' 自体を検索できない */
}
```

→ `char` が signed な環境で `c` に `128` 以上の値（バイナリファイル由来の文字など）を渡すと符号拡張でズレが生じることがある。また `'\0'` 検索に対応していないと、`ft_strchr_gnl(s, '\0')` で常に `NULL` が返り、呼び出し側の想定と食い違う。

---

## 提出前チェック

- [ ] Norminette OK
- [ ] 見つかる場合は `strchr` と同じアドレス（オフセット）を返す
- [ ] 見つからない場合は `NULL` を返す
- [ ] `c = '\0'` のとき、文字列の終端ポインタを返す
