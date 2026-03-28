#include <unistd.h>

#define SIZE 4

/*
** ヒントの並び順:
**   clues[0][0..SIZE-1] : 上から見たヒント (左→右)
**   clues[1][0..SIZE-1] : 右から見たヒント (上→下)
**   clues[2][0..SIZE-1] : 下から見たヒント (左→右)
**   clues[3][0..SIZE-1] : 左から見たヒント (上→下)
*/

static int	g_grid[SIZE][SIZE];
static int	g_clues[4][SIZE];

/* ---- 出力 ---- */

static void	put_char(char c)
{
	write(1, &c, 1);
}

static void	put_number(int n)
{
	put_char('0' + n);
}

static void	print_grid(void)
{
	int	row;
	int	col;

	row = 0;
	while (row < SIZE)
	{
		col = 0;
		while (col < SIZE)
		{
			put_number(g_grid[row][col]);
			if (col < SIZE - 1)
				put_char(' ');
			col++;
		}
		put_char('\n');
		row++;
	}
}

/* ---- 制約チェック ---- */

/*
** line[0..SIZE-1] を先頭方向から見たときに見えるビルの数を返す
*/
static int	count_visible(int line[SIZE])
{
	int	visible;
	int	max_h;
	int	i;

	visible = 0;
	max_h = 0;
	i = 0;
	while (i < SIZE)
	{
		if (line[i] > max_h)
		{
			max_h = line[i];
			visible++;
		}
		i++;
	}
	return (visible);
}

/*
** pos番目のマスを置いた後、その行/列が完成したかチェックし、
** 完成していればヒントと照合する。
** 部分列でも「絶対に満たせない」ケースを早期検出する。
** 問題なければ 1 を返す。
*/
static int	check_row(int row)
{
	int	line[SIZE];
	int	rev[SIZE];
	int	col;

	col = 0;
	while (col < SIZE)
	{
		line[col] = g_grid[row][col];
		rev[col] = g_grid[row][SIZE - 1 - col];
		col++;
	}
	/* 左から */
	if (g_clues[3][row] && count_visible(line) != g_clues[3][row])
		return (0);
	/* 右から */
	if (g_clues[1][row] && count_visible(rev) != g_clues[1][row])
		return (0);
	return (1);
}

static int	check_col(int col)
{
	int	line[SIZE];
	int	rev[SIZE];
	int	row;

	row = 0;
	while (row < SIZE)
	{
		line[row] = g_grid[row][col];
		rev[row] = g_grid[SIZE - 1 - row][col];
		row++;
	}
	/* 上から */
	if (g_clues[0][col] && count_visible(line) != g_clues[0][col])
		return (0);
	/* 下から */
	if (g_clues[2][col] && count_visible(rev) != g_clues[2][col])
		return (0);
	return (1);
}

/* ---- 重複チェック ---- */

static int	is_valid_placement(int row, int col, int num)
{
	int	i;

	i = 0;
	while (i < col)
	{
		if (g_grid[row][i] == num)
			return (0);
		i++;
	}
	i = 0;
	while (i < row)
	{
		if (g_grid[i][col] == num)
			return (0);
		i++;
	}
	return (1);
}

/* ---- バックトラッキング ---- */

static int	solve(int pos)
{
	int	row;
	int	col;
	int	num;

	if (pos == SIZE * SIZE)
		return (1);
	row = pos / SIZE;
	col = pos % SIZE;
	num = 1;
	while (num <= SIZE)
	{
		if (is_valid_placement(row, col, num))
		{
			g_grid[row][col] = num;
			/* 行が完成したらヒントチェック */
			if (col == SIZE - 1 && !check_row(row))
			{
				g_grid[row][col] = 0;
				num++;
				continue ;
			}
			/* 列が完成したらヒントチェック */
			if (row == SIZE - 1 && !check_col(col))
			{
				g_grid[row][col] = 0;
				num++;
				continue ;
			}
			if (solve(pos + 1))
				return (1);
			g_grid[row][col] = 0;
		}
		num++;
	}
	return (0);
}

/* ---- 入力パース ---- */

static int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

/*
** 文字列 s から SIZE*4 個の数値を読み取り g_clues に格納する。
** 並び順: 上0..SIZE-1, 右0..SIZE-1, 下0..SIZE-1, 左0..SIZE-1
** エラー時は 0 を返す。
*/
static int	parse_clues(char *s)
{
	int	dir;
	int	i;
	int	num;

	dir = 0;
	while (dir < 4)
	{
		i = 0;
		while (i < SIZE)
		{
			while (*s && is_space(*s))
				s++;
			if (*s < '0' || *s > '9')
				return (0);
			num = 0;
			while (*s >= '0' && *s <= '9')
			{
				num = num * 10 + (*s - '0');
				s++;
			}
			if (num < 0 || num > SIZE)
				return (0);
			g_clues[dir][i] = num;
			i++;
		}
		dir++;
	}
	return (1);
}

/* ---- エントリーポイント ---- */

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (!parse_clues(argv[1]))
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (!solve(0))
	{
		write(2, "Error\n", 6);
		return (1);
	}
	print_grid();
	return (0);
}
