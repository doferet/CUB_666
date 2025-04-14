/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:05:24 by doferet           #+#    #+#             */
/*   Updated: 2025/04/14 18:07:26 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	is_valid_pos_wall_collision(t_cub *cub, double x, double y)
{
	if (cub->map.map[(int)y][(int)x] == '0')
		return (true);
	return (false);
}

static bool	is_valid_pos_in_map(double x, double y)
{
	if (x >= WIDTH)
		return (false);
	if (y >= HEIGHT)
		return (false);
	return (true);
}
static bool	is_valid_pos(t_cub *cub, double x, double y)
{
	if (is_valid_pos_in_map(x, y))
		return (true);
	if (is_valid_pos_wall_collision(cub, x, y))
		return (true);
	return (false);
}

static int	validate_move(t_cub *cub, double new_x, double new_y)
{
	int	moved;

	moved = 0;
	if (is_valid_pos(cub, new_x, cub->player_pos.posy))
	{
		cub->player_pos.posx = new_x;
		moved = 1;
	}
	if (is_valid_pos(cub, cub->player_pos.posx, new_y))
	{
		cub->player_pos.posy = new_y;
		moved = 1;
	}
	return (moved);
}

static int	move_player_forward(t_cub *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player_pos.posx + cub->player_pos.dirx * MOVESPEED;
	new_y = cub->player_pos.posy + cub->player_pos.diry * MOVESPEED;
	return (validate_move(cub, new_x, new_y));
}

static int	move_player_backward(t_cub *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player_pos.posx - cub->player_pos.dirx * MOVESPEED;
	new_y = cub->player_pos.posy - cub->player_pos.diry * MOVESPEED;
	return (validate_move(cub, new_x, new_y));
}

static int	move_player_left(t_cub *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player_pos.posx + cub->player_pos.diry * MOVESPEED;
	new_y = cub->player_pos.posy - cub->player_pos.dirx * MOVESPEED;
	return (validate_move(cub, new_x, new_y));
}

static int	move_player_right(t_cub *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player_pos.posx - cub->player_pos.diry * MOVESPEED;
	new_y = cub->player_pos.posy + cub->player_pos.dirx * MOVESPEED;
	return (validate_move(cub, new_x, new_y));
}

static int	rotate_left_right(t_cub *cub, double rotspeed)
{
	t_maths	*p;
	double		tmp_x;
	double		tmp_y;

	p = &cub->player_pos;
	tmp_x = p->dirx;
	p->dirx = p->dirx * cos(rotspeed) - p->diry * sin(rotspeed);
	p->diry = tmp_x * sin(rotspeed) + p->diry * cos(rotspeed);
	tmp_y = p->planx;
	p->planx = p->planx * cos(rotspeed) - p->plany * sin(rotspeed);
	p->plany = tmp_y * sin(rotspeed) + p->plany * cos(rotspeed);
	return (1);
}

static int	rotate_player(t_cub *cub, double rotdir)
{
	int		moved;
	double	rotspeed;

	moved = 0;
	rotspeed = ROTSPEED * rotdir;
	moved += rotate_left_right(cub, rotspeed);
	return (moved);
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
