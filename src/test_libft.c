# include <stdio.h>
# include <limits.h>
# include <string.h>
# include <sys/stat.h>
# include <fcntl.h>
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

	munit_assert_string_equal(ft_memcpy(blank, blank, 3), memcpy(blank_1, blank_1, 3));
	munit_assert_string_equal(ft_memcpy(dest, src, 5), memcpy(dest_1, src_1, 5));
	//munit_assert_null(ft_memcpy(((void*)0), ((void*)0), 3));
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

static MunitResult
test_strchr(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	char *s = "Bicycle";

	munit_assert_ptr_equal(ft_strchr(s, 'B'), s);
	munit_assert_ptr_equal(ft_strchr(s, 'c'), s + 2);
	munit_assert_ptr_equal(ft_strchr(s, 0), s + ft_strlen(s));
	munit_assert_ptr_equal(ft_strchr(s, 'X'), 0);
	munit_assert_ptr_equal(ft_strchr(s, 'B' + 256), s);
	return MUNIT_OK;
}

static MunitResult
test_strrchr(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	char *s = "Bicycle";
	char *empty = "";

	munit_assert_ptr_equal(ft_strrchr(s, 'B'), s);
	munit_assert_ptr_equal(ft_strrchr(s, 'c'), s + 4);
	munit_assert_ptr_equal(ft_strrchr(s, 0), s + ft_strlen(s));
	munit_assert_ptr_equal(ft_strrchr(s, 'X'), 0);
	munit_assert_ptr_equal(ft_strrchr(s, 'B' + 256), s);
	munit_assert_ptr_equal(ft_strrchr(empty, 'B'), 0);
	munit_assert_ptr_equal(ft_strrchr(empty, 0), empty);
	return MUNIT_OK;
}

static MunitResult
test_strncmp(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;

	munit_assert_int(ft_strncmp("", "", 100), ==, 0);
	munit_assert_int(ft_strncmp("1", "", 1), >, 0);
	munit_assert_int(ft_strncmp("", "1", 1), <, 0);
	munit_assert_int(ft_strncmp("abc", "abc", 3), ==, 0);
	munit_assert_int(ft_strncmp("abc", "abb", 3), >, 0);
	munit_assert_int(ft_strncmp("abC", "abc", 3), <, 0);
	munit_assert_int(ft_strncmp("one", "two", 0), ==, 0);
	return MUNIT_OK;
}

static MunitResult
test_memchr(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	char *s = "Bicycle";
	char arr[] = {0, 1, 2, 3};

	munit_assert_ptr_equal(ft_memchr(s, 'B', 1), s);
	munit_assert_ptr_equal(ft_memchr(s, 'c', 3), s + 2);
	munit_assert_ptr_equal(ft_memchr(s, 'X', 4), 0);
	munit_assert_ptr_equal(ft_memchr(s, 'B', 0), 0);
	munit_assert_ptr_equal(ft_memchr(arr, 0, 10), arr);
	munit_assert_ptr_equal(ft_memchr(arr, 2, 4), arr + 2);
	munit_assert_ptr_equal(ft_memchr(arr, 'B', 4), 0);
	return MUNIT_OK;
}

static MunitResult
test_memcmp(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	char s1[] = {3, 200, 42, 0, -1};
	char s1_1[] = {3, 200, 42, 0, -1};
	char s2[] = {1, 1, 1, 1, 42, 0, 0};
	char s3[] = {1, 1, 1, 1, 123, 0, 0};
	char s4[10] = "string";
	char s4x[10] = "strimg";

	munit_assert_int(ft_memcmp(s1, s1_1, 3), ==, 0);
	munit_assert_int(ft_memcmp(s1, s2, 5), >, 0);
	munit_assert_int(ft_memcmp(s2, s1, 5), <, 0);
	munit_assert_int(ft_memcmp(s1, s2, 0), ==, 0);
	munit_assert_int(ft_memcmp(s2, s3, 2), ==, 0);
	munit_assert_int(ft_memcmp(s2, s3, 7), <, 0);
	munit_assert_int(ft_memcmp(s4, s4x, 3), ==, 0);
	munit_assert_int(ft_memcmp(s4, s4x, 6), >, 0);
	return MUNIT_OK;
}

