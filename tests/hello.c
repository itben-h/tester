#include "munit.h"

static MunitResult
test_online(const MunitParameter params[], void* data) {
	char *online = "Online!";
	(void) params;
	(void) data;

	munit_assert_string_equal(online, "Online!");
	return MUNIT_OK;
}

static	MunitTest test_suite_tests[] = {
	{"/hello", test_online, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const	MunitSuite test_suite = {"", test_suite_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int	main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
	return munit_suite_main(&test_suite, (void*) "", argc, argv);
}
