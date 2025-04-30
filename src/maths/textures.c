/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:12:02 by doferet           #+#    #+#             */
/*   Updated: 2025/04/30 11:04:54 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	print_doors(t_cub *cub, int screen_x, int screen_y)
{
	int	tex_door;

	tex_door = get_pixel_img(cub->texture.door, cub->ray.tex_x,
			(int)cub->ray.tex_y);
	if (cub->map.map[cub->ray.mapy][cub->ray.mapx] == 'D')
	{
		if ((tex_door & 0x00FFFFFF) != 0)
			put_pixel(cub, screen_x, screen_y, tex_door);
	}
}

void	put_oriented_walls(t_cub *cub, int screen_x, int screen_y)
{
	if (cub->map.map[cub->ray.mapy][cub->ray.mapx] == '1')
	{
		if (cub->ray.side == 0)
		{
			if (cub->ray.dirx < 0)
				put_pixel(cub, screen_x, screen_y,
					get_pixel_img(cub->texture.wall_ea, cub->ray.tex_x,
						(int)cub->ray.tex_y));
			else
				put_pixel(cub, screen_x, screen_y,
					get_pixel_img(cub->texture.wall_we, cub->ray.tex_x,
						(int)cub->ray.tex_y));
		}
		else
		{
			if (cub->ray.diry < 0)
				put_pixel(cub, screen_x, screen_y,
					get_pixel_img(cub->texture.wall_so, cub->ray.tex_x,
						(int)cub->ray.tex_y));
			else
				put_pixel(cub, screen_x, screen_y,
					get_pixel_img(cub->texture.wall_no, cub->ray.tex_x,
						(int)cub->ray.tex_y));
		}
	}
}

void	texture_loop(t_cub *cub, int screen_x, int screen_y)
{
	double	tex_step;

	tex_step = (double)WALL_SIZE / cub->ray.line_height;
	cub->ray.tex_x = cub->ray.wall_x * WALL_SIZE;
	cub->ray.tex_y = (screen_y - HEIGHT / 2 + cub->ray.line_height / 2)
		* tex_step;
	while (screen_y < cub->ray.end_line)
	{
		cub->ray.tex_y += tex_step;
		put_oriented_walls(cub, screen_x, screen_y);
		print_doors(cub, screen_x, screen_y);
		screen_y++;
	}
}
