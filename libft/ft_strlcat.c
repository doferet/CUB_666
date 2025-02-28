/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:47:07 by doferet           #+#    #+#             */
/*   Updated: 2023/11/29 12:41:17 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len_src;

	if (!dst || !src)
		return (0);
	i = ft_strlen(dst);
	len_src = ft_strlen((char *)src);
	j = 0;
	if (i >= size)
		return (size + len_src);
	while (src[j] && j < size - i - 1)
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (i + len_src);
}
