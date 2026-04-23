#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	*ft_range(int min, int max);

int	main(int argc, char **argv)
{
	int	*arr;
	int	i;

	if (argc < 2)
		return (1);
	if (strcmp(argv[1], "basic") == 0)
	{
		arr = ft_range(3, 9);
		i = 0;
		while (i < 6)
		{
			if (i > 0)
				printf(" ");
			printf("%d", arr[i]);
			i++;
		}
		free(arr);
	}
	else if (strcmp(argv[1], "null") == 0)
	{
		arr = ft_range(3, 3);
		if (arr == NULL)
			printf("NULL");
		else
		{
			printf("NOT_NULL");
			free(arr);
		}
	}
	else if (strcmp(argv[1], "null2") == 0)
	{
		arr = ft_range(5, 3);
		if (arr == NULL)
			printf("NULL");
		else
		{
			printf("NOT_NULL");
			free(arr);
		}
	}
	else if (strcmp(argv[1], "neg") == 0)
	{
		arr = ft_range(-3, 3);
		i = 0;
		while (i < 6)
		{
			if (i > 0)
				printf(" ");
			printf("%d", arr[i]);
			i++;
		}
		free(arr);
	}
	return (0);
}
