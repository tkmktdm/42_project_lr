/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 16:17:10 by htakumi           #+#    #+#             */
/*   Updated: 2026/07/25 13:25:20 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_leftover
{
	size_t	len;
	size_t	capacity;
}			t_leftover;

char		*get_next_line(int fd);

char		*ft_strchr_gnl(char *s, int c);
char		*fill_leftover(int fd, char *leftover);
char		*extract_line(char *leftover);
char		*update_leftover(char *leftover);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif

#endif
