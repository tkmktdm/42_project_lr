#!/bin/bash
# =============================================================
# test_python01.sh — pythonModule01 (Code Cultivation) テストスクリプト
# 使い方: bash cursus/circle2/pythonModule01/tests/test_python01.sh
#   別の場所の解答を試す: SRC_DIR=/path/to/42_develop bash test_python01.sh
#
# Makefile はない課題なので、Python で各ファイルを直接実行する。
#
# 確認内容（ファイルごと）
#   1. flake8
#   2. mypy（全関数・メソッドに型ヒントが必須なので未注釈の関数も検出）
#   3. 使用可能関数（import 禁止、許可されていない関数呼び出し・デコレータ）
#   4. python3 で直接実行してエラーが出ない
#   5. 動作テスト（クラスを import して仕様どおりに動くか）
#   6. PDF の実行例との比較 → 実装の自由度が高い課題なので [WARN] 扱い
#
# 判定
#   [OK] / [FAIL] … 仕様で決まっている点
#   [WARN]        … PDF の実行例と出力が違う（失敗には数えない）
#   [SKIP]        … ファイルがない、または雛形のまま（失敗には数えない）
#
# 動作テストが想定しているコンストラクタ（違う場合はカスタマイズ欄を直す）
#   Plant(name, height, age)                 ex3 以降
#   Flower(name, height, age, color)         ex5 以降
#   Tree(name, height, age, trunk_diameter)  ex5 以降
#   Vegetable(name, height, age, harvest_season)  栄養価は 0 から始まる
#   Seed(name, height, age, color)           ex6
#   grow() / age() は引数なしで呼べる（デフォルト引数は OK）
#
# 【自分でカスタマイズできる箇所】
#   - 各 test_exN() 内の「カスタマイズここから/ここまで」ブロック
#   - 動作テストの追加: run_py を1行追記するだけ
#       run_py "名前" 'Python のコード（assert で判定）'
#     コード内で使えるもの
#       m                 提出ファイルを import したモジュール
#       out(f, *args)     f(*args) が print した文字列
#       make(cls, *args)  (生成したオブジェクト, 生成時に print した文字列)
#       script()          python3 で直接実行したときの出力
#       plant_lines(s)    s の中の「名前: 25.0cm, 30 days old」形式の行
#       number(label, s)  s の中で label の後ろにある整数
#       uses_super("C")   クラス C の中で super() を呼んでいるか
#       nested_class("C") クラス C の中に入れ子のクラスがあるか
#       module_funcs()    クラス外にある引数1つの関数の一覧
#       has_main()        if __name__ == "__main__": があるか
#       re                正規表現モジュール
# =============================================================

export PATH="$PATH:$HOME/.local/bin"

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
SRC_DIR="${SRC_DIR:-$SCRIPT_DIR/../42_develop}"
TMP_DIR="$(mktemp -d)"
RUNNER="$TMP_DIR/runner.py"
SCRIPT_OUT="$TMP_DIR/script_out.txt"
trap 'rm -rf "$TMP_DIR"' EXIT

PASS=0
FAIL=0
WARN=0
SKIP=0
CUR_FILE=""

GREEN=$'\033[32m'
RED=$'\033[31m'
YELLOW=$'\033[33m'
CYAN=$'\033[36m'
RESET=$'\033[0m'

cat > "$RUNNER" <<'PYTHON'
import ast
import contextlib
import importlib.util
import inspect
import io
import os
import re
import sys
import traceback

PLANT_LINE = r"^\s*\S.*: \d+(?:\.\d+)?cm, \d+ days old\s*$"


def load_tree(path):
    with open(path, encoding="utf-8") as file:
        return ast.parse(file.read(), path)


def is_main(node):
    return (isinstance(node, ast.If)
            and isinstance(node.test, ast.Compare)
            and isinstance(node.test.left, ast.Name)
            and node.test.left.id == "__name__")


def skeleton(path):
    for node in load_tree(path).body:
        if isinstance(node, ast.Expr) and isinstance(node.value,
                                                     ast.Constant):
            continue
        if is_main(node) and all(isinstance(n, ast.Pass)
                                 for n in node.body):
            continue
        return 1
    return 0


