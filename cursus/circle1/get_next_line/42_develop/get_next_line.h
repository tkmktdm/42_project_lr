/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 16:17:10 by htakumi           #+#    #+#             */
/*   Updated: 2026/07/08 20:07:54 by htakumi          ###   ########.fr       */
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
char		*extract_line(char *leftover);
char		*update_leftover(char *leftover);
char		*grow_buf(char *left, char *buf, int bytes, t_leftover *info);
size_t		ft_strlen(const char *s);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif

#endif
