#!/bin/bash
# =============================================================
# test_get_next_line.sh — get_next_line テストスクリプト
#
# 使い方:
#   bash cursus/circle1/get_next_line/tests/test_get_next_line.sh
#   BONUS=1 bash cursus/circle1/get_next_line/tests/test_get_next_line.sh
#   BUFFER_SIZES="1 42 9999" bash .../test_get_next_line.sh   (テストするBUFFER_SIZEを上書き)
#
# 【自分でカスタマイズできる箇所】
#   - BUFFER_SIZES 変数（下の方）でテストするバッファサイズの一覧を変更できる
#   - 各 test_xxx() 内の「カスタマイズここから/ここまで」ブロックにテストケースを追記できる
#   - bonus: BONUS=1 で実行（get_next_line_bonus.c/h, get_next_line_utils_bonus.c が
#            提出されていれば実行、なければ自動で [SKIP]）
# =============================================================

set -uo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJ_DIR="$(cd "$SCRIPT_DIR/../42_develop" && pwd)"
WORK_DIR="$(mktemp -d /tmp/gnl_test.XXXXXX)"
BONUS="${BONUS:-0}"
BUFFER_SIZES="${BUFFER_SIZES:-1 5 42 9999 10000000}"

trap 'rm -rf "$WORK_DIR"' EXIT

PASS=0
FAIL=0
SKIP=0

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

pass() { echo -e "  ${GREEN}[PASS]${NC} $1"; PASS=$((PASS + 1)); }
fail() { echo -e "  ${RED}[FAIL]${NC} $1"; FAIL=$((FAIL + 1)); }
skip() { echo -e "  ${YELLOW}[SKIP]${NC} $1"; SKIP=$((SKIP + 1)); }
section() { echo; echo "=== $1 ==="; }

# ----- ビルド方式の自動判定 -----------------------------------
HAS_MAKEFILE=0
[ -f "$PROJ_DIR/Makefile" ] && HAS_MAKEFILE=1

HAS_BONUS=0
if [ -f "$PROJ_DIR/get_next_line_bonus.c" ] && [ -f "$PROJ_DIR/get_next_line_bonus.h" ] \
	&& [ -f "$PROJ_DIR/get_next_line_utils_bonus.c" ]; then
	HAS_BONUS=1
fi

# compile_test: $1=driver.c $2=出力バイナリ $3=BUFFER_SIZE
# Makefile あり → make で get_next_line.a を作りリンク
# Makefile なし → cc で直接コンパイル
compile_test() {
	local driver="$1"
	local bin="$2"
	local bs="$3"

	if [ "$HAS_MAKEFILE" -eq 1 ]; then
		make -C "$PROJ_DIR" fclean >/dev/null 2>&1
		if ! make -C "$PROJ_DIR" BUFFER_SIZE="$bs" all >"$WORK_DIR/make.log" 2>&1; then
			cat "$WORK_DIR/make.log" >&2
			return 1
		fi
		cc -Wall -Wextra -Werror -D BUFFER_SIZE="$bs" -I "$PROJ_DIR" \
			"$driver" "$PROJ_DIR/get_next_line.a" -o "$bin" 2>"$WORK_DIR/cc.log"
	else
		cc -Wall -Wextra -Werror -D BUFFER_SIZE="$bs" -I "$PROJ_DIR" \
			"$driver" "$PROJ_DIR/get_next_line.c" "$PROJ_DIR/get_next_line_utils.c" \
			-o "$bin" 2>"$WORK_DIR/cc.log"
	fi
}

# compile_test_bonus: $1=driver.c $2=出力バイナリ $3=BUFFER_SIZE
compile_test_bonus() {
	local driver="$1"
	local bin="$2"
	local bs="$3"

	cc -Wall -Wextra -Werror -D BUFFER_SIZE="$bs" -I "$PROJ_DIR" \
		"$driver" "$PROJ_DIR/get_next_line_bonus.c" "$PROJ_DIR/get_next_line_utils_bonus.c" \
		-o "$bin" 2>"$WORK_DIR/cc_bonus.log"
}

