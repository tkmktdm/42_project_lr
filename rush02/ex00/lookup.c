/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/05 20:10:38 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"
#include <stdlib.h>

char	*dict_lookup(t_dict *dict, char *key)
{
	int	i;
	int	j;

	i = 0;
	while (i < dict->size)
	{
		j = 0;
		while (dict->entries[i].key[j] == key[j] && key[j] != '\0')
			j++;
		if (dict->entries[i].key[j] == key[j])
			return (dict->entries[i].value);
		i++;
	}
	return (NULL);
}

int	unit_exists(t_dict *dict, int idx)
{
	char	*unit_key;
	int		k;
	int		result;

	if (idx == 0)
		return (1);
	unit_key = malloc(idx * 3 + 2);
	if (!unit_key)
		return (0);
	unit_key[0] = '1';
	k = 0;
	while (k++ < idx * 3)
		unit_key[k] = '0';
	unit_key[k] = '\0';
	result = (dict_lookup(dict, unit_key) != NULL);
	free(unit_key);
	return (result);
}

int	print_unit(t_dict *dict, int idx)
{
	char	*unit_key;
	char	*unit;
	int		k;

	if (idx == 0)
		return (0);
	unit_key = malloc(idx * 3 + 2);
	if (!unit_key)
		return (1);
	unit_key[0] = '1';
	k = 0;
	while (k++ < idx * 3)
		unit_key[k] = '0';
	unit_key[k] = '\0';
	unit = dict_lookup(dict, unit_key);
	free(unit_key);
	if (!unit)
		return (1);
	ft_putstr(" ");
	ft_putstr(unit);
	return (0);
}
