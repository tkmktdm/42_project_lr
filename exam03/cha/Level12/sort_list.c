/* allowed functions: none */
#include "ft_list.h"

/*
** Bubble sort using cmp. cmp returns non-zero when (a, b) are in the right
** order. The shared header defines data as void *, so we treat it as int via
** (long) cast (entries are integer-tagged pointers in tests).
*/

t_list	*sort_list(t_list *lst, int (*cmp)(int, int))
{
	t_list	*cur;
	int		swapped;
	void	*tmp;

	if (!lst || !cmp)
		return (lst);
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		cur = lst;
		while (cur && cur->next)
		{
			if (!cmp((int)(long)cur->data, (int)(long)cur->next->data))
			{
				tmp = cur->data;
				cur->data = cur->next->data;
				cur->next->data = tmp;
				swapped = 1;
			}
			cur = cur->next;
		}
	}
	return (lst);
}
