/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumiji <msumiji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 14:25:11 by msumiji           #+#    #+#             */
/*   Updated: 2026/04/04 17:14:50 by msumiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
		{
			put_error();
			break ;
		}
	}
}

int	main(int argc, char *argv[])
{
	if (argc == 2)
	{
		is_number(argv[1]);
		convert(argv[1]);
		return (1);
	}
	else if (argc == 3)
	{
		is_number(argv[2]);
		dict_check(argv[1]);
		return (1);
	}
	else
	{
		put_error(0);
		return (1);
	}
}
