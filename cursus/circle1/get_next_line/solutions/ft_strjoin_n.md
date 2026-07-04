# ft_strjoin_n

## 要件メモ

| 項目 | 内容 |
|------|------|
| ファイル名 | `get_next_line_utils.c` |
| プロトタイプ | `char *ft_strjoin_n(char const *s1, size_t l1, char const *s2, size_t l2);` |
| 使える関数 | `malloc` |
| 再実装元 | libftの `ft_strjoin` に近いが、長さを引数で受け取る点が異なる |
| bonus | − |

---

## 考え方

- 素朴な `ft_strjoin(s1, s2)`（libft版）は内部で `ft_strlen(s1)` と `ft_strlen(s2)` を計算する。しかし `get_next_line` では `s1`（＝`leftover`）が呼び出しを重ねるごとに伸びていくため、毎回 `strlen` から数え直すと **読み込み回数に対して二乗オーダー** の計算量になってしまう。
- そこで、呼び出し側（`fill_leftover`）で `leftover` の長さを `left_len` として持ち回し、`ft_strjoin_n` には **既知の長さを直接渡す** ことで、この関数自体は毎回 `l1 + l2` に比例する時間で連結できるようにしている。
- `s1 == NULL` でも動作する（`l1 == 0` として扱われ、単に `s2` の内容だけがコピーされる）。これは `leftover` が初回呼び出しでまだ `NULL` の場合に対応するため。

---

## メモリ図解

```
s1 = "CD" (l1=2), s2 = "EF\nG" (l2=4)

r = malloc(2 + 4 + 1)
i=0..1: r[i] = s1[i]        → "CD"
i=2..5: r[i] = s2[i-l1]     → "CDEF\nG" ※実際には l2=4 なので "EF\nG" 全体
r[6] = '\0'

戻り値: "CDEF\nG"
```

---

## 解答コード

```c
/* Norminette 準拠 */
char	*ft_strjoin_n(char const *s1, size_t l1, char const *s2, size_t l2)
{
	char	*r;
	size_t	i;

	if (!s2)
		return (NULL);
	r = (char *)malloc(l1 + l2 + 1);
	if (!r)
		return (NULL);
	i = 0;
	while (i < l1)
	{
		r[i] = s1[i];
		i++;
	}
	while (i < l1 + l2)
	{
		r[i] = s2[i - l1];
		i++;
	}
	r[i] = '\0';
	return (r);
}
```

**なぜそう書くか**

| コード | 理由 |
|--------|------|
| `l1`, `l2` を引数で受け取る | 呼び出し側で既に長さを把握しているなら、この関数内で再計算しない。これが「毎回 `read()` した分だけ連結コストがかかる」設計の要。 |
| `if (!s2) return (NULL);` | `read()` で得たバッファ（`s2` 側）が渡らないケースは想定外なので、異常系として `NULL` を返す。 |
| `s1 == NULL` を許容（`l1 == 0` なら `while (i < l1)` が即終了） | `leftover` が `NULL` の初回呼び出しでも、`s1` を参照せずに安全に `s2` だけコピーできる。 |

---

## ハマりポイント

### ❌ NG: よくある間違い

```c
char	*ft_strjoin_n(char const *s1, char const *s2)
{
	size_t	l1 = ft_strlen(s1);   /* 呼ぶたびに s1 全体を数え直す */
	size_t	l2 = ft_strlen(s2);
	...
}
```

→ `leftover` が育つにつれて `ft_strlen(s1)` のコストが線形に増え、`read()` の呼び出し回数（＝ファイルサイズ / `BUFFER_SIZE`）をかけると全体で二乗オーダーになる。特に `BUFFER_SIZE=1` で大きいファイルを読むと、実行時間が体感できるレベルで悪化する。長さを引数で受け取る形にすることでこれを回避している。

---

## 提出前チェック

- [ ] Norminette OK
- [ ] `ft_strjoin_n("abc", 3, "def", 3)` → `"abcdef"`
- [ ] `ft_strjoin_n(NULL, 0, "xyz", 3)` → `"xyz"`（`s1` が `NULL` でも安全）
- [ ] `ft_strjoin_n("abc", 3, NULL, 0)` → `NULL`
- [ ] `malloc` 失敗時に `NULL` を返す
- [ ] メモリリークがない（呼び出し元で古い `s1` を `free` している）
