#include "test_helpers.h"
#include <stdio.h>
#include <string.h>

static void	fail_header(const char *label, const char *f, int l)
{
	fprintf(stderr, "FAIL %s:%d %s ", f, l, label);
}

void	assert_eq_int(const char *label, long a, long e, const char *f, int l)
{
	if (a == e)
	{
		g_pass++;
		return ;
	}
	g_fail++;
	fail_header(label, f, l);
	fprintf(stderr, "got %ld, want %ld\n", a, e);
}

void	assert_eq_str(const char *label, const char *a, const char *e, const char *f, int l)
{
	if (a == NULL && e == NULL)
	{
		g_pass++;
		return ;
	}
	if (a != NULL && e != NULL && strcmp(a, e) == 0)
	{
		g_pass++;
		return ;
	}
	g_fail++;
	fail_header(label, f, l);
	fprintf(stderr, "got %s, want %s\n",
		a ? a : "(null)", e ? e : "(null)");
}

void	assert_eq_mem(const char *label, const void *a, const void *b, size_t n, const char *f, int l)
{
	if (memcmp(a, b, n) == 0)
	{
		g_pass++;
		return ;
	}
	g_fail++;
	fail_header(label, f, l);
	fprintf(stderr, "memcmp failed (n=%zu)\n", n);
}

void	assert_null(const char *label, const void *p, const char *f, int l)
{
	if (p == NULL)
	{
		g_pass++;
		return ;
	}
	g_fail++;
	fail_header(label, f, l);
	fprintf(stderr, "expected NULL, got %p\n", p);
}

void	assert_not_null(const char *label, const void *p, const char *f, int l)
{
	if (p != NULL)
	{
		g_pass++;
		return ;
	}
	g_fail++;
	fail_header(label, f, l);
	fprintf(stderr, "expected non-NULL, got NULL\n");
}

void	assert_eq_ptr(const char *label, const void *a, const void *e, const char *f, int l)
{
	if (a == e)
	{
		g_pass++;
		return ;
	}
	g_fail++;
	fail_header(label, f, l);
	fprintf(stderr, "got %p, want %p\n", a, e);
}

void	assert_true(const char *label, int cond, const char *f, int l)
{
	if (cond)
	{
		g_pass++;
		return ;
	}
	g_fail++;
	fail_header(label, f, l);
	fprintf(stderr, "condition false\n");
}
