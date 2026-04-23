#!/bin/bash
# =============================================================
# test_c06.sh — c06 課題テストスクリプト
# 使い方: bash tests/c06/test_c06.sh
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
SUBMIT_DIR="$ROOT_DIR/c06/intra-uuid-d04a3862-210f-4c79-8e0d-95f34343d6b0-7341951-htakumi"
TMP_DIR=$(mktemp -d)
trap 'rm -rf "$TMP_DIR"' EXIT

# =============================================================
# 共通ヘルパー
# =============================================================

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
    local SRC="$1"
    local ALLOWED="${2:-write|_start|__libc|__cxa|dyld}"
    local OBJ="$TMP_DIR/$(basename "$SRC" .c).o"
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
    shift
    if command -v valgrind &>/dev/null; then
        valgrind --leak-check=full --error-exitcode=1 --quiet "$BIN" "$@" >/dev/null 2>&1 \
            && pass "valgrind: メモリリークなし" \
            || fail "valgrind: メモリリーク / エラー検出（valgrind を直接実行して確認）"
    elif command -v leaks &>/dev/null; then
        leaks --atExit -- "$BIN" "$@" >/dev/null 2>&1 \
            && pass "leaks: メモリリークなし" \
            || fail "leaks: メモリリーク検出"
    else
        warn "valgrind / leaks が見つかりません（スキップ）"
    fi
}

# =============================================================
# ex00 — ft_print_program_name
# =============================================================

