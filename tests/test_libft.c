# include <stdio.h>
#include "munit.h"
#include "../libft.h"

static MunitResult
test_isalpha(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	char is = 'a';
	char isnt = ' ';

	munit_assert_true(ft_isalpha(is));
	munit_assert_false(ft_isalpha(isnt));
	return MUNIT_OK;
}

static MunitResult
test_isdigit(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	char is = '5';
	char isnt = 'a';

	munit_assert_true(ft_isdigit(is));
	munit_assert_false(ft_isdigit(isnt));
	return MUNIT_OK;
}

static MunitResult
test_isalnum(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	char is1 = '9';
	char is2 = '3';
	char isnt1 = 1;
	char isnt2 = 127;

	munit_assert_true(ft_isalnum(is1));
	munit_assert_true(ft_isalnum(is2));
	munit_assert_false(ft_isalnum(isnt1));
	munit_assert_false(ft_isalnum(isnt2));
	return MUNIT_OK;
}

static MunitResult
test_isascii(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	char is = 31;
	unsigned char isnt = 255;

	munit_assert_true(ft_isascii(is));
	munit_assert_false(ft_isascii(isnt));
	return MUNIT_OK;
}

static MunitResult
test_isprint(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	char is = '~';
	char isnt = 17;

	munit_assert_true(ft_isprint(is));
	munit_assert_false(ft_isprint(isnt));
	return MUNIT_OK;
}

static MunitResult
test_strlen(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	char *string = "string";
	char *longString = "loooooooooong";

	munit_assert_size(ft_strlen(string), ==, 6);
	munit_assert_size(ft_strlen(longString), ==, 13);
	return MUNIT_OK;
}

static MunitResult
test_memset(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	char str[17] = "this is a string";
	int n = 10;
	int arr[n];
	int arr_a[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	
	ft_memset(str + 4, '$', 5 * sizeof(char));
	ft_memset(arr, -1, n * sizeof(arr[0]));
	
	munit_assert_string_equal(str, "this$$$$$ string");
	for (int i = 0; i < n; i++)
		munit_logf(MUNIT_LOG_INFO, "%d", arr[i]);
	for (int i = 0; i < n; i++)
		munit_assert_int(arr[i], ==, arr_a[i]);
	return MUNIT_OK;
}

static	MunitTest test_suite_tests[] = {
	{"/ft_isalpha", test_isalpha, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{"/ft_isdigit", test_isdigit, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{"/ft_isalnum", test_isalnum, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{"/ft_isascii", test_isascii, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{"/ft_isprint", test_isprint, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{"/ft_strlen", test_strlen, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{"/ft_memset", test_memset, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const	MunitSuite test_suite = {"", test_suite_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int	main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
	return munit_suite_main(&test_suite, (void*) "", argc, argv);
}
