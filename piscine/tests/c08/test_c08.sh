#!/bin/bash
# =============================================================
# test_c08.sh — c08 課題テストスクリプト
# 使い方: bash tests/c08/test_c08.sh
#
# 【自分でカスタマイズできる箇所】
#   - 各 test_exXX() 関数内の「カスタマイズここから/ここまで」ブロック
#   - テストケースの追加: run_test "ラベル" "期待する出力" コマンド を追記するだけ
# =============================================================

set -uo pipefail

# --- カラー ---
GREEN='\033[0;32m'; RED='\033[0;31m'; YELLOW='\033[1;33m'; BLUE='\033[0;34m'; NC='\033[0m'

# --- カウンター ---
PASS=0; FAIL=0; SKIP=0; ERRORS=()

# --- ユーティリティ ---
pass() { echo -e "  ${GREEN}[PASS]${NC} $1"; ((PASS++)) || true; }
fail() { echo -e "  ${RED}[FAIL]${NC} $1${2:+ — $2}"; ((FAIL++)) || true; ERRORS+=("$1"); }
skip() { echo -e "  ${YELLOW}[SKIP]${NC} $1"; ((SKIP++)) || true; }
info() { echo -e "\n${BLUE}▶ $1${NC}"; }
warn() { echo -e "  ${YELLOW}[WARN]${NC} $1"; }

# --- パス ---
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/../.." && pwd)"
SUBMIT_DIR="$ROOT_DIR/c08/htakumi"
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
    local extra="${2:-}"
    if command -v norminette &>/dev/null; then
        local out
        out=$(norminette $extra "$src" 2>&1)
        if echo "$out" | grep -q "Error!"; then
            fail "Norminette" "$(echo "$out" | grep "Error!" | head -3)"
        else
            pass "Norminette"
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
# exercise テスト関数
# =============================================================

# ------------------------------------------------------------
# ex00 — ft.h
# ヘッダファイルに5つの関数プロトタイプが含まれているか確認
# ------------------------------------------------------------
test_ex00() {
    local SRC="$SUBMIT_DIR/ex00/ft.h"
    info "ex00 — ft.h"

    [ ! -f "$SRC" ] && skip "ex00: ファイル未提出 ($SRC)" && return

    check_norminette "$SRC"

    # ===== カスタマイズここから =====
    # インクルードガードの確認（Norminette準拠: # define はスペースあり）
    if grep -q "#ifndef" "$SRC" && grep -qE "# *define" "$SRC" && grep -q "#endif" "$SRC"; then
        pass "インクルードガード (#ifndef/#define/#endif) あり"
    else
        fail "インクルードガード" "インクルードガードが見つかりません"
    fi

    # 5つのプロトタイプ確認
    grep -q "ft_putchar" "$SRC" && pass "ft_putchar プロトタイプあり" || fail "ft_putchar プロトタイプなし"
    grep -q "ft_swap"    "$SRC" && pass "ft_swap プロトタイプあり"    || fail "ft_swap プロトタイプなし"
    grep -q "ft_putstr"  "$SRC" && pass "ft_putstr プロトタイプあり"  || fail "ft_putstr プロトタイプなし"
    grep -q "ft_strlen"  "$SRC" && pass "ft_strlen プロトタイプあり"  || fail "ft_strlen プロトタイプなし"
    grep -q "ft_strcmp"  "$SRC" && pass "ft_strcmp プロトタイプあり"  || fail "ft_strcmp プロトタイプなし"

    # コンパイルテスト（スタブ実装 + mainでインクルードして通るか）
    local MAIN_C="$TMP_DIR/main_ex00.c"
    cat > "$MAIN_C" << 'EOF'
#include "ft.h"
#include <unistd.h>

void    ft_putchar(char c)  { write(1, &c, 1); }
void    ft_swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }
void    ft_putstr(char *str) { while (*str) write(1, str++, 1); }
int     ft_strlen(char *str) { int i = 0; while (str[i]) i++; return i; }
int     ft_strcmp(char *s1, char *s2) {
    while (*s1 && *s1 == *s2) { s1++; s2++; }
    return (unsigned char)*s1 - (unsigned char)*s2;
}
int     main(void) { return 0; }
EOF

    local BIN="$TMP_DIR/ex00"
    local CC_OUT
    if ! CC_OUT=$(cc -Wall -Wextra -Werror -I"$SUBMIT_DIR/ex00" "$MAIN_C" -o "$BIN" 2>&1); then
        fail "コンパイル" "$CC_OUT"
    else
        pass "コンパイル"
    fi
    # ===== カスタマイズここまで =====
}

