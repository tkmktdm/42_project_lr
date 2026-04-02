/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazonode <kazonode@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 22:45:18 by kazonode          #+#    #+#             */
/*   Updated: 2026/03/29 17:55:53 by kazonode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

extern int	*g_grid;
extern int	*g_hints;
extern int	g_size;

void	cleanup(void)
{
	free(g_grid);
	free(g_hints);
}
