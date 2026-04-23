/* allowed functions: malloc */
#include <stdlib.h>

int	*ft_range(int start, int end)
{
	int	*arr;
	int	len;
	int	i;
	int	step;

	if (start <= end)
	{
		len = end - start + 1;
		step = 1;
	}
	else
	{
		len = start - end + 1;
		step = -1;
	}
	arr = (int *)malloc(sizeof(int) * len);
	if (!arr)
		return (0);
	i = 0;
	while (i < len)
	{
		arr[i] = start + i * step;
		i++;
	}
	return (arr);
}
