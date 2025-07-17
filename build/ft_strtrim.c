/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:14:29 by bhowe             #+#    #+#             */
/*   Updated: 2024/05/24 09:54:02 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_set(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*new;
	size_t	start;
	size_t	end;

	start = -1;
	while (s1[++start])
	{
		if (!check_set(s1[start], set))
			break ;
	}
	end = ft_strlen(s1);
	while (s1[--end] && ft_strlen(s1) != start)
	{
		if (!check_set(s1[end], set))
			break ;
	}
	new = (char *)malloc((end - start + 2) * sizeof(char));
	if (!new)
		return (0);
	ft_memcpy(new, s1 + start, end - start + 1);
	new[end - start + 1] = '\0';
	return (new);
}
