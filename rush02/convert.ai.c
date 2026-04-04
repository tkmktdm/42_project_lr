/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.ai.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 13:17:21 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/04 16:38:49 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static char	*s_ones[] = {"zero", "one", "two", "three", "four", "five", "six",
		"seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen",
		"fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};

static char	*s_tens[] = {"", "", "twenty", "thirty", "forty", "fifty", "sixty",
		"seventy", "eighty", "ninety"};

static char	*s_units[] = {"", "thousand", "million", "billion", "trillion",
		"quadrillion", "quintillion"};

int			ft_strlen(char *str);
void		ft_putstrs(char *str);

static int	group_is_zero(char *group)
{
	int	j;

	j = 0;
	while (group[j])
	{
		if (group[j] != '0')
			return (0);
		j++;
	}
	return (1);
}

static void	print_tens(int remainder)
{
	if (remainder < 20)
	{
		ft_putstrs(s_ones[remainder]);
		return ;
	}
	ft_putstrs(s_tens[remainder / 10]);
	if (remainder % 10 > 0)
	{
		ft_putstrs("-");
		ft_putstrs(s_ones[remainder % 10]);
	}
}

static void	convert_hundreds(char *group)
{
	int	val;
	int	i;
	int	hundreds;
	int	remainder;

	val = 0;
	i = 0;
	while (group[i])
		val = val * 10 + (group[i++] - '0');
	if (val == 0)
		return ;
	hundreds = val / 100;
	remainder = val % 100;
	if (hundreds > 0)
	{
		ft_putstrs(s_ones[hundreds]);
		ft_putstrs(" hundred");
		if (remainder > 0)
			ft_putstrs(" ");
	}
	if (remainder > 0)
		print_tens(remainder);
}

static void	split_groups(char *num_str, char groups[][4], int *count)
{
	int	len;
	int	i;
	int	start;
	int	j;

	len = ft_strlen(num_str);
	i = len;
	*count = 0;
	while (i > 0)
	{
		start = (i >= 3) ? i - 3 : 0;
		j = 0;
		while (j < i - start)
		{
			groups[*count][j] = num_str[start + j];
			j++;
		}
		groups[*count][j] = '\0';
		(*count)++;
		i = start;
	}
}

static void	print_group(char *group, int unit_idx, int *first)
{
	if (group_is_zero(group))
		return ;
	if (!*first)
		ft_putstrs(" ");
	convert_hundreds(group);
	if (s_units[unit_idx][0] != '\0')
	{
		ft_putstrs(" ");
		ft_putstrs(s_units[unit_idx]);
	}
	*first = 0;
}

void	convert(char *num_str)
{
	char	groups[7][4];
	int		count;
	int		i;
	int		first;

	if (num_str[0] == '0' && num_str[1] == '\0')
	{
		ft_putstrs("zero");
		return ;
	}
	split_groups(num_str, groups, &count);
	first = 1;
	i = count - 1;
	while (i >= 0)
	{
		print_group(groups[i], i, &first);
		i--;
	}
}

int	main(void)
{
	convert("0");
	ft_putstrs("\n");
	convert("42");
	ft_putstrs("\n");
	convert("100");
	ft_putstrs("\n");
	convert("100000");
	ft_putstrs("\n");
	convert("1234567890");
	ft_putstrs("\n");
	return (0);
}