# ------------------------------------------------------------
# ex01 — ft_boolean.h
# PDFのmain関数がコンパイル・実行できるか
# EVEN(even) == FALSE, ft_is_even(even) == TRUE であるべき
# ※ norminette は -R CheckDefine オプション必須
# ------------------------------------------------------------
test_ex01() {
    local SRC="$SUBMIT_DIR/ex01/ft_boolean.h"
    info "ex01 — ft_boolean.h"

    [ ! -f "$SRC" ] && skip "ex01: ファイル未提出 ($SRC)" && return

    check_norminette "$SRC" "-R CheckDefine"

    # マクロ・型の存在確認
    grep -q "EVEN"      "$SRC" && pass "EVEN マクロあり"      || fail "EVEN マクロなし"
    grep -q "EVEN_MSG"  "$SRC" && pass "EVEN_MSG マクロあり"  || fail "EVEN_MSG マクロなし"
    grep -q "ODD_MSG"   "$SRC" && pass "ODD_MSG マクロあり"   || fail "ODD_MSG マクロなし"
    grep -q "TRUE"      "$SRC" && pass "TRUE マクロあり"      || fail "TRUE マクロなし"
    grep -q "FALSE"     "$SRC" && pass "FALSE マクロあり"     || fail "FALSE マクロなし"
    grep -q "SUCCESS"   "$SRC" && pass "SUCCESS マクロあり"   || fail "SUCCESS マクロなし"
    grep -q "t_bool"    "$SRC" && pass "t_bool 型あり"        || fail "t_bool 型なし"
    grep -q "ft_putstr" "$SRC" && pass "ft_putstr プロトタイプあり" || fail "ft_putstr プロトタイプなし"

    # ===== カスタマイズここから =====
    # PDFのmain関数でコンパイル・実行
    local MAIN_C="$TMP_DIR/main_ex01.c"
    cat > "$MAIN_C" << 'EOF'
#include "ft_boolean.h"
#include <unistd.h>

void    ft_putstr(char *str)
{
    while (*str)
        write(1, str++, 1);
}

t_bool  ft_is_even(int nbr)
{
    return ((EVEN(nbr)) ? TRUE : FALSE);
}

int     main(int argc, char **argv)
{
    (void)argv;
    if (ft_is_even(argc - 1) == TRUE)
        ft_putstr(EVEN_MSG);
    else
        ft_putstr(ODD_MSG);
    return (SUCCESS);
}
EOF

    local BIN="$TMP_DIR/ex01"
    local CC_OUT
    if ! CC_OUT=$(cc -Wall -Wextra -Werror -I"$SUBMIT_DIR/ex01" "$MAIN_C" -o "$BIN" 2>&1); then
        fail "コンパイル" "$CC_OUT"; return
    fi
    pass "コンパイル"

    # 引数0個 (argc-1=0, 偶数) → "I have an even number of arguments.\n"
    run_test "引数0個 → even メッセージ" \
        "I have an even number of arguments." \
        "$BIN"

    # 引数1個 (argc-1=1, 奇数) → "I have an odd number of arguments.\n"
    run_test "引数1個 → odd メッセージ" \
        "I have an odd number of arguments." \
        "$BIN" "arg1"

    # 引数2個 (argc-1=2, 偶数) → "I have an even number of arguments.\n"
    run_test "引数2個 → even メッセージ" \
        "I have an even number of arguments." \
        "$BIN" "arg1" "arg2"

    # 引数3個 (argc-1=3, 奇数) → "I have an odd number of arguments.\n"
    run_test "引数3個 → odd メッセージ" \
        "I have an odd number of arguments." \
        "$BIN" "arg1" "arg2" "arg3"
    # ===== カスタマイズここまで =====
}

