/* allowed functions: write */
#include <unistd.h>

int	main(int argc, char **argv)
{
	char	seen[256];
	int		i;
	int		j;
	unsigned char	c;

	i = 0;
	while (i < 256)
		seen[i++] = 0;
	if (argc == 3)
	{
		i = 0;
		while (argv[1][i])
		{
			c = (unsigned char)argv[1][i];
			if (!seen[c])
			{
				j = 0;
				while (argv[2][j] && argv[2][j] != argv[1][i])
					j++;
				if (argv[2][j] == argv[1][i])
				{
					write(1, &argv[1][i], 1);
					seen[c] = 1;
				}
			}
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
