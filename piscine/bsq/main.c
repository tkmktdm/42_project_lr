/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 20:44:26 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/08 21:01:24 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

static void	process_content(char *content)
{
	t_map	*map;

	map = parse_map(content);
	if (!map)
	{
		write(1, "map error\n", 10);
		return ;
	}
	solve_bsq(map);
	print_map(map);
	free_map(map);
}

static void	process_file(char *path, int is_first)
{
	int		fd;
	char	*content;

	if (!is_first)
		write(1, "\n", 1);
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		write(1, "map error\n", 10);
		return ;
	}
	content = read_fd(fd);
	close(fd);
	process_content(content);
	free(content);
}

int	main(int argc, char **argv)
{
	char	*content;
	int		i;

	if (argc == 1)
	{
		content = read_fd(0);
		process_content(content);
		free(content);
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		process_file(argv[i], i == 1);
		i++;
	}
	return (0);
}
