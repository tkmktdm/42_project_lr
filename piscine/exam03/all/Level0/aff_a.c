/* allowed functions: write */
#include <unistd.h>

int	main(int argc, char **argv)
{
	write(1, "a\n", 2);
	return (0);
}

// /* allowed functions: write */
// #include <unistd.h>

// int	main(void)
// {
// 	write(1, "a\n", 2);
// 	return (0);
// }
