/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_dc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:09:28 by bhowe             #+#    #+#             */
/*   Updated: 2024/06/24 15:22:41 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear_dc(t_lstdc **lst)
{
	t_lstdc	*node;
	t_lstdc	*tmp;

	if (!*lst)
		return ;
	node = *lst;
	if (node != node->next)
	{
		while (node->next != *lst)
		{
			tmp = node->next;
			free(node);
			node = tmp;
		}
	}
	free (node);
	*lst = NULL;
}