static MunitResult
test_strnstr(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	char *s1 = "string";
	char *s2 = "abcdefghijk";
	char *empty = "";

	munit_assert_ptr_equal(ft_strnstr(s1, "string", 6), s1);
	munit_assert_ptr_equal(ft_strnstr(s1, "string", 2), 0);
	munit_assert_ptr_equal(ft_strnstr(s1, "", 6), s1);
	munit_assert_ptr_equal(ft_strnstr(s2, "def", 10), s2 + 3);
	munit_assert_ptr_equal(ft_strnstr(s2, "e", 10), s2 + 4);
	munit_assert_ptr_equal(ft_strnstr(s2, "def", 4), 0);
	munit_assert_ptr_equal(ft_strnstr(empty, "", 3), empty);
	munit_assert_ptr_equal(ft_strnstr(empty, "a", 3), 0);
	return MUNIT_OK;
}

static MunitResult
test_atoi(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	char s[] = {9, 10, 13, 10, 32, '5'};

	munit_assert_int(ft_atoi("abc"), ==, 0);
	munit_assert_int(ft_atoi("3"), ==, 3);
	munit_assert_int(ft_atoi("-9"), ==, -9);
	munit_assert_int(ft_atoi("     +9"), ==, 9);
	munit_assert_int(ft_atoi(" -+9"), ==, 0);
	munit_assert_int(ft_atoi("   -00012009"), ==, -12009);
	munit_assert_int(ft_atoi("123456789"), ==, 123456789);
	munit_assert_int(ft_atoi(s), ==, 5);
	return MUNIT_OK;
}

static MunitResult
test_calloc(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	void *arr = ft_calloc(3, 2);
	char c[] = {0, 0, 0, 0, 0, 0};

	munit_assert_int(memcmp(arr, c, 6), ==, 0); free(arr);
	arr = ft_calloc(5, 25); munit_log(MUNIT_LOG_INFO, "calloc 1");
	munit_assert_not_null(arr); free(arr);
	arr = ft_calloc(4294967295, 2); munit_log(MUNIT_LOG_INFO, "calloc 2");
	munit_log(MUNIT_LOG_WARNING, "optional calloc below");
	munit_assert_null(arr); free(arr);
	arr = ft_calloc(0, -5); munit_log(MUNIT_LOG_INFO, "calloc 3");
	munit_assert_not_null(arr); free(arr);
	arr = ft_calloc(-5, 0); munit_log(MUNIT_LOG_INFO, "calloc 4");
	munit_assert_not_null(arr); free(arr);
	arr = ft_calloc(-5, 3); munit_log(MUNIT_LOG_INFO, "calloc 5");
	munit_assert_null(arr); free(arr);

	return MUNIT_OK;
}

static MunitResult
test_strdup(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;
	char *s = ft_strdup("string");

	munit_assert_string_equal(s, "string");
	munit_assert_char(*(s + 6), ==, 0); free(s);
	s = ft_strdup("");
	munit_assert_string_equal(s, "");
	munit_assert_char(*s, ==, 0); free(s);
	return MUNIT_OK;
}

static MunitResult
test_substr(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;

	munit_assert_string_equal(ft_substr("string", 0, 6), "string");
	munit_assert_string_equal(ft_substr("string", 3, 3), "ing");
	munit_assert_string_equal(ft_substr("string", 4, 100), "ng");
	munit_assert_string_equal(ft_substr("string", 6, 1), "");
	munit_assert_string_equal(ft_substr("string", 0, 0), "");
	munit_assert_string_equal(ft_substr("string", 101, 100), "");
	return MUNIT_OK;
}

static MunitResult
test_strjoin(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;

	munit_assert_string_equal(ft_strjoin("join", "string"), "joinstring");
	munit_assert_string_equal(ft_strjoin("foo", ""), "foo");
	munit_assert_string_equal(ft_strjoin("", "bar"), "bar");
	munit_assert_string_equal(ft_strjoin("", ""), "");
	return MUNIT_OK;
}

static MunitResult
test_strtrim(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;

	munit_assert_string_equal(ft_strtrim("   XXXstring", " X"), "string");
	munit_assert_string_equal(ft_strtrim("string xx x x xx", "x "), "string");
	munit_assert_string_equal(ft_strtrim("x   xx xxxx xx", " x"), "");
	munit_assert_string_equal(ft_strtrim("", "123"), "");
	munit_assert_string_equal(ft_strtrim("123", ""), "123");
	munit_assert_string_equal(ft_strtrim("bcadacb", "abc"), "d");
	return MUNIT_OK;
}

