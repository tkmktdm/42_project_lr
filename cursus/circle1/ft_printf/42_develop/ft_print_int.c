/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:10:23 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/05/30 12:53:53 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_int(va_list *ap)
{
	int		i;
	int		len;
	char	*str;
	int		ret;

	i = va_arg(*ap, int);
	str = ft_itoa(i);
	if (!str)
		return (-1);
	len = (int)ft_strlen(str);
	ret = (int)write(1, str, (size_t)len);
	free(str);
	if (ret == -1)
		return (-1);
	return (len);
}
