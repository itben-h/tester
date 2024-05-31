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
	char	*u_buf = strdup(read_stdout_buf());
	int o_count = printf("%c\n", 'c');
	char	*o_buf = strdup(read_stdout_buf());
	munit_assert_string_equal(u_buf, o_buf);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("hello%c\n", '~');
	u_buf = strdup(read_stdout_buf());
	o_count = printf("hello%c\n", '~');
	o_buf = strdup(read_stdout_buf());
	munit_assert_string_equal(u_buf, o_buf);
	munit_assert_int(u_count, ==, o_count);

	return MUNIT_OK;
}

static MunitResult
test_str(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	
	printf("\n");
	int u_count = ft_printf("%s\n", "string");
	char	*u_buf = strdup(read_stdout_buf());
	int o_count = printf("%s\n", "string");
	char	*o_buf = strdup(read_stdout_buf());
	munit_assert_string_equal(u_buf, o_buf);
	munit_assert_int(u_count, ==, o_count);
	
	char str[] = "this is a ";
	u_count = ft_printf("%sstring\n", str);
	u_buf = strdup(read_stdout_buf());
	o_count = printf("%sstring\n", str);
	o_buf = strdup(read_stdout_buf());
	munit_assert_string_equal(u_buf, o_buf);
	munit_assert_int(u_count, ==, o_count);

	return MUNIT_OK;
}

static	MunitTest test_suite_tests[] = {
	{"/print char", test_char, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{"/print str", test_str, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const	MunitSuite test_suite = {"", test_suite_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int	main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
	return munit_suite_main(&test_suite, (void*) "", argc, argv);
}
