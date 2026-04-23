#!/bin/bash
# =============================================================
# test_c05.sh — c05 課題テストスクリプト
# 使い方: bash tests/c05/test_c05.sh
# =============================================================

set -uo pipefail

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

PASS=0
FAIL=0
ERRORS=()

pass() { echo -e "  ${GREEN}[PASS]${NC} $1"; ((PASS++)) || true; }
fail() { echo -e "  ${RED}[FAIL]${NC} $1${2:+ — $2}"; ((FAIL++)) || true; ERRORS+=("$1"); }
info() { echo -e "\n${BLUE}▶ $1${NC}"; }
warn() { echo -e "  ${YELLOW}[WARN]${NC} $1"; }

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/../.." && pwd)"
SUBMIT_DIR="$ROOT_DIR/c05/intra-uuid-d4e91ff7-50d3-4ad3-a17c-b5b33529af0c-7341950-htakumi"
TEST_DIR="$SCRIPT_DIR"
TMP_DIR=$(mktemp -d)
trap 'rm -rf "$TMP_DIR"' EXIT

# =============================================================
# 共通ヘルパー
# =============================================================

compile_check() {
    local SRC="$1"
    local MAIN="$2"
    local BIN="$3"
    local CC_OUT
    if ! CC_OUT=$(cc -Wall -Wextra -Werror "$SRC" "$MAIN" -o "$BIN" 2>&1); then
        fail "コンパイル" "$CC_OUT"
        return 1
    fi
    pass "コンパイル (-Wall -Wextra -Werror)"
    return 0
}

norminette_check() {
    local SRC="$1"
    if command -v norminette &>/dev/null; then
        local NORM_OUT
        NORM_OUT=$(norminette -R CheckForbiddenSourceHeader "$SRC" 2>&1)
        if echo "$NORM_OUT" | grep -q "Error!"; then
            fail "Norminette" "$(echo "$NORM_OUT" | grep "Error!" | head -5)"
        else
            pass "Norminette"
        fi
    else
        warn "norminette が見つかりません（スキップ）"
    fi
}

forbidden_check() {
    # 提出ファイル単体のオブジェクトで禁止関数を確認（テスト用 main の printf は除外）
    local SRC="$1"
    local OBJ="$TMP_DIR/$(basename "$SRC" .c).o"
    local ALLOWED="${2:-_start|__libc|__cxa|dyld}"
    local OBJ_OUT
    if ! OBJ_OUT=$(cc -Wall -Wextra -Werror -c "$SRC" -o "$OBJ" 2>&1); then
        warn "禁止関数チェック: オブジェクト生成失敗（スキップ）"
        return
    fi
    local FORBIDDEN
    FORBIDDEN=$(nm -u "$OBJ" 2>/dev/null | grep "U " | grep -v -E "$ALLOWED" || true)
    if [ -n "$FORBIDDEN" ]; then
        fail "禁止関数チェック" "$FORBIDDEN"
    else
        pass "禁止関数チェック"
    fi
}

valgrind_check() {
    local BIN="$1"
    if command -v valgrind &>/dev/null; then
        valgrind --leak-check=full --error-exitcode=1 --quiet "$BIN" >/dev/null 2>&1 \
            && pass "valgrind: メモリリークなし" \
            || fail "valgrind: メモリリーク検出"
    elif command -v leaks &>/dev/null; then
        leaks --atExit -- "$BIN" >/dev/null 2>&1 \
            && pass "leaks: メモリリークなし" \
            || fail "leaks: メモリリーク検出"
    else
        warn "valgrind / leaks が見つかりません（スキップ）"
    fi
}

# =============================================================
# ex00 — ft_iterative_factorial
# =============================================================

test_ex00() {
    local EX="ex00"
    local FUNC="ft_iterative_factorial"
    info "Testing $EX — $FUNC"

    local SRC="$SUBMIT_DIR/$EX/${FUNC}.c"
    local MAIN="$TEST_DIR/main_${EX}.c"
    local BIN="$TMP_DIR/${EX}_bin"

    [ ! -f "$SRC" ] && fail "ファイル存在確認" "$SRC が見つかりません" && return
    pass "ファイル存在確認: $(basename "$SRC")"

    norminette_check "$SRC"
    compile_check "$SRC" "$MAIN" "$BIN" || return

    local EXPECTED ACTUAL
    EXPECTED="1
1
120
3628800
479001600
0
0"
    ACTUAL=$("$BIN" 2>&1)
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "動作テスト (0!, 1!, 5!, 10!, 12!, -1, -5)" \
        || fail "動作テスト" "expected=$(echo "$EXPECTED" | cat -A) got=$(echo "$ACTUAL" | cat -A)"

    forbidden_check "$SRC" "_start|__libc|__cxa|dyld"
    valgrind_check "$BIN"
}

