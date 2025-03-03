/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:27:43 by doferet           #+#    #+#             */
/*   Updated: 2025/03/03 17:49:17 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	check_wall(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cub->map.map[i])
	{
		if (cub->map.map[i][0] != '1' || cub->map.map[i][cub->map.columns
			- 1] != '1')
			ft_error(cub, "Walls are not valid");
		j = 0;
		if (i == 0 || i == cub->map.rows - 1)
		{
			while (cub->map.map[i][j])
			{
				if (cub->map.map[i][j] != '1')
					ft_error(cub, "Walls are not valid");
				j++;
			}
		}
		i++;
	}
}

static void	count_elements(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cub->map.rows)
	{
		j = -1;
		while (++j < cub->map.columns)
		{
			if (cub->map.map[i][j] == 'P')
			{
				cub->player_pos.x = j;
				cub->player_pos.y = i;
				cub->map.player++;
			}
		}
	}
	if (cub->map.player != 1)
		ft_error(cub, "Incorrect number of players");
}

static void	get_rows(char *map_file, t_cub *cub)
{
	int		count;
	int		map_fd;
	char	*temp;

	count = 0;
	map_fd = open(map_file, O_RDONLY);
	if (map_fd == -1)
		ft_error(cub, "Map file not found");
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
		ft_error(cub, "Empty map");
	cub->map.rows = count;
	close(map_fd);
}

static void	get_columns(char *map_file, t_cub *cub)
{
	int	map_fd;
	int	i;

	map_fd = open(map_file, O_RDONLY);
	if (map_fd == -1)
		ft_error(cub, "Map file not found");
	cub->map.map = malloc(sizeof(char *) * (cub->map.rows + 1));
	if (!cub->map.map)
		ft_error(cub, "Memory allocation error");
	i = -1;
	while (++i < cub->map.rows)
		cub->map.map[i] = get_next_line(map_fd);
	cub->map.map[i] = NULL;
	close(map_fd);
	i = 0;
	while (i < (cub->map.rows - 1))
	{
		if (cub->map.map[i] == NULL)
			ft_error(cub, "Map Error");
		cub->map.map[i][ft_strlen(cub->map.map[i]) - 1] = 0;
		i++;
	}
	cub->map.columns = ft_strlen(cub->map.map[0]);
}

int	parsing(t_cub *cub, int ac, char **av)
{
	int	len;

	len = ft_strlen(av[1]);
	if (len < 4 || ft_strncmp(&av[1][len - 4], ".cub", 4))
		ft_error(cub, "Invalid file extension");
	if (ac != 2)
	{
		printf("Wrong number of arguments");
		return (EXIT_FAILURE);
	}
	get_rows(av[1], cub);
	if (cub->map.rows <= 2)
		ft_error(cub, "Map is too small");
	get_columns(av[1], cub);
	check_wall(cub);
	count_elements(cub);
	return (EXIT_SUCCESS);
}
