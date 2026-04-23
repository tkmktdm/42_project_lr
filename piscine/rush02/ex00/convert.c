/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 13:17:21 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/05 20:44:30 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"
#include <stdlib.h>

static int	top_group_idx(char (*groups)[4], int i)
{
	int	k;

	k = -1;
	while (groups[i][++k] == '0')
		;
	while (i > 0 && !groups[i][k])
	{
		i--;
		k = -1;
		while (groups[i][++k] == '0')
			;
	}
	return (i);
}

int	convert_hundreds(char *group, int len, t_dict *dict, int unit_idx)
{
	if (len == 3 && group[0] != '0')
		if (print_hundreds(group, dict))
			return (1);
	if (len >= 2)
	{
		if (convert_tens(&group[len - 2], dict))
			return (1);
	}
	else if (group[0] != '0')
	{
		if (convert_ones(group, dict))
			return (1);
	}
	return (print_unit(dict, unit_idx));
}

static int	convert_groups(char (*groups)[4], int i, t_dict *dict)
{
	int	k;

	while (i-- > 0)
	{
		k = -1;
		while (groups[i][++k] == '0')
			;
		if (groups[i][k])
		{
			ft_putstr(" ");
			if (convert_hundreds(groups[i], ft_strlen(groups[i]), dict, i))
				return (1);
		}
	}
	return (0);
}

static int	handle_zero(t_dict *dict)
{
	char	*zero;

	zero = dict_lookup(dict, "0");
	if (!zero)
		return (1);
	ft_putstr(zero);
	ft_putstr("\n");
	return (0);
}

int	convert(char *num_str, t_dict *dict)
{
	char	(*groups)[4];
	int		i;

	if (is_zero(num_str))
		return (handle_zero(dict));
	groups = malloc((ft_strlen(num_str) / 3 + 1) * sizeof(*groups));
	if (!groups)
		return (1);
	i = top_group_idx(groups, split_groups(num_str, groups) - 1);
	if (validate_units(groups, i, dict)
		|| convert_hundreds(groups[i], ft_strlen(groups[i]), dict, i)
		|| convert_groups(groups, i, dict))
	{
		free(groups);
		return (1);
	}
	free(groups);
	ft_putstr("\n");
	return (0);
}
