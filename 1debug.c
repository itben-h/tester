#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
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
	if (len <= 0)
		return (0);
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
	if (!buf && !res)
		return (0);
	if (!buf)
		buf = ft_calloc(1, sizeof(char));
	len_total = ft_strchr(buf, '\0') + ft_strchr(res, '\0');
	new = ft_calloc(len_total + 1, sizeof(char));
	if (!new)
	{
		free(buf);
		return (0);
	}
	while (buf[++i])
		new[i] = buf[i];
	while (res[++j])
		new[i + j] = res[j];
	new[i + j] = '\0';
	free(buf);
	return (new);
}

char	*trim_a_nl(char *buf)
{
	char	*s;
	size_t	i;
	size_t	len;

	if (!buf[0])
		return (0);
	if (ft_strchr(buf, '\n') != ft_strchr(buf, '\0'))
		len = ft_strchr(buf, '\n') + 2;
	else
		len = ft_strchr(buf, '\n') + 1;
	s = ft_calloc(len, sizeof(char));
	if (!s)
		return (0);
	i = 0;
	while (buf[i] != '\0' && buf[i] != '\n')
	{
		s[i] = buf[i];
		i++;
	}
	if (buf[i] == '\n')
		s[i++] = '\n';
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
	{
		free(buf);
		return (0);
	}
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

void	free_null(char *buf)
{
	free(buf);
	buf = NULL;
}

char	*read_file(int fd, char *buf, char *buf_r)
{
	char	*tmp;
	ssize_t	bytesread;

	bytesread = 1;
	while (bytesread > 0 && (ft_strchr(buf_r, '\n') == ft_strchr(buf_r, '\0')))
	{
		bytesread = read(fd, buf_r, BUFFER_SIZE);
		if (bytesread == -1)
		{
			free_null(buf);
			free_null(buf_r);
			return (0);
		}
		buf_r[bytesread] = '\0';
		tmp = ft_strjoin(buf, buf_r);
		free_null(buf);
		buf = tmp;
	}
	free_null(buf_r);
	return (buf);
}

char	*get_next_line(int fd)
{
	char		*res;
	char		*buf_r;
	static char	*buf[FD_SETSIZE + 1];

	if (fd < 0 || fd > FD_SETSIZE || BUFFER_SIZE <= 0)
		return (0);
	buf_r = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf_r)
		return (0);
	if (!buf[fd])
		buf[fd] = ft_calloc(1, sizeof(char));
	buf[fd] = read_file(fd, buf[fd], buf_r);
	if (!buf[fd])
	{
		free_null(buf_r);
		free_null(buf[fd]);
		return (0);
	}
	res = trim_a_nl(buf[fd]);
	buf[fd] = trim_b_nl(buf[fd]);
	return (res);
}

int main()
{
	char *s = malloc(sizeof(char));
	while (s != NULL)
	{
		free(s);
		s = get_next_line(42);
		printf("%s", s);
	}
	free(s);
}
