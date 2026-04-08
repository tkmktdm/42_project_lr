/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 20:46:27 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/08 20:46:28 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_map
{
	char	**grid;
	int		rows;
	int		cols;
	char	empty;
	char	obst;
	char	full;
}			t_map;

int		ft_strlen(char *s);
char	*ft_strdup_n(char *s, int n);
void	free_split(char **lines);
void	free_map(t_map *map);
char	**split_content(char *s);
char	*read_fd(int fd);
t_map	*parse_map(char *content);
void	mark_square(t_map *map, int size, int mr, int mc);
void	solve_bsq(t_map *map);
void	print_map(t_map *map);

#endif
