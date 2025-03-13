/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:27:43 by doferet           #+#    #+#             */
/*   Updated: 2025/03/12 19:16:32 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	check_wall(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cub->map.map[i])
	{
		if (cub->map.map[i][0] != '1' || cub->map.map[i][cub->map.columns - 1] != '1')
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

static void	search_player(t_cub *cub)
{
	int	x;
	int	y;

	y = -1;
	while (++y < cub->map.rows)
	{
		x = -1;
		while (++x < cub->map.columns)
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

static void count_map_rows(char *map_file, t_cub *cub)
{
	int		count;
	char	*temp;

	count = 0;
	cub->fd = open(map_file, O_RDONLY);
	if (cub->fd == -1)
		ft_error(cub, "Map file not found");
	temp = get_next_line(cub->fd);
	while (temp)
	{
		if (temp[0] == '1')
			count++;
		free(temp);
		temp = get_next_line(cub->fd);
		if (!temp)
			break ;
	}
	cub->map.rows = count;
	close(cub->fd);
}

static void read_data(char *map_file, t_cub *cub)
{
	char	*temp;

	cub->fd = open(map_file, O_RDONLY);
	if (cub->fd == -1)
		ft_error(cub, "Map file not found");
	temp = get_next_line(cub->fd);
	while(temp)
	{
		free(temp);
		temp = get_next_line(cub->fd);
		check_data(temp, cub);
		if (!temp || temp[0] == 'C')
			break;
	}
}

static void	create_map(t_cub *cub)
{
	int i;
	cub->map.map = malloc(sizeof(char *) * (cub->map.rows + 1));
	if (!cub->map.map)
		ft_error(cub, "Memory allocation error");
	i = -1;
	while (++i <= cub->map.rows)
		cub->map.map[i] = get_next_line(cub->fd);
	cub->map.map[i] = NULL;
	close(cub->fd);
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

	if (ac != 2)
		ft_error(cub, "Invalid arguments");
	len = ft_strlen(av[1]);
	if (len < 4 || ft_strncmp(&av[1][len - 4], ".cub", 4))
		ft_error(cub, "Invalid file extension");
	count_map_rows(av[1], cub);
	read_data(av[1], cub);
	create_map(cub);
	if (cub->map.rows <= 2)
		ft_error(cub, "Map is too small");
	check_wall(cub);
	search_player(cub);

	printf("NO: %s\n", cub->datafile.no);
	printf("SO: %s\n", cub->datafile.so);
	printf("WE: %s\n", cub->datafile.we);
	printf("EA: %s\n", cub->datafile.ea);

	printf("Floor Red: %d\n", cub->datafile.floor_red);
	printf("Floor Green: %d\n", cub->datafile.floor_green);
	printf("Floor Blue: %d\n", cub->datafile.floor_blue);
	printf("Ceiling Red: %d\n", cub->datafile.ceiling_red);
	printf("Ceiling Green: %d\n", cub->datafile.ceiling_green);
	printf("Ceiling Blue: %d\n", cub->datafile.ceiling_blue);
	//init_texture_image(cub, &cub->texture.wall_ea, cub->datafile.ea);
	//init_texture_image(cub, &cub->texture.wall_no, cub->datafile.no);
	//init_texture_image(cub, &cub->texture.wall_so, cub->datafile.so);
	//init_texture_image(cub, &cub->texture.wall_we, cub->datafile.we);
	return (EXIT_SUCCESS);
}