# memcheck: $1=バイナリ, 残りは引数。0=leak無し 1=leak有り 2=ツール無し(SKIP)
memcheck() {
	local bin="$1"
	shift
	if command -v valgrind >/dev/null 2>&1; then
		valgrind --leak-check=full --error-exitcode=1 -q "$bin" "$@" \
			>/dev/null 2>"$WORK_DIR/valgrind.log"
		return $?
	elif [ "$(uname)" = "Darwin" ] && command -v leaks >/dev/null 2>&1; then
		if MallocStackLogging=1 leaks --atExit -- "$bin" "$@" \
			>"$WORK_DIR/leaks.log" 2>&1; then
			grep -q "0 leaks for 0 total leaked bytes" "$WORK_DIR/leaks.log"
			return $?
		fi
		return 1
	fi
	return 2
}

# ----- 固定テストファイル (fixtures) ---------------------------
FIXTURES_DIR="$WORK_DIR/fixtures"
mkdir -p "$FIXTURES_DIR"

# 既存の手書きfixtureをそのまま利用
for f in test1_normal.txt test2_no_newline_at_end.txt test3_empty_lines.txt \
	test4_single_line.txt test5_empty.txt test6_long_lines.txt test7_only_newlines.txt; do
	cp "$SCRIPT_DIR/$f" "$FIXTURES_DIR/$f"
done

# 追加fixture: BUFFER_SIZEをまたぐ大きめのファイルを実行時に生成 (リポジトリを汚さない)
: >"$FIXTURES_DIR/test8_big.txt"
i=1
while [ "$i" -le 2000 ]; do
	echo "line number $i xxxxxxxxxxxxxxxxxxxx"
	i=$((i + 1))
done >"$FIXTURES_DIR/test8_big.txt"

FIXTURE_FILES="test1_normal.txt test2_no_newline_at_end.txt test3_empty_lines.txt test4_single_line.txt test5_empty.txt test6_long_lines.txt test7_only_newlines.txt test8_big.txt"

# ===== カスタマイズここから (drivers) =====

cat >"$WORK_DIR/driver_cat.c" <<'EOF'
/* get_next_line() を繰り返し呼び、読んだ内容をそのまま標準出力に書き出す。
 * 元ファイルと出力をdiffすれば、行の分割と \n の扱いが正しいか検証できる。 */
#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>

/* get_next_line.h の ft_strlen をそのまま使うと利用可能関数の議論が
 * 混ざるので、テスト側では独自に長さを数える */
static size_t	ft_strlen_(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc >= 2)
		fd = open(argv[1], O_RDONLY);
	else
		fd = 0;
	if (fd < 0)
		return (1);
	while ((line = get_next_line(fd)) != NULL)
	{
		write(1, line, ft_strlen_(line));
		free(line);
	}
	if (argc >= 2)
		close(fd);
	return (0);
}
EOF

cat >"$WORK_DIR/driver_one_call.c" <<'EOF'
/* 1回の呼び出しで複数行を跨いで返していないか (改行は最後の1文字だけか) を確認する */
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		i;
	int		nl_count;

	(void)argc;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (2);
	line = get_next_line(fd);
	close(fd);
	if (!line)
		return (2);
	i = 0;
	nl_count = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			nl_count++;
		i++;
	}
	if (nl_count > 1)
	{
		free(line);
		return (1);
	}
	if (nl_count == 1 && line[i - 1] != '\n')
	{
		free(line);
		return (1);
	}
	free(line);
	return (0);
}
EOF

cat >"$WORK_DIR/driver_invalid_fd.c" <<'EOF'
/* 不正なfd (負の値、既にcloseされたfd) は NULL を返すべき */
#include "get_next_line.h"
#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	*line;

	line = get_next_line(-1);
	if (line != NULL)
		return (1);
	fd = open("/dev/null", O_RDONLY);
	close(fd);
	line = get_next_line(fd);
	if (line != NULL)
	{
		free(line);
		return (1);
	}
	return (0);
}
EOF

cat >"$WORK_DIR/driver_devnull.c" <<'EOF'
/* /dev/null (中身が無いfd) からの読み込みは最初からNULLを返すべき */
#include "get_next_line.h"
#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("/dev/null", O_RDONLY);
	line = get_next_line(fd);
	close(fd);
	if (line != NULL)
	{
		free(line);
		return (1);
	}
	return (0);
}
EOF

