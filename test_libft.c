# include <stdio.h>
#include "munit.h"
#include "../libft/libft.h"

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
	int arr[10];
	int arr_a[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	
	ft_memset(str + 4, '$', 5 * sizeof(char));
	ft_memset(arr, -1, 10 * sizeof(arr[0]));
	
	munit_assert_string_equal(str, "this$$$$$ string");
	for (int i = 0; i < 10; i++)
		munit_assert_int(arr[i], ==, arr_a[i]);
	return MUNIT_OK;
}

static MunitResult
test_bzero(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	char str1[] = "string";
	char str1_1[] = "string";
	char str2[] = "test-test";

	ft_bzero(str1, 5);
	bzero(str1_1, 5);
	munit_assert_string_equal(str1, str1_1);
	ft_bzero(str2, 3);
	munit_assert_string_equal(str2, "");
	ft_bzero(str2, 10);
	munit_assert_string_equal(str2, "");
	return MUNIT_OK;
}

static MunitResult
test_memcpy(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	char blank[5] = "";
	char blank_1[5] = "";
	char dest[50] = "Replace Me";
	char dest_1[50] = "Replace Me";
	char src[50] = "Get Replaced";
	char src_1[50] = "Get Replaced";
	int arr[5] = {1, 2, 3, 4, 5};
	int arr_1[5] = {1, 2, 3, 4, 5};
	int arr_s[3] = {6, 7, 8};
	
	munit_assert_string_equal(ft_memmove(blank, blank, 3), memmove(blank_1, blank_1, 3));
	munit_assert_string_equal(ft_memcpy(dest, src, 5), memcpy(dest_1, src_1, 5));
	ft_memcpy(arr, arr_s, 2);
	memcpy(arr_1, arr_s, 2);
	for (int i = 0; i < 5; i++)
		munit_assert_int(arr[i], ==, arr_1[i]);
	return MUNIT_OK;
}

static MunitResult
test_memmove(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	char blank[5] = "";
	char blank_1[5] = "";
	char dest[50] = "Replace Me";
	char dest_1[50] = "Replace Me";
	char src[50] = "Get Replaced";
	char src_1[50] = "Get Replaced";
	char overlap[50] = "overlap";
	char overlap_1[50] = "overlap";
	int arr[9] = {1, 2, 3, 4, 5};
	int arr_1[9] = {1, 2, 3, 4, 5};
	
	munit_assert_string_equal(ft_memmove(blank, blank, 3), memmove(blank_1, blank_1, 3));
	munit_assert_string_equal(ft_memmove(dest, src, 5), memmove(dest_1, src_1, 5));
	munit_assert_string_equal(ft_memmove(overlap + 5, overlap, 7), memmove(overlap_1 + 4, overlap_1, 7));
	munit_logf(MUNIT_LOG_INFO, "Memmoved String is %s", overlap);
	ft_memmove(arr + 3, arr, 4);
	memmove(arr_1 + 3, arr, 4);
	for (int i = 0; i < 5; i++) {
		munit_assert_int(arr[i], ==, arr_1[i]);
		munit_logf(MUNIT_LOG_INFO, "Memmoved element %d is %d", i, arr[i]);
	}
	return MUNIT_OK;
}

static MunitResult
test_strlcpy(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	char dest[] = "dest";
	char src[] = "src";

	ft_strlcpy(dest, src, 2);
	munit_assert_string_equal(dest, "s");
	ft_strlcpy(dest, src, 4);
	munit_assert_string_equal(dest, "src");
	munit_assert_int(ft_strlcpy(dest, src, 0), ==, 3);
	return MUNIT_OK;
}

static MunitResult
test_strlcat(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	char dest[10] = "dest";
	char src[10] = "src";

	munit_assert_int(ft_strlcat(dest, src, 0), ==, 3);
	ft_strlcat(dest, src, 6);
	munit_assert_string_equal(dest, "dests");
	ft_strlcat(dest, src, 10);
	munit_assert_string_equal(dest, "destssrc");
	munit_assert_int(ft_strlcat(dest, src, 12), ==, 11);
	munit_logf(MUNIT_LOG_INFO, "Final strlcat is %s", dest);
	return MUNIT_OK;
}

static MunitResult
test_toupper(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	char lower = 'a';
	char upper = 'Z';
	char none = ' ';

	munit_assert_char(ft_toupper(lower), ==, 'A');
	munit_assert_char(ft_toupper(upper), ==, 'Z');
	munit_assert_char(ft_toupper(none), ==, ' ');
	return MUNIT_OK;
}

static MunitResult
test_tolower(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	char lower = 'a';
	char upper = 'Z';
	char none = '~';

	munit_assert_char(ft_tolower(lower), ==, 'a');
	munit_assert_char(ft_tolower(upper), ==, 'z');
	munit_assert_char(ft_tolower(none), ==, '~');
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
	{"/ft_bzero", test_bzero, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{"/ft_memcpy", test_memcpy, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{"/ft_memmove", test_memmove, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{"/ft_strlcpy", test_strlcpy, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{"/ft_strlcat", test_strlcat, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{"/ft_toupper", test_toupper, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{"/ft_tolower", test_tolower, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const	MunitSuite test_suite = {"", test_suite_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int	main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
	return munit_suite_main(&test_suite, (void*) "", argc, argv);
}
