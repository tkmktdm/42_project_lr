#!/bin/bash
# =============================================================
# test_c07.sh — c07 課題テストスクリプト
# 使い方: bash tests/c07/test_c07.sh
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
SUBMIT_DIR="$ROOT_DIR/c07/intra-uuid-c954933b-9515-4406-9fec-8c24160d2a52-7345081-htakumi"
TEST_DIR="$SCRIPT_DIR"
TMP_DIR=$(mktemp -d)
trap 'rm -rf "$TMP_DIR"' EXIT

# =============================================================
# ex00: ft_strdup
# =============================================================
test_ex00()
{
    local EX="ex00"
    info "Testing $EX — ft_strdup"

    local SRC="$SUBMIT_DIR/$EX/ft_strdup.c"
    local MAIN="$TEST_DIR/main_ex00.c"
    local BIN="$TMP_DIR/ex00_bin"

    [ -f "$SRC" ] && pass "ファイル存在確認" || { fail "ファイル存在確認" "$SRC が見つかりません"; return; }

    if command -v norminette &>/dev/null; then
        local NORM_OUT
        NORM_OUT=$(norminette "$SRC" 2>&1)
        echo "$NORM_OUT" | grep -q "Error!" \
            && fail "Norminette" "$(echo "$NORM_OUT" | grep "Error!" | head -5)" \
            || pass "Norminette"
    else
        warn "norminette が見つかりません（スキップ）"
    fi

    local CC_OUT
    CC_OUT=$(cc -Wall -Wextra -Werror "$SRC" "$MAIN" -o "$BIN" 2>&1) \
        && pass "コンパイル" \
        || { fail "コンパイル" "$CC_OUT"; return; }

    # 基本動作
    local ACTUAL EXPECTED
    ACTUAL=$("$BIN" basic 2>&1)
    EXPECTED="hello"
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "基本動作: 文字列コピー" \
        || fail "基本動作: 文字列コピー" "expected=$(echo "$EXPECTED"|cat -A) got=$(echo "$ACTUAL"|cat -A)"

    # アドレスが異なる（別メモリ）
    ACTUAL=$("$BIN" addr 2>&1)
    [ "$ACTUAL" = "different" ] \
        && pass "別アドレス確認" \
        || fail "別アドレス確認" "src と dest が同じアドレス"

    # 空文字列
    ACTUAL=$("$BIN" empty 2>&1)
    EXPECTED=""
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "エッジケース: 空文字列" \
        || fail "エッジケース: 空文字列" "expected=empty got=$(echo "$ACTUAL"|cat -A)"

    # valgrind
    if command -v valgrind &>/dev/null; then
        valgrind --leak-check=full --error-exitcode=1 --quiet "$BIN" basic >/dev/null 2>&1 \
            && pass "valgrind: メモリリークなし" \
            || fail "valgrind: メモリリーク検出"
    else
        warn "valgrind が見つかりません（スキップ）"
    fi
}

# =============================================================
# ex01: ft_range
# =============================================================
test_ex01()
{
    local EX="ex01"
    info "Testing $EX — ft_range"

    local SRC="$SUBMIT_DIR/$EX/ft_range.c"
    local MAIN="$TEST_DIR/main_ex01.c"
    local BIN="$TMP_DIR/ex01_bin"

    [ -f "$SRC" ] && pass "ファイル存在確認" || { fail "ファイル存在確認" "$SRC が見つかりません"; return; }

    if command -v norminette &>/dev/null; then
        local NORM_OUT
        NORM_OUT=$(norminette "$SRC" 2>&1)
        echo "$NORM_OUT" | grep -q "Error!" \
            && fail "Norminette" "$(echo "$NORM_OUT" | grep "Error!" | head -5)" \
            || pass "Norminette"
    else
        warn "norminette が見つかりません（スキップ）"
    fi

    local CC_OUT
    CC_OUT=$(cc -Wall -Wextra -Werror "$SRC" "$MAIN" -o "$BIN" 2>&1) \
        && pass "コンパイル" \
        || { fail "コンパイル" "$CC_OUT"; return; }

    # 基本動作: min=3, max=9 → 3 4 5 6 7 8
    local ACTUAL EXPECTED
    ACTUAL=$("$BIN" basic 2>&1)
    EXPECTED="3 4 5 6 7 8"
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "基本動作: ft_range(3, 9)" \
        || fail "基本動作: ft_range(3, 9)" "expected=$(echo "$EXPECTED"|cat -A) got=$(echo "$ACTUAL"|cat -A)"

    # min >= max → NULL
    ACTUAL=$("$BIN" null 2>&1)
    [ "$ACTUAL" = "NULL" ] \
        && pass "境界値: min==max → NULL" \
        || fail "境界値: min==max → NULL" "got=$ACTUAL"

    ACTUAL=$("$BIN" null2 2>&1)
    [ "$ACTUAL" = "NULL" ] \
        && pass "境界値: min>max → NULL" \
        || fail "境界値: min>max → NULL" "got=$ACTUAL"

    # 負の範囲
    ACTUAL=$("$BIN" neg 2>&1)
    EXPECTED="-3 -2 -1 0 1 2"
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "エッジケース: 負の範囲 ft_range(-3, 3)" \
        || fail "エッジケース: 負の範囲 ft_range(-3, 3)" "expected=$(echo "$EXPECTED"|cat -A) got=$(echo "$ACTUAL"|cat -A)"

    if command -v valgrind &>/dev/null; then
        valgrind --leak-check=full --error-exitcode=1 --quiet "$BIN" basic >/dev/null 2>&1 \
            && pass "valgrind: メモリリークなし" \
            || fail "valgrind: メモリリーク検出"
    else
        warn "valgrind が見つかりません（スキップ）"
    fi
}

