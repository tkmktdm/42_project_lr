/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujikaw <tfujikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 21:35:31 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/05/08 14:13:55 by tfujikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	s_len;

	s_len = ft_strlen(s);
	while (s_len > 0 && s[s_len] != (unsigned char)c)
		s_len--;
	if (s[s_len] == (unsigned char)c)
		return ((char *)&s[s_len]);
	return ((void *)0);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*real;
	char	*self;

	self = ft_strrchr("Hello", 0);
	real = strrchr("Hello", 0);
	printf("%s\n",real);
	printf("%s\n",self);
	return (0);
}
*/
