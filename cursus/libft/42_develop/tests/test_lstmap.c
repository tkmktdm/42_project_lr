#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));

static void	check(const char *label, int ok)
{
	printf("[%s] %s\n", ok ? "OK" : "NG", label);
}

static void	*dup_upper(void *content)
{
	char	*s;
	char	*res;
	int		i;

	s = (char *)content;
	res = malloc(strlen(s) + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (s[i])
	{
		res[i] = (char)toupper((unsigned char)s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}

static void	del_free(void *content)
{
	free(content);
}

static void	del_noop(void *content)
{
	(void)content;
}

int	main(void)
{
	t_list	*lst;
	t_list	*mapped;

	lst = ft_lstnew("hello");
	lst->next = ft_lstnew("world");

	mapped = ft_lstmap(lst, dup_upper, del_free);
	check("mapped: not NULL", mapped != NULL);
	check("mapped[0]: HELLO",
		mapped && strcmp((char *)mapped->content, "HELLO") == 0);
	check("mapped[1]: WORLD",
		mapped && mapped->next
		&& strcmp((char *)mapped->next->content, "WORLD") == 0);
	check("mapped[2]: NULL",
		mapped && mapped->next && mapped->next->next == NULL);
	check("original[0] unchanged",
		strcmp((char *)lst->content, "hello") == 0);

	ft_lstclear(&mapped, del_free);
	ft_lstclear(&lst, del_noop);

	check("NULL input: NULL", ft_lstmap(NULL, dup_upper, del_free) == NULL);

	return (0);
}