static MunitResult
test_split(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;

	char **arr = ft_split("   split   me   up    ", ' ');
	munit_assert_string_equal(arr[0], "split");
	munit_assert_string_equal(arr[1], "me");
	munit_assert_string_equal(arr[2], "up");
	munit_assert_null(arr[3]); free(arr);
	arr = ft_split("1----2--3----42", '-');
	for (int i = 0; i < 4; i++)
		munit_assert_int(sizeof(arr[i]), ==, sizeof(char*));
	munit_assert_string_equal(arr[3], "42"); free(arr);
	return MUNIT_OK;
}

static MunitResult
test_itoa(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;

	munit_assert_string_equal(ft_itoa(-9), "-9");
	munit_assert_string_equal(ft_itoa(123), "123");
	munit_assert_string_equal(ft_itoa(100000), "100000");
	munit_assert_string_equal(ft_itoa(INT_MIN), "-2147483648");
	munit_assert_string_equal(ft_itoa(INT_MAX), "2147483647");
	munit_assert_string_equal(ft_itoa(0), "0");
	return MUNIT_OK;
}

static char addOne(unsigned int i, char c) {return (i + c);}
static MunitResult
test_strmapi(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;

	char *s = ft_strmapi("1234", addOne);
	munit_assert_string_equal(s, "1357"); free(s);
	s = ft_strmapi("", addOne);
	munit_assert_string_equal(s, ""); free(s);
	return MUNIT_OK;
}

static void iterOne(unsigned int i, char * s) {*s += i;}
static MunitResult
test_striteri(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;

	char s0[] = "0000000000"; ft_striteri(s0, iterOne);
	munit_assert_string_equal(s0, "0123456789");
	char s1[] = ""; ft_striteri(s1, iterOne);
	munit_assert_string_equal(s1, "");
	char s2[] = "a"; ft_striteri(s2, iterOne);
	munit_assert_string_equal(s2, "a");
	return MUNIT_OK;
}

static MunitResult
test_putchar_fd(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;

	int fd = open("testfile", O_RDWR | O_CREAT, 0777);
	ft_putchar_fd('a', fd);
	lseek(fd, SEEK_SET, 0);
	char s[50] = {0}; read(fd, s, 2);
	munit_assert_char(s[0], ==, 'a');
	unlink("./testfile");

	fd = open("testfile", O_RDWR | O_CREAT, 0777);
	ft_putchar_fd('~', fd);
	lseek(fd, SEEK_SET, 0); read(fd, s, 2);
	munit_assert_char(s[0], ==, '~');
	unlink("./testfile");
	return MUNIT_OK;
}

static MunitResult
test_putstr_fd(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;

	int fd = open("testfile", O_RDWR | O_CREAT, 0777);
	ft_putstr_fd("string", fd);
	lseek(fd, SEEK_SET, 0);
	char s[50] = {0}; read(fd, s, 7);
	int i = 0; while (i <= 7)
		munit_logf(MUNIT_LOG_INFO, "%c", s[i++]);
	munit_assert_true(!strcmp(s, "string"));
	unlink("./testfile");

	return MUNIT_OK;
}

static MunitResult
test_lstnew(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;

	t_list *l = ft_lstnew((void*)100);
	munit_assert_ptr_equal(l->content, (void*)100);
	munit_assert_ptr_equal(l->next, 0);
	free(l);
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
	{"/ft_strchr", test_strchr, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{"/ft_strrchr", test_strrchr, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{"/ft_strncmp", test_strncmp, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{"/ft_memchr", test_memchr, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{"/ft_memcmp", test_memcmp, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{"/ft_strnstr", test_strnstr, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{"/ft_atoi", test_atoi, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{"/ft_calloc", test_calloc, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{"/ft_strdup", test_strdup, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{"/ft_substr", test_substr, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{"/ft_strjoin", test_strjoin, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{"/ft_strtrim", test_strtrim, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{"/ft_split", test_split, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{"/ft_itoa", test_itoa, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{"/ft_strmapi", test_strmapi, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{"/ft_striteri", test_striteri, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{"/ft_putchar_fd", test_putchar_fd, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{"/ft_putstr_fd", test_putstr_fd, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{"/ft_lstnew", test_lstnew, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
	{NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const	MunitSuite test_suite = {"", test_suite_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int	main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
	return munit_suite_main(&test_suite, (void*) "", argc, argv);
}
