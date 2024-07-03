#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "./libft.h"

int main() {
	int fd = open("./gnl_txt/move", O_RDWR);

	char *s = "go";
	while (s)
	{
		s = get_next_line(fd);
		printf("%s", s);
		free(s);
	}
	close(fd);
}
