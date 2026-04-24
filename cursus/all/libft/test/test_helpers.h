#ifndef TEST_HELPERS_H
# define TEST_HELPERS_H

# include <stddef.h>

extern int	g_pass;
extern int	g_fail;

# define ASSERT_EQ_INT(label, actual, expected) \
	assert_eq_int((label), (long)(actual), (long)(expected), __FILE__, __LINE__)

# define ASSERT_EQ_STR(label, actual, expected) \
	assert_eq_str((label), (actual), (expected), __FILE__, __LINE__)

# define ASSERT_EQ_MEM(label, a, b, n) \
	assert_eq_mem((label), (a), (b), (size_t)(n), __FILE__, __LINE__)

# define ASSERT_NULL(label, p) \
	assert_null((label), (p), __FILE__, __LINE__)

# define ASSERT_NOT_NULL(label, p) \
	assert_not_null((label), (p), __FILE__, __LINE__)

# define ASSERT_EQ_PTR(label, actual, expected) \
	assert_eq_ptr((label), (const void *)(actual), (const void *)(expected), __FILE__, __LINE__)

# define ASSERT_TRUE(label, cond) \
	assert_true((label), (int)(cond), __FILE__, __LINE__)

void	assert_eq_int(const char *label, long a, long e, const char *f, int l);
void	assert_eq_str(const char *label, const char *a, const char *e, const char *f, int l);
void	assert_eq_mem(const char *label, const void *a, const void *b, size_t n, const char *f, int l);
void	assert_null(const char *label, const void *p, const char *f, int l);
void	assert_not_null(const char *label, const void *p, const char *f, int l);
void	assert_eq_ptr(const char *label, const void *a, const void *e, const char *f, int l);
void	assert_true(const char *label, int cond, const char *f, int l);

void	run_part1_tests(void);
void	run_part2_tests(void);
void	run_part3_tests(void);

#endif
