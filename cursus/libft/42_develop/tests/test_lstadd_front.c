#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);

static void	check(const char *label, int ok)
{
	printf("[%s] %s\n", ok ? "OK" : "NG", label);
}

int	main(void)
{
	t_list	*lst;
	t_list	*node1;
	t_list	*node2;

	lst = NULL;
	node1 = ft_lstnew("world");
	ft_lstadd_front(&lst, node1);
	check("add to empty: head set", lst == node1);
	check("add to empty: next NULL", lst->next == NULL);

	node2 = ft_lstnew("hello");
	ft_lstadd_front(&lst, node2);
	check("add front: new head", lst == node2);
	check("add front: old head is next", lst->next == node1);
	check("content: hello", strcmp((char *)lst->content, "hello") == 0);
	check("next content: world", strcmp((char *)lst->next->content, "world") == 0);

	free(node1);
	free(node2);
	return (0);
}
