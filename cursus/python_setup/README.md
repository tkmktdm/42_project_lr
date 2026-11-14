# Python開発環境セットアップ

VSCodeでPythonを書くための環境構築メモ。C言語用のプロファイルとは完全に分離している。

---

## 構成概要

| 項目 | 内容 |
|---|---|
| プロファイル | `python`（Cの `code` プロファイルとは別） |
| 拡張機能 | Python (ms-python.python), Pylance, debugpy, Python Environments, ruff, Code Spell Checker |
| フォーマッタ | ruff |
| 型チェック | Pylance strict モード |
| Git | `user.email` / `user.name` を設定済み |

---

## プロファイル

C言語用とPython用で拡張機能・設定を分けるため、専用プロファイル `python` を作成している。

```bash
# ~/.zshrc に追加済みのエイリアス
alias code_p='/usr/bin/code --profile=python'
```

### 起動方法

```bash
code_p ~/Documents/42_cursus
```

新しいターミナルを開くか `source ~/.zshrc` 実行後に使用可能。

---

## インストール済み拡張機能

- `ms-python.python` — Python本体サポート
- `ms-python.vscode-pylance` — 型チェック・補完エンジン
- `ms-python.debugpy` — デバッガ
- `ms-python.vscode-python-envs` — venv等の環境検出・切り替え
- `charliermarsh.ruff` — フォーマッタ兼静的チェック（line-length 79, 選択ルール E/W/F）
- `streetsidesoftware.code-spell-checker` — スペルチェック

---

## settings.json（pythonプロファイル）

```json
{
    "editor.renderWhitespace": "all",
    "editor.rulers": [80],
    "files.trimTrailingWhitespace": true,
    "files.insertFinalNewline": true,

    "editor.parameterHints.enabled": false,
    "editor.quickSuggestions": {
        "comments": "off",
        "strings": "off",
        "other": "off"
    },

    "cSpell.customDictionaries": {
        "user-custom": {
            "name": "user-custom",
            "path": "~/.cspell/user-custom.txt",
            "addWords": true,
            "scope": "user"
        }
    },

    "ruff.configuration": {
        "line-length": 79,
        "lint": {
            "select": ["E", "W", "F"]
        }
    },
    "[python]": {
        "editor.defaultFormatter": "charliermarsh.ruff"
    },

    "python.analysis.typeCheckingMode": "strict",
    "python.analysis.typeEvaluation.deprecateTypingAliases": true
}
```

---

## 使い方

### フォーマット

| ショートカット | 内容 |
|---|---|
| `Ctrl+Shift+I` | ruffでフォーマット |
| `Alt+Shift+O` | importの整理 |

保存時の自動フォーマットは設定していない（任意のタイミングで実行する運用）。

### 型チェック（strict）

Pylanceがファイルを開いた時点からstrictモードで型エラーを表示する。関数の引数・戻り値に型アノテーションがないとすぐ警告が出るレベルの厳しさ。これをクリアしておくと後続の `mypy` チェックも通りやすい。

### スペルチェック

辞書にない単語は青線で表示される。該当語にクイックフィックス→「Add word to user-custom」で `~/.cspell/user-custom.txt` に登録できる。

### 実行・デバッグ

- `F5` またはエディタ右上の再生ボタンでデバッグ実行（debugpy使用）
- 左下のステータスバーからインタープリター/venvを選択（Python Environments拡張）

---

## 備考

- ホームディレクトリ（`/home/htakumi`）は42tokyoの5GBクォータ制限下にあるため、拡張機能インストール時に `ENOSPC` で失敗することがある。発生した場合はゴミ箱（`~/.local/share/Trash`）や古いキャッシュ、不要な提出物クローンの削除で対処した。
- `/goinfre`, `/sgoinfre` はクォータ対象外の領域。恒久対策が必要なら `~/.vscode/extensions` 等をそちらにシンボリックリンクする選択肢もある（ただし `goinfre` はログアウトで消える場合がある点に注意）。

---

## Mac環境での差分

上記は42校内Linux環境（goinfreやホームクォータがある前提）向けの内容。個人のMacで同じセットアップをする場合は以下が変わる。

### `code` コマンドのパス

Linuxでは `/usr/bin/code` に固定パスで存在したが、Macには標準でそのパスはない。VSCodeを起動し、コマンドパレット（`Cmd+Shift+P`）から以下を実行してPATHに通す。

```
Shell Command: Install 'code' command in PATH
```

有効化後は `code` コマンドとしてPATH経由で呼べるようになるので、エイリアスは固定パス不要。

```bash
# ~/.zshrc (Macでも標準シェルはzshなのでそのまま使える)
alias code_p='code --profile=python'
```

### ディスククォータ・goinfre関連

- 42校内特有のNFSマウント（`/goinfre`, `/sgoinfre`）や5GBホームクォータはMacには存在しない。「備考」セクションのENOSPC対処やシンボリックリンクの話はMacでは不要。
- 自分のMacのディスク容量次第だが、基本的に容量不足でハマることは想定しにくい。

### 変更不要な部分

- プロファイル作成手順（`code --new-window --profile=python` でプロファイル作成、`code --profile=python --install-extension ...` で拡張機能インストール）
- 拡張機能一覧・`settings.json` の内容（ruff設定、strict型チェック、cSpellのユーザー辞書パスなど）
- フォーマット・デバッグ・スペルチェックの使い方

これらはクロスプラットフォームな設定なので、そのままMacでも使える。
