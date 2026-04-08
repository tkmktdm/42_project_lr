/* allowed functions: write */

#include <unistd.h>

void	ft_putnbr(int nb)
{
	char			c;
	unsigned int	n;

	if (nb < 0)
	{
		write(1, "-", 1);
		n = (unsigned int)(-(nb + 1)) + 1;
	}
	else
		n = (unsigned int)nb;
	if (n >= 10)
		ft_putnbr((int)(n / 10));
	c = '0' + (n % 10);
	write(1, &c, 1);
}
