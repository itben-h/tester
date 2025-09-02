#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include "../inc/unity.h"
#include "../build/libft.h"

void setUp(void) {}
void tearDown(void) {}

void test_isalpha() {
	char yes1 = 'a';
	char yes2 = 'Y';
	char no1 = ' ';
	char no2 = '~';

	TEST_ASSERT_TRUE(ft_isalpha(yes1));
	TEST_ASSERT_TRUE(ft_isalpha(yes2));
	TEST_ASSERT_FALSE(ft_isalpha(no1));
	TEST_ASSERT_FALSE(ft_isalpha(no2));
}

void test_isdigit() {
	char yes1 = '5';
	char yes2 = '9';
	char no1 = ' ';
	char no2 = 'a';

	TEST_ASSERT_TRUE(ft_isdigit(yes1));
	TEST_ASSERT_TRUE(ft_isdigit(yes2));
	TEST_ASSERT_FALSE(ft_isdigit(no1));
	TEST_ASSERT_FALSE(ft_isdigit(no2));
}

void test_isalnum() {
	char yes1 = '9';
	char yes2 = '3';
	char no1 = 1;
	char no2 = 127;

	TEST_ASSERT_TRUE(ft_isalnum(yes1));
	TEST_ASSERT_TRUE(ft_isalnum(yes2));
	TEST_ASSERT_FALSE(ft_isalnum(no1));
	TEST_ASSERT_FALSE(ft_isalnum(no2));
}

void test_isascii() {
	char yes1 = 0;
	char yes2 = 31;
	unsigned char no1 = 128;
	unsigned char no2 = 255;

	TEST_ASSERT_TRUE(ft_isascii(yes1));
	TEST_ASSERT_TRUE(ft_isascii(yes2));
	TEST_ASSERT_FALSE(ft_isascii(no1));
	TEST_ASSERT_FALSE(ft_isascii(no2));
}

void test_isprint() {
	char yes1 = '~';
	char yes2 = '1';
	char no1 = 17;
	char no2 = 127;

	TEST_ASSERT_TRUE(ft_isprint(yes1));
	TEST_ASSERT_TRUE(ft_isprint(yes2));
	TEST_ASSERT_FALSE(ft_isprint(no1));
	TEST_ASSERT_FALSE(ft_isprint(no2));
}

void test_strlen() {
	char *str = "string";
	char *longStr = "longstring";
	char *longestStr = "looooooooooooooooooooooooooooooooooooooong";

	TEST_ASSERT_EQUAL(ft_strlen(str), 6);
	TEST_ASSERT_EQUAL(ft_strlen(longStr), 10);
	TEST_ASSERT_EQUAL(ft_strlen(longestStr), 42);
}

void test_memset() {
	char str1[] = "this is a string";
	char str2[] = "this is a string";
	int arr1[10];
	int arr2[10];

	TEST_ASSERT_EQUAL_PTR(ft_memset(str1 + 4, '$', 5 * sizeof(char)), str1 + 4);
	TEST_ASSERT_EQUAL_PTR(ft_memset(arr1, -1, 10 * sizeof(arr1[0])), arr1);

	memset(str2 + 4, '$', 5 * sizeof(char));
	memset(arr2, -1, 10 * sizeof(arr2[0]));
	TEST_ASSERT_EQUAL_STRING(str1, str2);
	TEST_ASSERT_EQUAL_INT_ARRAY(arr1, arr2, 10);
}

void test_bzero() {
	char *str1a = "string";
	char *str1b = "string";
	char *str2 = "test-test";

	ft_bzero(str1a, 5);
	bzero(str1b, 5);
	TEST_ASSERT_EQUAL_STRING(str1a, str1b);
	ft_bzero(str2, 2);
	TEST_ASSERT_EQUAL_STRING(str2, "");
	ft_bzero(str2, 999);
	TEST_ASSERT_EQUAL_STRING(str2, "");
}

void test_memcpy() {
	char blank1[5] = "";
	char blank2[5] = "";
	char dest1[50] = "Replace Me";
	char dest2[50] = "Replace Me";
	char src1[50] = "Get Replaced";
	char src2[50] = "Get Replaced";
	int arr1[5] = {1, 2, 3, 4, 5};
	int arr2[5] = {1, 2, 3, 4, 5};
	int arr_s[3] = {6, 7, 8};

	void* res = ft_memcpy(blank1, blank1, 3);
	TEST_ASSERT_EQUAL_PTR(res, blank1);
	TEST_ASSERT_EQUAL_STRING(res, memcpy(blank2, blank2, 3));
	res = ft_memcpy(dest1, src1, 5);
	TEST_ASSERT_EQUAL_PTR(res, dest1);
	TEST_ASSERT_EQUAL_STRING(res, memcpy(dest2, src2, 5));
	ft_memcpy(arr1, arr_s, 2);
	memcpy(arr2, arr_s, 2);
	TEST_ASSERT_EQUAL_INT_ARRAY(arr1, arr2, 5);
}

