#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "munit.h"
#include "../printf/ft_printf.h"

int	pipefd[2];
int	saved_stdout = -1;
char	buf[256] = {0};

static void*
test_setup(const MunitParameter params[], void* user_data) {
  	(void) params;
  	(void) user_data;

	saved_stdout = dup(fileno(stdout));
	dup2(pipefd[1], fileno(stdout));

	long flags = fcntl(pipefd[0], F_GETFL);
   	flags |= O_NONBLOCK;
   	fcntl(pipefd[0], F_SETFL, flags);

	return (void*) (uintptr_t) 0xdeadbeef;
}

static void
test_teardown(void* fixture) {

	dup2(saved_stdout, fileno(stdout));
	close(saved_stdout);
	saved_stdout = -1;
	close(pipefd[0]);
	close(pipefd[1]);
	munit_assert_ptr_equal(fixture, (void*)(uintptr_t)0xdeadbeef);
}

char *read_stdout_buf(void)
{
	fflush(stdout);
	bzero(buf, 256);
	int ret = read(pipefd[0], buf, 255);
	if (ret != -1)
		buf[ret] = '\0';
	return (buf);
}

static MunitResult
test_char(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;

	printf("\n");

	int u_count = ft_printf("%5c|\n", 'x');
	int o_count = printf("%5c|\n", 'x');
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%-9c|\n", 'W');
	o_count = printf("%-9c|\n", 'W');
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%-------11c|\n", 'p');
	o_count = printf("%-------11c|\n", 'p');
	munit_assert_int(u_count, ==, o_count);

	return MUNIT_OK;
}

static MunitResult
test_str(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;

	char *s = "string";

	printf("\n");
	int u_count = ft_printf("%-10s|1\n", s);
	int o_count = printf("%-10s|1\n", s);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%1s|2\n", s);
	o_count = printf("%1s|2\n", s);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%------20s|3\n", s);
	o_count = printf("%------20s|3\n", s);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%13sstring |4\n", s);
	o_count = printf("%13sstring |4\n", s);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%.3s|5\n", s);
	o_count = printf("%.3s|5\n", s);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%.0s|6\n", s);
	o_count = printf("%.0s|6\n", s);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%7.3s|7\n", s);
	o_count = printf("%7.3s|7\n", s);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%2.5s|8\n", s);
	o_count = printf("%2.5s|8\n", s);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%12.0s|9\n", s);
	o_count = printf("%12.0s|9\n", s);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%14.14s|10\n", s);
	o_count = printf("%14.14s|10\n", s);
	munit_assert_int(u_count, ==, o_count);

	return MUNIT_OK;
}

