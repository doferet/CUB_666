/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:22:44 by doferet           #+#    #+#             */
/*   Updated: 2023/11/30 14:50:49 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (c == s[i])
			return (1);
		i++;
	}
	return (0);
}

static size_t	ft_start(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen((char *)s1);
	while (i < len)
	{
		if (ft_isset(set, s1[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

static size_t	ft_end(char const *s1, char const *set)
{
	size_t	i;

	i = ft_strlen((char *)s1);
	while (i > 0)
	{
		if (ft_isset(set, s1[i - 1]) == 0)
			break ;
		i--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	size_t	len;
	char	*trim;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	start = ft_start(s1, set);
	end = ft_end(s1, set);
	len = end - start;
	if (start >= end)
		return (ft_strdup(""));
	trim = malloc(sizeof(char) * len + 1);
	if (!trim)
		return (NULL);
	while (s1[start] && i < len)
	{
		trim[i] = s1[start];
		i++;
		start++;
	}
	trim[i] = '\0';
	return (trim);
}

/*#include <stdio.h>
#include <stdlib.h>
int main (void)
{
	char const s1[] = "tripouille   xxx";
	char const set[] = " x";

	printf("%s\n", ft_strtrim(s1, set));
}*/
