/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:30:49 by doferet           #+#    #+#             */
/*   Updated: 2023/11/30 11:12:06 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*element;

	if (!lst || !f || !del)
		return (0);
	new = 0;
	while (lst)
	{
		element = ft_lstnew((*f)(lst->content));
		if (!element)
		{
			del((*f)(lst->content));
			ft_lstclear(&new, del);
			return (new);
		}
		ft_lstadd_back(&new, element);
		lst = lst->next;
	}
	return (new);
}