# ------------------------------------------------------------
# ex02 — ft_abs.h
# ABS(Value) マクロが正しく絶対値を返すか
# ※ norminette は -R CheckDefine オプション必須
# ------------------------------------------------------------
test_ex02() {
    local SRC="$SUBMIT_DIR/ex02/ft_abs.h"
    info "ex02 — ft_abs.h"

    [ ! -f "$SRC" ] && skip "ex02: ファイル未提出 ($SRC)" && return

    check_norminette "$SRC" "-R CheckDefine"

    grep -q "ABS" "$SRC" && pass "ABS マクロあり" || fail "ABS マクロなし"

    # ===== カスタマイズここから =====
    local MAIN_C="$TMP_DIR/main_ex02.c"
    cat > "$MAIN_C" << 'EOF'
#include "ft_abs.h"
#include <unistd.h>
#include <stdlib.h>

void    ft_putnbr(int n)
{
    char    c;
    if (n < 0) { write(1, "-", 1); n = -n; }
    if (n >= 10) ft_putnbr(n / 10);
    c = (n % 10) + '0';
    write(1, &c, 1);
}

int     main(int argc, char **argv)
{
    if (argc != 2) return 1;
    int val = atoi(argv[1]);
    ft_putnbr(ABS(val));
    return 0;
}
EOF

    local BIN="$TMP_DIR/ex02"
    local CC_OUT
    if ! CC_OUT=$(cc -Wall -Wextra -Werror -I"$SUBMIT_DIR/ex02" "$MAIN_C" -o "$BIN" 2>&1); then
        fail "コンパイル" "$CC_OUT"; return
    fi
    pass "コンパイル"

    run_test "ABS(5) = 5"    "5"  "$BIN" "5"
    run_test "ABS(-5) = 5"   "5"  "$BIN" "-5"
    run_test "ABS(0) = 0"    "0"  "$BIN" "0"
    run_test "ABS(42) = 42"  "42" "$BIN" "42"
    run_test "ABS(-42) = 42" "42" "$BIN" "-42"
    run_test "ABS(1) = 1"    "1"  "$BIN" "1"
    run_test "ABS(-1) = 1"   "1"  "$BIN" "-1"
    # ===== カスタマイズここまで =====
}

