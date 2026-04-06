/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkariya <kkariya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 16:27:34 by kkariya           #+#    #+#             */
/*   Updated: 2026/04/05 21:25:19 by kkariya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUSH_H
# define RUSH_H

typedef struct s_entry
{
	char	*key;
	char	*value;
}			t_entry;

typedef struct s_dict
{
	t_entry	*entries;
	int		size;
	char	**lines;
}			t_dict;

/* dict.c */
t_dict		*load_dict(char *path);
void		free_dict(t_dict *dict);

/* output.c */
int			put_error(void);
int			dict_error(void);
void		ft_putstr(char *str);
int			ft_strlen(char *str);
int			split_groups(char *num_str, char groups[][4]);

/* lookup.c */
char		*dict_lookup(t_dict *dict, char *key);
int			unit_exists(t_dict *dict, int idx);
int			print_unit(t_dict *dict, int idx);

/* convert_sub.c */
int			is_zero(char *str);
int			convert_ones(char *group, t_dict *dict);
int			convert_tens(char *group, t_dict *dict);
int			print_hundreds(char *group, t_dict *dict);
int			validate_units(char (*groups)[4], int top, t_dict *dict);

/* convert.c */
int			convert(char *num_str, t_dict *dict);
int			convert_hundreds(char *group, int len, t_dict *dict, int unit_idx);

#endif
