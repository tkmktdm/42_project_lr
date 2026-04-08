/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 20:46:15 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/08 21:01:28 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

static int	parse_header(char *line, t_map *map)
{
	int	i;

	i = 0;
	map->rows = 0;
	while (line[i] >= '0' && line[i] <= '9')
	{
		map->rows = map->rows * 10 + (line[i] - '0');
		i++;
	}
	if (i == 0 || map->rows <= 0)
		return (-1);
	if (!line[i] || !line[i + 1] || !line[i + 2] || line[i + 3])
		return (-1);
	map->empty = line[i];
	map->obst = line[i + 1];
	map->full = line[i + 2];
	if (map->empty == map->obst || map->empty == map->full)
		return (-1);
	if (map->obst == map->full)
		return (-1);
	if ((unsigned char)map->empty <= 32 || (unsigned char)map->obst <= 32)
		return (-1);
	if ((unsigned char)map->full <= 32)
		return (-1);
	return (0);
}

static int	validate_row(char *row, t_map *map)
{
	int	i;

	i = 0;
	while (row[i])
	{
		if (row[i] != map->empty && row[i] != map->obst)
			return (-1);
		i++;
	}
	if (i != map->cols)
		return (-1);
	return (0);
}

static int	set_grid(t_map *map, char **lines, int n_lines)
{
	int	i;

	if (n_lines != map->rows + 1 || ft_strlen(lines[1]) == 0)
		return (-1);
	map->cols = ft_strlen(lines[1]);
	map->grid = malloc(sizeof(char *) * (map->rows + 1));
	if (!map->grid)
		return (-1);
	i = 0;
	while (i <= map->rows)
		map->grid[i++] = NULL;
	i = 0;
	while (i < map->rows)
	{
		if (validate_row(lines[i + 1], map) == -1)
			return (-1);
		map->grid[i] = ft_strdup_n(lines[i + 1], map->cols);
		if (!map->grid[i])
			return (-1);
		i++;
	}
	return (0);
}

t_map	*parse_map(char *content)
{
	t_map	*map;
	char	**lines;
	int		n;

	if (!content)
		return (NULL);
	lines = split_content(content);
	if (!lines || !lines[0] || !lines[1])
		return (free_split(lines), NULL);
	map = malloc(sizeof(t_map));
	if (!map)
		return (free_split(lines), NULL);
	map->grid = NULL;
	if (parse_header(lines[0], map) == -1)
		return (free_split(lines), free(map), NULL);
	n = 0;
	while (lines[n])
		n++;
	if (set_grid(map, lines, n) == -1)
		return (free_split(lines), free_map(map), NULL);
	free_split(lines);
	return (map);
}
