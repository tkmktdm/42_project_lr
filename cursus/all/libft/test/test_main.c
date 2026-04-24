#include <stdio.h>
#include "test_helpers.h"

int	g_pass = 0;
int	g_fail = 0;

int	main(void)
{
	run_part1_tests();
	run_part2_tests();
	run_part3_tests();
	printf("\n=== RESULT: PASS=%d FAIL=%d ===\n", g_pass, g_fail);
	if (g_fail != 0)
		return (1);
	return (0);
}