void test_memmove() {
	char blank1[5] = "";
	char blank2[5] = "";
	char dest1[50] = "Replace Me";
	char dest2[50] = "Replace Me";
	char src1[50] = "Get Replaced";
	char src2[50] = "Get Replaced";
	char overlap1[50] = "overlap";
	char overlap2[50] = "overlap";
	int arr1[9] = {1, 2, 3, 4, 5};
	int arr2[9] = {1, 2, 3, 4, 5};

	TEST_ASSERT_EQUAL_STRING(ft_memmove(blank1, blank1, 3), memmove(blank2, blank2, 3));
	TEST_ASSERT_EQUAL_STRING(ft_memmove(dest1, src1, 5), memmove(dest2, src2, 5));
	TEST_ASSERT_EQUAL_STRING(ft_memmove(overlap1 + 4, overlap1, 7), memmove(overlap2 + 4, overlap2, 7));
	TEST_PRINTF("Memmoved String is %s", overlap1);
	ft_memmove(arr1 + 3, arr1, 4);
	memmove(arr2 + 3, arr2, 4);
	TEST_ASSERT_EQUAL_INT_ARRAY(arr1, arr2, 5);
	TEST_PRINTF("Memmoved elem at Index %d is: %d", 3, arr1[3]);
}

void test_strlcpy() {
	char dest[] = "dest";
	char src[] = "src";

	ft_strlcpy(dest, src, 2);
	TEST_ASSERT_EQUAL_STRING(dest, "s");
	ft_strlcpy(dest, src, 4);
	TEST_ASSERT_EQUAL_STRING(dest, "src");
	TEST_ASSERT_EQUAL_INT(ft_strlcpy(dest, src, 0), 3);
}

void test_strlcat() {
	char dest[10] = "dest";
	char src[10] = "src";

	TEST_ASSERT_EQUAL_INT(ft_strlcat(dest, src, 0), 3);
	ft_strlcat(dest, src, 6);
	TEST_ASSERT_EQUAL_STRING(dest, "dests");
	ft_strlcat(dest, src, 10);
	TEST_ASSERT_EQUAL_STRING(dest, "destssrc");
	TEST_ASSERT_EQUAL_INT(ft_strlcat(dest, src, 12), 11);
	TEST_PRINTF("Final strlcat is %s", dest);
}

void test_toupper() {
	char lower = 'b';
	char upper = 'Y';
	char none = ' ';

	TEST_ASSERT_EQUAL_CHAR(ft_toupper(lower), 'B');
	TEST_ASSERT_EQUAL_CHAR(ft_toupper(upper), 'Y');
	TEST_ASSERT_EQUAL_CHAR(ft_toupper(none), ' ');
}

void test_tolower() {
	char lower = 'a';
	char upper = 'Z';
	char none = '~';

	TEST_ASSERT_EQUAL_CHAR(ft_tolower(lower), 'a');
	TEST_ASSERT_EQUAL_CHAR(ft_tolower(upper), 'z');
	TEST_ASSERT_EQUAL_CHAR(ft_tolower(none), '~');
}

void test_strchr() {
	char *s = "Bicycle";
	char *empty = "";

	TEST_ASSERT_EQUAL_PTR(ft_strchr(s, 'B'), s);
	TEST_ASSERT_EQUAL_PTR(ft_strchr(s, 'c'), s + 2);
	TEST_ASSERT_EQUAL_PTR(ft_strchr(s, 0), s + ft_strlen(s));
	TEST_ASSERT_EQUAL_PTR(ft_strchr(s, 'X'), 0);
	TEST_ASSERT_EQUAL_PTR(ft_strchr(s, 'B' + 256), s);
	TEST_ASSERT_EQUAL_PTR(ft_strchr(empty, 'B'), 0);
	TEST_ASSERT_EQUAL_PTR(ft_strchr(empty, 0), empty);
}

