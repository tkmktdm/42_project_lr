/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 11:52:05 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/02 20:15:12 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	int		i;
	int		j;
	int		strs_size;
	int		sep_size;
	char	*dest;

	i = 0;
	strs_size = 0;
	sep_size = 0;
	if (size == 0)
		return ("");
	while (i < size)
	{
		printf("%s\n", strs[i]);
		strs_size += ft_strlen(strs[i]);
		i++;
	}
	sep_size = ft_strlen(sep);
	printf("%d\n", strs_size);
	dest = malloc(sizeof(char) * strs_size * (size * sep_size) + 1);
	i = 0;
	while (i < size)
	{
		j = 0;
		dest[i] = *strs[i];
		while (sep[j] == '\0')
		{
			dest[i] += sep[j];
			j++;
		}
		i++;
	}
	return (dest);
}

int	main(void)
{
	char	*strs[2];
	char	*sep;
	char	*result;
	int		size;

	strs[0] = "hello";
	strs[1] = "world";
	sep = "!";
	size = 2;
	result = ft_strjoin(size, strs, sep);
	printf("%s\n", result);
	free(result);
	return (0);
}
