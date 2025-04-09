/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:53:33 by doferet           #+#    #+#             */
/*   Updated: 2025/04/09 15:15:52 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	calcul(int x, t_cub *cub)
{
	cub->player_pos.cam_orientation = 2 * x / (double)WIDTH - 1;
	cub->player_pos.dirx = cub->player_pos.dirx + cub->player_pos.planx
		* cub->player_pos.cam_orientation;
	cub->player_pos.diry = cub->player_pos.diry + cub->player_pos.plany
		* cub->player_pos.cam_orientation;
	cub->player_pos.deltax = fabs(1 / cub->player_pos.raydirx);
	cub->player_pos.deltay = fabs(1 / cub->player_pos.raydirx);
}

static void	calcul_2(t_cub *cub)
{
	if (cub->player_pos.dirx < 0)
	{
		cub->player_pos.stepx = -1;
		cub->player_pos.sidex = (cub->player_pos.posx - cub->player_pos.mapx)
			* cub->player_pos.deltax;
	}
	else
	{
		cub->player_pos.stepx = 1;
		cub->player_pos.sidex = (cub->player_pos.mapx + 1.0
				- cub->player_pos.posx) * cub->player_pos.deltax;
	}
	if (cub->player_pos.diry < 0)
	{
		cub->player_pos.stepy = -1;
		cub->player_pos.sidey = (cub->player_pos.posy - cub->player_pos.mapy)
			* cub->player_pos.deltay;
	}
	else
	{
		cub->player_pos.stepy = 1;
		cub->player_pos.sidey = (cub->player_pos.mapy + 1.0
				- cub->player_pos.posy) * cub->player_pos.deltay;
	}
}

// static void	dda_algo(t_cub *cub)
// {
// 	int	hit;

// 	hit = 0;
// 	while (hit == 0)
// 	{
// 		if (cub->player_pos.sidex < cub->player_pos.sidey)
// 		{
// 			cub->player_pos.sidex += cub->player_pos.deltax;
// 			cub->player_pos.mapx += cub->player_pos.stepx;
// 			cub->player_pos.side = 0;
// 		}
// 		else
// 		{
// 			cub->player_pos.sidey += cub->player_pos.deltay;
// 			cub->player_pos.mapy += cub->player_pos.stepy;
// 			cub->player_pos.side = 1;
// 		}
// 		if (cub->player_pos.mapx < cub->map.columns
// 			&& cub->player_pos.mapy < cub->map.rows
// 			&& cub->map.map[cub->player_pos.mapy][cub->player_pos.mapx] > 0)
// 		{
// 			hit = 1;
// 		}
// 	}
// }

// static void	height_of_line(t_cub *cub)
// {
// 	if (cub->player_pos.side == 0)
// 		cub->player_pos.wall_dist = cub->player_pos.sidex
// 			- cub->player_pos.deltax;
// 	else
// 		cub->player_pos.wall_dist = cub->player_pos.sidey
// 			- cub->player_pos.deltay;
// 	cub->player_pos.line_height = (int)(HEIGHT / cub->player_pos.wall_dist);
// 	cub->player_pos.start_line = -(cub->player_pos.line_height) / 2 + HEIGHT
// 		/ 2;
// 	if (cub->player_pos.start_line < 0)
// 		cub->player_pos.start_line = 0;
// 	cub->player_pos.end_line = cub->player_pos.line_height / 2 + HEIGHT / 2;
// 	if (cub->player_pos.end_line >= HEIGHT)
// 		cub->player_pos.end_line = HEIGHT - 1;
// 	if (cub->player_pos.side == 0)
// 		cub->player_pos.wall_x = cub->player_pos.posy
// 			+ cub->player_pos.wall_dist * cub->player_pos.diry;
// 	else
// 		cub->player_pos.wall_x = cub->player_pos.posx
// 			+ cub->player_pos.wall_dist * cub->player_pos.dirx;
// 	cub->player_pos.wall_x -= floor(cub->player_pos.wall_x);
// }

int	raycasting(t_cub *cub)
{
	int	x;

	x = 0;
	put_color_floor_ceiling(cub);
	while (x < WIDTH)
	{
		calcul(x, cub);
		calcul_2(cub);
		//dda_algo(cub);
		//height_of_line(cub);
		//put_textures(cub);
		x++;
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->image.img, 0, 0);
	mlx_destroy_image(cub->mlx_ptr, cub->image.img);
	cub->image.img = mlx_new_image(cub->mlx_ptr, WIDTH, HEIGHT);
	cub->image.addr = mlx_get_data_addr(cub->image.img, &cub->image.bpp,
			&cub->image.line_len, &cub->image.endian);
	return (0);
}