static MunitResult
test_int_0(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;

	printf("\n");
	int i = 0;

	int u_count = ft_printf("%7i|1\n", i);
	int o_count = printf("%7d|1\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%1i|2\n", i);
	o_count = printf("%1d|2\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%.8i|3\n", i);
	o_count = printf("%.8d|3\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%.8i|4\n", i);
	o_count = printf("%.8d|4\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%2.9i|5\n", i);
	o_count = printf("%2.9d|5\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%5.4i|6\n", i);
	o_count = printf("%5.4d|6\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%8.0i|7\n", i);
	o_count = printf("%8.0d|7\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%-8i|8\n", i);
	o_count = printf("%-8d|8\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%-1i|9\n", i);
	o_count = printf("%-1d|9\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%-.9i|10\n", i);
	o_count = printf("%-.9d|10\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%-.1i|11\n", i);
	o_count = printf("%-.1d|11\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%-8.3i|12\n", i);
	o_count = printf("%-8.3d|12\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%-3.8i|13\n", i);
	o_count = printf("%-3.8d|13\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%-9.9i|14\n", i);
	o_count = printf("%-9.9d|14\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%09i|15\n", i);
	o_count = printf("%09d|15\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%0.10i|16\n", i);
	o_count = printf("%0.10d|16\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%09.3i|17\n", i);
	o_count = printf("%09.3d|17\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%02.7i|18\n", i);
	o_count = printf("%02.7d|18\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%04.4i|19\n", i);
	o_count = printf("%04.4d|19\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%+2.3i|20\n", i);
	o_count = printf("%+2.3d|20\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%+7.4i|21\n", i);
	o_count = printf("%+7.4d|21\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("% 3.4i|22\n", i);
	o_count = printf("% 3.4d|22\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("% 8.5i|23\n", i);
	o_count = printf("% 8.5d|23\n", i);
	munit_assert_int(u_count, ==, o_count);

	return MUNIT_OK;
}

static MunitResult
test_int_min(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;

	printf("\n");
	int i = INT_MIN;

	int u_count = ft_printf("%20i|1\n", i);
	int o_count = printf("%20d|1\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%1i|2\n", i);
	o_count = printf("%1d|2\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%.15i|3\n", i);
	o_count = printf("%.15d|3\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%.2i|4\n", i);
	o_count = printf("%.2d|4\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%14.19i|5\n", i);
	o_count = printf("%14.19d|5\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%15.14i|6\n", i);
	o_count = printf("%15.14d|6\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%15.0i|7\n", i);
	o_count = printf("%15.0d|7\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%15.0i|7\n", i);
	o_count = printf("%15.0d|7\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%-12d|8\n", i);
	o_count = printf("%-12d|8\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%-14.12d|9\n", i);
	o_count = printf("%-14.12d|9\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%-14.17d|9\n", i);
	o_count = printf("%-14.17d|9\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%15d|10\n", i);
	o_count = printf("%15d|10\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%015d|10\n", i);
	o_count = printf("%015d|10\n", i);
	munit_assert_int(u_count, ==, o_count);

	return MUNIT_OK;
}

static MunitResult
test_int_max(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;

	printf("\n");
	int i = INT_MAX;

	int u_count = ft_printf("%20i|1\n", i);
	int o_count = printf("%20d|1\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%1i|2\n", i);
	o_count = printf("%1d|2\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%.14i|3\n", i);
	o_count = printf("%.14d|3\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%.1i|4\n", i);
	o_count = printf("%.1d|4\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%12.19i|5\n", i);
	o_count = printf("%12.19d|5\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%17.11i|6\n", i);
	o_count = printf("%17.11d|6\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%15.0i|7\n", i);
	o_count = printf("%15.0d|7\n", i);
	munit_assert_int(u_count, ==, o_count);

	return MUNIT_OK;
}

static MunitResult
test_int_rand(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;

	printf("\n");
	int i = munit_rand_int_range(INT_MIN, INT_MAX);

	int u_count = ft_printf("%7i|1\n", i);
	int o_count = printf("%7d|1\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%1i|2\n", i);
	o_count = printf("%1d|2\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%.8i|3\n", i);
	o_count = printf("%.8d|3\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%.8i|4\n", i);
	o_count = printf("%.8d|4\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%2.9i|5\n", i);
	o_count = printf("%2.9d|5\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%5.4i|6\n", i);
	o_count = printf("%5.4d|6\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%8.0i|7\n", i);
	o_count = printf("%8.0d|7\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%-8i|8\n", i);
	o_count = printf("%-8d|8\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%-1i|9\n", i);
	o_count = printf("%-1d|9\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%-.9i|10\n", i);
	o_count = printf("%-.9d|10\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%-.1i|11\n", i);
	o_count = printf("%-.1d|11\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%-8.3i|12\n", i);
	o_count = printf("%-8.3d|12\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%-3.8i|13\n", i);
	o_count = printf("%-3.8d|13\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%-9.9i|14\n", i);
	o_count = printf("%-9.9d|14\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%09i|15\n", i);
	o_count = printf("%09d|15\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%0.10i|16\n", i);
	o_count = printf("%0.10d|16\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%09.3i|17\n", i);
	o_count = printf("%09.3d|17\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%02.7i|18\n", i);
	o_count = printf("%02.7d|18\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%04.4i|19\n", i);
	o_count = printf("%04.4d|19\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%+2.3i|20\n", i);
	o_count = printf("%+2.3d|20\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%+7.4i|21\n", i);
	o_count = printf("%+7.4d|21\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("% 3.4i|22\n", i);
	o_count = printf("% 3.4d|22\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("% 8.5i|23\n", i);
	o_count = printf("% 8.5d|23\n", i);
	munit_assert_int(u_count, ==, o_count);

	return MUNIT_OK;
}

static MunitResult
test_uint(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;

	printf("\n");
	int u_count = ft_printf("%u\n", 0);
	int o_count = printf("%u\n", 0);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%u\n", UINT_MAX);
	o_count = printf("%u\n", UINT_MAX);
	munit_assert_int(u_count, ==, o_count);

	return MUNIT_OK;
}

static MunitResult
test_percent(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;

	printf("\n");
	int u_count = ft_printf("%%\n");
	int o_count = printf("%%\n");
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%s%%ha\n", "ha");
	o_count = printf("%s%%ha\n", "ha");
	munit_assert_int(u_count, ==, o_count);

	return MUNIT_OK;
}

static MunitResult
test_hexa(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;

	printf("\n");
	int u_count = ft_printf("%x\n", 123456);
	int o_count = printf("%x\n", 123456);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("test%x%Xtest\n", 42, 6666);
	o_count = printf("test%x%Xtest\n", 42, 6666);
	munit_assert_int(u_count, ==, o_count);

	return MUNIT_OK;
}

static MunitResult
test_ptr(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;

	int i = 1; int j = 42; char c = 'x'; char *s = "ghhhhh";

	printf("\n");
	int u_count = ft_printf("%p\n", &i);
	int o_count = printf("%p\n", &i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("1 %p\n2 %p\n3 %p\n", &j, &c, &s);
	o_count = printf("1 %p\n2 %p\n3 %p\n", &j, &c, &s);
	munit_assert_int(u_count, ==, o_count);

	return MUNIT_OK;
}

static MunitResult
test_mix(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;

	printf("\n");
	int u_count = ft_printf("%%%%%d%%%%%%%ssss%Xx%x%u%%sss%%%%%%%c%s %p %%\n", 2, "string", 400, 200, UINT_MAX - 1, 'a', "///", "yes" );
	int o_count = printf("%%%%%d%%%%%%%ssss%Xx%x%u%%sss%%%%%%%c%s %p %%\n", 2, "string", 400, 200, UINT_MAX - 1, 'a', "///", "yes" );
	munit_assert_int(u_count, ==, o_count);

	return MUNIT_OK;
}

static	MunitTest test_suite_tests[] = {
	{"/print char", test_char, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{"/print str", test_str, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{"/print int_0", test_int_0, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{"/print int_min", test_int_min, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{"/print int_max", test_int_max, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{"/print int_rand", test_int_rand, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{"/print uint", test_uint, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{"/print percent", test_percent, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{"/print hexa", test_hexa, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{"/print ptr", test_ptr, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{"/print mix", test_mix, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const	MunitSuite test_suite = {"", test_suite_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int	main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
	return munit_suite_main(&test_suite, (void*) "", argc, argv);
}
