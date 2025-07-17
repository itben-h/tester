/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:36:37 by bhowe             #+#    #+#             */
/*   Updated: 2024/05/22 23:40:19 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*tmp;

	if (!*lst || !del)
		return ;
	node = *lst;
	while (node)
	{
		tmp = (node)->next;
		ft_lstdelone(node, (*del));
		node = tmp;
	}
	*lst = NULL;
}
