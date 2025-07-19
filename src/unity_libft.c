#include <string.h>
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
	char no1 = 128;
	char no2 = 255;

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

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_isalpha);
	RUN_TEST(test_isdigit);
	RUN_TEST(test_isalnum);
	RUN_TEST(test_isascii);
	RUN_TEST(test_isprint);
	RUN_TEST(test_strlen);
	RUN_TEST(test_memset);

	return UNITY_END();
}