# =============================================================
# ex01 — ft_recursive_factorial
# =============================================================

test_ex01() {
    local EX="ex01"
    local FUNC="ft_recursive_factorial"
    info "Testing $EX — $FUNC"

    local SRC="$SUBMIT_DIR/$EX/${FUNC}.c"
    local MAIN="$TEST_DIR/main_${EX}.c"
    local BIN="$TMP_DIR/${EX}_bin"

    [ ! -f "$SRC" ] && fail "ファイル存在確認" "$SRC が見つかりません" && return
    pass "ファイル存在確認: $(basename "$SRC")"

    norminette_check "$SRC"

    # コンパイル（提出ファイルの関数名が ft_iterative_factorial になっているためリンクエラーになる可能性あり）
    local CC_OUT
    if ! CC_OUT=$(cc -Wall -Wextra -Werror "$SRC" "$MAIN" -o "$BIN" 2>&1); then
        fail "コンパイル" "$CC_OUT"
        warn "注意: 提出ファイル内の関数名が ft_recursive_factorial ではなく ft_iterative_factorial になっている疑いあり"
        return
    fi
    pass "コンパイル (-Wall -Wextra -Werror)"

    local EXPECTED ACTUAL
    EXPECTED="1
1
120
3628800
479001600
0
0"
    ACTUAL=$("$BIN" 2>&1)
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "動作テスト (0!, 1!, 5!, 10!, 12!, -1, -5)" \
        || fail "動作テスト" "expected=$(echo "$EXPECTED" | cat -A) got=$(echo "$ACTUAL" | cat -A)"

    forbidden_check "$SRC" "_start|__libc|__cxa|dyld"
    valgrind_check "$BIN"
}

# =============================================================
# ex02 — ft_iterative_power
# =============================================================

test_ex02() {
    local EX="ex02"
    local FUNC="ft_iterative_power"
    info "Testing $EX — $FUNC"

    local SRC="$SUBMIT_DIR/$EX/${FUNC}.c"
    local MAIN="$TEST_DIR/main_${EX}.c"
    local BIN="$TMP_DIR/${EX}_bin"

    [ ! -f "$SRC" ] && fail "ファイル存在確認" "$SRC が見つかりません" && return
    pass "ファイル存在確認: $(basename "$SRC")"

    norminette_check "$SRC"
    compile_check "$SRC" "$MAIN" "$BIN" || return

    local EXPECTED ACTUAL
    EXPECTED="1
5
25
125
1024
1
0
9"
    ACTUAL=$("$BIN" 2>&1)
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "動作テスト (5^0, 5^1, 5^2, 5^3, 2^10, 0^0, 5^-1, (-3)^2)" \
        || fail "動作テスト" "expected=$(echo "$EXPECTED" | cat -A) got=$(echo "$ACTUAL" | cat -A)"

    forbidden_check "$SRC" "_start|__libc|__cxa|dyld"
    valgrind_check "$BIN"
}

# =============================================================
# ex03 — ft_recursive_power
# =============================================================

test_ex03() {
    local EX="ex03"
    local FUNC="ft_recursive_power"
    info "Testing $EX — $FUNC"

    local SRC="$SUBMIT_DIR/$EX/${FUNC}.c"
    local MAIN="$TEST_DIR/main_${EX}.c"
    local BIN="$TMP_DIR/${EX}_bin"

    [ ! -f "$SRC" ] && fail "ファイル存在確認" "$SRC が見つかりません" && return
    pass "ファイル存在確認: $(basename "$SRC")"

    norminette_check "$SRC"
    compile_check "$SRC" "$MAIN" "$BIN" || return

    local EXPECTED ACTUAL
    EXPECTED="1
5
25
125
1024
1
0
9"
    ACTUAL=$("$BIN" 2>&1)
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "動作テスト (5^0, 5^1, 5^2, 5^3, 2^10, 0^0, 5^-1, (-3)^2)" \
        || fail "動作テスト" "expected=$(echo "$EXPECTED" | cat -A) got=$(echo "$ACTUAL" | cat -A)"

    forbidden_check "$SRC" "_start|__libc|__cxa|dyld"
    valgrind_check "$BIN"
}

# =============================================================
# ex04 — ft_fibonacci
# =============================================================

test_ex04() {
    local EX="ex04"
    local FUNC="ft_fibonacci"
    info "Testing $EX — $FUNC"

    local SRC="$SUBMIT_DIR/$EX/${FUNC}.c"
    local MAIN="$TEST_DIR/main_${EX}.c"
    local BIN="$TMP_DIR/${EX}_bin"

    [ ! -f "$SRC" ] && fail "ファイル存在確認" "$SRC が見つかりません" && return
    pass "ファイル存在確認: $(basename "$SRC")"

    norminette_check "$SRC"
    compile_check "$SRC" "$MAIN" "$BIN" || return

    local EXPECTED ACTUAL
    EXPECTED="-1
0
1
1
2
5
55"
    ACTUAL=$("$BIN" 2>&1)
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "動作テスト (index=-1, 0, 1, 2, 3, 5, 10)" \
        || fail "動作テスト" "expected=$(echo "$EXPECTED" | cat -A) got=$(echo "$ACTUAL" | cat -A)"

    forbidden_check "$SRC" "_start|__libc|__cxa|dyld"
    valgrind_check "$BIN"
}

