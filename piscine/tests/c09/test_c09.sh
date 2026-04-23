#!/bin/bash
# =============================================================
# test_c09.sh — c09 課題テストスクリプト
# 使い方: bash tests/c09/test_c09.sh
#
# 【自分でカスタマイズできる箇所】
#   - 各 test_exXX() 関数内の「カスタマイズここから/ここまで」ブロック
# =============================================================

set -uo pipefail

GREEN='\033[0;32m'; RED='\033[0;31m'; YELLOW='\033[1;33m'; BLUE='\033[0;34m'; NC='\033[0m'

PASS=0; FAIL=0; SKIP=0; ERRORS=()

pass() { echo -e "  ${GREEN}[PASS]${NC} $1"; ((PASS++)) || true; }
fail() { echo -e "  ${RED}[FAIL]${NC} $1${2:+ — $2}"; ((FAIL++)) || true; ERRORS+=("$1"); }
skip() { echo -e "  ${YELLOW}[SKIP]${NC} $1"; ((SKIP++)) || true; }
info() { echo -e "\n${BLUE}▶ $1${NC}"; }
warn() { echo -e "  ${YELLOW}[WARN]${NC} $1"; }

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/../.." && pwd)"
SUBMIT_DIR="$ROOT_DIR/c09/htakumi"
TMP_DIR=$(mktemp -d)
trap 'rm -rf "$TMP_DIR"' EXIT

# =============================================================
# 共通テスト関数（編集不要）
# =============================================================

run_test() {
    local label="$1"
    local expected="$2"
    shift 2
    local actual
    actual=$("$@" 2>&1)
    if [ "$actual" = "$expected" ]; then
        pass "$label"
    else
        fail "$label" "expected=$(printf '%s' "$expected" | cat -A) got=$(printf '%s' "$actual" | cat -A)"
    fi
}

check_forbidden() {
    local bin="$1"
    local allowed="$2"
    local forbidden
    forbidden=$(nm -u "$bin" 2>/dev/null | grep "U " | grep -v -E "$allowed" || true)
    if [ -n "$forbidden" ]; then
        fail "禁止関数チェック" "$(echo "$forbidden" | tr '\n' ' ')"
    else
        pass "禁止関数チェック"
    fi
}

check_norminette() {
    local src="$1"
    if command -v norminette &>/dev/null; then
        local out
        out=$(norminette "$src" 2>&1)
        if echo "$out" | grep -q "Error!"; then
            fail "Norminette: $(basename "$src")" "$(echo "$out" | grep "Error!" | head -3)"
        else
            pass "Norminette: $(basename "$src")"
        fi
    else
        warn "norminette が見つかりません（スキップ）"
    fi
}

check_memory() {
    local bin="$1"
    shift
    if command -v valgrind &>/dev/null; then
        valgrind --leak-check=full --error-exitcode=1 --quiet "$bin" "$@" >/dev/null 2>&1 \
            && pass "valgrind: リークなし" || fail "valgrind: リーク検出"
    elif command -v leaks &>/dev/null; then
        leaks --atExit -- "$bin" "$@" >/dev/null 2>&1 \
            && pass "leaks: リークなし" || fail "leaks: リーク検出"
    else
        warn "valgrind/leaks なし（スキップ）"
    fi
}

