/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:47:31 by bhowe             #+#    #+#             */
/*   Updated: 2024/05/23 14:18:51 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*head;
	void	*map;

	if (!lst || !f || !del)
		return (NULL);
	head = NULL;
	while (lst)
	{
		map = (*f)(lst->content);
		node = ft_lstnew(map);
		if (!node)
		{
			del(map);
			ft_lstclear(&head, (*del));
			return (0);
		}
		ft_lstadd_back(&head, node);
		lst = lst->next;
	}
	node->next = NULL;
	return (head);
}
