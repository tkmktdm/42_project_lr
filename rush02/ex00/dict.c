/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 11:39:48 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/04 17:52:32 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"
#include <fcntl.h>  // open
#include <unistd.h> // read, close

int		ft_strlen(char *str);

char	*trim(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] == ' ' && str[i] != '\0')
		i++;
	j = ft_strlen(str) - 1;
	while (str[j] == ' ' && str[j] != '\0')
		j--;
	str[j + 1] = '\0';
	return (str + i);
}

int	parse_line(char *line, t_entry *entry)
{
	int	point;

	while (point)
}

// int	load_dict(path)

// sample
// int	dist(void)
// {
// 	int		fd;
// 	char	buf[100];
// 	ssize_t	bytesRead;

// 	fd = open("example.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	bytesRead = read(fd, buf, sizeof(buf) - 1);
// 	if (bytesRead == -1)
// 	{
// 		perror("Error reading file");
// 		close(fd);
// 		return (1);
// 	}
// 	buf[bytesRead] = '\0';
// 	printf("Read %zd bytes: %s\n", bytesRead, buf);
// 	// 3. close: ファイルを閉じる
// 	if (close(fd) == -1)
// 	{
// 		perror("Error closing file");
// 		return (1);
// 	}
// 	return (0);
// }
