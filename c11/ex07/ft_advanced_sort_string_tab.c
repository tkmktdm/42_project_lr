/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_advanced_sort_string_tab.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 20:05:07 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/09 20:16:23 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_advanced_sort_string_tab(char **tab, int (*cmp)(char *, char *))
{
	int		i;
	int		len;
	char	*tmp;

	len = 0;
	while (tab[len])
		len++;
	i = 0;
	while (i < len - 1)
	{
		if (cmp(tab[i], tab[i + 1]) > 0)
		{
			tmp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

// #include <stdio.h>
// static int	ft_strcmp(char *s1, char *s2)
// {
// 	int	i;
//
// 	i = 0;
// 	while (s1[i] && s2[i] && s1[i] == s2[i])
// 		i++;
// 	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// }
//
// int	main(void)
// {
// 	char	*tab[] = {"banana", "apple", "cherry", "avocado", NULL};
// 	int		i;
//
// 	ft_advanced_sort_string_tab(tab, ft_strcmp);
// 	i = 0;
// 	while (tab[i])
// 	{
// 		printf("%s\n", tab[i]);
// 		i++;
// 	}
// 	return (0);
// }