# =============================================================
# ex02: ft_ultimate_range
# =============================================================
test_ex02()
{
    local EX="ex02"
    info "Testing $EX — ft_ultimate_range"

    local SRC="$SUBMIT_DIR/$EX/ft_ultimate_range.c"
    local MAIN="$TEST_DIR/main_ex02.c"
    local BIN="$TMP_DIR/ex02_bin"

    [ -f "$SRC" ] && pass "ファイル存在確認" || { fail "ファイル存在確認" "$SRC が見つかりません"; return; }

    if command -v norminette &>/dev/null; then
        local NORM_OUT
        NORM_OUT=$(norminette "$SRC" 2>&1)
        echo "$NORM_OUT" | grep -q "Error!" \
            && fail "Norminette" "$(echo "$NORM_OUT" | grep "Error!" | head -5)" \
            || pass "Norminette"
    else
        warn "norminette が見つかりません（スキップ）"
    fi

    local CC_OUT
    CC_OUT=$(cc -Wall -Wextra -Werror "$SRC" "$MAIN" -o "$BIN" 2>&1) \
        && pass "コンパイル" \
        || { fail "コンパイル" "$CC_OUT"; return; }

    # 基本動作: min=3, max=9 → size=6, 3 4 5 6 7 8
    local ACTUAL EXPECTED
    ACTUAL=$("$BIN" basic 2>&1)
    EXPECTED="6 3 4 5 6 7 8"
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "基本動作: ft_ultimate_range(3, 9)" \
        || fail "基本動作: ft_ultimate_range(3, 9)" "expected=$(echo "$EXPECTED"|cat -A) got=$(echo "$ACTUAL"|cat -A)"

    # min >= max → range=NULL, 戻り値=0
    ACTUAL=$("$BIN" null 2>&1)
    EXPECTED="0 NULL"
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "境界値: min==max → 0, NULL" \
        || fail "境界値: min==max → 0, NULL" "expected=$(echo "$EXPECTED"|cat -A) got=$(echo "$ACTUAL"|cat -A)"

    if command -v valgrind &>/dev/null; then
        valgrind --leak-check=full --error-exitcode=1 --quiet "$BIN" basic >/dev/null 2>&1 \
            && pass "valgrind: メモリリークなし" \
            || fail "valgrind: メモリリーク検出"
    else
        warn "valgrind が見つかりません（スキップ）"
    fi
}

