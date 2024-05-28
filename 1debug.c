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

size_t	ft_strchr(char *s, char c)
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

char	*ft_strjoin(char *buf, char *res)
{
	char	*new;
	size_t	i;
	size_t	j;
	size_t	len_total;

	i = -1;
	j = -1;
	if (!buf)
		buf = ft_calloc(1, sizeof(char));
	len_total = ft_strchr(buf, '\0') + ft_strchr(res, '\0');
	new = (char *)malloc((len_total + 1) * sizeof(char));
	if (!new)
		return (0);
	while (buf[++i])
		new[i] = buf[i];
	while (res[++j])
		new[i + j] = res[j];
	new[i + j] = '\0';
	return (new);
}

char	*trim_a_nl(char *buf)
{
	char	*s;
	size_t	i;
	size_t	n;

	n = ft_strchr(buf, '\n');
	s = ft_calloc(n + 2, sizeof(char));
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

char	*trim_b_nl(char *buf)
{
	char	*s;
	size_t	i;
	size_t	n;
	size_t	len;

	n = ft_strchr(buf, '\n');
	len = ft_strchr(buf, '\0') - n;
	s = ft_calloc(len, sizeof(char));
	if (!s)
		return (0);
	i = 0;
	n += 1;
	while (buf[n])
	{
		s[i] = buf[n];
		i++;
		n++;
	}
	s[i] = '\0';
	free(buf);
	return (s);
}

char	*free_all(char *res, char *buf)
{
	free(res);
	free(buf);
	buf = NULL;
	return (buf);
}

char	*get_next_line(int fd)
{
	char		*res;
	ssize_t		bytesread;
	static char	*buf;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (0);
	res = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!res)
		return (0);
	while (bytesread > 0 && (ft_strchr(res, '\n') == ft_strchr(res, '\0')))
	{
		bytesread = read(fd, res, BUFFER_SIZE);
		if (bytesread == -1)
		{
			buf = free_all(res, buf);
			return (0);
		}
		buf = ft_strjoin(buf, res);
	}
	free(res);
	res = trim_a_nl(buf);
	buf = trim_b_nl(buf);
	return (res);
}

int main()
{
	int fd = open("./test1", O_RDWR);
	char *s = malloc(sizeof(char));
	while (s != NULL)
	{
		free(s);
		s = get_next_line(fd);
		printf("%s", s);
	}
}
