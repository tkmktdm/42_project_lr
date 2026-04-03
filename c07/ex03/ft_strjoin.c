/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 11:52:05 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/03 11:01:46 by htakumi          ###   ########.fr       */
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

char	*ft_strcpy(char *dest, char *src)
{
	char	*temp;

	temp = dest;
	while (*src)
	{
		*temp = *src;
		temp++;
		src++;
	}
	*temp = '\0';
	return (dest);
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	int		i;
	int		len;
	char	*dest;
	char	*ptr;

	i = -1;
	len = (size > 0) * ft_strlen(sep) * (size - 1);
	while (++i < size)
		len += ft_strlen(strs[i]);
	dest = malloc(len + 1);
	dest[0] = '\0';
	ptr = dest;
	i = -1;
	while (++i < size)
	{
		ft_strcpy(ptr, strs[i]);
		ptr += ft_strlen(strs[i]);
		if (i < size - 1)
		{
			ft_strcpy(ptr, sep);
			ptr += ft_strlen(sep);
		}
	}
	return (dest);
}

int	main(void)
{
	char	*args[2] = {"hello", "world"};
	char	*sep;
	char	*str;
	int		size;

	sep = "!!";
	size = 2;
	str = ft_strjoin(size, args, sep);
	printf("ft_strjoin: %s\n", str);
	free(str);
	return (0);
}