# ------------------------------------------------------------
# ex03 — ft_point.h
# t_point 構造体と set_point プロトタイプが正しく定義されているか
# ------------------------------------------------------------
test_ex03() {
    local SRC="$SUBMIT_DIR/ex03/ft_point.h"
    info "ex03 — ft_point.h"

    [ ! -f "$SRC" ] && skip "ex03: ファイル未提出 ($SRC)" && return

    check_norminette "$SRC"

    grep -q "t_point"    "$SRC" && pass "t_point 型あり"       || fail "t_point 型なし"
    grep -q "set_point"  "$SRC" && pass "set_point プロトタイプあり" || fail "set_point プロトタイプなし"
    grep -q "int.*x"     "$SRC" && pass "メンバ x あり"         || fail "メンバ x なし"
    grep -q "int.*y"     "$SRC" && pass "メンバ y あり"         || fail "メンバ y なし"

    # ===== カスタマイズここから =====
    # PDFのmain関数でコンパイルできるか確認
    local MAIN_C="$TMP_DIR/main_ex03.c"
    cat > "$MAIN_C" << 'EOF'
#include "ft_point.h"
#include <unistd.h>

void    set_point(t_point *point)
{
    point->x = 42;
    point->y = 21;
}

int     main(void)
{
    t_point     point;

    set_point(&point);
    return (0);
}
EOF

    local BIN="$TMP_DIR/ex03"
    local CC_OUT
    if ! CC_OUT=$(cc -Wall -Wextra -Werror -I"$SUBMIT_DIR/ex03" "$MAIN_C" -o "$BIN" 2>&1); then
        fail "コンパイル" "$CC_OUT"; return
    fi
    pass "コンパイル"

    # set_point後にx=42, y=21になっているか確認
    local MAIN2_C="$TMP_DIR/main_ex03_check.c"
    cat > "$MAIN2_C" << 'EOF'
#include "ft_point.h"
#include <unistd.h>
#include <stdlib.h>

void    set_point(t_point *point)
{
    point->x = 42;
    point->y = 21;
}

void    ft_putnbr(int n)
{
    char c;
    if (n < 0) { write(1, "-", 1); n = -n; }
    if (n >= 10) ft_putnbr(n / 10);
    c = (n % 10) + '0';
    write(1, &c, 1);
}

int     main(void)
{
    t_point point;
    set_point(&point);
    ft_putnbr(point.x);
    write(1, " ", 1);
    ft_putnbr(point.y);
    return (0);
}
EOF

    local BIN2="$TMP_DIR/ex03_check"
    if cc -Wall -Wextra -Werror -I"$SUBMIT_DIR/ex03" "$MAIN2_C" -o "$BIN2" 2>&1; then
        run_test "t_point の x=42, y=21 にセット" "42 21" "$BIN2"
    fi
    # ===== カスタマイズここまで =====
}

