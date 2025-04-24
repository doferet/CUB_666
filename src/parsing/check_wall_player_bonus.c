/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall_player_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:41:13 by rbalazs           #+#    #+#             */
/*   Updated: 2025/04/24 16:55:41 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	check_around_floor_player(t_cub *cub, int x, int y)
{
	if ((cub->map.map[y][x] == '0' || is_player_or_door(cub, x, y))
		&& cub->map.map[y][x - 1] == ' ')
		ft_error(cub, "Walls are not valid or player / door is outside");
	if ((cub->map.map[y][x] == '0' || is_player_or_door(cub, x, y))
		&& cub->map.map[y][x + 1] == ' ')
		ft_error(cub, "Walls are not valid or player / door is outside");
	if ((cub->map.map[y][x] == '0' || is_player_or_door(cub, x, y))
		&& (cub->map.map[y + 1][x] == ' ' || cub->map.map[y + 1][x] == '\0'
			|| cub->map.map[y + 1][x] == 0))
		ft_error(cub, "Walls are not valid or player / door is outside");
	if ((cub->map.map[y][x] == '0' || is_player_or_door(cub, x, y))
		&& (cub->map.map[y - 1][x] == ' ' || cub->map.map[y - 1][x] == '\0'
			|| cub->map.map[y - 1][x] == 0))
		ft_error(cub, "Walls are not valid or player / door is outside");
}

static bool	check_begin_end(t_cub *cub, int x, int y, bool start)
{
	if (cub->map.map[y][x] == '1')
		start = true;
	if ((cub->map.map[y][x] == '0' || is_player_or_door(cub, x, y))
		&& start == false)
		ft_error(cub, "Walls are not valid or player / door is outside");
	if ((cub->map.map[y][(int)ft_strlen(cub->map.map[y]) - 1] == '0'
		|| is_player_or_door(cub, (int)ft_strlen(cub->map.map[y]) - 1, y)))
		ft_error(cub, "Walls are not valid or player / door is outside");
	return (start);
}

static void	check_invalid_character(t_cub *cub, int x, int y)
{
	if (cub->map.map[y][x] != 'N' && cub->map.map[y][x] != 'S'
		&& cub->map.map[y][x] != 'E' && cub->map.map[y][x] != 'W'
		&& cub->map.map[y][x] != '1' && cub->map.map[y][x] != '0'
		&& cub->map.map[y][x] != 'D' && cub->map.map[y][x] != ' '
		&& cub->map.map[y][x] != '\n' && cub->map.map[y][x] != '\t'
		&& cub->map.map[y][x] != '\0')
		ft_error(cub, "Invalid character in map");
}

void	check_first_and_last_line(t_cub *cub)
{
	int	x;

	x = -1;
	while (++x < (int)ft_strlen(cub->map.map[0]))
	{
		if (cub->map.map[0][x] == '0' || is_player_or_door(cub, x, 0))
			ft_error(cub, "Walls are not valid or player / door is outside");
	}
	x = -1;
	while (++x < (int)ft_strlen(cub->map.map[cub->map.rows - 1]))
	{
		if (cub->map.map[cub->map.rows - 1][x] == '0'
			|| is_player_or_door(cub, x, cub->map.rows - 1))
			ft_error(cub, "Walls are not valid or player / door is outside");
	}
}

void	check_wall_player(t_cub *cub)
{
	bool	start;
	int		x;
	int		y;

	y = -1;
	check_first_and_last_line(cub);
	while (++y < cub->map.rows)
	{
		x = -1;
		start = false;
		while (++x <= (int)ft_strlen(cub->map.map[y]))
		{
			start = check_begin_end(cub, x, y, start);
			check_around_floor_player(cub, x, y);
			check_invalid_character(cub, x, y);
			take_info_from_player(cub, x, y);
		}
	}
	if (cub->map.player != 1)
		ft_error(cub, "Incorrect number of players");
}
