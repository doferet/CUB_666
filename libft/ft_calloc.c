/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:31:50 by doferet           #+#    #+#             */
/*   Updated: 2023/11/29 16:53:21 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*tab;
	size_t	sizemax;

	sizemax = nmemb * size;
	if (size && sizemax / size < nmemb)
		return (NULL);
	if (nmemb == 0 || size == 0)
	{
		tab = malloc(1);
		return (tab);
	}
	tab = malloc(sizemax);
	if (!tab)
		return (NULL);
	ft_bzero(tab, sizemax);
	return (tab);
}
