/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujikaw <tfujikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 09:01:55 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/05/12 14:49:45 by tfujikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
char	strmapi_f(unsigned int i, char c)
{
	if (((i == 0) || (i % 2 == 0)) && (c >= 'a' && c <= 'z'))
		return (c - 32);
	return (c);
}

#include <stdio.h>

int main()
{
	char	*str = "thankyou";
	char	*ans;
	ans = ft_strmapi(str, strmapi_f);
	printf("%s\n", ans);
	return 0;
}
*/
