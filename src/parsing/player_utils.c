/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:02:05 by rbalazs           #+#    #+#             */
/*   Updated: 2025/04/22 03:13:14 by rbalazs          ###   ########.fr       */
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

bool	is_player_or_door(t_cub *cub, int x, int y)
{
	if (cub->map.map[y][x] == 'N' || cub->map.map[y][x] == 'S'
		|| cub->map.map[y][x] == 'E' || cub->map.map[y][x] == 'W'
		|| cub->map.map[y][x] == 'D')
		return (true);
	return (false);
}

void	take_info_from_player(t_cub *cub, int x, int y)
{
	if (is_player(cub, x, y))
	{
		cub->player_pos.posx = (double)x;
		cub->player_pos.posy = (double)y;
		cub->player_pos.start_orientation = cub->map.map[y][x];
		cub->map.player++;
	}
}
