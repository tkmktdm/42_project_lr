#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstdelone(t_list *lst, void (*del)(void *));

static void	check(const char *label, int ok)
{
	printf("[%s] %s\n", ok ? "OK" : "NG", label);
}

static void	del_noop(void *content)
{
	(void)content;
}

int	main(void)
{
	t_list	*a;
	t_list	*b;

	a = ft_lstnew("a");
	b = ft_lstnew("b");
	a->next = b;

	ft_lstdelone(a, del_noop);
	check("next node not freed: still accessible",
		strcmp((char *)b->content, "b") == 0);

	free(b);
	printf("[OK] lstdelone: no crash\n");
	return (0);
}
