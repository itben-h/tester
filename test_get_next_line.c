#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "munit.h"
#include "./build/get_next_line.h"

static MunitResult
test_oneLine(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	
	int fd = open("./test1", O_RDWR);
	
	char *s = get_next_line(fd);
	munit_logf(MUNIT_LOG_INFO, "next line: %s", s);
	munit_assert_string_equal(s, "this is a sentence that should be getted\n");
	
	s = get_next_line(fd);
	munit_assert_string_equal(s, "do not get this sentence\n");
	munit_logf(MUNIT_LOG_INFO, "next line: %s", s);
	
	s = get_next_line(fd);
	munit_assert_string_equal(s, "nothing\n");
	munit_logf(MUNIT_LOG_INFO, "next line: %s", s);
	
	s = get_next_line(fd);
	munit_assert_string_equal(s, "");
	munit_logf(MUNIT_LOG_INFO, "next line: %s", s);
	
	close(fd);
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
