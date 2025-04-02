/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:07:48 by rbalazs           #+#    #+#             */
/*   Updated: 2025/04/02 12:28:17 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	**ft_double_strjoin(char **file, char *line)
{
	int		i;
	size_t	len;
	char	**new_file;

	if (!file || !line)
		return (NULL);
	len = 0;
	i = 0;
	while (file[len])
		len++;
	len++;
	new_file = malloc(sizeof(char *) * (len + 1));
	if (!new_file)
		return (NULL);
	i = 0;
	while (file[i])
	{
		new_file[i] = ft_strdup(file[i]);
		i++;
	}
	new_file[i] = ft_strdup(line);
	new_file[i + 1] = NULL;
	free_matrix(file);
	return (new_file);
}

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

void	check_wrong_char_color(char *str, int i, t_cub *cub)
{
	int	count;

	i++;
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

bool	is_line_map(char *line)
{
	int	i;

	i = 0;
	if (line[0] == '\0' || line[0] == '\n')
		return (false);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == 'N' || line[i] == 'S'
		|| line[i] == 'E' || line[i] == 'W' || line[i] == 'F' || line[i] == 'C')
		return (false);
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0')
			return (true);
		i++;
	}
	return (false);
}

void	check_empty_line(t_cub *cub)
{
	int	i;

	i = -1;
	while (cub->file[++i])
	{
		if (!is_line_map(cub->file[i]) && cub->start_map <= i
			&& cub->end_map >= i)
			ft_error(cub, "Empty or wrong line in map");
		if (cub->end_map < i && cub->file[i][0] != '\n')
			ft_error(cub, "Empty or wrong line in map");
	}
}
