/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:09:04 by bhowe             #+#    #+#             */
/*   Updated: 2024/05/21 17:19:17 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_abs(int n)
{
	if (n < 0)
		n = -n;
	return (n);
}

static size_t	find_size(int n)
{
	size_t	size;

	size = 1;
	while (!(n <= 9 && n >= -9))
	{
		n = n / 10;
		size++;
	}
	if (n < 0)
		size++;
	return (size);
}

char	*ft_strrev(char *str, size_t len)
{
	char	c;
	size_t	i;

	i = 0;
	while (i < len / 2)
	{
		c = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = c;
		i++;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	is_neg;
	size_t	len;

	str = (char *)malloc((find_size(n) + 1) * sizeof(char));
	if (!str)
		return (0);
	is_neg = (n < 0);
	len = 0;
	if (n == 0)
		str[len++] = '0';
	while (n != 0)
	{
		str[len++] = ft_abs(n % 10) + '0';
		n = n / 10;
	}
	if (is_neg)
		str[len++] = '-';
	str[len] = '\0';
	str = ft_strrev(str, len);
	return (str);
}
