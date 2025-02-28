/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:42:22 by doferet           #+#    #+#             */
/*   Updated: 2023/11/27 13:33:53 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	i = 0;
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (!d && !s)
		return (NULL);
	if (d < s)
	{
		while (n--)
		{
			d[i] = s[i];
			i++;
		}
	}
	else
		while (n--)
			d[n] = s[n];
	return (dest);
}
/*#include <stdio.h>
#include <string.h>
int main(void)
{
	char dest[] = "";
	char src[] = "";
	size_t n;

	n = 5;
	ft_memmove(dest + 2, src, n);
	printf("dest : %s, source : %s\n", dest, src);
	memmove(dest + 2, src, n);
	printf("dest : %s, source : %s\n", dest, src);
}*/
