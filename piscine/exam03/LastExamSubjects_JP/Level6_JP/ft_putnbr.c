#include <unistd.h>
void	ft_putnbr(int nb)
{
	long	n;
	char	c;

	n = nb;
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n == 0)
	{
		write(1, "0", 1);
	}
	if (n > 9)
	{
		ft_putnbr(n / 10);
	}
	else
	{
		c = n % 10 + '0';
		write(1, c, 1);
	}
}

int	main(void)
{
	ft_putnbr(1000);
	return 0;
}
