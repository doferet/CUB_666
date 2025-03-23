/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:27:43 by doferet           #+#    #+#             */
/*   Updated: 2025/03/23 22:26:10 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	search_player(t_cub *cub)
{
	int	x;
	int	y;

	y = -1;
	while (++y < cub->map.rows)
	{
		x = -1;
		while (++x < (int)ft_strlen(cub->map.map[y]))
		{
			if (cub->map.map[y][x] == 'N' || cub->map.map[y][x] == 'S'
				|| cub->map.map[y][x] == 'E' || cub->map.map[y][x] == 'W')
			{
				cub->player_pos.x = x;
				cub->player_pos.y = y;
				cub->player_pos.start_orientation = cub->map.map[y][x];
				cub->map.player++;
			}
		}
	}
	if (cub->map.player != 1)
		ft_error(cub, "Incorrect number of players");
}

void	read_data(t_cub *cub)
{
	int		i;
	bool	start;

	i = 0;
	start = false;
	while (cub->file[i])
	{
		if (is_line_map(cub->file[i]) == true && start == false)
		{
			start = true;
			cub->start_map = i;
		}
		if (is_line_map(cub->file[i]) == true && start == true)
			cub->end_map = i;
		i++;
	}
	i = 0;
	while (i < cub->start_map)
	{
		check_data(cub->file[i], cub);
		i++;
	}
	if (cub->datafile.all_values == false)
		ft_error(cub, "Missing values");
}

void	create_map(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (cub->file[++i])
	{
		if (is_line_map(cub->file[i]) == true)
			cub->map.map[j++] = ft_strdup(cub->file[i]);
	}
	cub->map.map[j] = NULL;
	i = -1;
	while (++i < (cub->map.rows - 1))
	{
		if (cub->map.map[i] == NULL)
			ft_error(cub, "Map Error");
		cub->map.map[i][ft_strlen(cub->map.map[i]) - 1] = 0;
		if (cub->map.columns < (int)ft_strlen(cub->map.map[i]))
			cub->map.columns = (int)ft_strlen(cub->map.map[i]);
	}
	check_empty_line(cub);
}

void	stock_file_in_array(char *map_file, t_cub *cub)
{
	int		fd;
	char	*temp;

	fd = open(map_file, O_RDONLY);
	cub->file = malloc(sizeof(char *));
	if (!cub->file)
		ft_error(cub, "Memory allocation error");
	cub->file[0] = NULL;
	temp = get_next_line(fd);
	while (temp)
	{
		if (is_line_map(temp) == true)
			cub->map.rows++;
		cub->file = ft_double_strjoin(cub->file, temp);
		free(temp);
		temp = get_next_line(fd);
	}
	if (cub->map.rows == 0)
		ft_error(cub, "Map is empty");
	if (cub->map.rows <= 2)
		ft_error(cub, "Map is too small");
}

int	parsing(t_cub *cub, int ac, char **av)
{
	int	len;

	if (ac != 2)
		ft_error(cub, "Invalid arguments");
	len = ft_strlen(av[1]);
	if (len < 4 || ft_strncmp(&av[1][len - 4], ".cub", 4))
		ft_error(cub, "Invalid file extension");
	stock_file_in_array(av[1], cub);
	read_data(cub);
	cub->map.map = malloc(sizeof(char *) * (cub->map.rows + 1));
	if (!cub->map.map)
		ft_error(cub, "Memory allocation error");
	create_map(cub);
	check_wall(cub);
	search_player(cub);
	init_mlx(cub);
	return (EXIT_SUCCESS);
}
