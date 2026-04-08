/* allowed functions: write */

#include <unistd.h>

static void	put_nbr(int n)
{
	char	buf[16];
	int		i;

	i = 0;
	if (n == 0)
	{
		write(1, "0", 1);
		return ;
	}
	while (n > 0)
	{
		buf[i++] = '0' + (n % 10);
		n /= 10;
	}
	while (i--)
		write(1, &buf[i], 1);
}

int	main(void)
{
	int	i;

	i = 1;
	while (i <= 100)
	{
		if (i % 3 == 0 && i % 5 == 0)
			write(1, "fizzbuzz", 8);
		else if (i % 3 == 0)
			write(1, "fizz", 4);
		else if (i % 5 == 0)
			write(1, "buzz", 4);
		else
			put_nbr(i);
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
