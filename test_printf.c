#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "munit.h"
#include "../printf/ft_printf.h"

char	*capture_stdout(

static void
test_setup(const MunitParameter params[], void* user_data) {
  	(void) params;

  	origin_buf = NULL;
	user_buf = NULL;
	saved_stdout = dup(fileno(stdout));
	dup2(pipefd[1], fileno(stdout));
}

static void
test_teardown(const MunitParameter params[], void* user_data) {
  	(void) params;

	dup2(saved_stdout, fileno(stdout));
	close(saved_stdout);
	saved_stdout = -1;
	close(pipefd[0]);
	close(pipefd[1]);
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
	(void) data;
	
	ft_printf("%c", 'c');
	u_buf = read_stdout_buf();
	printf("%c", 'c');
	o_buf = read_stdout_buf();

	munit_assert_string_equal(u_buf, o_buf);

	return MUNIT_OK;
}

static	MunitTest test_suite_tests[] = {
	{"/print one line", test_oneLine, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const	MunitSuite test_suite = {"", test_suite_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int	main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
	return munit_suite_main(&test_suite, (void*) "", argc, argv);
}
