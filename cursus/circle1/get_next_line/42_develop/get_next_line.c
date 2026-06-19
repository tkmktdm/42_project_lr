/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 19:52:31 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/06/16 00:02:14 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

static char	*fill_leftover(int fd, char *leftover)
{
	char	*buf;
	int		byte_num;
	char	*tmp;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	byte_num = 0;
	while (buf && (leftover == NULL || ft_strchr_gnl(leftover, '\n') == NULL))
	{
		byte_num = read(fd, buf, BUFFER_SIZE);
		if (byte_num <= 0)
			break ;
		buf[byte_num] = '\0';
		tmp = leftover;
		leftover = ft_strjoin(leftover, buf);
		free(tmp);
	}
	free(buf);
	if (!buf || byte_num == -1)
	{
		free(leftover);
		return (NULL);
	}
	return (leftover);
}

char	*get_next_line(int fd)
{
	static char	*leftover = NULL;
	char		*line;
	char		*new_g_leftover;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	leftover = fill_leftover(fd, leftover);
	if (leftover == NULL || leftover[0] == '\0')
	{
		free(leftover);
		leftover = NULL;
		return (NULL);
	}
	line = extract_line(leftover);
	if (!line)
	{
		free(leftover);
		leftover = NULL;
		return (NULL);
	}
	new_g_leftover = update_leftover(leftover);
	free(leftover);
	leftover = new_g_leftover;
	return (line);
}
