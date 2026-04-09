/* allowed functions: write */
#include <unistd.h>

int	main(int argc, char **argv)
{
	char			seen[256];
	int				a;
	int				i;
	unsigned char	c;

	i = 0;
	while (i < 256)
		seen[i++] = 0;
	if (argc == 3)
	{
		a = 1;
		while (a <= 2)
		{
			i = 0;
			while (argv[a][i])
			{
				c = (unsigned char)argv[a][i];
				if (!seen[c])
				{
					write(1, &argv[a][i], 1);
					seen[c] = 1;
				}
				i++;
			}
			a++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
