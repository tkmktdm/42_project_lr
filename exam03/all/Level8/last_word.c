/* allowed functions: write */
#include <unistd.h>

static int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

int	main(int argc, char **argv)
{
	int	i;
	int	end;
	int	start;

	if (argc == 2)
	{
		i = 0;
		while (argv[1][i])
			i++;
		i--;
		while (i >= 0 && is_space(argv[1][i]))
			i--;
		end = i;
		while (i >= 0 && !is_space(argv[1][i]))
			i--;
		start = i + 1;
		if (end >= start)
			write(1, &argv[1][start], end - start + 1);
	}
	write(1, "\n", 1);
	return (0);
}
