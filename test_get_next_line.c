#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "munit.h"
#include "./build/get_next_line.h"

static MunitResult
test_nothing(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	
	int fd = open("./gnl_txt/nothing", O_RDWR);

	char *s = get_next_line(fd);
	munit_logf(MUNIT_LOG_INFO, "next line: %s", s);
	munit_assert_null(s);
	
	close(fd);
	return MUNIT_OK;
}

static MunitResult
test_oneLine(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	
	int fd = open("./gnl_txt/test1", O_RDWR);
	
	char *s = get_next_line(fd);
	munit_logf(MUNIT_LOG_INFO, "next line: %s", s);
	munit_assert_string_equal(s, "01234567890123456789012345678901234567890");
	
	s = get_next_line(fd);
	munit_logf(MUNIT_LOG_INFO, "next line: %s", s);
	munit_assert_null(s);
	
	close(fd);
	return MUNIT_OK;
}

static MunitResult
test_multLine(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	
	int fd = open("./gnl_txt/test2", O_RDWR);
	
	char *s = get_next_line(fd);
	munit_logf(MUNIT_LOG_INFO, "next line: %s", s);
	munit_assert_string_equal(s, "this is line one\n");
	
	s = get_next_line(fd);
	munit_logf(MUNIT_LOG_INFO, "next line: %s", s);
	munit_assert_string_equal(s, "this is line two\n");
	
	s = get_next_line(fd);
	munit_logf(MUNIT_LOG_INFO, "next line: %s", s);
	munit_assert_string_equal(s, "this is line three\n");
	
	s = get_next_line(fd);
	munit_logf(MUNIT_LOG_INFO, "next line: %s", s);
	munit_assert_string_equal(s, "this is line four                             4\n");
	
	s = get_next_line(fd);
	munit_logf(MUNIT_LOG_INFO, "next line: %s", s);
	munit_assert_string_equal(s, "\n");
	
	s = get_next_line(fd);
	munit_logf(MUNIT_LOG_INFO, "next line: %s", s);
	munit_assert_string_equal(s, "this is the last linnnneeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee0");
	
	s = get_next_line(fd);
	munit_logf(MUNIT_LOG_INFO, "next line: %s", s);
	munit_assert_null(s);
	
	close(fd);
	return MUNIT_OK;
}

static MunitResult
test_longLine(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	
	int fd = open("./gnl_txt/testLong", O_RDWR);
	
	char *s = get_next_line(fd);
	munit_logf(MUNIT_LOG_INFO, "next line: %s", s);
	munit_assert_string_equal(s, "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890\n");
	
	s = get_next_line(fd);
	munit_logf(MUNIT_LOG_INFO, "next line: %s", s);
	munit_assert_string_equal(s, "1");
	
	s = get_next_line(fd);
	munit_logf(MUNIT_LOG_INFO, "next line: %s", s);
	munit_assert_null(s);
	
	close(fd);
	return MUNIT_OK;
}

static	MunitTest test_suite_tests[] = {
	{"/print nothing", test_nothing, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{"/print one line", test_oneLine, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{"/print mult line", test_multLine, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{"/print long line", test_longLine, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const	MunitSuite test_suite = {"", test_suite_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int	main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
	return munit_suite_main(&test_suite, (void*) "", argc, argv);
}