# ------------------------------------------------------------
# ex04 — ft_strs_to_tab
# 文字列配列を t_stock_str 配列に変換する関数
# ------------------------------------------------------------
test_ex04() {
    local SRC="$SUBMIT_DIR/ex04/ft_strs_to_tab.c"
    local HDR="$SUBMIT_DIR/ex04/ft_stock_str.h"
    info "ex04 — ft_strs_to_tab"

    [ ! -f "$SRC" ] && skip "ex04: ft_strs_to_tab.c 未提出" && return
    [ ! -f "$HDR" ] && skip "ex04: ft_stock_str.h 未提出" && return

    check_norminette "$SRC"
    check_norminette "$HDR"

    # ft_stock_str.h の構造体確認
    grep -q "size"  "$HDR" && pass "メンバ size あり"  || fail "メンバ size なし"
    grep -q "\*str" "$HDR" && pass "メンバ str あり"   || fail "メンバ str なし"
    grep -q "\*copy" "$HDR" && pass "メンバ copy あり" || fail "メンバ copy なし"

    # ===== カスタマイズここから =====
    local MAIN_C="$TMP_DIR/main_ex04.c"
    cat > "$MAIN_C" << 'EOF'
#include "ft_stock_str.h"
#include <unistd.h>
#include <stdlib.h>

struct s_stock_str  *ft_strs_to_tab(int ac, char **av);

void    ft_putnbr(int n)
{
    char c;
    if (n < 0) { write(1, "-", 1); n = -n; }
    if (n >= 10) ft_putnbr(n / 10);
    c = (n % 10) + '0';
    write(1, &c, 1);
}

void    ft_putstr(char *s) { while (*s) write(1, s++, 1); }

int     main(int argc, char **argv)
{
    struct s_stock_str  *tab;
    int                 i;

    if (argc < 2)
        return (0);
    tab = ft_strs_to_tab(argc - 1, argv + 1);
    if (!tab)
    {
        write(1, "NULL\n", 5);
        return (1);
    }
    i = 0;
    while (tab[i].str != 0)
    {
        ft_putstr(tab[i].str);
        write(1, "\n", 1);
        ft_putnbr(tab[i].size);
        write(1, "\n", 1);
        ft_putstr(tab[i].copy);
        write(1, "\n", 1);
        i++;
    }
    /* 末尾のstr==0確認: 最後の次の要素のstrが0なら "SENTINEL_OK" 出力 */
    if (tab[argc - 1].str == 0)
        write(1, "SENTINEL_OK\n", 12);
    /* 各 copy を free */
    i = 0;
    while (tab[i].str != 0)
    {
        free(tab[i].copy);
        i++;
    }
    free(tab);
    return (0);
}
EOF

    local BIN="$TMP_DIR/ex04"
    local CC_OUT
    if ! CC_OUT=$(cc -Wall -Wextra -Werror \
        -I"$SUBMIT_DIR/ex04" \
        "$SRC" "$MAIN_C" \
        -o "$BIN" 2>&1); then
        fail "コンパイル" "$CC_OUT"; return
    fi
    pass "コンパイル"

    # 基本テスト: 1要素
    run_test "1要素: hello (str/size/copy)" \
        "$(printf 'hello\n5\nhello\nSENTINEL_OK')" \
        "$BIN" "hello"

    # 2要素
    run_test "2要素: hello world" \
        "$(printf 'hello\n5\nhello\nworld\n5\nworld\nSENTINEL_OK')" \
        "$BIN" "hello" "world"

    # 空文字列
    run_test "空文字列 (size=0)" \
        "$(printf '\n0\n\nSENTINEL_OK')" \
        "$BIN" ""

    # 要素なし (ac=0) 専用のバイナリ
    local MAIN0_C="$TMP_DIR/main_ex04_empty.c"
    cat > "$MAIN0_C" << 'EOF2'
#include "ft_stock_str.h"
#include <unistd.h>
#include <stdlib.h>

struct s_stock_str  *ft_strs_to_tab(int ac, char **av);

int     main(void)
{
    char                *empty[] = {0};
    struct s_stock_str  *tab;

    tab = ft_strs_to_tab(0, empty);
    if (!tab)
    {
        write(1, "NULL\n", 5);
        return (1);
    }
    if (tab[0].str == 0)
        write(1, "SENTINEL_OK\n", 12);
    free(tab);
    return (0);
}
EOF2
    local BIN0="$TMP_DIR/ex04_empty"
    if cc -Wall -Wextra -Werror \
        -I"$SUBMIT_DIR/ex04" \
        "$SRC" "$MAIN0_C" \
        -o "$BIN0" 2>&1 | grep -q "error"; then
        warn "引数なし専用バイナリのコンパイル失敗"
    else
        run_test "引数なし → 空配列 (str[0]==0)" \
            "SENTINEL_OK" \
            "$BIN0"
    fi

    # メモリリーク確認 (引数ありで)
    check_memory "$BIN" "hello" "world"

    check_forbidden "$BIN" "malloc|free|_start|__libc|__cxa|dyld|write"
    # ===== カスタマイズここまで =====
}

