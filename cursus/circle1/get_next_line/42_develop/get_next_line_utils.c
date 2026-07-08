/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 19:52:31 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/07/06 14:25:39 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strcount(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	return (i);
}

char	*ft_strchr_gnl(char *s, int c)
{
	while (*s != '\0')
	{
		if ((unsigned char)*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

char	*extract_line(char *leftover)
{
	char	*line;
	int		i;
	int		len;

	i = 0;
	len = ft_strcount(leftover);
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	while (leftover[i] != '\n' && leftover[i] != '\0')
	{
		line[i] = leftover[i];
		i++;
	}
	line[i] = leftover[i];
	if (leftover[i] == '\n')
		line[i + 1] = '\0';
	return (line);
}

char	*update_leftover(char *leftover)
{
	char	*p;
	char	*right;
	int		len;
	int		i;

	i = 0;
	p = ft_strchr_gnl(leftover, '\n');
	if (p == NULL)
		return (NULL);
	p++;
	len = ft_strlen(p);
	if (len == 0)
		return (NULL);
	right = malloc(sizeof(char) * (len + 1));
	if (!right)
		return (NULL);
	while (p[i] != '\0')
	{
		right[i] = p[i];
		i++;
	}
	right[i] = '\0';
	return (right);
}

char	*grow_buf(char *left, char *buf, int bytes, t_leftover *info)
{
	size_t	i;
	size_t	new_capacity;
	char	*new_left;

	new_capacity = (info->len + (size_t)bytes) * 2;
	new_left = malloc(new_capacity);
	if (!new_left)
	{
		free(left);
		info->len = 0;
		info->capacity = 0;
		return (NULL);
	}
	i = -1;
	while (++i != info->len)
		new_left[i] = left[i];
	free(left);
	i = -1;
	while (++i != (size_t)bytes)
		new_left[info->len + i] = buf[i];
	new_left[info->len + i] = '\0';
	info->len += (size_t)bytes;
	info->capacity = new_capacity;
	return (new_left);
}
