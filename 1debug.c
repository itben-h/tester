#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
#endif

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	check_nl(char *buf)
{
	size_t	i;

	i = 0;
	while(buf[i])
	{
		if (buf[i] == '\n')
			break ;
		i++;
	}
	return (i);
}

char	*trim_before_nl(char *buf, size_t n)
{
	char	*s;
	size_t	i;
	size_t	j;
	
	s = (char *)malloc(ft_strlen(buf + n) * sizeof(char));
	if (!s)
		return (0);
	i = n + 1;
	j = 0;
	while (buf[i])
	{
		s[j] = buf[i];
		i++;
		j++;
	}
	s[j] = '\0';
	return (s);
}

char	*trim_after_nl(char *buf, size_t n)
{
	char	*s;
	size_t	i;
	
	s = (char *)malloc((n + 2) * sizeof(char));
	if (!s)
		return (0);
	i = 0;
	while (i <= n)
	{
		s[i] = buf[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	i;
	size_t	j;
	size_t	len_total;

	i = -1;
	j = -1;
	len_total = ft_strlen(s1) + ft_strlen(s2);
	new = (char *)malloc((len_total + 1) * sizeof(char));
	if (!new)
		return (0);
	while (s1[++i])
		new[i] = s1[i];
	while (s2[++j])
		new[i + j] = s2[j];
	new[i + j] = '\0';
	free(s1);
	return (new);
}

char	*alloc_buf(char* line, char *buf)
{
	static char	*mem;

	if (mem && !line)
		line = ft_strjoin(line, mem);
	if (check_nl(buf) != ft_strlen(buf))
	{
		mem = trim_before_nl(buf, check_nl(buf));
		buf = trim_after_nl(buf, check_nl(buf));
	}
	else
		mem = buf;
	line = ft_strjoin(line, buf);
	return (line);
}

char	*get_next_line(int fd)
{
	char	*buf;
	char	*line;
	size_t	count;

	count = BUFFER_SIZE;
	line = (char *)malloc(sizeof(char));
	line[0] = '\0';
	buf = (char *)malloc(count * (sizeof(char) + 1));
	if (!buf)
		return (0);
	while (read(fd, buf, count))
	{
		line = alloc_buf(line, buf);
		if (line[ft_strlen(line) - 1] == '\n')
			break ;
	}
	free(buf);
	return (line);
}

int main()
{
	int fd = open("./test1", O_RDWR);
	char *s = get_next_line(fd);
	printf("%s", s);
	s = get_next_line(fd);
	printf("%s", s);
}
