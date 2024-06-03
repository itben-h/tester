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

#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

void	ft_putnbr_fd(long long n, int fd)
{
	if (n == LLONG_MAX)
		ft_putstr_fd("-9223372036854775808", fd);
	else if (n < 0)
	{
		n = -n;
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(n, fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
		ft_putchar_fd('0' + n, fd);
}

int	print_int(int n)
{
	int	size;

	ft_putnbr_fd(n, 1);
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

char	find_radix(size_t i, char c)
{
	char	*radix;

	radix = "0123456789ABCDEF";
	if (c == 'x')
		return (ft_tolower(radix[i]));
	else
		return (radix[i]);
}

void	ft_put_hexa(long long n, char c)
{
	if (n > 15)
	{
		ft_put_hexa(n / 16, c);
		ft_put_hexa(n % 16, c);
	}
	else
		ft_putchar_fd(find_radix(n, c), 1);
}

int	print_hexa(unsigned int n, char c)
{
	int				size;
	unsigned int	tmp;

	tmp = n;
	size = 1;
	while (tmp > 15)
	{
		tmp = tmp / 16;
		size++;
	}
	ft_put_hexa(n, c);
	return (size);
}

int	print_ptr(unsigned long long ptr)
{
	int					size;
	unsigned long long	tmp;

	size = 2;
	tmp = ptr;
	while (tmp > 15)
	{
		tmp = tmp / 16;
		size++;
	}
	ft_putstr_fd("0x", 1);
	ft_put_hexa(ptr, 'x');
	return (size);
}

int	find_format(va_list ptr, const char *s, size_t i)
{
	int	total;

	total = 0;
	if (s[i] == 'p')
		total += print_ptr(va_arg(ptr, unsigned long long));
	return (total);
}

int	ft_printf(const char *s, ...)
{
	int		total;
	size_t	i;
	va_list	ptr;

	i = 0;
	total = 0;
	va_start(ptr, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			total += find_format(ptr, s, i);
		}
		else
		{
			ft_putchar_fd(s[i], 1);
			total++;
		}
		i++;
	}
	va_end(ptr);
	return (total);
}

int	main()
{
	int i = 1;
	unsigned long long j = (unsigned long long)&i;
	printf("%llu\n", j);
	ft_printf("%p", &i);
}
