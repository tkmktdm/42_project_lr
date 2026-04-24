/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokubo <kokubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 20:15:00 by kokubo            #+#    #+#             */
/*   Updated: 2026/04/23 01:00:00 by kokubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	ch;
	const char		*last;
	size_t			i;

	ch = (unsigned char)c;
	last = NULL;
	i = 0;
	while (s[i])
	{
		if ((unsigned char)s[i] == ch)
			last = &s[i];
		i++;
	}
	if (ch == 0)
		return ((char *)&s[i]);
	return ((char *)last);
}
