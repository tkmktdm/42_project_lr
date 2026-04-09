#!/bin/bash
# =============================================================
# test_c04.sh — c04 課題テストスクリプト
# 使い方: bash tests/c04/test_c04.sh
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
SUBMIT_DIR="$ROOT_DIR/c04/intra-uuid-2d4e0d42-b242-4d84-98fa-6dd3b24ed564-7336147-htakumi"
TEST_DIR="$SCRIPT_DIR"
TMP_DIR=$(mktemp -d)
trap 'rm -rf "$TMP_DIR"' EXIT

# =============================================================
# ex00 — ft_strlen
# =============================================================
test_ex00() {
    local EX="ex00"
    local FUNC="ft_strlen"
    info "Testing $EX — $FUNC"

    local SRC="$SUBMIT_DIR/$EX/${FUNC}.c"
    local BIN="$TMP_DIR/${EX}_bin"
    local CMP_BIN="$TMP_DIR/${EX}_cmp_bin"

    # ① ファイル存在確認
    if [ ! -f "$SRC" ]; then
        fail "ファイル存在確認" "$SRC が見つかりません"; return
    fi
    pass "ファイル存在確認: $(basename "$SRC")"

    # ② Norminette
    if command -v norminette &>/dev/null; then
        local NORM_OUT
        NORM_OUT=$(norminette "$SRC" 2>&1)
        if echo "$NORM_OUT" | grep -q "Error!"; then
            fail "Norminette" "$(echo "$NORM_OUT" | grep "Error!" | head -5)"
        else
            pass "Norminette"
        fi
    else
        warn "norminette が見つかりません（スキップ）"
    fi

    # ③ コンパイル（動作テスト用）
    local CC_OUT
    if ! CC_OUT=$(cc -Wall -Wextra -Werror "$SRC" "$TEST_DIR/main_ex00.c" -o "$BIN" 2>&1); then
        fail "コンパイル" "$CC_OUT"; return
    fi
    pass "コンパイル (-Wall -Wextra -Werror)"

    # ④ 動作テスト
    local EXPECTED ACTUAL
    EXPECTED="5
0
1
13
3"
    ACTUAL=$("$BIN" 2>&1)
    if [ "$ACTUAL" = "$EXPECTED" ]; then
        pass "基本動作テスト"
    else
        fail "基本動作テスト" "expected=$(echo "$EXPECTED" | cat -A) got=$(echo "$ACTUAL" | cat -A)"
    fi

    # ⑤ strlen との比較テスト
    if ! CC_OUT=$(cc -Wall -Wextra -Werror "$SRC" "$TEST_DIR/compare_ex00.c" -o "$CMP_BIN" 2>&1); then
        fail "比較テスト コンパイル" "$CC_OUT"
    else
        if "$CMP_BIN" > /dev/null 2>&1; then
            pass "strlen との比較テスト (全ケース一致)"
        else
            fail "strlen との比較テスト" "結果の不一致あり（$CMP_BIN を直接実行して確認）"
            "$CMP_BIN" 2>&1 | sed 's/^/    /'
        fi
    fi

    # ⑥ 禁止関数チェック（提出ファイル単体のオブジェクトで確認: None → libc 関数不可）
    local OBJ="$TMP_DIR/${EX}_obj.o"
    if cc -Wall -Wextra -Werror -c "$SRC" -o "$OBJ" 2>/dev/null; then
        local FORBIDDEN
        FORBIDDEN=$(nm -u "$OBJ" 2>/dev/null | grep "U " | grep -v -E "_start|__libc|__cxa|dyld" || true)
        [ -n "$FORBIDDEN" ] \
            && fail "禁止関数チェック" "$FORBIDDEN" \
            || pass "禁止関数チェック"
    else
        warn "禁止関数チェック用オブジェクトのコンパイル失敗（スキップ）"
    fi

    # ⑦ valgrind / leaks
    if command -v valgrind &>/dev/null; then
        valgrind --leak-check=full --error-exitcode=1 --quiet "$BIN" >/dev/null 2>&1 \
            && pass "valgrind: メモリリークなし" \
            || fail "valgrind: メモリリーク検出"
    else
        warn "valgrind が見つかりません（スキップ）"
    fi
}

