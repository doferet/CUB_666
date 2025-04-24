/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:53:33 by doferet           #+#    #+#             */
/*   Updated: 2025/04/24 17:05:01 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	calcul(int x, t_cub *cub)
{
	cub->ray.cam_orientation = 2 * x / (double)WIDTH - 1;
	cub->ray.dirx = cub->player_pos.dirx + cub->player_pos.planx
		* cub->ray.cam_orientation;
	cub->ray.diry = cub->player_pos.diry + cub->player_pos.plany
		* cub->ray.cam_orientation;
	cub->ray.mapx = (int)cub->player_pos.posx;
	cub->ray.mapy = (int)cub->player_pos.posy;
	cub->ray.deltax = fabs(1 / cub->ray.dirx);
	cub->ray.deltay = fabs(1 / cub->ray.diry);
}

static void	calcul_2(t_cub *cub)
{
	if (cub->ray.dirx < 0)
	{
		cub->ray.stepx = -1;
		cub->ray.sidex = (cub->player_pos.posx - cub->ray.mapx)
			* cub->ray.deltax;
	}
	else
	{
		cub->ray.stepx = 1;
		cub->ray.sidex = (cub->ray.mapx + 1.0 - cub->player_pos.posx)
			* cub->ray.deltax;
	}
	if (cub->ray.diry < 0)
	{
		cub->ray.stepy = -1;
		cub->ray.sidey = (cub->player_pos.posy - cub->ray.mapy)
			* cub->ray.deltay;
	}
	else
	{
		cub->ray.stepy = 1;
		cub->ray.sidey = (cub->ray.mapy + 1.0 - cub->player_pos.posy)
			* cub->ray.deltay;
	}
}

static void	dda_algo(t_cub *cub)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (cub->ray.sidex < cub->ray.sidey)
		{
			cub->ray.sidex += cub->ray.deltax;
			cub->ray.mapx += cub->ray.stepx;
			cub->ray.side = 0;
		}
		else
		{
			cub->ray.sidey += cub->ray.deltay;
			cub->ray.mapy += cub->ray.stepy;
			cub->ray.side = 1;
		}
		if (cub->map.map[cub->ray.mapy][cub->ray.mapx] == '1'
			|| cub->map.map[cub->ray.mapy][cub->ray.mapx] == 'D')
			hit = 1;
	}
}

static void	height_of_line(t_cub *cub)
{
	if (cub->ray.side == 0)
		cub->ray.wall_dist = cub->ray.sidex - cub->ray.deltax;
	else
		cub->ray.wall_dist = cub->ray.sidey - cub->ray.deltay;
	cub->ray.line_height = (int)(HEIGHT / cub->ray.wall_dist);
	cub->ray.start_line = -(cub->ray.line_height) / 2 + HEIGHT / 2;
	if (cub->ray.start_line < 0)
		cub->ray.start_line = 0;
	cub->ray.end_line = cub->ray.line_height / 2 + HEIGHT / 2;
	if (cub->ray.end_line >= HEIGHT)
		cub->ray.end_line = HEIGHT - 1;
	if (cub->ray.side == 0)
		cub->ray.wall_x = cub->player_pos.posy + cub->ray.wall_dist
			* cub->ray.diry;
	else
		cub->ray.wall_x = cub->player_pos.posx + cub->ray.wall_dist
			* cub->ray.dirx;
	cub->ray.wall_x -= floor(cub->ray.wall_x);
}

void	draw_ray(int x, t_cub *cub)
{
	calcul(x, cub);
	calcul_2(cub);
	dda_algo(cub);
	height_of_line(cub);
	texture_loop(cub, x, cub->ray.start_line);
}
