#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char		**ft_split(char *str, char *charset);

static void	print_result(char **res)
{
	int	i;

	i = 0;
	while (res[i] != NULL)
	{
		if (i > 0)
			printf("|");
		printf("%s", res[i]);
		free(res[i]);
		i++;
	}
	free(res);
}

int	main(int argc, char **argv)
{
	char	**result;
	int		i;

	if (argc < 2)
		return (1);
	if (strcmp(argv[1], "basic") == 0)
	{
		result = ft_split("hello,world,foo", ",");
		print_result(result);
	}
	else if (strcmp(argv[1], "multi") == 0)
	{
		result = ft_split("hello,,world", ",");
		print_result(result);
	}
	else if (strcmp(argv[1], "trim") == 0)
	{
		result = ft_split(",hello,world,", ",");
		print_result(result);
	}
	else if (strcmp(argv[1], "null_end") == 0)
	{
		result = ft_split("hello", ",");
		i = 0;
		while (result[i] != NULL)
		{
			free(result[i]);
			i++;
		}
		printf("NULL");
		free(result);
	}
	return (0);
}
