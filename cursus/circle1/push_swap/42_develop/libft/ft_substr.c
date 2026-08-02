/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujikaw <tfujikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 07:44:10 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/05/01 18:51:43 by tfujikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	total_s_len;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len <= start)
		return (ft_strdup(""));
	total_s_len = s_len - start;
	if (len < total_s_len)
	{
		str = malloc(len + 1);
		if (!str)
			return (NULL);
		ft_strlcpy(str, &s[start], len + 1);
	}
	else
	{
		str = malloc(total_s_len + 1);
		if (!str)
			return (NULL);
		ft_strlcpy(str, &s[start], total_s_len + 1);
	}
	return (str);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*cpy;
	char	*str;

	str = "Hello world";
	cpy = ft_substr(str, 3, 6);
	printf("%s\n", cpy);
	free(cpy);
	return (0);
}
*/
