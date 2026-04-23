#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*ft_strdup(char *src);

int	main(int argc, char **argv)
{
	char	*src;
	char	*dest;

	if (argc < 2)
		return (1);
	if (strcmp(argv[1], "basic") == 0)
	{
		src = "hello";
		dest = ft_strdup(src);
		printf("%s", dest);
		free(dest);
	}
	else if (strcmp(argv[1], "addr") == 0)
	{
		src = "hello";
		dest = ft_strdup(src);
		if ((void *)src != (void *)dest)
			printf("different");
		else
			printf("same");
		free(dest);
	}
	else if (strcmp(argv[1], "empty") == 0)
	{
		src = "";
		dest = ft_strdup(src);
		printf("%s", dest);
		free(dest);
	}
	return (0);
}
