/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:26:50 by bhowe             #+#    #+#             */
/*   Updated: 2024/05/20 22:26:17 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	len_new;

	len_new = 0;
	if (start > ft_strlen(s))
		start = ft_strlen(s);
	while (s[start] && start < ft_strlen(s) && len_new < len)
	{
		start++;
		len_new++;
	}
	start -= len_new;
	new = (char *)malloc((len_new + 1) * sizeof(char));
	if (!new)
		return (0);
	ft_memcpy(new, s + start, len_new);
	new[len_new] = '\0';
	return (new);
}
