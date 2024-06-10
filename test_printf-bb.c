#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "munit.h"
#include "../printf/ft_printf.h"

int	pipefd[2];
int	saved_stdout = -1;
char	buf[256] = {0};

static void*
test_setup(const MunitParameter params[], void* user_data) {
  	(void) params;
  	(void) user_data;

	saved_stdout = dup(fileno(stdout));
	dup2(pipefd[1], fileno(stdout));

	long flags = fcntl(pipefd[0], F_GETFL);
   	flags |= O_NONBLOCK;
   	fcntl(pipefd[0], F_SETFL, flags);

	return (void*) (uintptr_t) 0xdeadbeef;
}

static void
test_teardown(void* fixture) {

	dup2(saved_stdout, fileno(stdout));
	close(saved_stdout);
	saved_stdout = -1;
	close(pipefd[0]);
	close(pipefd[1]);
	munit_assert_ptr_equal(fixture, (void*)(uintptr_t)0xdeadbeef);
}

char *read_stdout_buf(void)
{
	fflush(stdout);
	bzero(buf, 256);
	int ret = read(pipefd[0], buf, 255);
	if (ret != -1)
		buf[ret] = '\0';
	return (buf);
}

static MunitResult
test_char(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;

	printf("\n");

	int u_count = ft_printf("%- 09.20c|\n", 'a');
	int o_count = printf("%- 09.20c|\n", 'a');
	munit_assert_int(u_count, ==, o_count);

	return MUNIT_OK;
}

static MunitResult
test_str(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;

	char *s = "string";

	printf("\n");

	int u_count = ft_printf("%-0 10.4s|\n", s);
	int o_count = printf("%-0 10.4s|\n", s);
	munit_assert_int(u_count, ==, o_count);

	return MUNIT_OK;
}

static MunitResult
test_int(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;

	printf("\n");
	int i = munit_rand_int_range(INT_MIN, INT_MAX);

	int u_count = ft_printf("%-0 +12.10i|\n", i);
	int o_count = printf("%-0 +12.10d|\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%-014.12i|\n", i);
	o_count = printf("%-014.12d|\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%-021.24i|\n", i);
	o_count = printf("%021.24d|\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%0 0+--+-- -+ 15.30i|\n", i);
	o_count = printf("%0 0+--+-- -+ 15.30d|\n", i);
	munit_assert_int(u_count, ==, o_count);

	return MUNIT_OK;
}

static MunitResult
test_hexa(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;

	printf("\n");
	int i = 123456;
	
	int u_count = ft_printf("%-0 +12.10x|1\n", i);
	int o_count = printf("%-0 +12.10x|1\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%-014.12X|2\n", i);
	o_count = printf("%-014.12X|2\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%-021.24x|3\n", i);
	o_count = printf("%021.24x|3\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%#-021.16x|4\n", i);
	o_count = printf("%#-021.16x|4\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%## 0 -0- -00 - + 0+0000 + + #15.30X|5\n", i);
	o_count = printf("%## 0 -0- -00 - + 0+0000 + + #15.30X|5\n", i);
	munit_assert_int(u_count, ==, o_count);

	return MUNIT_OK;
}

static MunitResult
test_ptr(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;

	int i = 1; int j = 42; char c = 'x'; char *s = "gabagoo";

	printf("\n");

	int u_count = ft_printf("%.20p|1\n", &i);
	int o_count = printf("%.20p|1\n", &i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%17.21p|2\n", &j);
	o_count = printf("%17.21p|2\n", &j);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%20.16p|3\n", &c);
	o_count = printf("%20.16p|3\n", &c);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%014p|4\n", &s);
	o_count = printf("%014p|4\n", &s);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%+022.17p|5\n", &s);
	o_count = printf("%+022.17p|5\n", &s);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%-+ 019.24p|6\n", &s);
	o_count = printf("%-+ 019.24p|6\n", &s);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%-+ 024.19p|7\n", &s);
	o_count = printf("%-+ 024.19p|7\n", &s);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%- +   +    0000000-    ++ --25.20p|8\n", &s);
	o_count = printf("%- +   +    0000000-    ++ --25.20p|8\n", &s);
	munit_assert_int(u_count, ==, o_count);

	return MUNIT_OK;
}

static	MunitTest test_suite_tests[] = {
	{"/print char", test_char, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{"/print str", test_str, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{"/print int", test_int, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{"/print hexa", test_hexa, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{"/print ptr", test_ptr, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const	MunitSuite test_suite = {"", test_suite_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int	main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
	return munit_suite_main(&test_suite, (void*) "", argc, argv);
}