test_ex00() {
    local EX="ex00"
    local FUNC="ft_print_program_name"
    info "Testing $EX — $FUNC"

    local SRC="$SUBMIT_DIR/$EX/${FUNC}.c"
    local BIN="$TMP_DIR/${EX}_bin"

    [ ! -f "$SRC" ] && fail "ファイル存在確認" "$SRC が見つかりません" && return
    pass "ファイル存在確認: $(basename "$SRC")"

    norminette_check "$SRC"

    local CC_OUT
    if ! CC_OUT=$(cc -Wall -Wextra -Werror "$SRC" -o "$BIN" 2>&1); then
        fail "コンパイル" "$CC_OUT"; return
    fi
    pass "コンパイル (-Wall -Wextra -Werror)"

    local EXPECTED ACTUAL

    # argv[0] が出力されるか（絶対パスで実行時は絶対パスが出力される）
    EXPECTED="$BIN"
    ACTUAL=$("$BIN" 2>&1)
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "基本動作テスト: argv[0] を出力" \
        || fail "基本動作テスト" "expected=$(echo "$EXPECTED" | cat -A) got=$(echo "$ACTUAL" | cat -A)"

    # 引数を与えても argv[0] のみ出力
    ACTUAL=$("$BIN" hello world 2>&1)
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "引数付き: argv[0] のみ出力される" \
        || fail "引数付きテスト" "expected=$(echo "$EXPECTED" | cat -A) got=$(echo "$ACTUAL" | cat -A)"

    # 末尾が改行であることを確認（出力バイト数チェック）
    local BYTE_COUNT
    BYTE_COUNT=$("$BIN" | wc -c | tr -d ' ')
    local EXPECTED_BYTES=$(( ${#BIN} + 1 ))  # パス長 + 改行1文字
    [ "$BYTE_COUNT" -eq "$EXPECTED_BYTES" ] \
        && pass "末尾改行チェック" \
        || fail "末尾改行チェック" "expected ${EXPECTED_BYTES} bytes, got ${BYTE_COUNT} bytes"

    forbidden_check "$SRC" "write|_start|__libc|__cxa|dyld"
    valgrind_check "$BIN"
}

# =============================================================
# ex01 — ft_print_params
# =============================================================

test_ex01() {
    local EX="ex01"
    local FUNC="ft_print_params"
    info "Testing $EX — $FUNC"

    local SRC="$SUBMIT_DIR/$EX/${FUNC}.c"
    local BIN="$TMP_DIR/${EX}_bin"

    [ ! -f "$SRC" ] && fail "ファイル存在確認" "$SRC が見つかりません" && return
    pass "ファイル存在確認: $(basename "$SRC")"

    norminette_check "$SRC"

    local CC_OUT
    if ! CC_OUT=$(cc -Wall -Wextra -Werror "$SRC" -o "$BIN" 2>&1); then
        fail "コンパイル" "$CC_OUT"; return
    fi
    pass "コンパイル (-Wall -Wextra -Werror)"

    local EXPECTED ACTUAL

    # PDF の例: ./a.out test1 test2 test3 → test1\ntest2\ntest3
    EXPECTED="test1
test2
test3"
    ACTUAL=$("$BIN" test1 test2 test3 2>&1)
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "基本動作テスト (test1 test2 test3)" \
        || fail "基本動作テスト" "expected=$(echo "$EXPECTED" | cat -A) got=$(echo "$ACTUAL" | cat -A)"

    # 引数なし → 何も出力しない
    ACTUAL=$("$BIN" 2>&1)
    [ -z "$ACTUAL" ] \
        && pass "引数なし → 出力なし" \
        || fail "引数なしテスト" "expected=（空） got=$(echo "$ACTUAL" | cat -A)"

    # 1引数のみ
    EXPECTED="hello"
    ACTUAL=$("$BIN" hello 2>&1)
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "1引数テスト" \
        || fail "1引数テスト" "expected=$(echo "$EXPECTED" | cat -A) got=$(echo "$ACTUAL" | cat -A)"

    # スペースを含む引数（クォートで1引数として渡す）
    EXPECTED="hello world
foo"
    ACTUAL=$("$BIN" "hello world" foo 2>&1)
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "スペース含む引数テスト" \
        || fail "スペース含む引数テスト" "expected=$(echo "$EXPECTED" | cat -A) got=$(echo "$ACTUAL" | cat -A)"

    forbidden_check "$SRC" "write|_start|__libc|__cxa|dyld"
    valgrind_check "$BIN" arg1 arg2
}

# =============================================================
# ex02 — ft_rev_params
# =============================================================

test_ex02() {
    local EX="ex02"
    local FUNC="ft_rev_params"
    info "Testing $EX — $FUNC"

    local SRC="$SUBMIT_DIR/$EX/${FUNC}.c"
    local BIN="$TMP_DIR/${EX}_bin"

    [ ! -f "$SRC" ] && fail "ファイル存在確認" "$SRC が見つかりません" && return
    pass "ファイル存在確認: $(basename "$SRC")"

    norminette_check "$SRC"

    local CC_OUT
    if ! CC_OUT=$(cc -Wall -Wextra -Werror "$SRC" -o "$BIN" 2>&1); then
        fail "コンパイル" "$CC_OUT"; return
    fi
    pass "コンパイル (-Wall -Wextra -Werror)"

    local EXPECTED ACTUAL

    # 3引数: 逆順
    EXPECTED="test3
test2
test1"
    ACTUAL=$("$BIN" test1 test2 test3 2>&1)
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "基本動作テスト (test1 test2 test3 → 逆順)" \
        || fail "基本動作テスト" "expected=$(echo "$EXPECTED" | cat -A) got=$(echo "$ACTUAL" | cat -A)"

    # 引数なし → 何も出力しない
    ACTUAL=$("$BIN" 2>&1)
    [ -z "$ACTUAL" ] \
        && pass "引数なし → 出力なし" \
        || fail "引数なしテスト" "expected=（空） got=$(echo "$ACTUAL" | cat -A)"

    # 1引数のみ（逆順でも変わらない）
    EXPECTED="hello"
    ACTUAL=$("$BIN" hello 2>&1)
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "1引数テスト（逆順でも同じ）" \
        || fail "1引数テスト" "expected=$(echo "$EXPECTED" | cat -A) got=$(echo "$ACTUAL" | cat -A)"

    # 2引数の逆順
    EXPECTED="b
a"
    ACTUAL=$("$BIN" a b 2>&1)
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "2引数テスト (a b → b\\na)" \
        || fail "2引数テスト" "expected=$(echo "$EXPECTED" | cat -A) got=$(echo "$ACTUAL" | cat -A)"

    # 5引数の逆順
    EXPECTED="e
d
c
b
a"
    ACTUAL=$("$BIN" a b c d e 2>&1)
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "5引数テスト (a b c d e → 逆順)" \
        || fail "5引数テスト" "expected=$(echo "$EXPECTED" | cat -A) got=$(echo "$ACTUAL" | cat -A)"

    forbidden_check "$SRC" "write|_start|__libc|__cxa|dyld"
    valgrind_check "$BIN" arg1 arg2 arg3
}

# =============================================================
# ex03 — ft_sort_params
# =============================================================

test_ex03() {
    local EX="ex03"
    local FUNC="ft_sort_params"
    info "Testing $EX — $FUNC"

    local SRC="$SUBMIT_DIR/$EX/${FUNC}.c"
    local BIN="$TMP_DIR/${EX}_bin"

    [ ! -f "$SRC" ] && fail "ファイル存在確認" "$SRC が見つかりません" && return
    pass "ファイル存在確認: $(basename "$SRC")"

    norminette_check "$SRC"

    local CC_OUT
    if ! CC_OUT=$(cc -Wall -Wextra -Werror "$SRC" -o "$BIN" 2>&1); then
        fail "コンパイル" "$CC_OUT"; return
    fi
    pass "コンパイル (-Wall -Wextra -Werror)"

    local EXPECTED ACTUAL

    # 基本ソートテスト（ASCII順: banana apple cherry → apple banana cherry）
    EXPECTED="apple
banana
cherry"
    ACTUAL=$("$BIN" banana apple cherry 2>&1)
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "基本ソートテスト (banana apple cherry → ASCII順)" \
        || fail "基本ソートテスト" "expected=$(echo "$EXPECTED" | cat -A) got=$(echo "$ACTUAL" | cat -A)"

    # 引数なし → 何も出力しない
    ACTUAL=$("$BIN" 2>&1)
    [ -z "$ACTUAL" ] \
        && pass "引数なし → 出力なし" \
        || fail "引数なしテスト" "expected=（空） got=$(echo "$ACTUAL" | cat -A)"

    # 既にソート済み
    EXPECTED="a
b
c"
    ACTUAL=$("$BIN" a b c 2>&1)
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "既ソート済みテスト (a b c → そのまま)" \
        || fail "既ソート済みテスト" "expected=$(echo "$EXPECTED" | cat -A) got=$(echo "$ACTUAL" | cat -A)"

    # 大文字小文字混在（ASCII: 大文字 < 小文字、'A'=65 < 'a'=97）
    EXPECTED="Apple
banana"
    ACTUAL=$("$BIN" banana Apple 2>&1)
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "大文字小文字混在テスト (ASCII順: 大文字 < 小文字)" \
        || fail "大文字小文字混在テスト" "expected=$(echo "$EXPECTED" | cat -A) got=$(echo "$ACTUAL" | cat -A)"

    # 逆順入力
    EXPECTED="a
b
c
d"
    ACTUAL=$("$BIN" d c b a 2>&1)
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "逆順入力テスト (d c b a → a b c d)" \
        || fail "逆順入力テスト" "expected=$(echo "$EXPECTED" | cat -A) got=$(echo "$ACTUAL" | cat -A)"

    # 禁止関数チェック（write のみ許可）
    forbidden_check "$SRC" "write|_start|__libc|__cxa|dyld"
    valgrind_check "$BIN" banana apple cherry
}

# =============================================================
# メイン実行
# =============================================================
echo "========================================"
echo " 42Tokyo — c06 テスト"
echo " $(date '+%Y-%m-%d %H:%M:%S')"
echo "========================================"

test_ex00
test_ex01
test_ex02
test_ex03

echo ""
echo "========================================"
echo -e " 結果: ${GREEN}${PASS} passed${NC} / ${RED}${FAIL} failed${NC}"
if [ ${#ERRORS[@]} -gt 0 ]; then
    echo " 失敗したテスト:"
    for err in "${ERRORS[@]}"; do echo "   ✗ $err"; done
fi
echo "========================================"
[ $FAIL -eq 0 ] && exit 0 || exit 1
