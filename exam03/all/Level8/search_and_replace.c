/* allowed functions: write, exit */
#include <unistd.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int		i;
	char	c;

	if (argc != 4 || argv[2][0] == '\0' || argv[2][1] != '\0'
		|| argv[3][0] == '\0' || argv[3][1] != '\0')
	{
		write(1, "\n", 1);
		return (0);
	}
	i = 0;
	while (argv[1][i])
	{
		if (argv[1][i] == argv[2][0])
			c = argv[3][0];
		else
			c = argv[1][i];
		write(1, &c, 1);
		i++;
	}
	write(1, "\n", 1);
	return (0);
}