# =============================================================
# ex01 — ft_putstr
# =============================================================
test_ex01() {
    local EX="ex01"
    local FUNC="ft_putstr"
    info "Testing $EX — $FUNC"

    local SRC="$SUBMIT_DIR/$EX/${FUNC}.c"
    local BIN="$TMP_DIR/${EX}_bin"

    if [ ! -f "$SRC" ]; then
        fail "ファイル存在確認" "$SRC が見つかりません"; return
    fi
    pass "ファイル存在確認: $(basename "$SRC")"

    if command -v norminette &>/dev/null; then
        local NORM_OUT
        NORM_OUT=$(norminette "$SRC" 2>&1)
        if echo "$NORM_OUT" | grep -q "Error!"; then
            fail "Norminette" "$(echo "$NORM_OUT" | grep "Error!" | head -5)"
        else
            pass "Norminette"
        fi
    else
        warn "norminette が見つかりません（スキップ）"
    fi

    local CC_OUT
    if ! CC_OUT=$(cc -Wall -Wextra -Werror "$SRC" "$TEST_DIR/main_ex01.c" -o "$BIN" 2>&1); then
        fail "コンパイル" "$CC_OUT"; return
    fi
    pass "コンパイル (-Wall -Wextra -Werror)"

    local EXPECTED ACTUAL
    EXPECTED="hello world

a
Hello, 42!"
    ACTUAL=$("$BIN" 2>&1)
    if [ "$ACTUAL" = "$EXPECTED" ]; then
        pass "基本動作テスト"
    else
        fail "基本動作テスト" "expected=$(echo "$EXPECTED" | cat -A) got=$(echo "$ACTUAL" | cat -A)"
    fi

    # 禁止関数チェック（write のみ許可）
    local FORBIDDEN
    FORBIDDEN=$(nm -u "$BIN" 2>/dev/null | grep "U " | grep -v -E "write|_start|__libc|__cxa|dyld" || true)
    [ -n "$FORBIDDEN" ] \
        && fail "禁止関数チェック" "$FORBIDDEN" \
        || pass "禁止関数チェック"

    if command -v valgrind &>/dev/null; then
        valgrind --leak-check=full --error-exitcode=1 --quiet "$BIN" >/dev/null 2>&1 \
            && pass "valgrind: メモリリークなし" \
            || fail "valgrind: メモリリーク検出"
    else
        warn "valgrind が見つかりません（スキップ）"
    fi
}

