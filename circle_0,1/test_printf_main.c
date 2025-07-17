#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../printf/ft_printf.h"

int main()
{
	int i; int j;
	i = ft_printf("% x", 12345);
	printf("|");
	printf("\n");
	j = printf("% x", 12345);
	printf("|");
	printf("\n%d %d", i, j);
}
