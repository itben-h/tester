#include "munit.h"
#include "../get_next_line/get_next_line.h"

static MunitResult
test_oneLine(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	
	t_list *l = ft_lstnew((void*)100);
	munit_assert_ptr_equal(l->content, (void*)100);
	munit_assert_ptr_equal(l->next, 0);
	free(l);
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
