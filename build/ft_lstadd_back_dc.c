/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_dc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:51:00 by bhowe             #+#    #+#             */
/*   Updated: 2024/06/25 10:56:20 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back_dc(t_lstdc **lst, t_lstdc *new)
{
	if (!*lst)
	{
		new->next = new;
		*lst = &*new;
	}
	else
		new->next = *lst;
	new->prev = new->next->prev;
	new->next->prev = &*new;
	new->prev->next = &*new;
}
