/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_sub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 16:30:00 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/05 20:57:16 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

int	is_zero(char *str)
{
	while (*str == '0')
		str++;
	return (*str == '\0');
}

int	convert_ones(char *group, t_dict *dict)
{
	char	*word;

	if (group[0] == '0')
		return (0);
	word = dict_lookup(dict, group);
	if (!word)
		return (1);
	ft_putstr(word);
	return (0);
}

int	convert_tens(char *group, t_dict *dict)
{
	char	list[3];
	char	*word;

	if (group[0] == '1')
		return (convert_ones(group, dict));
	if (group[0] != '0')
	{
		list[0] = group[0];
		list[1] = '0';
		list[2] = '\0';
		word = dict_lookup(dict, list);
		if (!word)
			return (1);
		ft_putstr(word);
		if (group[1] != '0')
		{
			ft_putstr(" ");
			return (convert_ones(&group[1], dict));
		}
		return (0);
	}
	return (convert_ones(&group[1], dict));
}

int	print_hundreds(char *group, t_dict *dict)
{
	char	list[2];
	char	*word;
	char	*hundred;

	list[0] = group[0];
	list[1] = '\0';
	word = dict_lookup(dict, list);
	hundred = dict_lookup(dict, "100");
	if (!word || !hundred)
		return (1);
	ft_putstr(word);
	ft_putstr(" ");
	ft_putstr(hundred);
	if (group[1] != '0' || group[2] != '0')
		ft_putstr(" ");
	return (0);
}

int	validate_units(char (*groups)[4], int top, t_dict *dict)
{
	int	i;
	int	k;

	i = top;
	while (i >= 0)
	{
		k = -1;
		while (groups[i][++k] == '0')
			;
		if (groups[i][k] && !unit_exists(dict, i))
			return (1);
		i--;
	}
	return (0);
}
