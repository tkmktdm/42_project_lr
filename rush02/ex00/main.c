/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkariya <kkariya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 14:25:11 by msumiji           #+#    #+#             */
/*   Updated: 2026/04/05 14:58:16 by kkariya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

static int	run_convert(char *dict_path, char *num_str)
{
	t_dict	*dict;

	dict = load_dict(dict_path);
	if (!dict)
		return (dict_error());
	if (convert(num_str, dict))
	{
		free_dict(dict);
		return (dict_error());
	}
	free_dict(dict);
	return (0);
}

int	main(int argc, char *argv[])
{
	if (argc == 2 && is_number(argv[1]))
		return (run_convert("numbers.dict", argv[1]));
	if (argc == 3 && is_number(argv[2]))
		return (run_convert(argv[1], argv[2]));
	return (put_error());
}
