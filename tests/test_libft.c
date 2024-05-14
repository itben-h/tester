#include "munit.h"
#include "libft.h"

static MunitResult
test_isalpha(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
    char a = 'a';
    char b = ' ';

	munit_assert_true(ft_isalpha(a));
    munit_assert_false(ft_isalpha(b));
	return MUNIT_OK;
}

static	MunitTest test_suite_tests[] = {
	{"/isalpha", test_isalpha, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const	MunitSuite test_suite = {"", test_suite_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int	main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
	return munit_suite_main(&test_suite, (void*) "", argc, argv);
}