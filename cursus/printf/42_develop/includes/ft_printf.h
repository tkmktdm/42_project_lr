/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 16:17:10 by htakumi           #+#    #+#             */
/*   Updated: 2026/05/11 20:24:27 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
size_t				ft_strlen(const char *s);
size_t				ft_strcount(const char *s, char word);


#endif
