#include <stdio.h>
#include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);

static void	check(const char *label, int ok)
{
	printf("[%s] %s\n", ok ? "OK" : "NG", label);
}

int	main(void)
{
	t_list	*a;
	t_list	*b;
	t_list	*c;

	check("NULL: NULL", ft_lstlast(NULL) == NULL);

	a = ft_lstnew("a");
	check("1 node: itself", ft_lstlast(a) == a);

	b = ft_lstnew("b");
	c = ft_lstnew("c");
	a->next = b;
	b->next = c;
	check("3 nodes: last is c", ft_lstlast(a) == c);
	check("last->next is NULL", ft_lstlast(a)->next == NULL);

	free(c);
	free(b);
	free(a);
	return (0);
}
