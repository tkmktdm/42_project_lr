#include <stdio.h>
#include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstclear(t_list **lst, void (*del)(void *));

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
	t_list	*lst;

	lst = ft_lstnew("a");
	lst->next = ft_lstnew("b");
	lst->next->next = ft_lstnew("c");

	ft_lstclear(&lst, del_noop);
	check("after clear: lst is NULL", lst == NULL);

	ft_lstclear(NULL, del_noop);
	printf("[OK] lstclear NULL: no crash\n");

	ft_lstclear(&lst, del_noop);
	printf("[OK] lstclear already NULL: no crash\n");

	return (0);
}