cat >"$WORK_DIR/driver_helpers.c" <<'EOF'
/* get_next_line.h で公開されているヘルパー関数の単体テスト */
#include "get_next_line.h"
#include <string.h>

static int	check(int cond, const char *label)
{
	if (!cond)
		write(2, label, strlen(label));
	return (!cond);
}

int	main(void)
{
	int		errors;
	char	*s;
	char	*joined;

	errors = 0;
	errors += check(ft_strlen("") == 0, "ft_strlen empty\n");
	errors += check(ft_strlen("hello") == 5, "ft_strlen hello\n");
	errors += check(ft_strlen(NULL) == 0, "ft_strlen NULL\n");

	s = ft_strchr_gnl("hello", 'l');
	errors += check(s != NULL && s == strchr("hello", 'l'), "ft_strchr_gnl found\n");
	s = ft_strchr_gnl("hello", 'z');
	errors += check(s == NULL, "ft_strchr_gnl not found\n");
	s = ft_strchr_gnl("hello", '\0');
	errors += check(s != NULL && *s == '\0', "ft_strchr_gnl nul\n");

	joined = ft_strjoin_n("abc", 3, "def", 3);
	errors += check(joined != NULL && strcmp(joined, "abcdef") == 0, "ft_strjoin_n basic\n");
	free(joined);
	joined = ft_strjoin_n(NULL, 0, "xyz", 3);
	errors += check(joined != NULL && strcmp(joined, "xyz") == 0, "ft_strjoin_n null s1\n");
	free(joined);
	joined = ft_strjoin_n("abc", 3, NULL, 0);
	errors += check(joined == NULL, "ft_strjoin_n null s2\n");

	s = extract_line("hello\nworld");
	errors += check(s != NULL && strcmp(s, "hello\n") == 0, "extract_line with newline\n");
	free(s);
	s = extract_line("hello");
	errors += check(s != NULL && strcmp(s, "hello") == 0, "extract_line without newline\n");
	free(s);

	s = update_leftover("hello\nworld");
	errors += check(s != NULL && strcmp(s, "world") == 0, "update_leftover basic\n");
	free(s);
	s = update_leftover("hello\n");
	errors += check(s == NULL, "update_leftover nothing left\n");
	s = update_leftover("hello");
	errors += check(s == NULL, "update_leftover no newline\n");

	return (errors > 0);
}
EOF

cat >"$WORK_DIR/driver_bonus_multi.c" <<'EOF'
/* bonus: fd 3,4,5 を切り替えながら読んでも、それぞれの読み込み状態を
 * 見失わないことを確認する */
#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <string.h>

int	main(int argc, char **argv)
{
	int		fds[3];
	char	*line;
	char	*expect[3][3];
	int		i;

	if (argc < 4)
		return (2);
	fds[0] = open(argv[1], O_RDONLY);
	fds[1] = open(argv[2], O_RDONLY);
	fds[2] = open(argv[3], O_RDONLY);
	if (fds[0] < 0 || fds[1] < 0 || fds[2] < 0)
		return (2);
	expect[0][0] = "fdA line1\n"; expect[0][1] = "fdA line2\n"; expect[0][2] = "fdA line3\n";
	expect[1][0] = "fdB line1\n"; expect[1][1] = "fdB line2\n"; expect[1][2] = "fdB line3\n";
	expect[2][0] = "fdC line1\n"; expect[2][1] = "fdC line2\n"; expect[2][2] = "fdC line3\n";
	i = 0;
	while (i < 3)
	{
		line = get_next_line(fds[0]);
		if (!line || strcmp(line, expect[0][i]) != 0)
			return (1);
		free(line);
		line = get_next_line(fds[1]);
		if (!line || strcmp(line, expect[1][i]) != 0)
			return (1);
		free(line);
		line = get_next_line(fds[2]);
		if (!line || strcmp(line, expect[2][i]) != 0)
			return (1);
		free(line);
		i++;
	}
	close(fds[0]);
	close(fds[1]);
	close(fds[2]);
	return (0);
}
EOF

# ===== カスタマイズここまで (drivers) =====

# ----- テスト本体 ------------------------------------------------

