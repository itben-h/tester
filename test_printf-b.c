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
	
	u_count = ft_printf("%-10s|\n", (char*)NULL);
	o_count = printf("%-10s|\n", (char*)NULL);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%12.7s|\n", (char*)NULL);
	o_count = printf("%12.7s|\n", (char*)NULL);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%3.5s|\n", (char*)NULL);
	o_count = printf("%3.5s|\n", (char*)NULL);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%.s|\n", (char*)NULL);
	o_count = printf("%.s|\n", (char*)NULL);
	munit_assert_int(u_count, ==, o_count);

	return MUNIT_OK;
}

static MunitResult
test_int_i(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;

	printf("\n");
	int i = munit_rand_int_range(1, 9);

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
	
	u_count = ft_printf("%- - -- -- -1.20i|24\n", i);
	o_count = printf("%- - -- -- -1.20d|24\n", i);
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

	u_count = ft_printf("%-12d|8\n", i);
	o_count = printf("%-12d|8\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%-14.12d|9\n", i);
	o_count = printf("%-14.12d|9\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%-14.17d|10\n", i);
	o_count = printf("%-14.17d|10\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%015d|11\n", i);
	o_count = printf("%015d|11\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%014.18d|12\n", i);
	o_count = printf("%014.18d|12\n", i);
	
	u_count = ft_printf("%016.13d|13\n", i);
	o_count = printf("%016.13d|13\n", i);
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
	
	u_count = ft_printf("%-12d|8\n", i);
	o_count = printf("%-12d|8\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%-14.12d|9\n", i);
	o_count = printf("%-14.12d|9\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%-14.17d|10\n", i);
	o_count = printf("%-14.17d|10\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%015d|11\n", i);
	o_count = printf("%015d|11\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%014.18d|12\n", i);
	o_count = printf("%014.18d|12\n", i);
	
	u_count = ft_printf("%016.13d|13\n", i);
	o_count = printf("%016.13d|13\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("% 12.19i|14\n", i);
	o_count = printf("% 12.19d|14\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("% 17.11i|15\n", i);
	o_count = printf("% 17.11d|15\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%+12.19i|16\n", i);
	o_count = printf("%+12.19d|16\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%+17.11i|17\n", i);
	o_count = printf("%+17.11d|17\n", i);
	munit_assert_int(u_count, ==, o_count);

	return MUNIT_OK;
}

static MunitResult
test_uint(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;

	printf("\n");
	unsigned int i = UINT_MAX;
	
	unsigned int u_count = ft_printf("%20u|1\n", i);
	unsigned int o_count = printf("%20u|1\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%1u|2\n", i);
	o_count = printf("%1u|2\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%.14u|3\n", i);
	o_count = printf("%.14u|3\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%.1u|4\n", i);
	o_count = printf("%.1u|4\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%12.19u|5\n", i);
	o_count = printf("%12.19u|5\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%17.11u|6\n", i);
	o_count = printf("%17.11u|6\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%15.0u|7\n", i);
	o_count = printf("%15.0u|7\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%-12u|8\n", i);
	o_count = printf("%-12u|8\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%-14.12u|9\n", i);
	o_count = printf("%-14.12u|9\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%-14.17u|10\n", i);
	o_count = printf("%-14.17u|10\n", i);
	munit_assert_int(u_count, ==, o_count);

	u_count = ft_printf("%015u|11\n", i);
	o_count = printf("%015u|11\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%014.18u|12\n", i);
	o_count = printf("%014.18u|12\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%016.13u|13\n", i);
	o_count = printf("%016.13u|13\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%000000000000000000000000000017.11u|13\n", i);
	o_count = printf("%000000000000000000000000000017.11u|13\n", i);
	munit_assert_int(u_count, ==, o_count);

	return MUNIT_OK;
}

static MunitResult
test_hexa_x(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;

	printf("\n");
	int i = 123456;
	
	int u_count = ft_printf("%7x|1\n", i);
	int o_count = printf("%7x|1\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%.7x|2\n", i);
	o_count = printf("%.7x|2\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%7.9x|3\n", i);
	o_count = printf("%7.9x|3\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%9.7x|4\n", i);
	o_count = printf("%9.7x|4\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%-9.7x|5\n", i);
	o_count = printf("%-9.7x|5\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%010x|6\n", i);
	o_count = printf("%010x|6\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%010.7x|7\n", i);
	o_count = printf("%010.7x|7\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%#x|8\n", i);
	o_count = printf("%#x|8\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%#10x|9\n", i);
	o_count = printf("%#10x|9\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%#.9x|10\n", i);
	o_count = printf("%#.9x|10\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%#9.12x|11\n", i);
	o_count = printf("%#9.12x|11\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%#13.8x|12\n", i);
	o_count = printf("%#13.8x|12\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%#09.14x|13\n", i);
	o_count = printf("%#09.14x|13\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%#012.8x|14\n", i);
	o_count = printf("%#012.8x|14\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%-#8.13x|15\n", i);
	o_count = printf("%-#8.13x|15\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%-#14.9x|16\n", i);
	o_count = printf("%-#14.9x|16\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%#0x|17\n", i);
	o_count = printf("%#0x|17\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%#0#######0###0###010.15x|18\n", i);
	o_count = printf("%#0#######0###0###010.15x|18\n", i);
	munit_assert_int(u_count, ==, o_count);

	return MUNIT_OK;
}

static MunitResult
test_hexa_X(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;

	printf("\n");
	int i = 123456;
	
	int u_count = ft_printf("%7X|1\n", i);
	int o_count = printf("%7X|1\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%.7X|2\n", i);
	o_count = printf("%.7X|2\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%7.9X|3\n", i);
	o_count = printf("%7.9X|3\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%9.7X|4\n", i);
	o_count = printf("%9.7X|4\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%-9.7X|5\n", i);
	o_count = printf("%-9.7X|5\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%010X|6\n", i);
	o_count = printf("%010X|6\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%010.7X|7\n", i);
	o_count = printf("%010.7X|7\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%#X|8\n", i);
	o_count = printf("%#X|8\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%#10X|9\n", i);
	o_count = printf("%#10X|9\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%#.9X|10\n", i);
	o_count = printf("%#.9X|10\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%#9.12X|11\n", i);
	o_count = printf("%#9.12X|11\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%#13.8X|12\n", i);
	o_count = printf("%#13.8X|12\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%#09.14X|13\n", i);
	o_count = printf("%#09.14X|13\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%#012.8X|14\n", i);
	o_count = printf("%#012.8X|14\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%-#8.13X|15\n", i);
	o_count = printf("%-#8.13X|15\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%-#14.9X|16\n", i);
	o_count = printf("%-#14.9X|16\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%#0X|17\n", i);
	o_count = printf("%#0X|17\n", i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%#0#######0###0###010.15X|18\n", i);
	o_count = printf("%#0#######0###0###010.15X|18\n", i);
	munit_assert_int(u_count, ==, o_count);

	return MUNIT_OK;
}

static MunitResult
test_ptr(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;

	int i = 24; char *s = "pain";

	printf("\n");
	int u_count = ft_printf("%25p|1\n", &i);
	int o_count = printf("%25p|1\n", &i);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%-36p|2\n", &s);
	o_count = printf("%-36p|2\n", &s);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%-15p|\n", NULL);
	o_count = printf("%-15p|\n", NULL);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%8p|\n", NULL);
	o_count = printf("%8p|\n", NULL);
	munit_assert_int(u_count, ==, o_count);

	return MUNIT_OK;
}

static MunitResult
test_zeroes(const MunitParameter params[], void* data) {
	(void) params;
	(void) data;

	printf("\n");
	int u_count = ft_printf("%.d|1\n", 0);
	int o_count = printf("%.d|1\n", 0);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%-4.0i|2\n", 0);
	o_count = printf("%-4.0i|2\n", 0);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%08.0d|3\n", 0);
	o_count = printf("%08.0d|3\n", 0);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%#7x|4\n", 0);
	o_count = printf("%#7x|4\n", 0);
	munit_assert_int(u_count, ==, o_count);
	
	u_count = ft_printf("%#-4x|5\n", 0);
	o_count = printf("%#-4x|5\n", 0);
	munit_assert_int(u_count, ==, o_count);

	return MUNIT_OK;
}

static	MunitTest test_suite_tests[] = {
	{"/print char", test_char, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{"/print str", test_str, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{"/print int_i", test_int_i, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{"/print int_min", test_int_min, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{"/print int_max", test_int_max, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{"/print uint", test_uint, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{"/print hexa_x", test_hexa_x, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{"/print hexa_X", test_hexa_X, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{"/print ptr", test_ptr, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{"/print zeroes", test_zeroes, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL},
	{NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const	MunitSuite test_suite = {"", test_suite_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int	main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
	return munit_suite_main(&test_suite, (void*) "", argc, argv);
}
