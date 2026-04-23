/* allowed functions: write */
#include <unistd.h>

static int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

int	main(int argc, char **argv)
{
	int		i;
	int		j;
	int		new_word;
	char	c;

	i = 1;
	while (i < argc)
	{
		j = 0;
		new_word = 1;
		while (argv[i][j])
		{
			c = argv[i][j];
			if (is_space(c))
				new_word = 1;
			else
			{
				if (new_word && c >= 'a' && c <= 'z')
					c = c - 'a' + 'A';
				new_word = 0;
			}
			write(1, &c, 1);
			j++;
		}
		if (i + 1 < argc)
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
	return (0);
}
