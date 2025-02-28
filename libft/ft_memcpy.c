/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:36:50 by doferet           #+#    #+#             */
/*   Updated: 2023/11/30 10:51:41 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dst;
	unsigned char	*source;

	i = 0;
	dst = (unsigned char *)dest;
	source = (unsigned char *)src;
	if (!dst && !source)
		return (0);
	while (i < n)
	{
		dst[i] = source[i];
		i++;
	}
	return (dest);
}
