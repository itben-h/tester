/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:15:54 by bhowe             #+#    #+#             */
/*   Updated: 2024/05/23 00:09:01 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *s, char c)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

static void	*free_all(char **arr, size_t len)
{
	size_t	i;

	i = 0;
	while (i <= len)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (0);
}

static void	*split_words(char **arr, const char *s, char c, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			j = 0;
			while (s[i + j] != c && s[i + j] != '\0')
				j++;
			arr[len] = (char *)malloc((j + 1) * sizeof(char));
			if (!arr[len])
				return (free_all(arr, len));
			ft_memcpy(arr[len], s + i, j);
			arr[len][j] = '\0';
			i += j;
			len++;
		}
	}
	arr[len] = 0;
	return (arr);
}

char	**ft_split(const char *s, char c)
{
	char	**arr;
	size_t	len;

	len = 0;
	arr = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (0);
	if (!split_words(arr, s, c, len))
		return (0);
	return (arr);
}
