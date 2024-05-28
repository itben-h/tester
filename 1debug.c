#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 100
#endif

size_t	findi(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

char	*trim_b_nl(char *buf, size_t n)
{
	char	*s;
	size_t	i;
	size_t	j;
	size_t	len;

	len = findi(buf + n, '\0');
	s = (char *)malloc(len * sizeof(char));
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

char	*trim_a_nl(char *buf, size_t n)
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
	len_total = findi(s1, '\0') + findi(s1, '\0');
	new = (char *)malloc((len_total + 1) * sizeof(char));
	if (!new)
		return (0);
	while (s1[++i])
		new[i] = s1[i];
	while (s2[++j])
		new[i + j] = s2[j];
	new[i + j] = '\0';
	return (new);
}

char	*alloc_mem(char *buf, char *mem)
{
	char	*add;
	
	add = trim_b_nl(buf, findi(buf, '\n') + 1);
	mem = ft_strjoin(mem, add);
	return (mem);
}

char	*alloc_line(char* line, char *buf, char *mem)
{
	if (mem && !line[0])
	{
		if (findi(mem, '\n') != findi(mem, '\0'))
			line = ft_strjoin(line, trim_a_nl(mem, findi(mem, '\n')));
		else
			line = ft_strjoin(line, mem);
	}
	if (findi(buf, '\n') != findi(buf, '\0'))
		buf = trim_a_nl(buf, findi(buf, '\n'));
	if (buf)
		line = ft_strjoin(line, buf);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buf;

	line = (char *)malloc(sizeof(char));
	line[0] = '\0';
	buf = (char *)malloc(count * (sizeof(char) + 1));
	if (!buf)
		return (0);
	buf[count] = '\0';
	while (read(fd, buf, count) || mem)
	{
		line = alloc_line(line, buf, mem);
		mem = alloc_mem(buf, mem);
		if (line[findi(line, '\0') - 1] == '\n')
			break ;
	}
	free(buf);
	return (line);
}

int main()
{
	int fd = open("./test1", O_RDWR);
	char *s = get_next_line(fd);
	s = get_next_line(fd);
}
