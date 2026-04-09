#include <unistd.h>

void	ft_putnbr_base(int nbr, char *base);

int	main(void)
{
	ft_putnbr_base(42, "0123456789");
	write(1, "\n", 1);
	ft_putnbr_base(0, "0123456789");
	write(1, "\n", 1);
	ft_putnbr_base(-42, "0123456789");
	write(1, "\n", 1);
	ft_putnbr_base(255, "0123456789ABCDEF");
	write(1, "\n", 1);
	ft_putnbr_base(8, "01");
	write(1, "\n", 1);
	ft_putnbr_base(100, "poneyvif");
	write(1, "\n", 1);
	ft_putnbr_base(2147483647, "0123456789");
	write(1, "\n", 1);
	ft_putnbr_base(-2147483648, "0123456789");
	write(1, "\n", 1);
	ft_putnbr_base(42, "+0");
	write(1, "|\n", 2);
	ft_putnbr_base(42, "0");
	write(1, "|\n", 2);
	ft_putnbr_base(42, "001");
	write(1, "|\n", 2);
	ft_putnbr_base(42, "-0123");
	write(1, "|\n", 2);
	return (0);
}
