/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:05:24 by doferet           #+#    #+#             */
/*   Updated: 2025/04/17 13:33:50 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	move_player_forward(t_cub *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player_pos.posx + cub->player_pos.dirx * MOVESPEED;
	new_y = cub->player_pos.posy + cub->player_pos.diry * MOVESPEED;
	return (valid_move(cub, new_x, new_y));
}

static int	move_player_backward(t_cub *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player_pos.posx - cub->player_pos.dirx * MOVESPEED;
	new_y = cub->player_pos.posy - cub->player_pos.diry * MOVESPEED;
	return (valid_move(cub, new_x, new_y));
}

static int	move_player_left(t_cub *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player_pos.posx + cub->player_pos.diry * MOVESPEED;
	new_y = cub->player_pos.posy - cub->player_pos.dirx * MOVESPEED;
	return (valid_move(cub, new_x, new_y));
}

static int	move_player_right(t_cub *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player_pos.posx - cub->player_pos.diry * MOVESPEED;
	new_y = cub->player_pos.posy + cub->player_pos.dirx * MOVESPEED;
	return (valid_move(cub, new_x, new_y));
}

int	move_player(t_cub *cub)
{
	int	moved;

	moved = 0;
	if (cub->player_pos.move_y == 1)
		moved += move_player_forward(cub);
	if (cub->player_pos.move_y == -1)
		moved += move_player_backward(cub);
	if (cub->player_pos.move_x == -1)
		moved += move_player_left(cub);
	if (cub->player_pos.move_x == 1)
		moved += move_player_right(cub);
	if (cub->player_pos.rotate != 0)
		moved += rotate_player(cub, cub->player_pos.rotate);
	return (moved);
}
