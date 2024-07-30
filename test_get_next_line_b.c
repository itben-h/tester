#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "munit.h"
#include "./build/get_next_line_bonus.h"

static MunitResult
test_print3files(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	
	int fd1 = open("./gnl_txt/testb1", O_RDWR);
	int fd2 = open("./gnl_txt/testb2", O_RDWR);
	int fd3 = open("./gnl_txt/testb3", O_RDWR);
	
	char *s = get_next_line(fd1);
	munit_logf(MUNIT_LOG_INFO, "next line b1: %s", s);
	munit_assert_string_equal(s, "this is b1 first line\n");
	free(s);
	
	s = get_next_line(fd2);
	munit_logf(MUNIT_LOG_INFO, "next line b2: %s", s);
	munit_assert_string_equal(s, "first line this is b2\n");
	free(s);
	
	s = get_next_line(fd3);
	munit_logf(MUNIT_LOG_INFO, "next line b3: %s", s);
	munit_assert_string_equal(s, "line first b3 this is\n");
	free(s);
	
	s = get_next_line(fd1);
	munit_logf(MUNIT_LOG_INFO, "next line b1: %s", s);
	munit_assert_string_equal(s, "b1 second line");
	free(s);
	
	s = get_next_line(fd2);
	munit_logf(MUNIT_LOG_INFO, "next line b2: %s", s);
	munit_assert_string_equal(s, "second line b2");
	free(s);
	
	s = get_next_line(fd3);
	munit_logf(MUNIT_LOG_INFO, "next line b3: %s", s);
	munit_assert_string_equal(s, "line second b3");
	free(s);
	
	s = get_next_line(fd1);
	munit_logf(MUNIT_LOG_INFO, "next line b1: %s", s);
	munit_assert_null(s);
	
	s = get_next_line(fd2);
	munit_logf(MUNIT_LOG_INFO, "next line b2: %s", s);
	munit_assert_null(s);
	
	s = get_next_line(fd3);
	munit_logf(MUNIT_LOG_INFO, "next line b3: %s", s);
	munit_assert_null(s);
	
	close(fd1); close(fd2); close(fd3);
	return MUNIT_OK;
}

static	MunitTest test_suite_tests[] = {
	{"/print 3 files", test_print3files, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const	MunitSuite test_suite = {"", test_suite_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int	main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
	return munit_suite_main(&test_suite, (void*) "", argc, argv);
}