# =============================================================
# ex03: ft_strjoin
# =============================================================
test_ex03()
{
    local EX="ex03"
    info "Testing $EX — ft_strjoin"

    local SRC="$SUBMIT_DIR/$EX/ft_strjoin.c"
    local MAIN="$TEST_DIR/main_ex03.c"
    local BIN="$TMP_DIR/ex03_bin"

    [ -f "$SRC" ] && pass "ファイル存在確認" || { fail "ファイル存在確認" "$SRC が見つかりません"; return; }

    if command -v norminette &>/dev/null; then
        local NORM_OUT
        NORM_OUT=$(norminette "$SRC" 2>&1)
        echo "$NORM_OUT" | grep -q "Error!" \
            && fail "Norminette" "$(echo "$NORM_OUT" | grep "Error!" | head -5)" \
            || pass "Norminette"
    else
        warn "norminette が見つかりません（スキップ）"
    fi

    local CC_OUT
    CC_OUT=$(cc -Wall -Wextra -Werror "$SRC" "$MAIN" -o "$BIN" 2>&1) \
        && pass "コンパイル" \
        || { fail "コンパイル" "$CC_OUT"; return; }

    local ACTUAL EXPECTED
    # 基本動作
    ACTUAL=$("$BIN" basic 2>&1)
    EXPECTED="hello!!world"
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "基本動作: [hello,world] sep=!!" \
        || fail "基本動作: [hello,world] sep=!!" "expected=$(echo "$EXPECTED"|cat -A) got=$(echo "$ACTUAL"|cat -A)"

    # size=0 → 空文字列
    ACTUAL=$("$BIN" zero 2>&1)
    EXPECTED=""
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "エッジケース: size=0 → 空文字列" \
        || fail "エッジケース: size=0 → 空文字列" "expected=empty got=$(echo "$ACTUAL"|cat -A)"

    # size=1 → sep なし
    ACTUAL=$("$BIN" one 2>&1)
    EXPECTED="hello"
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "エッジケース: size=1 → sepなし" \
        || fail "エッジケース: size=1 → sepなし" "expected=$(echo "$EXPECTED"|cat -A) got=$(echo "$ACTUAL"|cat -A)"

    # sep が空文字
    ACTUAL=$("$BIN" nosep 2>&1)
    EXPECTED="helloworld"
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "エッジケース: sep=空文字" \
        || fail "エッジケース: sep=空文字" "expected=$(echo "$EXPECTED"|cat -A) got=$(echo "$ACTUAL"|cat -A)"

    if command -v valgrind &>/dev/null; then
        valgrind --leak-check=full --error-exitcode=1 --quiet "$BIN" basic >/dev/null 2>&1 \
            && pass "valgrind: メモリリークなし" \
            || fail "valgrind: メモリリーク検出"
    else
        warn "valgrind が見つかりません（スキップ）"
    fi
}

# =============================================================
# ex04: ft_convert_base
# =============================================================
test_ex04()
{
    local EX="ex04"
    info "Testing $EX — ft_convert_base"

    local SRC1="$SUBMIT_DIR/$EX/ft_convert_base.c"
    local SRC2="$SUBMIT_DIR/$EX/ft_convert_base2.c"
    local MAIN="$TEST_DIR/main_ex04.c"
    local BIN="$TMP_DIR/ex04_bin"

    [ -f "$SRC1" ] && pass "ファイル存在確認: ft_convert_base.c" || { fail "ファイル存在確認" "$SRC1 が見つかりません"; return; }
    [ -f "$SRC2" ] && pass "ファイル存在確認: ft_convert_base2.c" || { fail "ファイル存在確認" "$SRC2 が見つかりません"; return; }

    if command -v norminette &>/dev/null; then
        local NORM_OUT
        NORM_OUT=$(norminette "$SRC1" "$SRC2" 2>&1)
        echo "$NORM_OUT" | grep -q "Error!" \
            && fail "Norminette" "$(echo "$NORM_OUT" | grep "Error!" | head -5)" \
            || pass "Norminette"
    else
        warn "norminette が見つかりません（スキップ）"
    fi

    local CC_OUT
    CC_OUT=$(cc -Wall -Wextra -Werror "$SRC1" "$SRC2" "$MAIN" -o "$BIN" 2>&1) \
        && pass "コンパイル" \
        || { fail "コンパイル" "$CC_OUT"; return; }

    local ACTUAL EXPECTED
    # 10進数 → 16進数
    ACTUAL=$("$BIN" dec2hex 2>&1)
    EXPECTED="F"
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "基本動作: 15(10進) → F(16進)" \
        || fail "基本動作: 15(10進) → F(16進)" "expected=$(echo "$EXPECTED"|cat -A) got=$(echo "$ACTUAL"|cat -A)"

    # 2進数 → 10進数
    ACTUAL=$("$BIN" bin2dec 2>&1)
    EXPECTED="6"
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "基本動作: 110(2進) → 6(10進)" \
        || fail "基本動作: 110(2進) → 6(10進)" "expected=$(echo "$EXPECTED"|cat -A) got=$(echo "$ACTUAL"|cat -A)"

    # 負の数
    ACTUAL=$("$BIN" neg 2>&1)
    EXPECTED="-F"
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "符号: -15(10進) → -F(16進)" \
        || fail "符号: -15(10進) → -F(16進)" "expected=$(echo "$EXPECTED"|cat -A) got=$(echo "$ACTUAL"|cat -A)"

    # 複数符号 ++-- → 正
    ACTUAL=$("$BIN" signs 2>&1)
    EXPECTED="F"
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "符号: ++--15 → F(正)" \
        || fail "符号: ++--15 → F(正)" "expected=$(echo "$EXPECTED"|cat -A) got=$(echo "$ACTUAL"|cat -A)"

    # 0
    ACTUAL=$("$BIN" zero 2>&1)
    EXPECTED="0"
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "境界値: 0 → 0" \
        || fail "境界値: 0 → 0" "expected=$(echo "$EXPECTED"|cat -A) got=$(echo "$ACTUAL"|cat -A)"

    # 無効なbase → NULL
    ACTUAL=$("$BIN" invalid 2>&1)
    [ "$ACTUAL" = "NULL" ] \
        && pass "無効なbase → NULL" \
        || fail "無効なbase → NULL" "got=$ACTUAL"

    if command -v valgrind &>/dev/null; then
        valgrind --leak-check=full --error-exitcode=1 --quiet "$BIN" dec2hex >/dev/null 2>&1 \
            && pass "valgrind: メモリリークなし" \
            || fail "valgrind: メモリリーク検出"
    else
        warn "valgrind が見つかりません（スキップ）"
    fi
}

