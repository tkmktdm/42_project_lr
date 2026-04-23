/* allowed functions: write */
#include <unistd.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

void	ft_putstr(char *str)
{
	int	len;

	len = 0;
	len = ft_strlen(str);
	write(1, str, len);
}
