#include <stdio.h>
#include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);

static void	check(const char *label, int ok)
{
	printf("[%s] %s\n", ok ? "OK" : "NG", label);
}

int	main(void)
{
	t_list	*a;
	t_list	*b;
	t_list	*c;

	check("NULL: 0", ft_lstsize(NULL) == 0);

	a = ft_lstnew("a");
	check("1 node: 1", ft_lstsize(a) == 1);

	b = ft_lstnew("b");
	c = ft_lstnew("c");
	a->next = b;
	b->next = c;
	check("3 nodes: 3", ft_lstsize(a) == 3);

	free(c);
	free(b);
	free(a);
	return (0);
}
