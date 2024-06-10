#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../printf/ft_printf.h"

int main()
{
	int i; int j;
	i = ft_printf("%d%d%d%d%d%d", 1, 2,3,4,5,6);
	printf("|");
	printf("\n");
	j = printf("%d%d%d%d%d%d", 1, 2,3,4,5,6);
	printf("|");
	printf("\n%d %d", i, j);
}