def check(path, allowed):
    tree = load_tree(path)
    names = allowed | {n.name for n in ast.walk(tree)
                       if isinstance(n, (ast.FunctionDef, ast.ClassDef))}
    # cls() のように引数で受け取ったものを呼ぶのは組み込み関数ではない
    names |= {a.arg for n in ast.walk(tree) if isinstance(n, ast.arguments)
              for a in n.posonlyargs + n.args + n.kwonlyargs}
    errors = []
    for node in ast.walk(tree):
        if isinstance(node, (ast.Import, ast.ImportFrom)):
            errors.append(f"line {node.lineno}: import は使用不可")
        if isinstance(node, ast.Call) and isinstance(node.func, ast.Name):
            if node.func.id not in names:
                errors.append(f"line {node.lineno}: {node.func.id}() は"
                              " 使用不可")
        if isinstance(node, (ast.FunctionDef, ast.ClassDef)):
            for deco in node.decorator_list:
                if isinstance(deco, ast.Name) and deco.id not in names:
                    errors.append(f"line {deco.lineno}: @{deco.id} は"
                                  " 使用不可")
    for error in errors:
        print(error)
    return 1 if errors else 0


def load(path):
    spec = importlib.util.spec_from_file_location("target", path)
    module = importlib.util.module_from_spec(spec)
    sys.modules["target"] = module
    with contextlib.redirect_stdout(io.StringIO()):
        spec.loader.exec_module(module)
    return module


def case(path, code):
    tree = load_tree(path)

    def class_node(name):
        for node in ast.walk(tree):
            if isinstance(node, ast.ClassDef) and node.name == name:
                return node
        return None

    def out(func, *args):
        buf = io.StringIO()
        with contextlib.redirect_stdout(buf):
            func(*args)
        return buf.getvalue()

    def make(cls, *args):
        box = []
        text = out(lambda: box.append(cls(*args)))
        return box[0], text

    def script():
        with open(os.environ["SCRIPT_OUT"], encoding="utf-8") as file:
            return file.read()

    def plant_lines(text):
        return re.findall(PLANT_LINE, text, re.M)

    def number(label, text):
        found = re.search(re.escape(label) + r"\D*(\d+)", text)
        assert found, f"'{label}' の後ろに数値がない: {text!r}"
        return int(found.group(1))

    def uses_super(name):
        node = class_node(name)
        return node is not None and any(
            isinstance(n, ast.Call) and isinstance(n.func, ast.Name)
            and n.func.id == "super" for n in ast.walk(node))

    def nested_class(name):
        node = class_node(name)
        return node is not None and any(isinstance(n, ast.ClassDef)
                                        for n in node.body)

    def module_funcs():
        return [f for f in vars(module).values()
                if inspect.isfunction(f) and f.__module__ == "target"
                and len(inspect.signature(f).parameters) == 1]

    def has_main():
        return any(is_main(n) for n in tree.body)

    try:
        module = load(path)
        exec(code, {"m": module, "out": out, "make": make,
                    "script": script, "plant_lines": plant_lines,
                    "number": number, "uses_super": uses_super,
                    "nested_class": nested_class,
                    "module_funcs": module_funcs, "has_main": has_main,
                    "re": re})
    except AssertionError as error:
        print(f"条件を満たしていない: {error}" if str(error)
              else "条件を満たしていない")
        print(f"コード: {code}")
        return 1
    except Exception:
        lines = traceback.format_exc().strip().splitlines()
        print("\n".join(lines[-3:]))
        print(f"コード: {code}")
        return 1
    return 0


if sys.argv[1] == "skeleton":
    sys.exit(skeleton(sys.argv[2]))
if sys.argv[1] == "check":
    sys.exit(check(sys.argv[2], set(sys.argv[3].split(","))))
sys.exit(case(sys.argv[2], sys.argv[3]))
PYTHON

