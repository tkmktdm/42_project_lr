/* allowed functions: write */
#include <unistd.h>

static int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	main(int argc, char **argv)
{
	int	i;
	int	len;

	if (argc == 2)
	{
		len = ft_strlen(argv[1]);
		i = 0;
		while (i < len / 2)
		{
			if (argv[1][i] != argv[1][len - 1 - i])
			{
				write(1, "\n", 1);
				return (0);
			}
			i++;
		}
		write(1, argv[1], len);
	}
	write(1, "\n", 1);
	return (0);
}