void test_strrchr() {
	char *s = "Bicycle";
	char *empty = "";

	TEST_ASSERT_EQUAL_PTR(ft_strrchr(s, 'B'), s);
	TEST_ASSERT_EQUAL_PTR(ft_strrchr(s, 'c'), s + 4);
	TEST_ASSERT_EQUAL_PTR(ft_strrchr(s, 0), s + ft_strlen(s));
	TEST_ASSERT_EQUAL_PTR(ft_strrchr(s, 'X'), 0);
	TEST_ASSERT_EQUAL_PTR(ft_strrchr(s, 'B' + 256), s);
	TEST_ASSERT_EQUAL_PTR(ft_strrchr(empty, 'B'), 0);
	TEST_ASSERT_EQUAL_PTR(ft_strrchr(empty, 0), empty);
}

void test_strncmp() {
	TEST_ASSERT_EQUAL_INT(ft_strncmp("", "", 100), 0);
	TEST_ASSERT_EQUAL_INT(ft_strncmp("abc", "abc", 3), 0);
	TEST_ASSERT_EQUAL_INT(ft_strncmp("one", "two", 0), 0);
	TEST_ASSERT_LESS_THAN_INT(ft_strncmp("1", "", 1), 0);
	TEST_ASSERT_GREATER_THAN_INT(ft_strncmp("", "1", 1), 0);
	TEST_ASSERT_LESS_THAN_INT(ft_strncmp("abc", "abb", 3), 0);
	TEST_ASSERT_GREATER_THAN_INT(ft_strncmp("abC", "abc", 3), 0);
}

void test_memchr() {
	char *s = "Bicycle";
	char arr[] = {0, 1, 2, 3};

	TEST_ASSERT_EQUAL_PTR(ft_memchr(s, 'B', 1), s);
	TEST_ASSERT_EQUAL_PTR(ft_memchr(s, 'c', 3), s + 2);
	TEST_ASSERT_EQUAL_PTR(ft_memchr(s, 'X', 4), 0);
	TEST_ASSERT_EQUAL_PTR(ft_memchr(s, 'B', 0), 0);
	TEST_ASSERT_EQUAL_PTR(ft_memchr(arr, 0, 10), arr);
	TEST_ASSERT_EQUAL_PTR(ft_memchr(arr, 2, 4), arr + 2);
	TEST_ASSERT_EQUAL_PTR(ft_memchr(arr, 'B', 4), 0);
}

void test_memcmp() {
	char s1[] = {3, 200, 42, 0, -1};
	char s1_1[] = {3, 200, 42, 0, -1};
	char s2[] = {1, 1, 1, 1, 42, 0, 0};
	char s3[] = {1, 1, 1, 1, 123, 0, 0};
	char s4[10] = "string";
	char s4x[10] = "strimg";

	TEST_ASSERT_EQUAL_INT(ft_memcmp(s1, s1_1, 3), 0);
	TEST_ASSERT_LESS_THAN_INT(ft_memcmp(s1, s2, 5), 0);
	TEST_ASSERT_GREATER_THAN_INT(ft_memcmp(s2, s1, 5), 0);
	TEST_ASSERT_EQUAL_INT(ft_memcmp(s1, s2, 0), 0);
	TEST_ASSERT_EQUAL_INT(ft_memcmp(s2, s3, 2), 0);
	TEST_ASSERT_GREATER_THAN_INT(ft_memcmp(s2, s3, 7), 0);
	TEST_ASSERT_EQUAL_INT(ft_memcmp(s4, s4x, 3), 0);
	TEST_ASSERT_LESS_THAN_INT(ft_memcmp(s4, s4x, 6), 0);
}

void test_strnstr() {
	char *s1 = "string";
	char *s2 = "abcdefghijk";
	char *empty = "";

	TEST_ASSERT_EQUAL_PTR(ft_strnstr(s1, "string", 6), s1);
	TEST_ASSERT_EQUAL_PTR(ft_strnstr(s1, "string", 2), 0);
	TEST_ASSERT_EQUAL_PTR(ft_strnstr(s1, "", 6), s1);
	TEST_ASSERT_EQUAL_PTR(ft_strnstr(s2, "def", 10), s2 + 3);
	TEST_ASSERT_EQUAL_PTR(ft_strnstr(s2, "e", 10), s2 + 4);
	TEST_ASSERT_EQUAL_PTR(ft_strnstr(s2, "def", 4), 0);
	TEST_ASSERT_EQUAL_PTR(ft_strnstr(empty, "", 3), empty);
	TEST_ASSERT_EQUAL_PTR(ft_strnstr(empty, "a", 3), 0);
}