find_python() {
    local candidate
    for candidate in python3 python3.13 python3.12 python3.11 python3.10 \
        "$HOME"/.pyenv/versions/3.1[0-9]*/bin/python3 \
        /opt/homebrew/bin/python3; do
        if "$candidate" -c \
            'import sys; sys.exit(sys.version_info < (3, 10))' \
            >/dev/null 2>&1; then
            echo "$candidate"
            return 0
        fi
    done
    return 1
}

PYTHON_BIN="$(find_python)"
if [ -z "$PYTHON_BIN" ]; then
    echo "${RED}Python 3.10 以上が見つかりません${RESET}"
    exit 1
fi

ok() {
    echo "  ${GREEN}[OK]${RESET} $1"
    PASS=$((PASS + 1))
}

ng() {
    echo "  ${RED}[FAIL]${RESET} $1"
    [ -n "$2" ] && echo "$2" | sed 's/^/      /'
    FAIL=$((FAIL + 1))
}

warn() {
    echo "  ${CYAN}[WARN]${RESET} $1"
    [ -n "$2" ] && echo "$2" | sed 's/^/      /'
    WARN=$((WARN + 1))
}

skip() {
    echo "  ${YELLOW}[SKIP]${RESET} $1"
    SKIP=$((SKIP + 1))
}

# 共通チェック。ファイルがない・雛形のままなら 1 を返して、その課題を飛ばす
begin_file() {
    local dir="$1" module="$2" allowed="$3" output err

    CUR_FILE="$SRC_DIR/$dir/$module.py"
    echo
    echo "=== $dir/$module.py ==="
    if [ ! -f "$CUR_FILE" ]; then
        skip "提出ファイルなし"
        return 1
    fi
    if "$PYTHON_BIN" -B "$RUNNER" skeleton "$CUR_FILE" >/dev/null 2>&1; then
        skip "未実装（雛形のまま）"
        return 1
    fi

    if command -v flake8 >/dev/null 2>&1; then
        if output="$(flake8 "$CUR_FILE" 2>&1)"; then
            ok "flake8"
        else
            ng "flake8" "$output"
        fi
    else
        skip "flake8 が見つかりません"
    fi

    if command -v mypy >/dev/null 2>&1; then
        if output="$(mypy --cache-dir="$TMP_DIR/mypy" \
            --disallow-untyped-defs --disallow-incomplete-defs \
            "$CUR_FILE" 2>&1)"; then
            ok "mypy（型ヒント）"
        else
            ng "mypy（型ヒント）" "$output"
        fi
    else
        skip "mypy が見つかりません"
    fi

    if output="$("$PYTHON_BIN" -B "$RUNNER" check "$CUR_FILE" \
        "$allowed" 2>&1)"; then
        ok "使用可能関数（$allowed）"
    else
        ng "使用可能関数（$allowed）" "$output"
    fi

    err="$TMP_DIR/stderr.txt"
    if (cd "$SRC_DIR/$dir" && "$PYTHON_BIN" -B "$module.py" \
        </dev/null >"$SCRIPT_OUT" 2>"$err") && [ ! -s "$err" ]; then
        ok "python3 $module.py がエラーなく動く"
    else
        ng "python3 $module.py がエラーなく動く" "$(tail -n 5 "$err")"
    fi
    return 0
}

# 動作テスト: Python のコードを実行し、assert が通れば OK
run_py() {
    local name="$1" code="$2" output

    if output="$(SCRIPT_OUT="$SCRIPT_OUT" "$PYTHON_BIN" -B "$RUNNER" case \
        "$CUR_FILE" "$code" 2>&1)"; then
        ok "$name"
    else
        ng "$name" "$output"
    fi
}

# PDF の実行例との比較。標準入力に期待する出力を渡す（$> の行は除く）
# 行末の空白は無視する。違っても [WARN] で、失敗には数えない
compare_example() {
    local expected actual

    expected="$(sed 's/[[:space:]]*$//')"
    actual="$(sed 's/[[:space:]]*$//' "$SCRIPT_OUT")"
    if [ "$actual" = "$expected" ]; then
        ok "PDF の実行例と完全一致"
    else
        warn "PDF の実行例と出力が違う（自由に実装してよい部分なら問題なし）" \
            "$(diff -u <(echo "$expected") <(echo "$actual") \
                --label "PDF の例" --label "実際" | tail -n +3 | head -n 40)"
    fi
}

