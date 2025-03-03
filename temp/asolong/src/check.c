/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 19:54:11 by rbalazs           #+#    #+#             */
/*   Updated: 2024/07/06 19:54:12 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/solong.h"

static char	**copymap(t_data *data)
{
	int		i;
	char	**copy;

	i = 0;
	copy = malloc(sizeof(char *) * (data->map.rows + 1));
	if (!copy)
		ft_error(data, "Malloc failed");
	while (data->map.map[i])
	{
		if (data->map.map[i] == NULL)
		{
			free_matrix(copy);
			ft_error(data, "Malloc failed");
		}
		copy[i] = ft_strdup(data->map.map[i]);
		if (copy[i] == NULL)
		{
			free_matrix(copy);
			ft_error(data, "Malloc failed");
		}
		i++;
	}
	return (copy[i] = NULL, copy);
}

static bool	flood_fill(char **copy, t_map *map, t_point cur)
{
	static int	check_collectibles = 0;
	static bool	exit = false;

	if (cur.x < 0 || cur.y < 0 || cur.x >= map->columns || cur.y >= map->rows)
		return (false);
	if (copy[cur.y][cur.x] == '1')
		return (false);
	if (copy[cur.y][cur.x] == 'C')
		check_collectibles++;
	if (copy[cur.y][cur.x] == 'E')
		exit = true;
	copy[cur.y][cur.x] = '1';
	flood_fill(copy, map, (t_point){cur.x + 1, cur.y});
	flood_fill(copy, map, (t_point){cur.x - 1, cur.y});
	flood_fill(copy, map, (t_point){cur.x, cur.y + 1});
	flood_fill(copy, map, (t_point){cur.x, cur.y - 1});
	return (check_collectibles == map->collectibles && exit);
}

static void	check_wall(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map.map[i])
	{
		if (data->map.map[i][0] != '1' || data->map.map[i][data->map.columns
			- 1] != '1')
			ft_error(data, "Walls are not valid");
		j = 0;
		if (i == 0 || i == data->map.rows - 1)
		{
			while (data->map.map[i][j])
			{
				if (data->map.map[i][j] != '1')
					ft_error(data, "Walls are not valid");
				j++;
			}
		}
		i++;
	}
}

static void	count_elements(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->map.rows)
	{
		j = -1;
		while (++j < data->map.columns)
		{
			check_character(data->map.map[i][j], data);
			if (data->map.map[i][j] == 'C')
				data->map.collectibles++;
			if (data->map.map[i][j] == 'P')
			{
				data->player_pos.x = j;
				data->player_pos.y = i;
				data->map.player++;
			}
			if (data->map.map[i][j] == 'E')
				data->map.exit++;
		}
	}
}

void	check(char *file, t_data *data)
{
	char	**copy;
	int		len;

	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(&file[len - 4], ".ber", 4))
		ft_error(data, "Invalid file extension");
	count_elements(data);
	if (data->map.player != 1)
		ft_error(data, "Incorrect number of players");
	if (data->map.collectibles == 0)
		ft_error(data, "No collectibles on the map");
	if (data->map.exit != 1)
		ft_error(data, "Incorrect number of exit");
	check_wall(data);
	copy = copymap(data);
	if (!flood_fill(copy, &data->map, data->player_pos))
	{
		free_matrix(copy);
		ft_error(data, "Map is not closed");
	}
	free_matrix(copy);
}
