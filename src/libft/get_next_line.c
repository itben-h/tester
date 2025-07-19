/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:07:42 by bhowe             #+#    #+#             */
/*   Updated: 2024/07/02 15:23:58 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "./libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4
#endif

size_t	find_nlen(char *s)
{
	char	*n;

	n = ft_strchr(s, '\n');
	if (n)
		return((size_t)(n - s) + 1);
	else
		return(ft_strlen(s));
}

static char	*trim_a_nl(char *s, size_t len)
{
	char	*res;
	char	*n;

	n = ft_strchr(s, '\n');
	res = ft_calloc(len + 1, sizeof(char));
	if (!s)
		return (0);
	res = ft_memcpy(res, s, len);
	res[len] = '\0';
	free(s);
	return (res);
}

static void	save_rem(char *s, char *save, size_t nlen)
{
	char	*n;
	size_t	len;

	n = "";
	if (!s)
	{
		ft_bzero(save, BUFFER_SIZE + 1);
		return ;
	}
	len = ft_strlen(s) - nlen;
	if (len)
		ft_memcpy(save, n, len);
	save[len] = '\0';
}

static char	*read_file(int fd, char *str, char *buf_read)
{
	ssize_t	bytesread;

	bytesread = 1;
	while (bytesread > 0 && !ft_strchr(buf_read, '\n'))
	{
		bytesread = read(fd, buf_read, BUFFER_SIZE);
		if (bytesread == -1)
		{
			free(str);
			return (NULL);
		}
		buf_read[bytesread] = '\0';
		str = ft_strjoin(str, buf_read);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	char		*str;
	char		buf_read[BUFFER_SIZE + 1];
	static char	save[BUFFER_SIZE];
	size_t		nlen;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str = "";
	ft_bzero(buf_read, BUFFER_SIZE + 1);
	if (!str)
		return (0);
	if (save[0])
		ft_strjoin(str, save);
	str = read_file(fd, str, buf_read);
	if (!str || !str[0])
	{
		free(str);
		return (NULL);
	}
	nlen = find_nlen(str);
	save_rem(str, save, nlen);
	str = trim_a_nl(str, nlen);
	return (str);
}