test_ex0() {
    begin_file ex0 ft_garden_intro "print" || return
    # ===== カスタマイズここから =====
    run_py "if __name__ == \"__main__\": を使っている" 'assert has_main()'
    run_py "Plant / Height / Age を表示" \
        's = script(); assert all(k in s for k in ("Plant:", "Height:", "Age:")), s'
    compare_example <<'EOF'
=== Welcome to My Garden ===
Plant: Rose
Height: 25cm
Age: 30 days

=== End of Program ===
EOF
    # ===== カスタマイズここまで =====
}

test_ex1() {
    begin_file ex1 ft_garden_data "print" || return
    # ===== カスタマイズここから =====
    run_py "Plant クラスがある" 'assert isinstance(getattr(m, "Plant", None), type)'
    run_py "show() メソッドがある" 'assert callable(getattr(m.Plant, "show", None))'
    run_py "3 種類以上の植物を表示" \
        'n = len(plant_lines(script())); assert n >= 3, f"{n} 件しかない"'
    compare_example <<'EOF'
=== Garden Plant Registry ===
Rose: 25cm, 30 days old
Sunflower: 80cm, 45 days old
Cactus: 15cm, 120 days old
EOF
    # ===== カスタマイズここまで =====
}

test_ex2() {
    begin_file ex2 ft_plant_growth "print,range,round" || return
    # ===== カスタマイズここから =====
    run_py "grow() / age() メソッドがある" \
        'assert all(callable(getattr(m.Plant, k, None)) for k in ("grow", "age", "show"))'
    run_py "初期状態と 7 日分の植物を表示" \
        'n = len(plant_lines(script())); assert n >= 8, f"{n} 件しかない"'
    run_py "1 週間の成長量を表示" \
        'assert re.search(r"[Gg]rowth.*\d+(\.\d+)?cm", script()), script()'
    compare_example <<'EOF'
=== Garden Plant Growth ===
Rose: 25.0cm, 30 days old
=== Day 1 ===
Rose: 25.8cm, 31 days old
=== Day 2 ===
Rose: 26.6cm, 32 days old
=== Day 3 ===
Rose: 27.4cm, 33 days old
=== Day 4 ===
Rose: 28.2cm, 34 days old
=== Day 5 ===
Rose: 29.0cm, 35 days old
=== Day 6 ===
Rose: 29.8cm, 36 days old
=== Day 7 ===
Rose: 30.6cm, 37 days old
Growth this week: 5.6cm
EOF
    # ===== カスタマイズここまで =====
}

test_ex3() {
    begin_file ex3 ft_plant_factory "print,range,round" || return
    # ===== カスタマイズここから =====
    run_py "Plant(名前, 高さ, 年齢) で生成して show()" \
        'p = make(m.Plant, "Rose", 25.0, 30)[0]; s = out(p.show); assert s.strip() == "Rose: 25.0cm, 30 days old", s'
    run_py "生成直後に grow() / age() できる" \
        'p = make(m.Plant, "Rose", 25.0, 30)[0]; before = out(p.show); out(p.grow); out(p.age); after = out(p.show); assert before != after, after'
    run_py "5 種類以上の植物を表示" \
        'n = len(plant_lines(script())); assert n >= 5, f"{n} 件しかない"'
    compare_example <<'EOF'
=== Plant Factory Output ===
Created: Rose: 25.0cm, 30 days old
Created: Oak: 200.0cm, 365 days old
Created: Cactus: 5.0cm, 90 days old
Created: Sunflower: 80.0cm, 45 days old
Created: Fern: 15.0cm, 120 days old
EOF
    # ===== カスタマイズここまで =====
}