# =============================================================
# ex02 — ft_putnbr
# =============================================================
test_ex02() {
    local EX="ex02"
    local FUNC="ft_putnbr"
    info "Testing $EX — $FUNC"

    local SRC="$SUBMIT_DIR/$EX/${FUNC}.c"
    local BIN="$TMP_DIR/${EX}_bin"

    if [ ! -f "$SRC" ]; then
        fail "ファイル存在確認" "$SRC が見つかりません"; return
    fi
    pass "ファイル存在確認: $(basename "$SRC")"

    if command -v norminette &>/dev/null; then
        local NORM_OUT
        NORM_OUT=$(norminette "$SRC" 2>&1)
        if echo "$NORM_OUT" | grep -q "Error!"; then
            fail "Norminette" "$(echo "$NORM_OUT" | grep "Error!" | head -5)"
        else
            pass "Norminette"
        fi
    else
        warn "norminette が見つかりません（スキップ）"
    fi

    # ※ ft_putnbr.c に未使用変数 int i があるため -Werror でコンパイルエラーになる可能性あり
    local CC_OUT
    if ! CC_OUT=$(cc -Wall -Wextra -Werror "$SRC" "$TEST_DIR/main_ex02.c" -o "$BIN" 2>&1); then
        fail "コンパイル (-Wall -Wextra -Werror)" "$CC_OUT"
        warn "→ ft_putnbr.c に未使用変数 'int i' がある可能性があります（Norminette も確認してください）"
        return
    fi
    pass "コンパイル (-Wall -Wextra -Werror)"

    local EXPECTED ACTUAL
    EXPECTED="42
0
-1
2147483647
-2147483648
100
-999"
    ACTUAL=$("$BIN" 2>&1)
    if [ "$ACTUAL" = "$EXPECTED" ]; then
        pass "基本動作テスト (42, 0, -1, INT_MAX, INT_MIN, 100, -999)"
    else
        fail "基本動作テスト" "expected=$(echo "$EXPECTED" | cat -A) got=$(echo "$ACTUAL" | cat -A)"
    fi

    # 禁止関数チェック（write のみ許可）
    local FORBIDDEN
    FORBIDDEN=$(nm -u "$BIN" 2>/dev/null | grep "U " | grep -v -E "write|_start|__libc|__cxa|dyld" || true)
    [ -n "$FORBIDDEN" ] \
        && fail "禁止関数チェック" "$FORBIDDEN" \
        || pass "禁止関数チェック"

    if command -v valgrind &>/dev/null; then
        valgrind --leak-check=full --error-exitcode=1 --quiet "$BIN" >/dev/null 2>&1 \
            && pass "valgrind: メモリリークなし" \
            || fail "valgrind: メモリリーク検出"
    else
        warn "valgrind が見つかりません（スキップ）"
    fi
}

# =============================================================
# ex03 — ft_atoi
# =============================================================
test_ex03() {
    local EX="ex03"
    local FUNC="ft_atoi"
    info "Testing $EX — $FUNC"

    local SRC="$SUBMIT_DIR/$EX/${FUNC}.c"
    local BIN="$TMP_DIR/${EX}_bin"
    local CMP_BIN="$TMP_DIR/${EX}_cmp_bin"

    if [ ! -f "$SRC" ]; then
        fail "ファイル存在確認" "$SRC が見つかりません"; return
    fi
    pass "ファイル存在確認: $(basename "$SRC")"

    if command -v norminette &>/dev/null; then
        local NORM_OUT
        NORM_OUT=$(norminette "$SRC" 2>&1)
        if echo "$NORM_OUT" | grep -q "Error!"; then
            fail "Norminette" "$(echo "$NORM_OUT" | grep "Error!" | head -5)"
        else
            pass "Norminette"
        fi
    else
        warn "norminette が見つかりません（スキップ）"
    fi

    # ※ ft_atoi.c は現状: main 未コメントアウト・構文エラー・未実装
    #    → コンパイルエラーが予想される
    local CC_OUT
    if ! CC_OUT=$(cc -Wall -Wextra -Werror "$SRC" "$TEST_DIR/main_ex03.c" -o "$BIN" 2>&1); then
        fail "コンパイル (-Wall -Wextra -Werror)" "$(echo "$CC_OUT" | head -10)"
        warn "→ ft_atoi.c の問題が疑われます:"
        warn "  1) main 関数がコメントアウトされていない"
        warn "  2) printf(\"%d\", ft_atoi() の構文エラー（引数なし・閉じカッコ不足）"
        warn "  3) 関数が未実装（return (0) のみ）"
        warn "  4) #include <stdio.h> が含まれている（禁止関数使用の可能性）"
        return
    fi
    pass "コンパイル (-Wall -Wextra -Werror)"

    # PDF 実行例: " ---+--+1234ab567" → -1234
    local ACTUAL
    ACTUAL=$("$BIN" 2>&1 | head -1)
    if [ "$ACTUAL" = "-1234" ]; then
        pass "PDF 実行例テスト (' ---+--+1234ab567' → -1234)"
    else
        fail "PDF 実行例テスト" "expected=-1234, got=$ACTUAL"
    fi

    # atoi との比較テスト
    if ! CC_OUT=$(cc -Wall -Wextra -Werror "$SRC" "$TEST_DIR/compare_ex03.c" -o "$CMP_BIN" 2>&1); then
        fail "比較テスト コンパイル" "$CC_OUT"
    else
        if "$CMP_BIN" > /dev/null 2>&1; then
            pass "atoi との比較テスト (全ケース一致)"
        else
            fail "atoi との比較テスト" "結果の不一致あり（$CMP_BIN を直接実行して確認）"
            "$CMP_BIN" 2>&1 | sed 's/^/    /'
        fi
    fi

    # 禁止関数チェック（提出ファイル単体のオブジェクトで確認: None → libc 関数不可）
    local OBJ="$TMP_DIR/${EX}_obj.o"
    if cc -Wall -Wextra -Werror -c "$SRC" -o "$OBJ" 2>/dev/null; then
        local FORBIDDEN
        FORBIDDEN=$(nm -u "$OBJ" 2>/dev/null | grep "U " | grep -v -E "_start|__libc|__cxa|dyld" || true)
        [ -n "$FORBIDDEN" ] \
            && fail "禁止関数チェック" "$FORBIDDEN" \
            || pass "禁止関数チェック"
    else
        warn "禁止関数チェック用オブジェクトのコンパイル失敗（スキップ）"
    fi

    if command -v valgrind &>/dev/null; then
        valgrind --leak-check=full --error-exitcode=1 --quiet "$BIN" >/dev/null 2>&1 \
            && pass "valgrind: メモリリークなし" \
            || fail "valgrind: メモリリーク検出"
    else
        warn "valgrind が見つかりません（スキップ）"
    fi
}

