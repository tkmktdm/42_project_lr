/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 12:35:17 by htakumi           #+#    #+#             */
/*   Updated: 2026/07/19 12:35:17 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "push_swap.h"
#include <stdlib.h>

static int	stack_append(t_swap **head, t_swap **tail, int num)
{
	t_swap	*node;

	node = malloc(sizeof(t_swap));
	if (!node)
		return (0);
	node->num = num;
	node->rank = 0;
	node->next = NULL;
	node->pre = *tail;
	if (*tail != NULL)
		(*tail)->next = node;
	if (*head == NULL)
		*head = node;
	*tail = node;
	return (1);
}

t_swap	*stack_init(char *str)
{
	char	**p_start;
	char	**p;
	t_swap	*head;
	t_swap	*tail;

	p_start = ft_split(str, ' ');
	if (p_start == NULL)
		return (NULL);
	p = p_start;
	head = NULL;
	tail = NULL;
	while (*p != NULL)
	{
		if (!stack_append(&head, &tail, ft_atoi(*p)))
			return (NULL);
		free(*p);
		p++;
	}
	free(p_start);
	return (head);
}

void	stack_free(t_swap *stack)
{
	t_swap	*tmp;

	while (stack != NULL)
	{
		tmp = stack->next;
		free(stack);
		stack = tmp;
	}
}
