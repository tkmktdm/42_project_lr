#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);

static void	check(const char *label, int ok)
{
	printf("[%s] %s\n", ok ? "OK" : "NG", label);
}

int	main(void)
{
	t_list	*node;
	int		n;

	node = ft_lstnew("hello");
	check("string content", node && strcmp((char *)node->content, "hello") == 0);
	check("next is NULL", node && node->next == NULL);
	free(node);

	node = ft_lstnew(NULL);
	check("NULL content", node && node->content == NULL);
	check("NULL content next: NULL", node && node->next == NULL);
	free(node);

	n = 42;
	node = ft_lstnew(&n);
	check("int pointer content", node && *(int *)node->content == 42);
	free(node);

	return (0);
}
