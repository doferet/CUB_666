/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:02:05 by rbalazs           #+#    #+#             */
/*   Updated: 2025/04/14 18:07:45 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	is_player(t_cub *cub, int x, int y)
{
	if (cub->map.map[y][x] == 'N' || cub->map.map[y][x] == 'S'
		|| cub->map.map[y][x] == 'E' || cub->map.map[y][x] == 'W')
		return (true);
	return (false);
}

static void	check_around_player(t_cub *cub, int x, int y)
{
	if (is_player(cub, x, y) && cub->map.map[y][x - 1] == ' ')
		ft_error(cub, "Player is outside the map");
	if (is_player(cub, x, y) && cub->map.map[y][x + 1] == ' ')
		ft_error(cub, "Player is outside the map");
	if (is_player(cub, x, y) && (cub->map.map[y + 1][x] == ' ' || cub->map.map[y
			+ 1][x] == '\0' || cub->map.map[y + 1][x] == 0))
		ft_error(cub, "Player is outside the map");
	if (is_player(cub, x, y) && (cub->map.map[y - 1][x] == ' ' || cub->map.map[y
			- 1][x] == '\0' || cub->map.map[y - 1][x] == 0))
		ft_error(cub, "Player is outside the map");
}

static bool	check_begin_end(t_cub *cub, int x, int y, bool start)
{
	if (cub->map.map[y][x] == '1')
		start = true;
	if (is_player(cub, x, y) && start == false)
		ft_error(cub, "Player is outside the map");
	if (is_player(cub, x, 0))
		ft_error(cub, "Player is outside the map");
	if (is_player(cub, (int)ft_strlen(cub->map.map[y]) - 1, y))
		ft_error(cub, "Player is outside the map");
	return (start);
}

static void	take_info_from_player(t_cub *cub, int x, int y)
{
	if (is_player(cub, x, y))
	{
		cub->player_pos.posx = (double)x;
		cub->player_pos.posy = (double)y;
		cub->player_pos.start_orientation = cub->map.map[y][x];
		cub->map.player++;
	}
}

void	check_player(t_cub *cub)
{
	bool	start;
	int		x;
	int		y;

	y = -1;
	x = -1;
	start = false;
	while (x++ < (int)ft_strlen(cub->map.map[cub->map.rows - 1]))
	{
		if (is_player(cub, x, cub->map.rows - 1) == true)
			ft_error(cub, "Player is outside the map");
	}
	while (++y < cub->map.rows)
	{
		x = -1;
		start = false;
		while (++x < (int)ft_strlen(cub->map.map[y]))
		{
			start = check_begin_end(cub, x, y, start);
			take_info_from_player(cub, x, y);
			check_around_player(cub, x, y);
		}
	}
	if (cub->map.player != 1)
		ft_error(cub, "Incorrect number of players");
}