void test_atoi() {
	char s[] = {9, 10, 13, 10, 32, '5'};

	TEST_ASSERT_EQUAL_INT(ft_atoi("abc"), 0);
	TEST_ASSERT_EQUAL_INT(ft_atoi("3"), 3);
	TEST_ASSERT_EQUAL_INT(ft_atoi("-9"), -9);
	TEST_ASSERT_EQUAL_INT(ft_atoi("     +9"), 9);
	TEST_ASSERT_EQUAL_INT(ft_atoi(" -+9"), 0);
	TEST_ASSERT_EQUAL_INT(ft_atoi(" +  9"), 0);
	TEST_ASSERT_EQUAL_INT(ft_atoi("   -00012009"), -12009);
	TEST_ASSERT_EQUAL_INT(ft_atoi("123456789"), 123456789);
	TEST_ASSERT_EQUAL_INT(ft_atoi(s), 5);
}

void test_calloc() {
	void *arr = ft_calloc(3, 2);
	char c[] = {0, 0, 0, 0, 0, 0};

	TEST_ASSERT_EQUAL_INT(memcmp(arr, c, 6), 0); free(arr);
	arr = ft_calloc(5, 25);
	TEST_ASSERT_NOT_NULL(arr); free(arr);
	arr = ft_calloc(4294967295, 2);
	TEST_ASSERT_NULL(arr); free(arr);
	TEST_PRINTF("Note that 303-308 is '''optional''' calloc");
	arr = ft_calloc(0, -5);
	TEST_ASSERT_NOT_NULL(arr); free(arr);
	arr = ft_calloc(-5, 0);
	TEST_ASSERT_NOT_NULL(arr); free(arr);
	arr = ft_calloc(-5, 3);
	TEST_ASSERT_NULL(arr); free(arr);
}

void test_strdup() {
	char *s = ft_strdup("string");

	TEST_ASSERT_EQUAL_STRING(s, "string");
	TEST_ASSERT_EQUAL_CHAR(*(s + 6), 0); free(s);
	s = ft_strdup("");
	TEST_ASSERT_EQUAL_STRING(s, "");
	TEST_ASSERT_EQUAL_CHAR(*s, 0); free(s);
}

void test_substr() {
	TEST_ASSERT_EQUAL_STRING(ft_substr("string", 0, 6), "string");
	TEST_ASSERT_EQUAL_STRING(ft_substr("string", 3, 3), "ing");
	TEST_ASSERT_EQUAL_STRING(ft_substr("string", 4, 100), "ng");
	TEST_ASSERT_EQUAL_STRING(ft_substr("string", 6, 1), "");
	TEST_ASSERT_EQUAL_STRING(ft_substr("string", 0, 0), "");
	TEST_ASSERT_EQUAL_STRING(ft_substr("string", 101, 100), "");
}

void test_strjoin() {
	TEST_ASSERT_EQUAL_STRING(ft_strjoin("join", "string"), "joinstring");
	TEST_ASSERT_EQUAL_STRING(ft_strjoin("foo", ""), "foo");
	TEST_ASSERT_EQUAL_STRING(ft_strjoin("", "bar"), "bar");
	TEST_ASSERT_EQUAL_STRING(ft_strjoin("", ""), "");
}

void test_strtrim() {
	TEST_ASSERT_EQUAL_STRING(ft_strtrim("   XXXstring", " X"), "string");
	TEST_ASSERT_EQUAL_STRING(ft_strtrim("string xx x x xx", "x "), "string");
	TEST_ASSERT_EQUAL_STRING(ft_strtrim("x   xx xxxx xx", " x"), "");
	TEST_ASSERT_EQUAL_STRING(ft_strtrim("", "123"), "");
	TEST_ASSERT_EQUAL_STRING(ft_strtrim("123", ""), "123");
	TEST_ASSERT_EQUAL_STRING(ft_strtrim("bcadacb", "abc"), "d");
}

void test_split() {
	char **arr = ft_split("   split   me   up    ", ' ');
	TEST_ASSERT_EQUAL_STRING(arr[0], "split");
	TEST_ASSERT_EQUAL_STRING(arr[1], "me");
	TEST_ASSERT_EQUAL_STRING(arr[2], "up");
	TEST_ASSERT_NULL(arr[3]); free(arr);

	arr = ft_split("1----2--3----42", '-');
	for (int i = 0; i < 4; i++)
		TEST_ASSERT_EQUAL_INT(sizeof(arr[i]), sizeof(char*));
	TEST_ASSERT_EQUAL_STRING(arr[3], "42"); free(arr);
}

