#!/bin/bash
# =============================================================
# test_ft_printf.sh — ft_printf テストスクリプト
# 使い方: bash cursus/circle1/ft_printf/tests/test_ft_printf.sh
# =============================================================

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJ_DIR="$(cd "$SCRIPT_DIR/.." && pwd)/42_develop"
BIN_DIR="/tmp/test_ft_printf_$$"
PASS=0
FAIL=0
SKIP=0

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[1;34m'
NC='\033[0m'

cleanup() { rm -rf "$BIN_DIR"; }
trap cleanup EXIT
mkdir -p "$BIN_DIR"

print_header() { echo -e "\n${BLUE}===== $1 =====${NC}"; }
ok()   { echo -e "  ${GREEN}[OK]${NC}   $1"; ((PASS++)); }
fail() { echo -e "  ${RED}[FAIL]${NC} $1"; ((FAIL++)); }
skip() { echo -e "  ${YELLOW}[SKIP]${NC} $1"; ((SKIP++)); }

# ============================================================
# STEP 1: ビルド前チェック
# ============================================================
print_header "ビルド前チェック"

MISSING=0
for f in libft/Makefile libft/libft.h; do
	if [ ! -f "$PROJ_DIR/$f" ]; then
		echo -e "  ${RED}[ERROR]${NC} $PROJ_DIR/$f が存在しません"
		echo "         → 修正: git restore \"cursus/circle1/ft_printf/42_develop/$f\""
		MISSING=1
	fi
done

if [ "$MISSING" -eq 1 ]; then
	echo ""
	echo -e "${RED}ビルドに必要なファイルが不足しています。上記 git restore で復元してください。${NC}"
	exit 1
fi
ok "libft/Makefile  存在確認"
ok "libft/libft.h   存在確認"

# ============================================================
# STEP 2: Norminette / 手動チェック
# ============================================================
print_header "Norminette チェック"

if command -v norminette &>/dev/null; then
	NORM_OUT=$(norminette "$PROJ_DIR"/*.c "$PROJ_DIR"/*.h 2>&1)
	NORM_ERR=$(echo "$NORM_OUT" | grep -c "Error" || true)
	if [ "$NORM_ERR" -eq 0 ]; then
		ok "Norminette: エラーなし"
	else
		echo "$NORM_OUT" | grep "Error"
		fail "Norminette: ${NORM_ERR}件のエラー"
	fi
else
	skip "Norminette: インストールされていません（手動チェックに切り替え）"
	# if文のスペースチェック
	if grep -qP 'if\(' "$PROJ_DIR"/*.c 2>/dev/null; then
		BADIF=$(grep -rn 'if(' "$PROJ_DIR"/*.c | grep -v '/\*' | grep -v '"')
		echo -e "  ${RED}[WARN]${NC}  Norm違反候補: if の後ろにスペースなし"
		echo "$BADIF" | while IFS= read -r line; do echo "         $line"; done
		fail "if文スペースチェック"
	else
		ok "if文スペースチェック: OK"
	fi
fi

# ============================================================
# STEP 3: ビルド (make re)
# ============================================================
print_header "ビルド (make re)"

if ! make -C "$PROJ_DIR" re 2>&1; then
	echo -e "${RED}make 失敗。ビルドエラーを修正してください。${NC}"
	exit 1
fi
ok "make re 成功"
ok "libftprintf.a 生成確認: $(ls -lh "$PROJ_DIR/libftprintf.a" | awk '{print $5}')"

# ============================================================
# STEP 4: 動作テスト
# ============================================================
# C テストプログラムを here-doc で生成
cat > "$BIN_DIR/test_main.c" << 'CEOF'
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "ft_printf.h"

static int g_pass = 0;
static int g_fail = 0;

static void check(const char *name, const char *exp, int exp_ret,
                  const char *got, int got_ret)
{
	if (strcmp(exp, got) == 0 && exp_ret == got_ret)
	{
		dprintf(2, "  [OK]   %s\n", name);
		g_pass++;
	}
	else
	{
		dprintf(2, "  [FAIL] %s\n", name);
		if (strcmp(exp, got) != 0)
		{
			dprintf(2, "         expected: [%s]\n", exp);
			dprintf(2, "         got:      [%s]\n", got);
		}
		if (exp_ret != got_ret)
			dprintf(2, "         ret: expected=%d  got=%d\n", exp_ret, got_ret);
		g_fail++;
	}
}

/* ft_printf の出力をパイプで捕捉し got[] に格納するマクロ */
#define CAPTURE(buf, ret, ...) do { \
	int _pfd[2]; int _fsv; int _n; \
	pipe(_pfd); \
	_fsv = dup(1); \
	dup2(_pfd[1], 1); \
	close(_pfd[1]); \
	(ret) = ft_printf(__VA_ARGS__); \
	dup2(_fsv, 1); \
	close(_fsv); \
	_n = (int)read(_pfd[0], (buf), 4095); \
	(buf)[_n >= 0 ? _n : 0] = '\0'; \
	close(_pfd[0]); \
} while (0)

/* snprintf で期待値を作り ft_printf の出力と比較するマクロ */
#define TEST(name, ...) do { \
	char _exp[4096] = {0}; char _got[4096] = {0}; \
	int _eret, _gret; \
	_eret = snprintf(_exp, sizeof(_exp), __VA_ARGS__); \
	CAPTURE(_got, _gret, __VA_ARGS__); \
	check(name, _exp, _eret, _got, _gret); \
} while (0)

