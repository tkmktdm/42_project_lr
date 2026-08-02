/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujikaw <tfujikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 18:32:59 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/05/01 19:20:50 by tfujikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total;
	size_t	s1_len;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	total = s1_len + ft_strlen(s2);
	str = malloc(total + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, s1_len + 1);
	ft_strlcat(str, s2, total + 1);
	return (str);
}
/*
#include <stdio.h>

int main()
{
	char	*str;

	str = ft_strjoin("Hello ", "world");
	printf("%s\n", str);
	return 0;
}
*/
