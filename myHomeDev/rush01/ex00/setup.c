/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazonode <kazonode@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 17:29:43 by kazonode          #+#    #+#             */
/*   Updated: 2026/03/29 18:07:19 by kazonode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

extern int	*g_grid;
extern int	*g_hints;
extern int	g_size;

int		*parse_hints(char *s, int *count);
int		validate_input(int count);
void	init_grid(void);
int		prefill_grid(void);
int		validate_hints(void);

int	setup_puzzle(char *input)
{
	int	count;

	g_hints = parse_hints(input, &count);
	g_size = validate_input(count);
	if (!g_hints || !g_size || !validate_hints())
	{
		free(g_hints);
		return (0);
	}
	g_grid = malloc(sizeof(int) * g_size * g_size);
	if (!g_grid)
	{
		free(g_hints);
		return (0);
	}
	init_grid();
	if (!prefill_grid())
	{
		free(g_grid);
		free(g_hints);
		return (0);
	}
	return (1);
}