# =============================================================
# ex05 — ft_sqrt
# =============================================================

test_ex05() {
    local EX="ex05"
    local FUNC="ft_sqrt"
    info "Testing $EX — $FUNC"

    local SRC="$SUBMIT_DIR/$EX/${FUNC}.c"
    local MAIN="$TEST_DIR/main_${EX}.c"
    local BIN="$TMP_DIR/${EX}_bin"

    [ ! -f "$SRC" ] && fail "ファイル存在確認" "$SRC が見つかりません" && return
    pass "ファイル存在確認: $(basename "$SRC")"

    norminette_check "$SRC"
    compile_check "$SRC" "$MAIN" "$BIN" || return

    local EXPECTED ACTUAL
    EXPECTED="0
0
1
2
3
5
9
0
0
46340"
    ACTUAL=$("$BIN" 2>&1)
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "動作テスト (-1, 0, 1, 4, 9, 25, 81, 2, 3, 46340^2)" \
        || fail "動作テスト" "expected=$(echo "$EXPECTED" | cat -A) got=$(echo "$ACTUAL" | cat -A)"

    forbidden_check "$SRC" "_start|__libc|__cxa|dyld"
    valgrind_check "$BIN"
}

# =============================================================
# ex06 — ft_is_prime
# =============================================================

test_ex06() {
    local EX="ex06"
    local FUNC="ft_is_prime"
    info "Testing $EX — $FUNC"

    local SRC="$SUBMIT_DIR/$EX/${FUNC}.c"
    local MAIN="$TEST_DIR/main_${EX}.c"
    local BIN="$TMP_DIR/${EX}_bin"

    [ ! -f "$SRC" ] && fail "ファイル存在確認" "$SRC が見つかりません" && return
    pass "ファイル存在確認: $(basename "$SRC")"

    norminette_check "$SRC"
    compile_check "$SRC" "$MAIN" "$BIN" || return

    local EXPECTED ACTUAL
    EXPECTED="0
0
0
1
1
0
1
0
1"
    ACTUAL=$("$BIN" 2>&1)
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "動作テスト (-1, 0, 1, 2, 3, 4, 11, 15, 71)" \
        || fail "動作テスト" "expected=$(echo "$EXPECTED" | cat -A) got=$(echo "$ACTUAL" | cat -A)"

    forbidden_check "$SRC" "_start|__libc|__cxa|dyld"
    valgrind_check "$BIN"
}

# =============================================================
# ex07 — ft_find_next_prime
# =============================================================

test_ex07() {
    local EX="ex07"
    local FUNC="ft_find_next_prime"
    info "Testing $EX — $FUNC"

    local SRC="$SUBMIT_DIR/$EX/${FUNC}.c"
    local MAIN="$TEST_DIR/main_${EX}.c"
    local BIN="$TMP_DIR/${EX}_bin"

    [ ! -f "$SRC" ] && fail "ファイル存在確認" "$SRC が見つかりません" && return
    pass "ファイル存在確認: $(basename "$SRC")"

    norminette_check "$SRC"
    compile_check "$SRC" "$MAIN" "$BIN" || return

    local EXPECTED ACTUAL
    EXPECTED="2
2
2
2
13
17"
    ACTUAL=$("$BIN" 2>&1)
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "動作テスト (-5, 0, 1, 2, 12, 15)" \
        || fail "動作テスト" "expected=$(echo "$EXPECTED" | cat -A) got=$(echo "$ACTUAL" | cat -A)"

    forbidden_check "$SRC" "_start|__libc|__cxa|dyld"
    valgrind_check "$BIN"
}

# =============================================================
# メイン実行
# =============================================================
echo "========================================"
echo " 42Tokyo — c05 テスト"
echo " $(date '+%Y-%m-%d %H:%M:%S')"
echo "========================================"

test_ex00
test_ex01
test_ex02
test_ex03
test_ex04
test_ex05
test_ex06
test_ex07

echo ""
echo "========================================"
echo -e " 結果: ${GREEN}${PASS} passed${NC} / ${RED}${FAIL} failed${NC}"
if [ ${#ERRORS[@]} -gt 0 ]; then
    echo " 失敗したテスト:"
    for err in "${ERRORS[@]}"; do echo "   ✗ $err"; done
fi
echo "========================================"
[ $FAIL -eq 0 ] && exit 0 || exit 1