# =============================================================
# ex04 — ft_putnbr_base
# =============================================================
test_ex04() {
    local EX="ex04"
    local FUNC="ft_putnbr_base"
    info "Testing $EX — $FUNC"

    local SRC="$SUBMIT_DIR/$EX/${FUNC}.c"
    local BIN="$TMP_DIR/${EX}_bin"

    if [ ! -f "$SRC" ]; then
        fail "ファイル存在確認" "$SRC が見つかりません"; return
    fi
    pass "ファイル存在確認: $(basename "$SRC")"

    if command -v norminette &>/dev/null; then
        local NORM_OUT
        NORM_OUT=$(norminette "$SRC" 2>&1)
        if echo "$NORM_OUT" | grep -q "Error!"; then
            fail "Norminette" "$(echo "$NORM_OUT" | grep "Error!" | head -5)"
        else
            pass "Norminette"
        fi
    else
        warn "norminette が見つかりません（スキップ）"
    fi

    local CC_OUT
    if ! CC_OUT=$(cc -Wall -Wextra -Werror "$SRC" "$TEST_DIR/main_ex04.c" -o "$BIN" 2>&1); then
        fail "コンパイル" "$CC_OUT"; return
    fi
    pass "コンパイル (-Wall -Wextra -Werror)"

    # 期待値:
    #   42   → 10進: 42
    #   0    → 10進: 0
    #   -42  → 10進: -42
    #   FF   → 16進: 255
    #   1000 → 2進: 8
    #   oyy  → poneyvif(8進): 100
    #   2147483647  → INT_MAX
    #   -2147483648 → INT_MIN
    #   |    → '+' 含む無効base → 何も出力しない
    #   |    → 長さ1の無効base → 何も出力しない
    #   |    → 重複文字の無効base → 何も出力しない
    #   |    → '-' 含む無効base → 何も出力しない
    local EXPECTED ACTUAL
    EXPECTED="42
0
-42
FF
1000
oyy
2147483647
-2147483648
|
|
|
|"
    ACTUAL=$("$BIN" 2>&1)
    if [ "$ACTUAL" = "$EXPECTED" ]; then
        pass "基本動作テスト (10進/16進/2進/8進/負数/無効base)"
    else
        fail "基本動作テスト" "expected=$(echo "$EXPECTED" | cat -A) got=$(echo "$ACTUAL" | cat -A)"
    fi

    # 禁止関数チェック（write のみ許可）
    local FORBIDDEN
    FORBIDDEN=$(nm -u "$BIN" 2>/dev/null | grep "U " | grep -v -E "write|_start|__libc|__cxa|dyld" || true)
    [ -n "$FORBIDDEN" ] \
        && fail "禁止関数チェック" "$FORBIDDEN" \
        || pass "禁止関数チェック"

    if command -v valgrind &>/dev/null; then
        valgrind --leak-check=full --error-exitcode=1 --quiet "$BIN" >/dev/null 2>&1 \
            && pass "valgrind: メモリリークなし" \
            || fail "valgrind: メモリリーク検出"
    else
        warn "valgrind が見つかりません（スキップ）"
    fi
}

