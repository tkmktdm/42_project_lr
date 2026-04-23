/* allowed functions: none */

int	count_alen(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != 'a')
		i++;
	return (i);
}
