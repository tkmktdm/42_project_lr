/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazonode <kazonode@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 22:46:18 by kazonode          #+#    #+#             */
/*   Updated: 2026/03/29 17:36:40 by kazonode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		setup_puzzle(char *input);
void	ft_putstr(char *s);
int		solve(int pos);
void	print_grid(void);
void	cleanup(void);

int	*g_grid;
int	*g_hints;
int	g_size;

int	main(int argc, char **argv)
{
	if (argc != 2 || !setup_puzzle(argv[1]))
	{
		ft_putstr("Error\n");
		return (1);
	}
	if (solve(0))
		print_grid();
	else
		ft_putstr("Error\n");
	cleanup();
	return (0);
}
