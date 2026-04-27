#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size);

static void	check(const char *label, int ok)
{
	printf("[%s] %s\n", ok ? "OK" : "NG", label);
}

int	main(void)
{
	unsigned char	*p;
	size_t			i;
	int				all_zero;

	/* 1. 通常確保 → 全バイトが 0 */
	p = ft_calloc(5, sizeof(int));
	check("alloc not null", p != NULL);
	all_zero = 1;
	i = 0;
	while (i < 5 * sizeof(int))
	{
		if (p[i] != 0)
			all_zero = 0;
		i++;
	}
	check("all bytes zero", all_zero);
	free(p);

	/* 2. 1要素確保 */
	p = ft_calloc(1, 1);
	check("1 byte alloc", p != NULL && p[0] == 0);
	free(p);

	/* 3. count = 0 → free できるポインタ（クラッシュしない） */
	p = ft_calloc(0, sizeof(int));
	free(p);
	check("count=0 no crash", 1);

	/* 4. size = 0 → free できるポインタ（クラッシュしない） */
	p = ft_calloc(5, 0);
	free(p);
	check("size=0 no crash", 1);

	/* 5. 大きめの確保 */
	p = ft_calloc(100, sizeof(long));
	check("large alloc not null", p != NULL);
	all_zero = 1;
	i = 0;
	while (i < 100 * sizeof(long))
	{
		if (p[i] != 0)
			all_zero = 0;
		i++;
	}
	check("large alloc all zero", all_zero);
	free(p);

	/* 6. malloc 失敗時は NULL を返す（size_t 最大値で試みる） */
	p = ft_calloc(1, (size_t)-1);
	check("huge alloc returns null", p == NULL);

	return (0);
}
