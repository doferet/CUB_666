/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:46:16 by doferet           #+#    #+#             */
/*   Updated: 2023/11/30 11:40:53 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	int		j;
	size_t	i;
	char	*dest;

	j = 0;
	i = ft_strlen(&src[j]);
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	while (src[j])
	{
		dest[j] = src[j];
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
