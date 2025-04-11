/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:53:33 by doferet           #+#    #+#             */
/*   Updated: 2025/04/11 19:11:23 by doferet          ###   ########.fr       */
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
		if (cub->map.map[cub->ray.mapx][cub->ray.mapy] > '0') 
		{
			hit = 1;
		}
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
		cub->ray.wall_x = cub->player_pos.posy + cub->ray.wall_dist * cub->ray.diry;
	else
		cub->ray.wall_x = cub->player_pos.posx + cub->ray.wall_dist * cub->ray.dirx;
	cub->ray.wall_x -= floor(cub->ray.wall_x);
}

// static void	put_pixel_img(t_img img, int x, int y, int color)
// {
// 	char	*dst;

// 	if (color == (int)0xFF000000)
// 		return ;
// 	if (x >= 0 && y >= 0 && x < img.width && y < img.height)
// 	{
// 		dst = img.addr + (y * img.line_len + x * (img.bpp / 8));
// 		*(unsigned int *)dst = color;
// 	}
// }

// void	texture_loop(t_cub *cub, int x)
// {
// 	int				i;

// 	i = cub->ray.start_line;
// 	while (i < cub->ray.end_line)
// 	{
// 		if (cub->ray.side == 1)
// 			put_pixel_img(dst, x + i, y + j, get_pixel_img(src, i, j));
// 		else
// 			put_pixel_img(dst, x + i, y + j, get_pixel_img(src, i, j));
// 		i++;
// 	}
// }

static unsigned int	get_pixel_img(t_img img, int x, int y)
{
	return (*(unsigned int *)((img.addr + (y * img.line_len) + (x * img.bpp
				/ 8))));
}

void	texture_loop(t_cub *cub, int x)
{
	int				i;
	int				index_img;

	index_img = 0;

	i = cub->ray.start_line;
	while (i < cub->ray.end_line)
	{
		if (cub->ray.side == 1)
			//cub-> = mlx_xpm_file_to_image(cub->mlx_ptr, "./textures/floor.xpm", &x, &i);
			put_pixel(cub, x, i, get_pixel_img(cub->texture.wall_ea, 0, 0));
		else
			put_pixel(cub, x, i, 0xfc9797);
		i++;
		index_img++;
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
	cub->player_pos.move = move_player(cub);
	return (0);
}
