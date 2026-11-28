#!/bin/bash
# =============================================================
# test_python00.sh — python00 (Growing Code) テストスクリプト
# 使い方: bash cursus/circle2/python00/tests/test_python00.sh
#
# Makefile はない課題なので、Python で各関数を直接実行する。
# 入力は自動で渡し、画面表示は PDF の実行例と同じ形で比較する。
#
# 確認内容: flake8 / 関数のみの構成 / 使用可能関数 / 動作 / mypy(ex7)
#
# 【自分でカスタマイズできる箇所】
#   - 各 test_exN() 内の「カスタマイズここから/ここまで」ブロック
#   - テストケースの追加: run_test を1行追記するだけ
#     run_test "名前" "入力(複数行は \n)" "引数タプル" $'期待する出力'
# =============================================================

export PATH="$PATH:$HOME/.local/bin"

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
SRC_DIR="$SCRIPT_DIR/../42_develop"
TMP_DIR="$(mktemp -d)"
RUNNER="$TMP_DIR/runner.py"
trap 'rm -rf "$TMP_DIR"' EXIT

PASS=0
FAIL=0
SKIP=0
CUR_FILE=""
CUR_MODULE=""

GREEN=$'\033[32m'
RED=$'\033[31m'
YELLOW=$'\033[33m'
RESET=$'\033[0m'

cat > "$RUNNER" <<'PYTHON'
import ast
import builtins
import os
import sys


def check(path, allowed, methods_ok):
    with open(path, encoding="utf-8") as file:
        tree = ast.parse(file.read())
    errors = []
    for node in tree.body:
        if not isinstance(node, ast.FunctionDef):
            errors.append(f"line {node.lineno}: 関数の外にコードがある")
    local = {n.name for n in ast.walk(tree)
             if isinstance(n, ast.FunctionDef)}
    for node in ast.walk(tree):
        if isinstance(node, (ast.Import, ast.ImportFrom)):
            errors.append(f"line {node.lineno}: import は使用不可")
        if not isinstance(node, ast.Call):
            continue
        if isinstance(node.func, ast.Name):
            if node.func.id not in allowed | local:
                errors.append(f"line {node.lineno}: {node.func.id}() は"
                              " 使用不可")
        elif not methods_ok:
            errors.append(f"line {node.lineno}: メソッド呼び出しは使用不可")
    for error in errors:
        print(error)
    return 1 if errors else 0


def run(path, func, stdin_text, args_text):
    sys.path.insert(0, os.path.dirname(path))
    module = __import__(os.path.basename(path)[:-3])
    lines = iter(stdin_text.splitlines())

    def fake_input(prompt=""):
        value = next(lines)
        print(f"{prompt}{value}")
        return value

    builtins.input = fake_input
    getattr(module, func)(*ast.literal_eval(args_text))
    return 0


if sys.argv[1] == "check":
    sys.exit(check(sys.argv[2], set(sys.argv[3].split(",")),
                   sys.argv[4] == "1"))
sys.exit(run(sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5]))
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

skip() {
    echo "  ${YELLOW}[SKIP]${RESET} $1"
    SKIP=$((SKIP + 1))
}

# 共通チェック。ファイルがなければ 1 を返して、その関数を飛ばす
begin_file() {
    local dir="$1" module="$2" allowed="$3" methods_ok="$4" output

    CUR_MODULE="$module"
    CUR_FILE="$SRC_DIR/$dir/$module.py"
    echo
    echo "=== $dir/$module.py ==="
    if [ ! -f "$CUR_FILE" ]; then
        skip "提出ファイルなし"
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
    if output="$("$PYTHON_BIN" -B "$RUNNER" check "$CUR_FILE" \
        "$allowed" "$methods_ok" 2>&1)"; then
        ok "関数のみの構成・使用可能関数"
    else
        ng "関数のみの構成・使用可能関数" "$output"
    fi
    return 0
}

run_test() {
    local name="$1" input="$2" args="$3" expected="$4" actual

    actual="$("$PYTHON_BIN" -B "$RUNNER" run "$CUR_FILE" "$CUR_MODULE" \
        "$(printf '%b' "$input")" "$args" 2>&1)"
    if [ "$actual" = "$expected" ]; then
        ok "$name"
    else
        ng "$name" "--- 期待
$expected
--- 実際
$actual"
    fi
}

run_mypy() {
    local output

    if ! command -v mypy >/dev/null 2>&1; then
        skip "mypy が見つかりません"
        return
    fi
    if output="$(mypy --cache-dir="$TMP_DIR/mypy" "$CUR_FILE" 2>&1)"; then
        ok "mypy"
    else
        ng "mypy" "$output"
    fi
}

