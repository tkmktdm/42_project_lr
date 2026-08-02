/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujikaw <tfujikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 19:23:23 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/05/12 23:04:34 by tfujikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	start;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	len = ft_strlen(s1);
	while (len > start && ft_strchr(set, s1[len - 1]))
		len--;
	str = ft_substr(s1, start, len - start);
	return (str);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*str;

	str = ft_strtrim("abcHelloab, worldcb", "abc");
	printf("%s\n", str);
	free(str);
	return (0);
}
*/
