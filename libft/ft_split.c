/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:16:51 by doferet           #+#    #+#             */
/*   Updated: 2025/03/06 10:42:20 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *str, char c)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	if (c == 0)
		return (str[i]);
	while (str[i] == c)
		i++;
	while (str[i])
	{
		while (str[i] != c && str[i])
			i++;
		count++;
		while (str[i] == c)
			i++;
	}
	return (count);
}

static size_t	count_letters(char const *str, char c, int i)
{
	size_t	len;

	len = 0;
	while (str[i] && str[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

static char	**ft_free(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

static char	**ft_boucle(char **split, char const *s, char c, size_t i)
{
	size_t	j;
	size_t	nb_letter;

	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			nb_letter = count_letters(s, c, i);
			split[j] = ft_substr(s, i, nb_letter);
			if (!split[j])
				return (ft_free(split));
			i += nb_letter;
			j++;
		}
	}
	split[j] = 0;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	size_t		i;
	size_t		len;
	char		**split;

	i = 0;
	if (!s)
		return (NULL);
	len = count_words(s, c);
	split = malloc(sizeof(char *) * (len + 1));
	if (!split)
		return (NULL);
	return (ft_boucle(split, s, c, i));
}

/*#include <stdio.h>
int main(void)
{
	char s[] = "tripouille ";
	size_t i = 0;
	char c = 0;
	char **split = ft_split(s, c);
	while (i < count_words(s, c))
	{
		printf("%s\n", split[i]);
		i++;
	}
	ft_free(split);
	return (0);
}*/
