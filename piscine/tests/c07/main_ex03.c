#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*ft_strjoin(int size, char **strs, char *sep);

int	main(int argc, char **argv)
{
	char	*result;
	char	*strs2[] = {"hello", "world"};
	char	*strs1[] = {"hello"};
	char	*strs0[] = {};

	if (argc < 2)
		return (1);
	if (strcmp(argv[1], "basic") == 0)
	{
		result = ft_strjoin(2, strs2, "!!");
		printf("%s", result);
		free(result);
	}
	else if (strcmp(argv[1], "zero") == 0)
	{
		result = ft_strjoin(0, strs0, "!!");
		printf("%s", result);
		free(result);
	}
	else if (strcmp(argv[1], "one") == 0)
	{
		result = ft_strjoin(1, strs1, "!!");
		printf("%s", result);
		free(result);
	}
	else if (strcmp(argv[1], "nosep") == 0)
	{
		result = ft_strjoin(2, strs2, "");
		printf("%s", result);
		free(result);
	}
	return (0);
}