# =============================================================
# ex05 — ft_atoi_base
# =============================================================
test_ex05() {
    local EX="ex05"
    local FUNC="ft_atoi_base"
    info "Testing $EX — $FUNC"

    local SRC="$SUBMIT_DIR/$EX/${FUNC}.c"
    local BIN="$TMP_DIR/${EX}_bin"

    if [ ! -f "$SRC" ]; then
        fail "ファイル存在確認" "$SRC が見つかりません"; return
    fi
    pass "ファイル存在確認: $(basename "$SRC")"

    if command -v norminette &>/dev/null; then
        local NORM_OUT
        NORM_OUT=$(norminette "$SRC" 2>&1)
        if echo "$NORM_OUT" | grep -q "Error!"; then
            fail "Norminette" "$(echo "$NORM_OUT" | grep "Error!" | head -5)"
        else
            pass "Norminette"
        fi
    else
        warn "norminette が見つかりません（スキップ）"
    fi

    local CC_OUT
    if ! CC_OUT=$(cc -Wall -Wextra -Werror "$SRC" "$TEST_DIR/main_ex05.c" -o "$BIN" 2>&1); then
        fail "コンパイル" "$(echo "$CC_OUT" | head -10)"; return
    fi
    pass "コンパイル (-Wall -Wextra -Werror)"

    # 期待値 (test_basic / test_sign / test_invalid の順):
    local EXPECTED ACTUAL
    EXPECTED="0
42
2147483647
10
8
255
255
26
10
100
-42
42
42
-42
-42
42
42
-42
42
10
0
0
0
0
0
0
0"
    ACTUAL=$("$BIN" 2>&1)
    if [ "$ACTUAL" = "$EXPECTED" ]; then
        pass "基本動作テスト (10進/16進/2進/8進/符号/無効base)"
    else
        fail "基本動作テスト" "expected=$(echo "$EXPECTED" | cat -A) got=$(echo "$ACTUAL" | cat -A)"
    fi

    # 禁止関数チェック（None → libc 関数不可）
    local FORBIDDEN
    FORBIDDEN=$(nm -u "$BIN" 2>/dev/null | grep "U " | grep -v -E "_start|__libc|__cxa|dyld|printf" || true)
    [ -n "$FORBIDDEN" ] \
        && fail "禁止関数チェック" "$FORBIDDEN" \
        || pass "禁止関数チェック"

    if command -v valgrind &>/dev/null; then
        valgrind --leak-check=full --error-exitcode=1 --quiet "$BIN" >/dev/null 2>&1 \
            && pass "valgrind: メモリリークなし" \
            || fail "valgrind: メモリリーク検出"
    else
        warn "valgrind が見つかりません（スキップ）"
    fi
}

# =============================================================
# メイン実行
# =============================================================
echo "========================================"
echo " 42Tokyo — c04 テスト"
echo " $(date '+%Y-%m-%d %H:%M:%S')"
echo "========================================"

test_ex00
test_ex01
test_ex02
test_ex03
test_ex04
test_ex05

echo ""
echo "========================================"
echo -e " 結果: ${GREEN}${PASS} passed${NC} / ${RED}${FAIL} failed${NC}"
if [ ${#ERRORS[@]} -gt 0 ]; then
    echo " 失敗したテスト:"
    for err in "${ERRORS[@]}"; do echo "   x $err"; done
fi
echo "========================================"
[ $FAIL -eq 0 ] && exit 0 || exit 1