test_ex4() {
    begin_file ex4 ft_garden_security "print,range,round" || return
    # ===== カスタマイズここから =====
    run_py "get_height() / get_age()" \
        'p = make(m.Plant, "Rose", 15.0, 10)[0]; assert (p.get_height(), p.get_age()) == (15.0, 10), (p.get_height(), p.get_age())'
    run_py "set_height() / set_age() で更新" \
        'p = make(m.Plant, "Rose", 15.0, 10)[0]; out(p.set_height, 25); out(p.set_age, 30); assert (p.get_height(), p.get_age()) == (25, 30), (p.get_height(), p.get_age())'
    run_py "負の高さは拒否してエラー表示" \
        'p = make(m.Plant, "Rose", 25.0, 30)[0]; s = out(p.set_height, -5); assert p.get_height() == 25.0, p.get_height(); assert s.strip(), "エラーメッセージがない"'
    run_py "負の年齢は拒否してエラー表示" \
        'p = make(m.Plant, "Rose", 25.0, 30)[0]; s = out(p.set_age, -1); assert p.get_age() == 30, p.get_age(); assert s.strip(), "エラーメッセージがない"'
    run_py "負の値で生成しても壊れない" \
        'p, s = make(m.Plant, "Bad", -10.0, -3); assert p.get_height() >= 0 and p.get_age() >= 0, (p.get_height(), p.get_age()); assert s.strip(), "エラーメッセージがない"'
    run_py "属性は protected（_ 付き、マングリングなし）" \
        'p = make(m.Plant, "Rose", 15.0, 10)[0]; bad = [k for k in vars(p) if not k.startswith("_") or k.startswith("_Plant__")]; assert not bad, f"直接使える属性: {bad}"'
    compare_example <<'EOF'
=== Garden Security System ===
Plant created: Rose: 15.0cm, 10 days old

Height updated: 25cm
Age updated: 30 days

Rose: Error, height can't be negative
Height update rejected
Rose: Error, age can't be negative
Age update rejected

Current state: Rose: 25.0cm, 30 days old
EOF
    # ===== カスタマイズここまで =====
}

test_ex5() {
    begin_file ex5 ft_plant_types "super,print,range,round" || return
    # ===== カスタマイズここから =====
    run_py "Flower / Tree / Vegetable が Plant を継承" \
        'assert all(issubclass(getattr(m, c), m.Plant) for c in ("Flower", "Tree", "Vegetable"))'
    run_py "各クラスで super() を使っている" \
        'bad = [c for c in ("Flower", "Tree", "Vegetable") if not uses_super(c)]; assert not bad, bad'
    run_py "Flower: 色の表示と bloom()" \
        'f = make(m.Flower, "Rose", 15.0, 10, "red")[0]; before = out(f.show); out(f.bloom); after = out(f.show); assert "Rose: 15.0cm, 10 days old" in before and "red" in before, before; assert after != before, "bloom() の前後で show() が同じ"'
    run_py "Tree: 幹の直径と produce_shade()" \
        't = make(m.Tree, "Oak", 200.0, 365, 5.0)[0]; s = out(t.show); assert "Oak: 200.0cm, 365 days old" in s and "5.0" in s, s; assert out(t.produce_shade).strip(), "produce_shade() が何も表示しない"'
    run_py "Vegetable: 栄養価が 0 から grow()/age() で増える" \
        'v = make(m.Vegetable, "Tomato", 5.0, 10, "April")[0]; s = out(v.show); assert "April" in s, s; before = number("Nutritional value", s); assert before == 0, s; out(v.grow); out(v.age); after = number("Nutritional value", out(v.show)); assert after > before, (before, after)'
    compare_example <<'EOF'
=== Garden Plant Types ===
=== Flower
Rose: 15.0cm, 10 days old
 Color: red
 Rose has not bloomed yet
[asking the rose to bloom]
Rose: 15.0cm, 10 days old
 Color: red
 Rose is blooming beautifully!

=== Tree
Oak: 200.0cm, 365 days old
 Trunk diameter: 5.0cm
[asking the oak to produce shade]
Tree Oak now produces a shade of 200.0cm long and 5.0cm wide.

=== Vegetable
Tomato: 5.0cm, 10 days old
 Harvest season: April
 Nutritional value: 0
[make tomato grow and age for 20 days]
Tomato: 47.0cm, 30 days old
 Harvest season: April
 Nutritional value: 20
EOF
    # ===== カスタマイズここまで =====
}

