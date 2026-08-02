/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujikaw <tfujikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 03:37:34 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/05/05 17:08:38 by tfujikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*num;
	size_t			total;
	size_t			i;

	if (size != 0 && nmemb > (size_t)(-1) / size)
		return (NULL);
	total = nmemb * size;
	num = (unsigned char *)malloc(total);
	if (!num)
		return (NULL);
	i = 0;
	while (i < total)
		num[i++] = 0;
	return ((void *)num);
}
/*
#include <stdio.h>

int	main(void) {
	int *check;
	int n = 5;
	int	*real;
	int	k = 5;

	check = (int *)ft_calloc(n, sizeof(int));
	if (check == NULL) {
		return (0);
	}
	real = (int *)calloc(k, sizeof(int));
	if (real == NULL) {
		return (0);
	}
	int i;
	for (i = 0; i < n; i++) {
		printf("%d ", check[i]);
	}
	printf("\n");
	for (i = 0; i < n; i++) {
		printf("%d ", real[i]);
	}

	free(check);
	free(real);
	return (0);
}
*/
