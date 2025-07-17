/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:54:09 by bhowe             #+#    #+#             */
/*   Updated: 2024/05/20 14:04:37 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_abs(int n)
{
	if (n < 0)
		n = -n;
	return (n);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		len;
	char	buf[11];
	size_t	is_neg;

	ft_bzero(buf, 11);
	is_neg = (n < 0);
	len = 0;
	if (n == 0)
		buf[len++] = '0';
	while (n != 0)
	{
		buf[len++] = ft_abs(n % 10) + '0';
		n = n / 10;
	}
	if (is_neg)
		buf[len++] = '-';
	while (len)
		write(fd, &buf[--len], 1);
}
