/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs_to_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:41:40 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/07 20:43:29 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stock_str.h"
// #include <stdio.h>
#include <stdlib.h>

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static char	*ft_strdup(char *src)
{
	char	*p;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(src);
	p = malloc(sizeof(char) * (len + 1));
	if (p == NULL)
		return (NULL);
	while (src[i] != '\0')
	{
		p[i] = src[i];
		i++;
	}
	p[len] = '\0';
	return (p);
}

static int	ft_fill_tab(struct s_stock_str *tab, int ac, char **av)
{
	int	i;

	i = 0;
	while (i < ac)
	{
		tab[i].size = ft_strlen(av[i]);
		tab[i].str = av[i];
		tab[i].copy = ft_strdup(av[i]);
		if (!tab[i].copy)
			return (0);
		i++;
	}
	tab[ac].str = 0;
	return (1);
}

struct s_stock_str	*ft_strs_to_tab(int ac, char **av)
{
	struct s_stock_str	*tab;

	tab = malloc(sizeof(struct s_stock_str) * (ac + 1));
	if (!tab)
		return (NULL);
	if (!ft_fill_tab(tab, ac, av))
		return (NULL);
	return (tab);
}

// int	main(int argc, char **argv)
// {
// 	struct s_stock_str	*tab;
// 	int					i;

// 	tab = ft_strs_to_tab(argc, argv);
// 	if (!tab)
// 		return (1);
// 	i = 0;
// 	while (tab[i].str)
// 	{
// 		printf("%s (len=%d)\n", tab[i].str, tab[i].size);
// 		i++;
// 	}
// 	return (0);
// }
