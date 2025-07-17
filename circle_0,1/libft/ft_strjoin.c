/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:58:16 by bhowe             #+#    #+#             */
/*   Updated: 2024/07/02 13:40:05 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	len_total;

	if (!s1 && !s2)
		return (0);
	len_total = ft_strlen(s1) + ft_strlen(s2);
	new = (char *)malloc((len_total + 1) * sizeof(char));
	if (!new)
		return (0);
	ft_memcpy(new, s1, ft_strlen(s1));
	ft_memcpy(new + ft_strlen(s1), s2, ft_strlen(s2));
	new[len_total] = '\0';
	return (new);
}