# =============================================================
# ex00: libft
# =============================================================
test_ex00() {
    info "ex00 — libft (libft_creator.sh)"

    local EX_DIR="$SUBMIT_DIR/ex00"
    local REQUIRED_FILES=(libft_creator.sh ft_putchar.c ft_swap.c ft_putstr.c ft_strlen.c ft_strcmp.c)

    # ===== 提出ファイル確認 =====
    local missing=0
    for f in "${REQUIRED_FILES[@]}"; do
        if [ ! -f "$EX_DIR/$f" ]; then
            fail "ファイル存在: $f" "見つかりません"
            missing=1
        else
            pass "ファイル存在: $f"
        fi
    done
    [ $missing -eq 1 ] && skip "ex00: 必須ファイル不足のためスキップ" && return

    # ===== Norminette =====
    for f in ft_putchar.c ft_swap.c ft_putstr.c ft_strlen.c ft_strcmp.c; do
        check_norminette "$EX_DIR/$f"
    done

    # ===== sh libft_creator.sh 実行（tempコピーで） =====
    local WORK="$TMP_DIR/ex00"
    mkdir -p "$WORK"
    cp "$EX_DIR"/*.c "$EX_DIR/libft_creator.sh" "$WORK/"

    local SH_OUT
    if ! SH_OUT=$(cd "$WORK" && sh libft_creator.sh 2>&1); then
        fail "sh libft_creator.sh" "$SH_OUT"
        return
    fi
    pass "sh libft_creator.sh 実行"

    # libft.a が生成されたか
    if [ -f "$WORK/libft.a" ]; then
        pass "libft.a が生成された"
    else
        fail "libft.a が生成されなかった"
        return
    fi

    # ===== カスタマイズここから =====
    # libft.a に各 .o が含まれているか
    local SYMBOLS
    SYMBOLS=$(ar t "$WORK/libft.a" 2>/dev/null)
    for f in ft_putchar.o ft_swap.o ft_putstr.o ft_strlen.o ft_strcmp.o; do
        if echo "$SYMBOLS" | grep -q "^$f$"; then
            pass "libft.a に含まれる: $f"
        else
            fail "libft.a に含まれない: $f"
        fi
    done

    # nm でシンボル確認
    local NM_OUT
    NM_OUT=$(nm "$WORK/libft.a" 2>/dev/null)
    for sym in ft_putchar ft_swap ft_putstr ft_strlen ft_strcmp; do
        if echo "$NM_OUT" | grep -qE " T _?${sym}$"; then
            pass "シンボル確認: $sym"
        else
            fail "シンボルが見つからない: $sym"
        fi
    done
    # ===== カスタマイズここまで =====
}

# =============================================================
# ex01: Makefile
# =============================================================
test_ex01() {
    info "ex01 — Makefile"

    local EX_DIR="$SUBMIT_DIR/ex01"
    [ ! -f "$EX_DIR/Makefile" ] && skip "ex01: Makefile 未提出" && return
    pass "ファイル存在: Makefile"

    # テスト用ディレクトリを構築（srcs/ includes/ を用意）
    local WORK="$TMP_DIR/ex01"
    mkdir -p "$WORK/srcs" "$WORK/includes"
    cp "$EX_DIR/Makefile" "$WORK/"
    touch "$WORK/includes/ft.h"

    # ex00 の .c ファイルを srcs/ にコピー
    local EX00="$SUBMIT_DIR/ex00"
    for f in ft_putchar.c ft_swap.c ft_putstr.c ft_strlen.c ft_strcmp.c; do
        if [ -f "$EX00/$f" ]; then
            cp "$EX00/$f" "$WORK/srcs/$f"
        else
            warn "srcs/$f が見つかりません（ex00 が必要）"
        fi
    done

    # ===== カスタマイズここから =====

    # make（引数なし）= make all と同じ動作
    local MAKE_OUT
    if ! MAKE_OUT=$(cd "$WORK" && make 2>&1); then
        fail "make（引数なし）" "$MAKE_OUT"; return
    fi
    pass "make（引数なし）実行"
    [ -f "$WORK/libft.a" ] && pass "libft.a 生成" || fail "libft.a が生成されなかった"

    # .o ファイルが srcs/ に生成されているか
    local o_ok=1
    for f in ft_putchar.o ft_swap.o ft_putstr.o ft_strlen.o ft_strcmp.o; do
        [ ! -f "$WORK/srcs/$f" ] && fail ".o が srcs/ にない: $f" && o_ok=0
    done
    [ $o_ok -eq 1 ] && pass ".o ファイルが srcs/ に生成された"

    # 2回目の make → 不要な再コンパイルなし
    local MAKE2_OUT
    MAKE2_OUT=$(cd "$WORK" && make 2>&1)
    if echo "$MAKE2_OUT" | grep -qiE "nothing to be done|is up to date|最新"; then
        pass "不要な再コンパイルなし"
    else
        fail "不要な再コンパイルが発生" "$MAKE2_OUT"
    fi

    # make clean → .o 削除、libft.a は残る
    cd "$WORK" && make clean >/dev/null 2>&1
    local clean_ok=1
    for f in ft_putchar.o ft_swap.o ft_putstr.o ft_strlen.o ft_strcmp.o; do
        [ -f "$WORK/srcs/$f" ] && fail "clean 後に .o が残存: $f" && clean_ok=0
    done
    [ $clean_ok -eq 1 ] && pass "make clean: .o 削除"
    [ -f "$WORK/libft.a" ] && pass "make clean: libft.a は残る" || fail "make clean: libft.a まで消えた"

    # make fclean → libft.a も削除
    cd "$WORK" && make fclean >/dev/null 2>&1
    [ ! -f "$WORK/libft.a" ] && pass "make fclean: libft.a 削除" || fail "make fclean: libft.a が残っている"

    # make re → 再ビルド
    if cd "$WORK" && make re >/dev/null 2>&1; then
        pass "make re 実行"
        [ -f "$WORK/libft.a" ] && pass "make re: libft.a 再生成" || fail "make re: libft.a なし"
    else
        fail "make re"
    fi

    # make all
    cd "$WORK" && make fclean >/dev/null 2>&1
    if cd "$WORK" && make all >/dev/null 2>&1; then
        pass "make all 実行"
        [ -f "$WORK/libft.a" ] && pass "make all: libft.a 生成" || fail "make all: libft.a なし"
    else
        fail "make all"
    fi

    # make libft.a（ルール名でも動くか）
    cd "$WORK" && make fclean >/dev/null 2>&1
    if cd "$WORK" && make libft.a >/dev/null 2>&1; then
        pass "make libft.a 実行"
        [ -f "$WORK/libft.a" ] && pass "make libft.a: libft.a 生成" || fail "make libft.a: libft.a なし"
    else
        fail "make libft.a"
    fi
    # ===== カスタマイズここまで =====
}

# =============================================================
# ex02: ft_split
# =============================================================
test_ex02() {
    local SRC="$SUBMIT_DIR/ex02/ft_split.c"
    info "ex02 — ft_split"

    [ ! -f "$SRC" ] && skip "ex02: ファイル未提出 ($SRC)" && return
    pass "ファイル存在: ft_split.c"

    check_norminette "$SRC"

    # ===== コンパイル用コード（here-doc） =====
    local MAIN_C="$TMP_DIR/main_ex02.c"
    cat > "$MAIN_C" << 'EOF'
#include <stdlib.h>
#include <stdio.h>

char	**ft_split(char *str, char *charset);

int	main(int argc, char **argv)
{
    char	**result;
    int		i;

    if (argc != 3)
        return (1);
    result = ft_split(argv[1], argv[2]);
    if (!result)
    {
        printf("NULL\n");
        return (0);
    }
    i = 0;
    while (result[i])
    {
        printf("%s\n", result[i]);
        free(result[i]);
        i++;
    }
    free(result);
    return (0);
}
EOF
    # ==========================================

    local BIN="$TMP_DIR/ex02"
    local CC_OUT
    if ! CC_OUT=$(cc -Wall -Wextra -Werror "$SRC" "$MAIN_C" -o "$BIN" 2>&1); then
        fail "コンパイル" "$CC_OUT"; return
    fi
    pass "コンパイル"

    # ===== カスタマイズここから =====
    run_test "基本分割（スペース区切り）" \
        "hello
world
foo" \
        "$BIN" "hello world foo" " "

    run_test "区切り文字が連続（空文字列を含めない）" \
        "hello
world" \
        "$BIN" "hello,,world" ","

    run_test "先頭に区切り文字" \
        "hello" \
        "$BIN" ",hello" ","

    run_test "末尾に区切り文字" \
        "hello" \
        "$BIN" "hello," ","

    run_test "全部区切り文字（空配列）" \
        "" \
        "$BIN" ",,," ","

    run_test "空文字列" \
        "" \
        "$BIN" "" ","

    run_test "区切り文字が存在しない（1要素）" \
        "hello" \
        "$BIN" "hello" ","

    run_test "charset 複数文字" \
        "a
b
c
d" \
        "$BIN" "a.b,c!d" ".,!"

    run_test "連続する複数 charset 文字" \
        "hello
world" \
        "$BIN" "hello...world" "."

    run_test "先頭・末尾・連続すべて混在" \
        "malloc
IS
C
A
N
split
fin" \
        "$BIN" "malloc.IS!C!,A........N'T?split!!fin" "T.,!?'"
    # ===== カスタマイズここまで =====

    check_forbidden "$BIN" "malloc|free|printf|_start|__libc|__cxa|dyld"
    check_memory "$BIN" "hello world foo" " "
}

# =============================================================
# メイン実行
# =============================================================
echo "========================================"
echo " 42Tokyo — c09 テスト"
echo " $(date '+%Y-%m-%d %H:%M:%S')"
echo "========================================"

test_ex00
test_ex01
test_ex02

echo ""
echo "========================================"
echo -e " PASS: ${GREEN}${PASS}${NC}  FAIL: ${RED}${FAIL}${NC}  SKIP: ${YELLOW}${SKIP}${NC}"
if [ ${#ERRORS[@]} -gt 0 ]; then
    echo " 失敗:"
    for e in "${ERRORS[@]}"; do echo "   ✗ $e"; done
fi
echo "========================================"
[ $FAIL -eq 0 ] && exit 0 || exit 1
