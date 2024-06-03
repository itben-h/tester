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
	int u_count = ft_printf("%c\n", 'c');
	int o_count = printf("%c\n", 'c');
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("hello%c\n", '~');
	o_count = printf("hello%c\n", '~');
	munit_assert_int(u_count, ==, o_count);

	return MUNIT_OK;
}

static MunitResult
test_str(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	
	printf("\n");
	int u_count = ft_printf("%s\n", "string");
	int o_count = printf("%s\n", "string");
	munit_assert_int(u_count, ==, o_count);
	
	char str[] = "this is a ";
	u_count = ft_printf("%sstring\n", str);
	o_count = printf("%sstring\n", str);
	munit_assert_int(u_count, ==, o_count);

	return MUNIT_OK;
}

static MunitResult
test_int(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	
	printf("\n");
	int u_count = ft_printf("%i\n", 100);
	int o_count = printf("%d\n", 100);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%i\n", INT_MAX);
	o_count = printf("%d\n", INT_MAX);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%i\n", INT_MIN);
	o_count = printf("%d\n", INT_MIN);
	munit_assert_int(u_count, ==, o_count);

	return MUNIT_OK;
}

static MunitResult
test_uint(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	
	printf("\n");
	int u_count = ft_printf("%u\n", 0);
	int o_count = printf("%u\n", 0);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%u\n", 10010);
	o_count = printf("%u\n", 10010);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%u\n", UINT_MAX);
	o_count = printf("%u\n", UINT_MAX);
	munit_assert_int(u_count, ==, o_count);

	return MUNIT_OK;
}

static MunitResult
test_percent(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	
	printf("\n");
	int u_count = ft_printf("%%\n");
	int o_count = printf("%%\n");
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%s%%ha\n", "ha");
	o_count = printf("%s%%ha\n", "ha");
	munit_assert_int(u_count, ==, o_count);

	return MUNIT_OK;
}

static MunitResult
test_hexa(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	
	printf("\n");
	int u_count = ft_printf("%x\n", 123456);
	int o_count = printf("%x\n", 123456);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("test%x%Xtest\n", 42, 6666);
	o_count = printf("test%x%Xtest\n", 42, 6666);
	munit_assert_int(u_count, ==, o_count);

	return MUNIT_OK;
}

static MunitResult
test_ptr(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	
	int i = 1; int j = 42; char c = 'x'; char *s = "ghhhhh";
	
	printf("\n");
	int u_count = ft_printf("%p\n", &i);
	int o_count = printf("%p\n", &i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("1%p\n2%p\n3%p\n", &j, &c, &s);
	o_count = printf("1%p2%p3%p\n", &j, &c, &s);
	munit_assert_int(u_count, ==, o_count);

	return MUNIT_OK;
}

static	MunitTest test_suite_tests[] = {
	{"/print char", test_char, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{"/print str", test_str, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{"/print int", test_int, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{"/print uint", test_uint, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{"/print percent", test_percent, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{"/print hexa", test_hexa, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{"/print ptr", test_ptr, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const	MunitSuite test_suite = {"", test_suite_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int	main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
	return munit_suite_main(&test_suite, (void*) "", argc, argv);
}