int	main(void)
{
	char	*null_str;
	void	*null_ptr;
	int		x;
	char	_got[4096];
	int		_gret;

	null_str = NULL;
	null_ptr = NULL;
	x = 42;

	/* ===== %c ===== */
	dprintf(2, "\n[%%c]\n");
	TEST("'A'",       "%c", 'A');
	TEST("'z'",       "%c", 'z');
	TEST("'0'",       "%c", '0');
	TEST("' '(space)", "%c", ' ');
	TEST("'@'",       "%c", '@');

	/* ===== %s ===== */
	dprintf(2, "\n[%%s]\n");
	TEST("\"hello\"",        "%s", "hello");
	TEST("\"\" (empty)",     "%s", "");
	TEST("\"Hello World\"",  "%s", "Hello, World!");
	TEST("\"42 is cool\"",   "%s", "42 is cool");
	/* NULL → "(null)", return 6  (Linux/42 サーバー準拠) */
	CAPTURE(_got, _gret, "%s", null_str);
	check("NULL → \"(null)\" ret=6", "(null)", 6, _got, _gret);

	/* ===== %d / %i ===== */
	dprintf(2, "\n[%%d / %%i]\n");
	TEST("%%d 0",       "%d", 0);
	TEST("%%d 42",      "%d", 42);
	TEST("%%d -42",     "%d", -42);
	TEST("%%d INT_MAX", "%d", INT_MAX);
	TEST("%%d INT_MIN", "%d", INT_MIN);
	TEST("%%i 0",       "%i", 0);
	TEST("%%i 1000",    "%i", 1000);
	TEST("%%i -1000",   "%i", -1000);
	TEST("%%i INT_MIN", "%i", INT_MIN);

	/* ===== %u ===== */
	dprintf(2, "\n[%%u]\n");
	TEST("%%u 0",        "%u", 0u);
	TEST("%%u 42",       "%u", 42u);
	TEST("%%u 4294967295 (UINT_MAX)", "%u", UINT_MAX);

	/* ===== %x ===== */
	dprintf(2, "\n[%%x]\n");
	TEST("%%x 0",    "%x", 0u);
	TEST("%%x 42",   "%x", 42u);
	TEST("%%x 255",  "%x", 255u);
	TEST("%%x 256",  "%x", 256u);
	TEST("%%x UINT_MAX", "%x", UINT_MAX);

	/* ===== %X ===== */
	dprintf(2, "\n[%%X]\n");
	TEST("%%X 0",    "%X", 0u);
	TEST("%%X 42",   "%X", 42u);
	TEST("%%X 255",  "%X", 255u);
	TEST("%%X UINT_MAX", "%X", UINT_MAX);

	/* ===== %% ===== */
	dprintf(2, "\n[%%%%]\n");
	TEST("%%%%",        "%%");
	TEST("\"a%%%%b\"",  "a%%b");
	TEST("\"%%d=42\"",  "%%d=%d", 42);

	/* ===== %p ===== */
	dprintf(2, "\n[%%p]\n");
	/* 有効ポインタ: ft_printf と snprintf(printf) で一致するか確認 */
	TEST("%%p &x", "%p", (void *)&x);
	{
		char _exp2[4096] = {0};
		int  _eret2;
		_eret2 = snprintf(_exp2, sizeof(_exp2), "%p", (void *)0xdeadbeef);
		CAPTURE(_got, _gret, "%p", (void *)0xdeadbeef);
		check("%%p 0xdeadbeef", _exp2, _eret2, _got, _gret);
	}
	/* NULL ポインタ: Linux="(nil)"(5), macOS="0x0"(3) どちらも許容 */
	CAPTURE(_got, _gret, "%p", null_ptr);
	if ((strcmp(_got, "(nil)") == 0 && _gret == 5)
		|| (strcmp(_got, "0x0") == 0 && _gret == 3))
	{
		dprintf(2, "  [OK]   %%p NULL → [%s] ret=%d\n", _got, _gret);
		g_pass++;
	}
	else
	{
		dprintf(2, "  [FAIL] %%p NULL → [%s] ret=%d"
			" (expected \"(nil)\" ret=5  or  \"0x0\" ret=3)\n", _got, _gret);
		g_fail++;
	}

	/* ===== 複合テスト ===== */
	dprintf(2, "\n[複合フォーマット]\n");
	TEST("%%s %%d",          "%s %d", "value", 42);
	TEST("%%d %%x",          "%d %x", 255, 255u);
	TEST("%%c%%c%%c",        "%c%c%c", 'a', 'b', 'c');
	TEST("複数変換+文字列",  "num=%d hex=%x str=%s", 42, 255u, "hello");
	TEST("文字列のみ",        "hello, world");
	TEST("空フォーマット",    "");

	/* ===== 戻り値テスト（return value） ===== */
	dprintf(2, "\n[戻り値テスト]\n");
	TEST("ret: 単一文字",    "A");
	TEST("ret: 数値 42",     "%d", 42);
	TEST("ret: 文字列",      "%s", "hello");
	TEST("ret: パーセント",  "100%%");

	/* ===== サマリー ===== */
	dprintf(2, "\n========================================\n");
	dprintf(2, "  合計 %d テスト   ✅ %d 合格   ❌ %d 失敗\n",
		g_pass + g_fail, g_pass, g_fail);
	dprintf(2, "========================================\n");

	return (g_fail > 0 ? 1 : 0);
}
CEOF

print_header "動作テスト (ft_printf vs printf)"

if ! cc -Wall -Wextra -Werror \
		-I "$PROJ_DIR" \
		"$BIN_DIR/test_main.c" \
		"$PROJ_DIR/libftprintf.a" \
		-o "$BIN_DIR/test_main" 2>"$BIN_DIR/cc_err.txt"; then
	echo -e "  ${RED}[ERROR]${NC} テストバイナリのコンパイル失敗:"
	cat "$BIN_DIR/cc_err.txt"
	exit 1
fi

"$BIN_DIR/test_main" 2>&1
TEST_EXIT=$?

if [ $TEST_EXIT -eq 0 ]; then
	PASS=$((PASS + 1))
else
	FAIL=$((FAIL + 1))
fi

# ============================================================
# STEP 5: 最終サマリー
# ============================================================
print_header "最終サマリー"
echo ""
if [ "$FAIL" -eq 0 ]; then
	echo -e "  ${GREEN}✅ 全チェック合格！提出可能です。${NC}"
else
	echo -e "  ${RED}❌ ${FAIL}件の問題があります。修正してから提出してください。${NC}"
fi
echo ""

exit "$FAIL"
CEOF_SCRIPT
