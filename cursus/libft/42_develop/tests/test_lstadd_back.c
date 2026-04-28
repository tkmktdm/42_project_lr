#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);

static void	check(const char *label, int ok)
{
	printf("[%s] %s\n", ok ? "OK" : "NG", label);
}

int	main(void)
{
	t_list	*lst;
	t_list	*node1;
	t_list	*node2;
	t_list	*node3;

	lst = NULL;
	node1 = ft_lstnew("hello");
	ft_lstadd_back(&lst, node1);
	check("add to empty: head set", lst == node1);
	check("add to empty: next NULL", lst->next == NULL);

	node2 = ft_lstnew("world");
	ft_lstadd_back(&lst, node2);
	check("add back: head unchanged", lst == node1);
	check("add back: last is new", lst->next == node2);
	check("last content: world", strcmp((char *)lst->next->content, "world") == 0);

	node3 = ft_lstnew("!");
	ft_lstadd_back(&lst, node3);
	check("3rd add back: last->next is new", lst->next->next == node3);

	free(node1);
	free(node2);
	free(node3);
	return (0);
}
