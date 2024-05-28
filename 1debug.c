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

char	*ft_calloc(size_t nmemb, size_t size)
{
	char	*tab;
	size_t	i;
	size_t	len;

	if (size && nmemb > 4294967295 / size)
		return (0);
	len = nmemb * size;
	tab = (char *)malloc(len);
	if (!tab)
		return (0);
	i = 0;
	while (i < len)
	{
		tab[i] = '\0';
		i++;
	}
	return (tab);
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

char	*ft_realloc(char *line, char *buf)
{
	char	*tmp;
	
	tmp = ft_strjoin(line, buf);
	free(line);
	return (tmp);
}

char	*copy_buf(char *buf)
{
	char	*s;
	size_t	i;
	size_t	n;
	
	n = findi(buf, '\n');
	s = ft_calloc(n + 2, sizeof(char));
	if (!s)
		return (0);
	i = 0;
	while (i <= n)
	{
		s[i] = buf[i];
		i++;
	}
	if (!s[i -1])
		s[i - 1] = '\n';
	s[i] = '\0';
	return (s);
}

char	*set_buf(char *line, char *buf, size_t buf_i)
{
	char	*s;
	size_t	i;
	size_t	len;

	len = buf_i - findi(line, '\0');
	s = ft_calloc(len, sizeof(char));
	if (!s)
		return (0);
	i = 0;
	while (buf[buf_i - len])
	{
		s[i] = buf[buf_i - len];
		i++;
		len--;
	}
	s[i] = '\0';
	free(buf);
	return (s);
}

char	*get_next_line(int fd)
{
	char		*line;
	ssize_t		bytesread;
	static char	buf[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (0);
	bytesread = 1;
	line = ft_calloc(1, sizeof(char));
	while (bytesread > 0)
	{
		bytesread = read(fd, buf, BUFFER_SIZE);
		if (bytesread == -1)
		{
			buf = NULL;
			return (NULL);
		}
		buf[bytesread] = '\0';
		line = ft_realloc(line, buf);
		if (findi(buf, '\n') != findi(buf, '\0'))
			break ;
	}
	return (line);
}

int main()
{
	int fd = open("./test1", O_RDWR);
	char *s = get_next_line(fd);
	s = get_next_line(fd);
}
