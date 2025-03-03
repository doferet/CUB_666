/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:33:08 by doferet           #+#    #+#             */
/*   Updated: 2025/03/03 16:29:44 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (unsigned char)c)
	{
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)s + i);
}

char	*ft_strjoin_2(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*s3;

	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	len = ft_strlen(s1) + ft_strlen(s2);
	s3 = malloc(sizeof(char) * len + 1);
	if (!s2 || !s3)
		return (NULL);
	i = ((j = 0));
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j])
		s3[i++] = s2[j++];
	s3[len] = '\0';
	free(s1);
	return (s3);
}
