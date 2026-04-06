/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkariya <kkariya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 11:39:48 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/05 19:54:17 by kkariya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "rush.h"

int		ft_strlen(char *str);
char	**ft_split(char *str, char *charset);
int		get_count(char *str, char *charset);

char	*trim(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0' && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (str + i);
	j = ft_strlen(str) - 1;
	while (j >= 0 && str[j] == ' ')
		j--;
	str[j + 1] = '\0';
	return (str + i);
}

static int	parse_line(char *line, t_entry *entry)
{
	int	colonp;

	colonp = 0;
	while (line[colonp] != ':' && line[colonp] != '\0')
		colonp++;
	if (line[colonp] == '\0')
		return (0);
	line[colonp] = '\0';
	entry->key = trim(line);
	entry->value = trim(line + colonp + 1);
	if (entry->key[0] == '\0' || entry->value[0] == '\0')
		return (0);
	return (1);
}

static int	read_file(char *path, char *buf)
{
	int		fd;
	ssize_t	bytes;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	bytes = read(fd, buf, 65535);
	close(fd);
	if (bytes == -1)
		return (0);
	buf[bytes] = '\0';
	return (1);
}

t_dict	*load_dict(char *path)
{
	t_dict	*dict;
	char	buf[65536];
	int		i;

	if (!read_file(path, buf))
		return (NULL);
	dict = malloc(sizeof(t_dict));
	if (!dict)
		return (NULL);
	dict->lines = ft_split(buf, "\n");
	dict->entries = malloc(sizeof(t_entry) * get_count(buf, "\n"));
	if (!dict->lines || !dict->entries)
		return (free_dict(dict), NULL);
	dict->size = get_count(buf, "\n");
	i = 0;
	while (dict->lines[i] != NULL)
	{
		if (!parse_line(dict->lines[i], &dict->entries[i]))
			return (free_dict(dict), NULL);
		i++;
	}
	return (dict);
}

void	free_dict(t_dict *dict)
{
	int	i;

	if (!dict)
		return ;
	i = 0;
	if (dict->lines)
	{
		while (dict->lines[i] != NULL)
		{
			free(dict->lines[i]);
			i++;
		}
		free(dict->lines);
	}
	free(dict->entries);
	free(dict);
}
