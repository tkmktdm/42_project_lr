/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 19:52:31 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/06/14 15:42:33 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*g_leftover = NULL;

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*get_next_line(int fd)
{
	int		byte_num;
	char	buf[BUFFER_SIZE + 1];
	char	*line;
	char	*new_g_leftover;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (g_leftover == NULL || ft_strchr_gnl(g_leftover, '\n') == NULL)
	{
		byte_num = read(fd, buf, BUFFER_SIZE);
		if (byte_num == -1)
			return (NULL);
		if (byte_num == 0)
			break ;
		buf[byte_num] = '\0';
		g_leftover = ft_strjoin(g_leftover, buf);
	}
	if (g_leftover == NULL || g_leftover[0] == '\0')
		return (NULL);
	line = extract_line(g_leftover);
	new_g_leftover = update_leftover(g_leftover);
	free(g_leftover);
	g_leftover = new_g_leftover;
	return (line);
}
