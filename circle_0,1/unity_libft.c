#include "unity.h"
#include "../libft/libft.h"

void setUp(void) {}
void tearDown(void) {}

void test_isalpha() {
	char yes = 'a';
	char no = ' ';

	TEST_ASSERT_TRUE(ft_isalpha(yes));
	TEST_ASSERT_FALSE(ft_isalpha(no));
}

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_isalpha);
	return UNITY_END();
}