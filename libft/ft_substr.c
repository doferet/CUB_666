/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:08:32 by doferet           #+#    #+#             */
/*   Updated: 2023/11/23 15:49:40 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_boucle(char const *s, unsigned int start,
		size_t len, char *news)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			news[j] = s[i];
			j++;
		}
		i++;
	}
	news[j] = '\0';
	return (news);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*news;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	if (ft_strlen(s) > len)
		news = malloc(sizeof(char) * (len + 1));
	else
		news = malloc(sizeof(char) * ft_strlen(s + start) + 1);
	if (!news)
		return (NULL);
	return (ft_boucle(s, start, len, news));
}

/*#include <stdio.h>
int main(void)
{
	char	*str = strdup("0123456789");
	char	*s = ft_substr(str, 1, 20);
	printf("%s", s);
}*/
