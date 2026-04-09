/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:20:55 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/09 20:16:01 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_sort(int *tab, int length, int (*f)(int, int))
{
	int	i;
	int	asc;
	int	desc;

	asc = 1;
	desc = 1;
	i = 0;
	while (i < length - 1)
	{
		if (f(tab[i], tab[i + 1]) > 0)
			asc = 0;
		if (f(tab[i], tab[i + 1]) < 0)
			desc = 0;
		i++;
	}
	return (asc || desc);
}

// int	ft_sort(int s1, int s2)
// {
// 	return (s1 - s2);
// }

// int	main(void)
// {
// 	int	tab[3];

// 	tab[0] = 1;
// 	tab[1] = 2;
// 	tab[2] = 3;
// 	printf("%d\n", ft_is_sort(tab, 3, &ft_sort));
// 	return (0);
// }
