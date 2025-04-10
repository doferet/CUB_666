/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:53:33 by doferet           #+#    #+#             */
/*   Updated: 2025/04/10 10:08:40 by rbalazs          ###   ########.fr       */
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
	cub->ray.deltax = fabs(1 / cub->ray.dirx);
	cub->ray.deltay = fabs(1 / cub->ray.diry);
	printf("\033[0;34mray.dirx: %f | ray.diry: %f\033[0m\n", cub->ray.dirx,
		cub->ray.diry);
	printf("\033[0;34mcam_orientation: %f\033[0m\n", cub->ray.cam_orientation);
	printf("\033[0;34mray.deltax: %f | ray.deltay: %f\033[0m\n",
		cub->ray.deltax, cub->ray.deltay);
	cub->ray.mapx = (int)cub->player_pos.posx;
	cub->ray.mapy = (int)cub->player_pos.posy;
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
		printf("\033[0;32mmapx: %d | mapy: %d\033[0m\n", cub->ray.mapx, cub->ray.mapy);
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
		if (cub->map.map[cub->ray.mapx][cub->ray.mapy] > '0') 
		{
			printf("\033[0;33mHit\033[0m\n");
			printf("\033[0;31mmapx: %d | mapy: %d\033[0m\n", cub->ray.mapx,
				cub->ray.mapy);
			hit = 1;
		}
	}
}

static void	height_of_line(t_cub *cub)
{
	printf("\033[0;31msidex: %f | sidey: %f | deltax: %f | deltay: %f\033[0m\n",
		cub->ray.sidex, cub->ray.sidey, cub->ray.deltax, cub->ray.deltay);
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
		cub->ray.wall_x = cub->ray.posy + cub->ray.wall_dist * cub->ray.diry;
	else
		cub->ray.wall_x = cub->ray.posx + cub->ray.wall_dist * cub->ray.dirx;
	cub->ray.wall_x -= floor(cub->ray.wall_x);
	printf("\033[0;91mwall_dist: %f | line_height: %d | start: %d | end: %d\033[0m\n", cub->ray.wall_dist, cub->ray.line_height,
		cub->ray.start_line, cub->ray.end_line);
}

void	texture_loop(t_cub *cub, int x)
{
	int				i;

	i = cub->ray.start_line;
	while (i < cub->ray.end_line)
	{
		if (cub->ray.side == 1)
			put_pixel(cub, x, i, 0x00800000);
		else
			put_pixel(cub, x, i, 0x00FF0000);
		i++;
	}
}

int	raycasting(t_cub *cub)
{
	int	x;

	x = 0;
	put_color_floor_ceiling(cub);
	while (x < WIDTH)
	{
		calcul(x, cub);
		calcul_2(cub);
		dda_algo(cub);
		height_of_line(cub);
		texture_loop(cub, x);
		x++;
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->image.img, 0, 0);
	mlx_destroy_image(cub->mlx_ptr, cub->image.img);
	cub->image.img = mlx_new_image(cub->mlx_ptr, WIDTH, HEIGHT);
	cub->image.addr = mlx_get_data_addr(cub->image.img, &cub->image.bpp,
			&cub->image.line_len, &cub->image.endian);
	return (0);
}
