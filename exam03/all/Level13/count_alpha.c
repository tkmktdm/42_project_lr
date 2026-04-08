/* allowed functions: write, printf */
#include <stdio.h>
#include <unistd.h>

static int	is_alpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

static char	to_lower(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c - 'A' + 'a');
	return (c);
}

int	main(int argc, char **argv)
{
	int		counts[26];
	int		order[26];
	int		n;
	int		i;
	char	*s;

	if (argc != 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	i = 0;
	while (i < 26)
		counts[i++] = 0;
	n = 0;
	s = argv[1];
	i = 0;
	while (s[i])
	{
		if (is_alpha(s[i]))
		{
			int idx = to_lower(s[i]) - 'a';
			if (counts[idx] == 0)
				order[n++] = idx;
			counts[idx]++;
		}
		i++;
	}
	i = 0;
	while (i < n)
	{
		if (i > 0)
			printf(", ");
		printf("%d%c", counts[order[i]], 'a' + order[i]);
		i++;
	}
	printf("\n");
	return (0);
}