test_cat_diff_all_fixtures() {
	local bs="$1"
	local bin="$WORK_DIR/cat_bs$bs"

	if ! compile_test "$WORK_DIR/driver_cat.c" "$bin" "$bs"; then
		fail "BUFFER_SIZE=$bs: コンパイル失敗 (詳細: $WORK_DIR/cc.log または make.log)"
		return
	fi
	local f
	for f in $FIXTURE_FILES; do
		local out="$WORK_DIR/out_${f}_bs$bs"
		"$bin" "$FIXTURES_DIR/$f" >"$out" 2>"$WORK_DIR/run.log"
		if diff -q "$FIXTURES_DIR/$f" "$out" >/dev/null 2>&1; then
			pass "BUFFER_SIZE=$bs, $f: 全行を過不足なく復元できた"
		else
			fail "BUFFER_SIZE=$bs, $f: 出力が元ファイルと一致しない"
		fi
	done
}

test_stdin() {
	local bs="$1"
	local bin="$WORK_DIR/cat_bs$bs"
	local input="line one\nline two\nlast (no newline)"
	local out="$WORK_DIR/stdin_out_bs$bs"

	if [ ! -x "$bin" ]; then
		skip "BUFFER_SIZE=$bs, 標準入力: cat_bs$bs が無いためスキップ"
		return
	fi
	printf "%b" "$input" | "$bin" >"$out" 2>"$WORK_DIR/run.log"
	if [ "$(printf "%b" "$input")" = "$(cat "$out")" ]; then
		pass "BUFFER_SIZE=$bs: 標準入力からの読み込みが正しい"
	else
		fail "BUFFER_SIZE=$bs: 標準入力からの読み込みが不正"
	fi
}

test_one_line_per_call() {
	local bs="$1"
	local bin="$WORK_DIR/one_call_bs$bs"

	if ! compile_test "$WORK_DIR/driver_one_call.c" "$bin" "$bs"; then
		fail "BUFFER_SIZE=$bs: 1回1行チェック用バイナリのコンパイル失敗"
		return
	fi
	if "$bin" "$FIXTURES_DIR/test6_long_lines.txt"; then
		pass "BUFFER_SIZE=$bs: 1回の呼び出しで1行しか返していない"
	else
		fail "BUFFER_SIZE=$bs: 1回の呼び出しで複数行、または改行の位置が不正"
	fi
}

test_invalid_fd() {
	local bin="$WORK_DIR/invalid_fd"
	if [ ! -x "$bin" ]; then
		if ! compile_test "$WORK_DIR/driver_invalid_fd.c" "$bin" 42; then
			fail "不正なfdチェック用バイナリのコンパイル失敗"
			return
		fi
	fi
	if "$bin"; then
		pass "不正なfd(-1, close済み)でNULLを返す"
	else
		fail "不正なfd(-1, close済み)でNULLを返していない"
	fi
}

test_devnull() {
	local bin="$WORK_DIR/devnull"
	if [ ! -x "$bin" ]; then
		if ! compile_test "$WORK_DIR/driver_devnull.c" "$bin" 42; then
			fail "/dev/null読み込みチェック用バイナリのコンパイル失敗"
			return
		fi
	fi
	if "$bin"; then
		pass "空(/dev/null)から最初の呼び出しでNULLを返す"
	else
		fail "空(/dev/null)から最初の呼び出しでNULLを返していない"
	fi
}

test_helpers() {
	local bin="$WORK_DIR/helpers"
	if ! compile_test "$WORK_DIR/driver_helpers.c" "$bin" 42; then
		skip "ヘルパー関数ユニットテスト: コンパイル失敗のためスキップ (関数名が変更された可能性)"
		return
	fi
	if "$bin" 2>"$WORK_DIR/helpers.log"; then
		pass "ヘルパー関数 (ft_strlen/ft_strchr_gnl/ft_strjoin_n/extract_line/update_leftover) の単体動作"
	else
		fail "ヘルパー関数の単体動作に問題あり (詳細: $WORK_DIR/helpers.log)"
	fi
}

test_norminette() {
	if ! command -v norminette >/dev/null 2>&1; then
		skip "Norminette: コマンドが見つからないためスキップ"
		return
	fi
	if norminette "$PROJ_DIR"/get_next_line.c "$PROJ_DIR"/get_next_line_utils.c \
		"$PROJ_DIR"/get_next_line.h >"$WORK_DIR/norm.log" 2>&1; then
		pass "Norminette OK"
	else
		fail "Norminette エラーあり (詳細: $WORK_DIR/norm.log)"
	fi
}