test_ex6() {
    begin_file ex6 ft_garden_analytics \
        "super,print,range,round,staticmethod,classmethod" || return
    # ===== カスタマイズここから =====
    run_py "静的メソッドで 1 年を超えるか判定" \
        'fs = [getattr(m.Plant, k) for k, v in vars(m.Plant).items() if isinstance(v, staticmethod)]; assert fs, "Plant に staticmethod がない"; assert any(f(30) is False and f(400) is True for f in fs), "30 -> False, 400 -> True にならない"'
    run_py "クラスメソッドで匿名の植物を作る" \
        'cs = [getattr(m.Plant, k) for k, v in vars(m.Plant).items() if isinstance(v, classmethod)]; assert cs, "Plant に classmethod がない"; p = make(cs[0])[0]; assert isinstance(p, m.Plant), p'
    run_py "Seed が Flower を継承し、開花後に種の数が増える" \
        'assert issubclass(m.Seed, m.Flower); s = make(m.Seed, "Sunflower", 80.0, 45, "yellow")[0]; assert number("Seeds", out(s.show)) == 0; out(s.bloom); assert number("Seeds", out(s.show)) > 0'
    run_py "Plant の中に統計用の入れ子クラスがある" 'assert nested_class("Plant")'
    run_py "クラス外の統計関数が grow/age の回数を反映" \
        'fs = module_funcs(); assert fs, "クラス外に引数1つの関数がない"; p = make(m.Plant, "Rose", 15.0, 10)[0]; out(p.grow); out(p.grow); out(p.age); s = out(fs[0], p); assert re.search(r"\b2\b", s) and re.search(r"\b1\b", s), s'
    run_py "Tree は produce_shade() の回数も数える" \
        'f = module_funcs()[0]; t = make(m.Tree, "Oak", 200.0, 365, 5.0)[0]; before = out(f, t); out(t.produce_shade); out(t.produce_shade); after = out(f, t); assert before != after and re.search(r"\b2\b", after), after'
    compare_example <<'EOF'
=== Garden statistics ===
=== Check year-old
Is 30 days more than a year? -> False
Is 400 days more than a year? -> True

=== Flower
Rose: 15.0cm, 10 days old
 Color: red
 Rose has not bloomed yet
[statistics for Rose]
Stats: 0 grow, 0 age, 1 show
[asking the rose to grow and bloom]
Rose: 23.0cm, 10 days old
 Color: red
 Rose is blooming beautifully!
[statistics for Rose]
Stats: 1 grow, 0 age, 2 show

=== Tree
Oak: 200.0cm, 365 days old
 Trunk diameter: 5.0cm
[statistics for Oak]
Stats: 0 grow, 0 age, 1 show
 0 shade
[asking the oak to produce shade]
Tree Oak now produces a shade of 200.0cm long and 5.0cm wide.
[statistics for Oak]
Stats: 0 grow, 0 age, 1 show
 1 shade

=== Seed
Sunflower: 80.0cm, 45 days old
 Color: yellow
 Sunflower has not bloomed yet
 Seeds: 0
[make sunflower grow, age and bloom]
Sunflower: 110.0cm, 65 days old
 Color: yellow
 Sunflower is blooming beautifully!
 Seeds: 42
[statistics for Sunflower]
Stats: 1 grow, 1 age, 2 show

=== Anonymous
Unknown plant: 0.0cm, 0 days old
[statistics for Unknown plant]
Stats: 0 grow, 0 age, 1 show
EOF
    # ===== カスタマイズここまで =====
}

echo "Python: $("$PYTHON_BIN" --version)"
echo "対象: $SRC_DIR"
test_ex0
test_ex1
test_ex2
test_ex3
test_ex4
test_ex5
test_ex6

echo
echo "===== 結果: ${GREEN}OK $PASS${RESET} / ${RED}FAIL $FAIL${RESET} / ${CYAN}WARN $WARN${RESET} / ${YELLOW}SKIP $SKIP${RESET} ====="
[ "$FAIL" -eq 0 ]
