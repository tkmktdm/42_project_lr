/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujikaw <tfujikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 18:20:33 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/05/04 10:11:27 by tfujikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*
void	striteri_f(unsigned int i, char *str)
{
	if (i % 2 == 0)
		*str = 'A';
}

#include <stdlib.h>
#include "libft.h"
#include <stdio.h>

int	main(void)
{
	char	*str;

	str = ft_strjoin("Hello ", "world");
	ft_striteri(str, &striteri_f);
	printf("%s\n", str);
	free(str);
	return (0);
}
*/
