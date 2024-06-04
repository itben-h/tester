#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../printf/ft_printf.h"

int main()
{
	ft_printf("%x", INT_MAX);
	printf("|");
	printf("\n");
	printf("%++.20x", INT_MAX);
	printf("|");
}
