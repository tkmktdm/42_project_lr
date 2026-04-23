#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	ft_ultimate_range(int **range, int min, int max);

int	main(int argc, char **argv)
{
	int	*arr;
	int	size;
	int	i;

	if (argc < 2)
		return (1);
	arr = NULL;
	if (strcmp(argv[1], "basic") == 0)
	{
		size = ft_ultimate_range(&arr, 3, 9);
		printf("%d", size);
		i = 0;
		while (i < size)
		{
			printf(" %d", arr[i]);
			i++;
		}
		free(arr);
	}
	else if (strcmp(argv[1], "null") == 0)
	{
		size = ft_ultimate_range(&arr, 3, 3);
		printf("%d", size);
		if (arr == NULL)
			printf(" NULL");
		else
		{
			printf(" NOT_NULL");
			free(arr);
		}
	}
	return (0);
}
