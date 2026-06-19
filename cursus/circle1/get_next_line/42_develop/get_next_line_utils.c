/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 19:52:31 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/06/16 00:01:29 by htakumi          ###   ########.fr       */
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	l1;
	size_t	l2;
	size_t	i;
	char	*r;

	if (!s2)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	r = (char *)malloc(l1 + l2 + 1);
	if (!r)
		return (NULL);
	i = 0;
	while (i < l1)
	{
		r[i] = s1[i];
		i++;
	}
	while (i < l1 + l2)
	{
		r[i] = s2[i - l1];
		i++;
	}
	r[i] = '\0';
	return (r);
}
