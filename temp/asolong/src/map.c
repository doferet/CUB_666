/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:23:55 by rbalazs           #+#    #+#             */
/*   Updated: 2024/07/06 21:25:27 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/solong.h"

static void	get_rows(char *map_file, t_data *data)
{
	int		count;
	int		map_fd;
	char	*temp;

	count = 0;
	map_fd = open(map_file, O_RDONLY);
	if (map_fd == -1)
		ft_error(data, "Map file not found\n");
	temp = get_next_line(map_fd);
	while (temp)
	{
		count++;
		free(temp);
		temp = get_next_line(map_fd);
		if (!temp)
			break ;
	}
	if (count == 0)
		ft_error(data, "Empty map\n");
	data->map.rows = count;
	close(map_fd);
}

static void	get_columns(char *map_file, t_data *data)
{
	int	map_fd;
	int	i;

	map_fd = open(map_file, O_RDONLY);
	if (map_fd == -1)
		ft_error(data, "Map file not found\n");
	data->map.map = malloc(sizeof(char *) * (data->map.rows + 1));
	if (!data->map.map)
		ft_error(data, "Memory allocation error\n");
	i = -1;
	while (++i < data->map.rows)
		data->map.map[i] = get_next_line(map_fd);
	data->map.map[i] = NULL;
	close(map_fd);
	i = 0;
	while (i < (data->map.rows - 1))
	{
		if (data->map.map[i] == NULL)
			ft_error(data, "Map Error\n");
		data->map.map[i][ft_strlen(data->map.map[i]) - 1] = 0;
		i++;
	}
	data->map.columns = ft_strlen(data->map.map[0]);
}

void	init_map(char *map_file, t_data *data)
{
	int	len;

	len = ft_strlen(map_file);
	if (len < 4 || ft_strncmp(&map_file[len - 4], ".ber", 4))
		ft_error(data, "Invalid file extension");
	get_rows(map_file, data);
	if (data->map.rows < 3)
		ft_error(data, "Map is too small\n");
	get_columns(map_file, data);
}
