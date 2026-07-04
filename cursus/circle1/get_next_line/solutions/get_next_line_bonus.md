# get_next_line_bonus（未実装・設計メモ）

## 要件メモ

| 項目 | 内容 |
|------|------|
| ファイル名 | `get_next_line_bonus.c`, `get_next_line_bonus.h`, `get_next_line_utils_bonus.c` |
| プロトタイプ | `char *get_next_line(int fd);`（必須パートと同じシグネチャ） |
| 使える関数 | `read`、`malloc`、`free` |
| 再実装元 | なし |
| bonus | ✓（この課題唯一のボーナス要件） |
| 現在の状態 | **未提出**（`42_develop/` に `_bonus` ファイルが存在しない）。このドキュメントは実装時の設計指針。 |

> `tests/test_get_next_line.sh` の `BONUS=1` 実行時、このファイル群が無い間は該当テストが `[SKIP]` される。実装したらそのまま同じスクリプトで検証できる。

---

## 考え方

必須パートとの違いは1点だけ：**複数のfdを同時並行で読んでも、それぞれの続きを見失わない**こと。

必須パート（`get_next_line.c`）は `static char *leftover` という **1本の文字列** を1つのfd専用に保持していた。ボーナスでは、これを **「fdごとの `leftover` を並べた配列」** に置き換える必要がある。

- 「静的変数は1つだけ」という制約があるので、`static char *leftover[N]`（固定長配列）のように **1つの静的変数の中に複数fd分の状態をまとめて入れる** のがオーソドックスな解法。
- 配列のインデックスに何を使うかが設計の肝：
  - 単純に `fd` をそのまま添字にする（`leftover[fd]`）と実装が最も簡単。ただし `fd` の上限（`OPEN_MAX` など）分の配列を確保するか、十分大きな固定サイズ（例: 1024）を用意する必要がある。
  - fdの値をそのまま添字にしたくない場合は、`{ int fd; char *leftover; }` の構造体配列にして線形探索する方式もあるが、静的変数を「1つ」に保つ制約と両立させる必要がある（構造体の配列自体は1つの静的変数として数えられる）。
- どちらの方式でも、**必須パートの3段関数（読み込む/取り出す/残りを更新する）はそのまま使い回せる**。変わるのは「どの `leftover` を読み書きするか」を fd で振り分ける層だけ。

### 用語メモ

- **状態の見失い**: fd Aを読んでいる途中でfd Bを読むと、共有の `leftover` を上書きしてしまい、Aの続きが消える不具合。ボーナスで最も起きやすいバグ。

---

## メモリ図解

`leftover[fd]` 方式（fdをそのまま添字にする場合）のイメージ：

```
静的変数（1つ）:
  static char *leftover[MAX_FD] = { NULL, NULL, NULL, ... };

get_next_line(3) 呼び出し
------------------------------------------------
leftover[3] を読み込み対象にして
必須パートと同じ fill_leftover / extract_line / update_leftover を実行
→ leftover[3] だけが更新される。leftover[4], leftover[5] はそのまま。

get_next_line(4) 呼び出し
------------------------------------------------
leftover[4] を読み込み対象にして同様に処理
→ leftover[3] の状態は保持されたまま影響を受けない

get_next_line(3) 呼び出し（再び）
------------------------------------------------
leftover[3] は前回の続きが残っているので、そこから再開できる
```

---

## 解答コード（実装方針の骨子・未実装）

```c
/* Norminette 準拠（イメージ） */
#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*leftover[MAX_FD];
	char		*line;
	char		*new_leftover;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	leftover[fd] = fill_leftover(fd, leftover[fd]);
	if (leftover[fd] == NULL || leftover[fd][0] == '\0')
	{
		free(leftover[fd]);
		leftover[fd] = NULL;
		return (NULL);
	}
	line = extract_line(leftover[fd]);
	if (!line)
	{
		free(leftover[fd]);
		leftover[fd] = NULL;
		return (NULL);
	}
	new_leftover = update_leftover(leftover[fd]);
	free(leftover[fd]);
	leftover[fd] = new_leftover;
	return (line);
}
```

**なぜそう書くか**

| コード | 理由 |
|--------|------|
| `static char *leftover[MAX_FD];` | 「静的変数は1つだけ」という制約を守りつつ、fdごとの状態を分離するための配列。 |
| `fd >= MAX_FD` もエラー扱い | 配列外アクセスを防ぐガード。`MAX_FD` は `get_next_line_bonus.h` で定義する定数（例: 256や1024）。 |
| `fill_leftover` / `extract_line` / `update_leftover` は必須パートと共通 | ロジック自体はfdに依存しないので、`get_next_line_utils_bonus.c` にそのままコピー（またはヘッダ経由で共有）すればよい。 |

---

## ハマりポイント

### ❌ NG: よくある間違い

```c
char	*get_next_line(int fd)
{
	static char	*leftover;   /* fdに関係なく1本だけ */

	leftover = fill_leftover(fd, leftover);
	...
}
```

→ 必須パートのコードをそのまま流用しただけでは、fd 3 を読んでいる途中で fd 4 を読むと `leftover` が fd 4 用の内容で上書きされ、fd 3 の続きが失われる。「複数fd対応」の核心はここ。

### ❌ NG: 配列サイズと fd の対応を誤る

```c
#define MAX_FD 3
static char *leftover[MAX_FD];
...
leftover[fd] = ...   /* fd が 3,4,5 だと配列外アクセスになる */
```

→ fd の実際の値（3, 4, 5, ...）とサイズの小さい配列の添字を混同すると、境界チェックをすり抜けて未定義動作になる。`MAX_FD` は実際に使われうる fd の最大値を十分にカバーするサイズにする（または `fd >= MAX_FD` を確実にガードする）。

---

## 提出前チェック

- [ ] Norminette OK（`_bonus.c/h` もチェック対象）
- [ ] 静的変数の宣言が **1個だけ**（`grep -c '^\s*static' get_next_line_bonus.c` で確認）
- [ ] fd 3 → 4 → 5 → 3 → 4 → ... と交互に呼んでも、各fdの続きを正しく返す
- [ ] 必須パートと同じ挙動（`\n` の扱い、EOF、エラー時の`NULL`）を維持している
- [ ] 必須パートが完璧に通っていることを確認済み（ボーナスは必須パート合格が前提条件）
- [ ] メモリリークがない
