/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:29:27 by doferet           #+#    #+#             */
/*   Updated: 2023/11/28 17:26:58 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*element;

	if (!del || !lst)
		return ;
	while (*lst)
	{
		element = (*lst)->next;
		ft_lstdelone((*lst), del);
		*lst = element;
	}
	*lst = NULL;
}
