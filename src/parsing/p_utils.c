/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:07:48 by rbalazs           #+#    #+#             */
/*   Updated: 2025/03/18 10:08:20 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	*ft_charjoin(char *str, char c, t_cub *cub)
{
	int		len;
	int		i;
	char	*res;

	if (ft_isalpha(c))
		ft_error(cub, "Caracter forbidden in color");
	if (c == '-')
		ft_error(cub, "Negative number are forbidden for color");
	len = ft_strlen(str) + 1;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		ft_error(cub, "Malloc Error");
	i = 0;
	while (str && str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i++] = c;
	res[i] = '\0';
	free(str);
	return (res);
}

void	check_wrong_char_color(char *str, t_cub *cub)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	while (str[i])
	{
		if (str[i] == '-')
			ft_error(cub, "Negative number for color");
		else if (ft_isdigit(str[i]) == false && str[i] != ' ' && str[i] != ','
			&& str[i] != '\0' && str[i] != '\n')
			ft_error(cub, "Caracter forbidden in color");
		if (str[i] == ',')
			count++;
		if (count > 2)
			ft_error(cub, "Too many values in color");
		i++;
	}
	if (count < 2)
		ft_error(cub, "Not enough values in color");
}
