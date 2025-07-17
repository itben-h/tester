/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_dc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:02:34 by bhowe             #+#    #+#             */
/*   Updated: 2024/06/24 14:55:01 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lstdc	*ft_lstnew_dc(int num)
{
	t_lstdc	*node;

	node = (t_lstdc *)malloc(sizeof(t_lstdc));
	if (!node)
		return (NULL);
	node->num = num;
	node->next = node;
	node->prev = node;
	return (node);
}
