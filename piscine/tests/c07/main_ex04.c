#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*ft_convert_base(char *nbr, char *base_from, char *base_to);

int	main(int argc, char **argv)
{
	char	*result;

	if (argc < 2)
		return (1);
	if (strcmp(argv[1], "dec2hex") == 0)
	{
		result = ft_convert_base("15", "0123456789", "0123456789ABCDEF");
		printf("%s", result ? result : "NULL");
		free(result);
	}
	else if (strcmp(argv[1], "bin2dec") == 0)
	{
		result = ft_convert_base("110", "01", "0123456789");
		printf("%s", result ? result : "NULL");
		free(result);
	}
	else if (strcmp(argv[1], "neg") == 0)
	{
		result = ft_convert_base("-15", "0123456789", "0123456789ABCDEF");
		printf("%s", result ? result : "NULL");
		free(result);
	}
	else if (strcmp(argv[1], "signs") == 0)
	{
		result = ft_convert_base("++--15", "0123456789", "0123456789ABCDEF");
		printf("%s", result ? result : "NULL");
		free(result);
	}
	else if (strcmp(argv[1], "zero") == 0)
	{
		result = ft_convert_base("0", "0123456789", "0123456789ABCDEF");
		printf("%s", result ? result : "NULL");
		free(result);
	}
	else if (strcmp(argv[1], "invalid") == 0)
	{
		result = ft_convert_base("15", "0+23456789", "0123456789ABCDEF");
		printf("%s", result ? result : "NULL");
		free(result);
	}
	return (0);
}