test_memleak() {
	local bs="$1"
	local bin="$WORK_DIR/cat_bs$bs"
	if [ ! -x "$bin" ]; then
		skip "BUFFER_SIZE=$bs: メモリリークチェック用バイナリが無いためスキップ"
		return
	fi
	memcheck "$bin" "$FIXTURES_DIR/test6_long_lines.txt"
	local ret=$?
	if [ "$ret" -eq 0 ]; then
		pass "BUFFER_SIZE=$bs: メモリリーク無し"
	elif [ "$ret" -eq 2 ]; then
		skip "BUFFER_SIZE=$bs: valgrind/leaks が無いためスキップ"
	else
		fail "BUFFER_SIZE=$bs: メモリリークあり (詳細: $WORK_DIR/valgrind.log または leaks.log)"
	fi
}

test_bonus_static_var_count() {
	if [ "$HAS_BONUS" -ne 1 ]; then
		skip "bonus: get_next_line_bonus.[ch] / get_next_line_utils_bonus.c が未提出のためスキップ"
		return
	fi
	local count
	count=$(grep -c '^\s*static' "$PROJ_DIR/get_next_line_bonus.c")
	if [ "$count" -eq 1 ]; then
		pass "bonus: 静的変数の宣言が1個だけ"
	else
		fail "bonus: 静的変数の宣言が${count}個 (1個である必要がある)"
	fi
}

test_bonus_multi_fd() {
	if [ "$HAS_BONUS" -ne 1 ]; then
		skip "bonus: get_next_line_bonus.[ch] / get_next_line_utils_bonus.c が未提出のためスキップ"
		return
	fi
	local a="$WORK_DIR/fdA.txt"
	local b="$WORK_DIR/fdB.txt"
	local c="$WORK_DIR/fdC.txt"
	printf "fdA line1\nfdA line2\nfdA line3\n" >"$a"
	printf "fdB line1\nfdB line2\nfdB line3\n" >"$b"
	printf "fdC line1\nfdC line2\nfdC line3\n" >"$c"
	local bin="$WORK_DIR/bonus_multi"
	if ! compile_test_bonus "$WORK_DIR/driver_bonus_multi.c" "$bin" 42; then
		fail "bonus: 複数fdテスト用バイナリのコンパイル失敗 (詳細: $WORK_DIR/cc_bonus.log)"
		return
	fi
	if "$bin" "$a" "$b" "$c"; then
		pass "bonus: fd 3,4,5 を交互に読んでも状態を見失わない"
	else
		fail "bonus: 複数fdの読み込み状態管理に問題あり"
	fi
}

# ----- 実行 --------------------------------------------------

echo "get_next_line テスト開始"
echo "対象ディレクトリ: $PROJ_DIR"
if [ "$HAS_MAKEFILE" -eq 1 ]; then
	echo "ビルド方式: Makefile あり (make → get_next_line.a をリンク)"
else
	echo "ビルド方式: Makefile なし (cc 直接コンパイル)"
fi

section "必須パート: get_next_line() の動作確認 (BUFFER_SIZE違い)"
for bs in $BUFFER_SIZES; do
	echo "--- BUFFER_SIZE=$bs ---"
	test_cat_diff_all_fixtures "$bs"
	test_stdin "$bs"
	test_one_line_per_call "$bs"
done

section "必須パート: 特殊なfd"
test_invalid_fd
test_devnull

section "必須パート: ヘルパー関数の単体テスト"
test_helpers

section "必須パート: Norminette"
test_norminette

section "必須パート: メモリリークチェック"
for bs in $BUFFER_SIZES; do
	test_memleak "$bs"
done

if [ "$BONUS" = "1" ]; then
	section "ボーナスパート: 静的変数1個 / 複数fd同時読み込み"
	test_bonus_static_var_count
	test_bonus_multi_fd
else
	echo
	echo "(ボーナステストをスキップしました。実行するには BONUS=1 を指定してください)"
fi

echo
echo "========================================"
echo " 結果: PASS=$PASS  FAIL=$FAIL  SKIP=$SKIP"
echo "========================================"

[ "$FAIL" -eq 0 ]
