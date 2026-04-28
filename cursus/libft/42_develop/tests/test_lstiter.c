#include <stdio.h>
#include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));

static void	check(const char *label, int ok)
{
	printf("[%s] %s\n", ok ? "OK" : "NG", label);
}

static int	g_count = 0;

static void	count_nodes(void *content)
{
	(void)content;
	g_count++;
}

static void	del_noop(void *content)
{
	(void)content;
}

int	main(void)
{
	t_list	*lst;

	lst = ft_lstnew("a");
	lst->next = ft_lstnew("b");
	lst->next->next = ft_lstnew("c");

	ft_lstiter(lst, count_nodes);
	check("iter 3 nodes: called 3 times", g_count == 3);

	ft_lstiter(NULL, count_nodes);
	printf("[OK] lstiter NULL: no crash\n");

	ft_lstclear(&lst, del_noop);
	return (0);
}