void test_itoa() {
	TEST_ASSERT_EQUAL_STRING(ft_itoa(-9), "-9");
	TEST_ASSERT_EQUAL_STRING(ft_itoa(123), "123");
	TEST_ASSERT_EQUAL_STRING(ft_itoa(100000), "100000");
	TEST_ASSERT_EQUAL_STRING(ft_itoa(INT_MIN), "-2147483648");
	TEST_ASSERT_EQUAL_STRING(ft_itoa(INT_MAX), "2147483647");
	TEST_ASSERT_EQUAL_STRING(ft_itoa(0), "0");
}

static char addOne(unsigned int i, char c) {return (i + c);}
void test_strmapi() {
	char *s = ft_strmapi("1234", addOne);
	TEST_ASSERT_EQUAL_STRING(s, "1357"); free(s);
	s = ft_strmapi("", addOne);
	TEST_ASSERT_EQUAL_STRING(s, ""); free(s);
}

static void iterOne(unsigned int i, char * s) {*s += i;}
void test_striteri() {
	char s0[] = "0000000000"; ft_striteri(s0, iterOne);
	TEST_ASSERT_EQUAL_STRING(s0, "0123456789");
	char s1[] = ""; ft_striteri(s1, iterOne);
	TEST_ASSERT_EQUAL_STRING(s1, "");
	char s2[] = "a"; ft_striteri(s2, iterOne);
	TEST_ASSERT_EQUAL_STRING(s2, "a");
}

void test_putchar_fd() {
	int fd = open("testfile", O_RDWR | O_CREAT, 0777);
	ft_putchar_fd('a', fd);
	lseek(fd, SEEK_SET, 0);
	char s[50] = {0}; read(fd, s, 2);
	TEST_ASSERT_EQUAL_CHAR(s[0], 'a');
	unlink("./testfile");

	fd = open("testfile", O_RDWR | O_CREAT, 0777);
	ft_putchar_fd('~', fd);
	lseek(fd, SEEK_SET, 0); read(fd, s, 2);
	TEST_ASSERT_EQUAL_CHAR(s[0], '~');
	unlink("./testfile");
}

void test_putstr_fd() {
	int fd = open("testfile", O_RDWR | O_CREAT, 0777);
	ft_putstr_fd("string", fd);
	lseek(fd, SEEK_SET, 0);
	char s[50] = {0}; read(fd, s, 7);
	int i = 0; while (i <= 6)
		TEST_PRINTF("%c", s[i++]);
	TEST_ASSERT_TRUE(!strcmp(s, "string"));
	unlink("./testfile");
}

void test_lstnew() {
	t_list *l = ft_lstnew((void*)100);
	TEST_ASSERT_EQUAL_PTR(l->content, (void*)100);
	TEST_ASSERT_EQUAL_PTR(l->next, 0);
	free(l);
}

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_isalpha);
	RUN_TEST(test_isdigit);
	RUN_TEST(test_isalnum);
	RUN_TEST(test_isascii);
	RUN_TEST(test_isprint);
	RUN_TEST(test_strlen);
	RUN_TEST(test_memset);
	RUN_TEST(test_memcpy);
	RUN_TEST(test_memmove);
	RUN_TEST(test_strlcpy);
	RUN_TEST(test_strlcat);
	RUN_TEST(test_toupper);
	RUN_TEST(test_tolower);
	RUN_TEST(test_strchr);
	RUN_TEST(test_strrchr);
	RUN_TEST(test_strncmp);
	RUN_TEST(test_memchr);
	RUN_TEST(test_memcmp);
	RUN_TEST(test_strnstr);
	RUN_TEST(test_atoi);
	RUN_TEST(test_calloc);
	RUN_TEST(test_strdup);
	RUN_TEST(test_substr);
	RUN_TEST(test_strjoin);
	RUN_TEST(test_strtrim);
	RUN_TEST(test_split);
	RUN_TEST(test_itoa);
	RUN_TEST(test_strmapi);
	RUN_TEST(test_striteri);
	RUN_TEST(test_putchar_fd);
	RUN_TEST(test_putstr_fd);
	RUN_TEST(test_lstnew);

	return UNITY_END();
}
