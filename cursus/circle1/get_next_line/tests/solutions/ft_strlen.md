# ft_strlen

## 要件メモ

| 項目 | 内容 |
|------|------|
| ファイル名 | `get_next_line.c`（内部で使用するため） |
| プロトタイプ | `size_t ft_strlen(const char *s);` |
| 使える関数 | なし |
| 再実装元 | `strlen`（man 3 strlen） |
| bonus | − |

---

## 考え方

- 標準の `strlen` は `NULL` を渡すと未定義動作（大抵はクラッシュ）になるが、この課題では `leftover`（static変数）が初回呼び出し時に `NULL` であることが普通にあり得る。
- そこで `s == NULL` のときは `0` を返す防御的な実装にしている。これにより呼び出し側（`fill_leftover`）で毎回 `NULL` チェックを書かずに済む。

---

## メモリ図解

```
s = "abc\0"
     ^i=0 ^i=1 ^i=2 ^i=3 ('\0'で停止)
戻り値 = 3
```

---

## 解答コード

```c
/* Norminette 準拠 */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
```

**なぜそう書くか**

| コード | 理由 |
|--------|------|
| `if (!s) return (0);` | `leftover` が `NULL` の状態（まだ何も読んでいない）でも安全に呼べるようにするため。標準の `strlen` にはない挙動。 |
| `size_t` を返す | 文字列長は負にならないため符号無し整数を使うのが自然（標準ライブラリと同じ設計）。 |

---

## ハマりポイント

### ❌ NG: よくある間違い

```c
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')   /* s が NULL だと即座にクラッシュ */
		i++;
	return (i);
}
```

→ `get_next_line` の初回呼び出しでは `leftover` が `NULL` のまま `ft_strlen(leftover)` を呼ぶ箇所がある（`fill_leftover` 内）。NULL チェックを省くとそこでセグフォルトする。

---

## 提出前チェック

- [ ] Norminette OK
- [ ] `ft_strlen(NULL) == 0` になる
- [ ] `ft_strlen("")   == 0` になる
- [ ] 標準の `strlen` と同じ結果になる（NULL以外）
