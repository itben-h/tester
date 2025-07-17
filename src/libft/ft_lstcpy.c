/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:51:59 by bhowe             #+#    #+#             */
/*   Updated: 2024/06/21 17:59:17 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstcpy(t_list *lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*head;

	if (!lst || !del)
		return (NULL);
	head = NULL;
	while (lst)
	{
		node = ft_lstnew(lst->content);
		if (!node)
		{
			ft_lstclear(&head, (*del));
			return (0);
		}
		ft_lstadd_back(&head, node);
		lst = lst->next;
	}
	node->next = NULL;
	return (head);
}