# ------------------------------------------------------------
# ex05 — ft_show_tab
# t_stock_str 配列の各要素を str\nsize\ncopy\n の形式で出力
# ※ ex04 (ft_strs_to_tab) と組み合わせてテストする
# ------------------------------------------------------------
test_ex05() {
    local SRC="$SUBMIT_DIR/ex05/ft_show_tab.c"
    local HDR="$SUBMIT_DIR/ex05/ft_stock_str.h"
    local SRC04="$SUBMIT_DIR/ex04/ft_strs_to_tab.c"
    info "ex05 — ft_show_tab"

    [ ! -f "$SRC" ] && skip "ex05: ft_show_tab.c 未提出" && return
    [ ! -f "$HDR" ] && skip "ex05: ft_stock_str.h 未提出" && return

    check_norminette "$SRC"

    # ===== カスタマイズここから =====
    # ft_strs_to_tab のスタブを常に自作（ft_strlen 重複リンクエラーを避けるため）
    # ex04 の .c と ex05 の .c 両方に ft_strlen が定義されているとリンクエラーになる
    local STUB_C="$TMP_DIR/stub_strs_to_tab.c"
    cat > "$STUB_C" << 'STUBEOF'
#include "ft_stock_str.h"
#include <stdlib.h>

/* ft_strlen はここでは定義しない (ex05 側に既にある) */
static int s_slen(char *s) { int i = 0; while (s[i]) i++; return i; }
static char *s_sdup(char *s) {
    int n = s_slen(s);
    char *p = malloc(n + 1);
    int i = 0;
    if (!p) return (NULL);
    while (s[i]) { p[i] = s[i]; i++; }
    p[n] = '\0';
    return (p);
}
struct s_stock_str *ft_strs_to_tab(int ac, char **av) {
    struct s_stock_str *tab;
    int i;
    tab = malloc(sizeof(struct s_stock_str) * (ac + 1));
    if (!tab) return (NULL);
    i = 0;
    while (i < ac) {
        tab[i].size = s_slen(av[i]);
        tab[i].str = av[i];
        tab[i].copy = s_sdup(av[i]);
        if (!tab[i].copy) return (NULL);
        i++;
    }
    tab[ac].str = 0;
    return (tab);
}
STUBEOF
    local STRS_TO_TAB_SRC="$STUB_C"

    local MAIN_C="$TMP_DIR/main_ex05.c"
    cat > "$MAIN_C" << 'EOF'
#include "ft_stock_str.h"
#include <stdlib.h>

struct s_stock_str  *ft_strs_to_tab(int ac, char **av);
void                ft_show_tab(struct s_stock_str *par);

int     main(int argc, char **argv)
{
    struct s_stock_str  *tab;
    int                 i;

    if (argc < 2)
        return (0);
    tab = ft_strs_to_tab(argc - 1, argv + 1);
    if (!tab)
        return (1);
    ft_show_tab(tab);
    i = 0;
    while (tab[i].str != 0)
    {
        free(tab[i].copy);
        i++;
    }
    free(tab);
    return (0);
}
EOF

    # ex05のft_stock_str.hをex04のft_strs_to_tab.cでも使えるようコピー
    cp "$HDR" "$TMP_DIR/ft_stock_str.h"

    local BIN="$TMP_DIR/ex05"
    local CC_OUT
    if ! CC_OUT=$(cc -Wall -Wextra -Werror \
        -I"$SUBMIT_DIR/ex05" \
        -I"$TMP_DIR" \
        "$SRC" "$STRS_TO_TAB_SRC" "$MAIN_C" \
        -o "$BIN" 2>&1); then
        fail "コンパイル" "$CC_OUT"; return
    fi
    pass "コンパイル"

    # 出力フォーマット: str\nsize\ncopy\n (各要素)
    run_test "1要素 hello の出力" \
        "$(printf 'hello\n5\nhello')" \
        "$BIN" "hello"

    run_test "2要素 hello world の出力" \
        "$(printf 'hello\n5\nhello\nworld\n5\nworld')" \
        "$BIN" "hello" "world"

    run_test "3要素の出力" \
        "$(printf 'abc\n3\nabc\nde\n2\nde\nf\n1\nf')" \
        "$BIN" "abc" "de" "f"

    run_test "空文字列の出力" \
        "$(printf '\n0\n')" \
        "$BIN" ""

    check_forbidden "$BIN" "write|malloc|free|_start|__libc|__cxa|dyld"
    check_memory "$BIN" "hello" "world"
    # ===== カスタマイズここまで =====
}

# =============================================================
# メイン実行
# =============================================================
echo "========================================"
echo " 42Tokyo — c08 テスト"
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
echo -e " PASS: ${GREEN}${PASS}${NC}  FAIL: ${RED}${FAIL}${NC}  SKIP: ${YELLOW}${SKIP}${NC}"
if [ ${#ERRORS[@]} -gt 0 ]; then
    echo " 失敗:"
    for e in "${ERRORS[@]}"; do echo "   ✗ $e"; done
fi
echo "========================================"
[ $FAIL -eq 0 ] && exit 0 || exit 1
