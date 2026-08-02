/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujikaw <tfujikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 23:41:35 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/05/07 17:58:24 by tfujikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != (unsigned char)c)
		i++;
	if (s[i] == (unsigned char)c)
		return ((char *)&s[i]);
	return ((void *)0);
}

/*
#include <stdio.h>
#include <string.h>

int main()
{
	char	*self;
	char	*real;

	self = ft_strchr("Hello", 'o');
	real = strchr("Hello", 'o');
	printf("%s\n", self);
	printf("%s\n", real);
	return 0;
}
*/
