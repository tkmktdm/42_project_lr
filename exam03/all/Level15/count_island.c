/* allowed functions: open, close, read, write, malloc, free */
#include "count_island.h"

#define BUF_INIT 4096

static void	put_nl(void)
{
	write(1, "\n", 1);
}

/*
** Reads the whole file into a malloc'd buffer (NUL-terminated). Returns NULL
** on error. *out_len receives the byte count (excluding the trailing NUL).
*/
static char	*slurp(int fd, int *out_len)
{
	char	*buf;
	char	*tmp;
	int		cap;
	int		len;
	int		n;
	int		i;

	cap = BUF_INIT;
	len = 0;
	buf = (char *)malloc(cap);
	if (!buf)
		return (NULL);
	while (1)
	{
		if (len + 1 >= cap)
		{
			cap *= 2;
			tmp = (char *)malloc(cap);
			if (!tmp)
			{
				free(buf);
				return (NULL);
			}
			i = 0;
			while (i < len)
			{
				tmp[i] = buf[i];
				i++;
			}
			free(buf);
			buf = tmp;
		}
		n = read(fd, buf + len, cap - len - 1);
		if (n < 0)
		{
			free(buf);
			return (NULL);
		}
		if (n == 0)
			break ;
		len += n;
	}
	buf[len] = '\0';
	*out_len = len;
	return (buf);
}

/*
** Parse the buffer into a grid. Returns a malloc'd char* of size rows*cols
** (no separators). Sets *rows and *cols. Returns NULL on incoherent input
** (lines of differing length, or non '.'/'X' chars).
*/
static char	*parse_grid(char *buf, int len, int *rows, int *cols)
{
	int		r;
	int		c;
	int		line_start;
	int		i;
	int		expected;
	char	*grid;
	int		gi;

	r = 0;
	expected = -1;
	i = 0;
	line_start = 0;
	while (i < len)
	{
		if (buf[i] == '\n')
		{
			c = i - line_start;
			if (expected == -1)
				expected = c;
			else if (c != expected)
				return (NULL);
			r++;
			line_start = i + 1;
		}
		else if (buf[i] != '.' && buf[i] != 'X')
			return (NULL);
		i++;
	}
	/* Trailing line without newline. */
	if (line_start < len)
	{
		c = len - line_start;
		if (expected == -1)
			expected = c;
		else if (c != expected)
			return (NULL);
		r++;
	}
	if (r == 0 || expected <= 0)
		return (NULL);
	*rows = r;
	*cols = expected;
	grid = (char *)malloc(sizeof(char) * (r * expected));
	if (!grid)
		return (NULL);
	gi = 0;
	i = 0;
	while (i < len)
	{
		if (buf[i] != '\n')
			grid[gi++] = buf[i];
		i++;
	}
	return (grid);
}

/*
** Iterative flood fill using a malloc'd stack of cell indices.
*/
static int	flood(char *grid, int rows, int cols, int sr, int sc, char id)
{
	int	*stack;
	int	top;
	int	cap;
	int	idx;
	int	r;
	int	c;
	int	*tmp;
	int	i;

	cap = 64;
	stack = (int *)malloc(sizeof(int) * cap);
	if (!stack)
		return (-1);
	top = 0;
	stack[top++] = sr * cols + sc;
	grid[sr * cols + sc] = id;
	while (top > 0)
	{
		idx = stack[--top];
		r = idx / cols;
		c = idx % cols;
		int dr[4] = {-1, 1, 0, 0};
		int dc[4] = {0, 0, -1, 1};
		int k = 0;
		while (k < 4)
		{
			int nr = r + dr[k];
			int nc = c + dc[k];
			if (nr >= 0 && nr < rows && nc >= 0 && nc < cols
				&& grid[nr * cols + nc] == 'X')
			{
				grid[nr * cols + nc] = id;
				if (top >= cap)
				{
					cap *= 2;
					tmp = (int *)malloc(sizeof(int) * cap);
					if (!tmp)
					{
						free(stack);
						return (-1);
					}
					i = 0;
					while (i < top)
					{
						tmp[i] = stack[i];
						i++;
					}
					free(stack);
					stack = tmp;
				}
				stack[top++] = nr * cols + nc;
			}
			k++;
		}
	}
	free(stack);
	return (0);
}

static int	label_islands(char *grid, int rows, int cols)
{
	int		r;
	int		c;
	int		next_id;

	next_id = 0;
	r = 0;
	while (r < rows)
	{
		c = 0;
		while (c < cols)
		{
			if (grid[r * cols + c] == 'X')
			{
				if (next_id > 9)
					return (-1);
				if (flood(grid, rows, cols, r, c, '0' + next_id) < 0)
					return (-1);
				next_id++;
			}
			c++;
		}
		r++;
	}
	return (0);
}

static int	emit(char *grid, int rows, int cols, int has_trail_nl)
{
	int	r;

	r = 0;
	while (r < rows)
	{
		write(1, grid + r * cols, cols);
		if (r < rows - 1 || has_trail_nl)
			write(1, "\n", 1);
		r++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int		fd;
	char	*buf;
	int		len;
	char	*grid;
	int		rows;
	int		cols;
	int		has_nl;

	if (argc != 2)
	{
		put_nl();
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		put_nl();
		return (0);
	}
	buf = slurp(fd, &len);
	close(fd);
	if (!buf || len == 0)
	{
		if (buf)
			free(buf);
		put_nl();
		return (0);
	}
	has_nl = (buf[len - 1] == '\n');
	grid = parse_grid(buf, len, &rows, &cols);
	free(buf);
	if (!grid)
	{
		put_nl();
		return (0);
	}
	if (label_islands(grid, rows, cols) < 0)
	{
		free(grid);
		put_nl();
		return (0);
	}
	emit(grid, rows, cols, has_nl);
	free(grid);
	return (0);
}
