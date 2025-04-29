/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:32:21 by doferet           #+#    #+#             */
/*   Updated: 2025/04/29 11:39:38 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	is_wall_collision(t_cub *cub, double x, double y)
{
	if (cub->map.map[(int)y][(int)x] == '1'
		|| cub->map.map[(int)y][(int)x] == 'D')
		return (true);
	return (false);
}

bool	is_valid_pos(t_cub *cub, double x, double y)
{
	if (is_wall_collision(cub, x, y))
		return (false);
	return (true);
}

int	valid_move(t_cub *cub, double new_x, double new_y)
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

int	rotate_left_right(t_cub *cub, double rotspeed)
{
	t_maths	*p;
	double	tmp_x;
	double	tmp_y;

	p = &cub->player_pos;
	tmp_x = p->dirx;
	p->dirx = p->dirx * cos(rotspeed) - p->diry * sin(rotspeed);
	p->diry = tmp_x * sin(rotspeed) + p->diry * cos(rotspeed);
	tmp_y = p->planx;
	p->planx = p->planx * cos(rotspeed) - p->plany * sin(rotspeed);
	p->plany = tmp_y * sin(rotspeed) + p->plany * cos(rotspeed);
	return (1);
}

int	rotate_player(t_cub *cub, double rotdir)
{
	int		moved;
	double	rotspeed;

	moved = 0;
	rotspeed = ROTSPEED * rotdir;
	moved += rotate_left_right(cub, rotspeed);
	return (moved);
}