# =============================================================
# ex05: ft_split
# =============================================================
test_ex05()
{
    local EX="ex05"
    info "Testing $EX — ft_split"

    local SRC="$SUBMIT_DIR/$EX/ft_split.c"
    local MAIN="$TEST_DIR/main_ex05.c"
    local BIN="$TMP_DIR/ex05_bin"

    [ -f "$SRC" ] && pass "ファイル存在確認" || { fail "ファイル存在確認" "$SRC が見つかりません"; return; }

    if command -v norminette &>/dev/null; then
        local NORM_OUT
        NORM_OUT=$(norminette "$SRC" 2>&1)
        echo "$NORM_OUT" | grep -q "Error!" \
            && fail "Norminette" "$(echo "$NORM_OUT" | grep "Error!" | head -5)" \
            || pass "Norminette"
    else
        warn "norminette が見つかりません（スキップ）"
    fi

    local CC_OUT
    CC_OUT=$(cc -Wall -Wextra -Werror "$SRC" "$MAIN" -o "$BIN" 2>&1) \
        && pass "コンパイル" \
        || { fail "コンパイル" "$CC_OUT"; return; }

    local ACTUAL EXPECTED
    # 基本動作
    ACTUAL=$("$BIN" basic 2>&1)
    EXPECTED="hello|world|foo"
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "基本動作: hello,world,foo sep=, " \
        || fail "基本動作: hello,world,foo sep=, " "expected=$(echo "$EXPECTED"|cat -A) got=$(echo "$ACTUAL"|cat -A)"

    # 連続区切り文字（空文字列を含まない）
    ACTUAL=$("$BIN" multi 2>&1)
    EXPECTED="hello|world"
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "連続区切り: hello,,world → [hello,world]" \
        || fail "連続区切り: hello,,world → [hello,world]" "expected=$(echo "$EXPECTED"|cat -A) got=$(echo "$ACTUAL"|cat -A)"

    # 先頭・末尾に区切り文字
    ACTUAL=$("$BIN" trim 2>&1)
    EXPECTED="hello|world"
    [ "$ACTUAL" = "$EXPECTED" ] \
        && pass "先頭末尾の区切り文字を無視" \
        || fail "先頭末尾の区切り文字を無視" "expected=$(echo "$EXPECTED"|cat -A) got=$(echo "$ACTUAL"|cat -A)"

    # 末尾がNULL
    ACTUAL=$("$BIN" null_end 2>&1)
    [ "$ACTUAL" = "NULL" ] \
        && pass "配列末尾がNULL" \
        || fail "配列末尾がNULL" "got=$ACTUAL"

    if command -v valgrind &>/dev/null; then
        valgrind --leak-check=full --error-exitcode=1 --quiet "$BIN" basic >/dev/null 2>&1 \
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
echo " 42Tokyo — c07 テスト"
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
    for err in "${ERRORS[@]}"; do echo "   ✗ $err"; done
fi
echo "========================================"
[ $FAIL -eq 0 ] && exit 0 || exit 1
