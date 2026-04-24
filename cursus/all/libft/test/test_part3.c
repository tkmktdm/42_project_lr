#include "test_helpers.h"
#include "libft.h"
#include <stdlib.h>
#include <string.h>

static int	g_iter_count;
static int	g_del_calls;

static void	count_cb(void *c)
{
	(void)c;
	g_iter_count++;
}

static void	del_record(void *c)
{
	(void)c;
	g_del_calls++;
}

static void	*f_strdup_wrap(void *c)
{
	return ((void *)strdup((char *)c));
}

static void	test_ft_lstnew(void)
{
	char	content[] = "x";
	t_list	*n;

	n = ft_lstnew(content);
	ASSERT_NOT_NULL("lstnew non-null", n);
	ASSERT_EQ_PTR("lstnew content", n->content, content);
	ASSERT_NULL("lstnew next", n->next);
	free(n);
}

static void	test_ft_lstadd_front(void)
{
	t_list	*lst;
	t_list	*a;
	t_list	*b;

	lst = NULL;
	a = ft_lstnew("a");
	ft_lstadd_front(&lst, a);
	ASSERT_EQ_PTR("add_front empty", lst, a);
	ASSERT_NULL("add_front empty next", lst->next);
	b = ft_lstnew("b");
	ft_lstadd_front(&lst, b);
	ASSERT_EQ_PTR("add_front head", lst, b);
	ASSERT_EQ_PTR("add_front new->next", lst->next, a);
	free(a);
	free(b);
}

static void	free_list_no_content(t_list *lst)
{
	t_list	*next;

	while (lst)
	{
		next = lst->next;
		free(lst);
		lst = next;
	}
}

static void	test_ft_lstsize(void)
{
	t_list	*lst;

	ASSERT_EQ_INT("lstsize empty", ft_lstsize(NULL), 0);
	lst = ft_lstnew("a");
	ASSERT_EQ_INT("lstsize 1", ft_lstsize(lst), 1);
	ft_lstadd_front(&lst, ft_lstnew("b"));
	ft_lstadd_front(&lst, ft_lstnew("c"));
	ASSERT_EQ_INT("lstsize 3", ft_lstsize(lst), 3);
	free_list_no_content(lst);
}

static void	test_ft_lstlast(void)
{
	t_list	*a;
	t_list	*b;
	t_list	*c;

	ASSERT_NULL("lstlast NULL", ft_lstlast(NULL));
	a = ft_lstnew("a");
	ASSERT_EQ_PTR("lstlast single", ft_lstlast(a), a);
	b = ft_lstnew("b");
	c = ft_lstnew("c");
	a->next = b;
	b->next = c;
	ASSERT_EQ_PTR("lstlast tail", ft_lstlast(a), c);
	free(a);
	free(b);
	free(c);
}

static void	test_ft_lstadd_back(void)
{
	t_list	*lst;
	t_list	*b;
	t_list	*c;

	lst = NULL;
	ft_lstadd_back(&lst, ft_lstnew("a"));
	ASSERT_EQ_INT("add_back empty size", ft_lstsize(lst), 1);
	b = ft_lstnew("b");
	ft_lstadd_back(&lst, b);
	ASSERT_EQ_INT("add_back size 2", ft_lstsize(lst), 2);
	c = ft_lstnew("c");
	ft_lstadd_back(&lst, c);
	ASSERT_EQ_INT("add_back size 3", ft_lstsize(lst), 3);
	ASSERT_EQ_PTR("add_back last", ft_lstlast(lst), c);
	free_list_no_content(lst);
}

static void	test_ft_lstdelone(void)
{
	t_list	*a;
	t_list	*b;

	g_del_calls = 0;
	a = ft_lstnew("a");
	b = ft_lstnew("b");
	a->next = b;
	ft_lstdelone(a, del_record);
	ASSERT_EQ_INT("lstdelone del called once", g_del_calls, 1);
	ASSERT_NOT_NULL("lstdelone next alive", b);
	ASSERT_EQ_STR("lstdelone next content", (char *)b->content, "b");
	free(b);
}

static void	test_ft_lstclear(void)
{
	t_list	*lst;

	g_del_calls = 0;
	lst = ft_lstnew(strdup("a"));
	ft_lstadd_back(&lst, ft_lstnew(strdup("b")));
	ft_lstadd_back(&lst, ft_lstnew(strdup("c")));
	ft_lstclear(&lst, free);
	ASSERT_NULL("lstclear sets NULL", lst);
	ft_lstclear(&lst, free);
	ASSERT_NULL("lstclear idempotent", lst);
}

static void	test_ft_lstiter(void)
{
	t_list	*lst;

	g_iter_count = 0;
	lst = ft_lstnew("a");
	ft_lstadd_back(&lst, ft_lstnew("b"));
	ft_lstadd_back(&lst, ft_lstnew("c"));
	ft_lstiter(lst, count_cb);
	ASSERT_EQ_INT("lstiter count", g_iter_count, 3);
	free_list_no_content(lst);
	g_iter_count = 0;
	ft_lstiter(NULL, count_cb);
	ASSERT_EQ_INT("lstiter NULL list", g_iter_count, 0);
}

static void	test_ft_lstmap(void)
{
	t_list	*lst;
	t_list	*mapped;
	t_list	*cur;
	t_list	*m;

	lst = ft_lstnew(strdup("a"));
	ft_lstadd_back(&lst, ft_lstnew(strdup("b")));
	ft_lstadd_back(&lst, ft_lstnew(strdup("c")));
	mapped = ft_lstmap(lst, f_strdup_wrap, free);
	ASSERT_NOT_NULL("lstmap result", mapped);
	ASSERT_EQ_INT("lstmap size", ft_lstsize(mapped), 3);
	cur = lst;
	m = mapped;
	while (cur && m)
	{
		ASSERT_EQ_STR("lstmap content eq",
			(char *)m->content, (char *)cur->content);
		ASSERT_TRUE("lstmap content distinct ptr",
			m->content != cur->content);
		cur = cur->next;
		m = m->next;
	}
	ft_lstclear(&lst, free);
	ft_lstclear(&mapped, free);
	ASSERT_NULL("lstmap lst cleared", lst);
	ASSERT_NULL("lstmap mapped cleared", mapped);
}

void	run_part3_tests(void)
{
	test_ft_lstnew();
	test_ft_lstadd_front();
	test_ft_lstsize();
	test_ft_lstlast();
	test_ft_lstadd_back();
	test_ft_lstdelone();
	test_ft_lstclear();
	test_ft_lstiter();
	test_ft_lstmap();
}