test_ex0() {
    begin_file ex0 ft_hello_garden "print" 0 || return
    # ===== カスタマイズここから =====
    run_test "PDF の例" "" "()" "Hello, Garden Community!"
    # ===== カスタマイズここまで =====
}

test_ex1() {
    begin_file ex1 ft_garden_name "input,print" 0 || return
    # ===== カスタマイズここから =====
    run_test "PDF の例" "Community Garden" "()" \
        $'Enter garden name: Community Garden\nGarden: Community Garden\nStatus: Growing well!'
    run_test "別の名前" "Rooftop" "()" \
        $'Enter garden name: Rooftop\nGarden: Rooftop\nStatus: Growing well!'
    # ===== カスタマイズここまで =====
}

test_ex2() {
    begin_file ex2 ft_plot_area "input,int,print" 0 || return
    # ===== カスタマイズここから =====
    run_test "PDF の例" "5\n3" "()" \
        $'Enter length: 5\nEnter width: 3\nPlot area: 15'
    run_test "0 を含む" "0\n7" "()" \
        $'Enter length: 0\nEnter width: 7\nPlot area: 0'
    # ===== カスタマイズここまで =====
}

test_ex3() {
    begin_file ex3 ft_harvest_total "input,int,print" 0 || return
    # ===== カスタマイズここから =====
    run_test "PDF の例" "5\n8\n3" "()" \
        $'Day 1 harvest: 5\nDay 2 harvest: 8\nDay 3 harvest: 3\nTotal harvest: 16'
    run_test "すべて 0" "0\n0\n0" "()" \
        $'Day 1 harvest: 0\nDay 2 harvest: 0\nDay 3 harvest: 0\nTotal harvest: 0'
    # ===== カスタマイズここまで =====
}

test_ex4() {
    begin_file ex4 ft_plant_age "input,int,print" 0 || return
    # ===== カスタマイズここから =====
    run_test "PDF の例 75" "75" "()" \
        $'Enter plant age in days: 75\nPlant is ready to harvest!'
    run_test "PDF の例 45" "45" "()" \
        $'Enter plant age in days: 45\nPlant needs more time to grow.'
    run_test "境界 60" "60" "()" \
        $'Enter plant age in days: 60\nPlant needs more time to grow.'
    run_test "境界 61" "61" "()" \
        $'Enter plant age in days: 61\nPlant is ready to harvest!'
    # ===== カスタマイズここまで =====
}

test_ex5() {
    begin_file ex5 ft_water_reminder "input,int,print" 0 || return
    # ===== カスタマイズここから =====
    run_test "PDF の例 4" "4" "()" \
        $'Days since last watering: 4\nWater the plants!'
    run_test "PDF の例 1" "1" "()" \
        $'Days since last watering: 1\nPlants are fine'
    run_test "境界 2" "2" "()" \
        $'Days since last watering: 2\nPlants are fine'
    run_test "境界 3" "3" "()" \
        $'Days since last watering: 3\nWater the plants!'
    # ===== カスタマイズここまで =====
}

test_count_cases() {
    # ===== カスタマイズここから =====
    run_test "PDF の例 5" "5" "()" \
        $'Days until harvest: 5\nDay 1\nDay 2\nDay 3\nDay 4\nDay 5\nHarvest time!'
    run_test "1 日" "1" "()" \
        $'Days until harvest: 1\nDay 1\nHarvest time!'
    run_test "0 日" "0" "()" \
        $'Days until harvest: 0\nHarvest time!'
    # ===== カスタマイズここまで =====
}

test_ex6() {
    if begin_file ex6 ft_count_harvest_iterative "input,int,print,range" 0; then
        test_count_cases
    fi
    if begin_file ex6 ft_count_harvest_recursive "input,int,print,range" 0; then
        test_count_cases
    fi
}

test_ex7() {
    begin_file ex7 ft_seed_inventory "print" 1 || return
    # ===== カスタマイズここから =====
    run_test "packets" "" '("tomato", 15, "packets")' \
        "Tomato seeds: 15 packets available"
    run_test "grams" "" '("carrot", 8, "grams")' \
        "Carrot seeds: 8 grams total"
    run_test "area" "" '("lettuce", 12, "area")' \
        "Lettuce seeds: covers 12 square meters"
    run_test "未対応の単位" "" '("basil", 3, "boxes")' \
        "Unknown unit type"
    # ===== カスタマイズここまで =====
    run_mypy
}

echo "Python: $("$PYTHON_BIN" --version)"
test_ex0
test_ex1
test_ex2
test_ex3
test_ex4
test_ex5
test_ex6
test_ex7

echo
echo "===== 結果: ${GREEN}OK $PASS${RESET} / ${RED}FAIL $FAIL${RESET} / ${YELLOW}SKIP $SKIP${RESET} ====="
[ "$FAIL" -eq 0 ]
