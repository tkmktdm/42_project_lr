/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 19:52:31 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/06/10 00:01:16 by htakumi          ###   ########.fr       */
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

// 1. leftoverに\nがあるか探す
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

// 2. leftoverから\nまでを切り出す（返す用）
char	*extract_line(char *leftover)
{
	char	*line;
	int		i;
	int		len;

	i = 0;
	len = ft_strcount(leftover);
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (0);
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

// 3. \nより後ろだけ残す（次回用）
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
	len = ft_strcount(p);
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
