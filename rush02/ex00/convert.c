/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 13:17:21 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/04 19:27:45 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

/*
// convert.c内に仮辞書を持つ
static char	*s_ones[] = {"zero", "one", "two", "three", "four", "five", "six",
		"seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen",
		"fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};

static char	*s_tens[] = {"", "", "twenty", "thirty", "forty", "fifty", "sixty",
		"seventy", "eighty", "ninety"};

static char	*s_units[] = {
	"", "thousand", "million", "billion", "trillion", "quadrillion" // どこまで対応する？
};
*/

int			ft_strlen(char *str);
void		ft_putstr(char *str);
void		ft_putstrs(char *str);
void		ft_split(char *c);

// void		convert_hundreds(char *group, t_dict *dict);
// void		split_groups(char *num_str, char groups[][4], int *count);
// void		convert(char *num_str, t_dict *dict);
void		convert_hundreds(char *group, int len);
void		convert_tens(char *group);
void		convert_ones(char *group);

void		split_groups(char *num_str, char groups[][4], int *count);
void		convert(char *num_str);

void	convert(char *num_str)
{
	int		len;
	char	*group;
	char	*dist;

	len = ft_strlen(num_str);
	convert_hundreds(num_str, len);
}

// 2桁だけ処理（"23" → "twenty-three", "13" → "thirteen"）
void	convert_tens(char *group)
{
	char	list[2];

	if (group[0] == '1')
	{
		ft_putstrs(list);
		ft_putstrs("| 10 |");
	}
	else if (group[0] != '0')
	{
		list[0] = group[0];
		list[1] = '\0';
		ft_putstrs(list);
		ft_putstrs("| 10 |");
		convert_ones(&group[1]);
	}
	// group[0]=='0': ones だけ
	// group[0]=='1': teens → 2桁まとめて引く
	// その他: tens 引く → '-' → ones 引く
}

void	convert_ones(char *group)
{
	char	list[2];

	list[0] = group[0];
	list[1] = '\0';
	ft_putstrs(list);
	ft_putstrs("| 1 |");
}

void	convert_hundreds(char *group, int len)
{
	char	list[2];

	if (len == 3 && group[0] != '0')
	{
		list[0] = group[0];
		list[1] = '\0';
		ft_putstrs(list);
		ft_putstrs("| 100 |");
	}
	if (len >= 2)
	{
		convert_tens(&group[len - 2]);
		ft_putstrs("-------------");
		ft_putstrs(&group[len - 2]);
		ft_putstrs("-------------");
	}
	else
	{
		list[0] = group[len - 1];
		list[1] = '\0';
		ft_putstrs("-------------");
		ft_putstrs(list);
		ft_putstrs("-------------");
		// ones だけの場合
	}
}

int	main(void)
{
	// convert("1234567");
	// convert("223");
	// ft_putstrs("\n");
	// convert("100");
	// ft_putstrs("\n");
	// convert("10");
	// ft_putstrs("\n");
	convert("103");
	ft_putstrs("\n");
	convert("3");
	ft_putstrs("\n");
	convert("0");
	ft_putstrs("\n");
	return (0);
}
