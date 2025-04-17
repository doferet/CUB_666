/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:12:02 by doferet           #+#    #+#             */
/*   Updated: 2025/04/17 17:02:26 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

unsigned int	get_pixel_img(t_img img, int x, int y)
{
	return (*(unsigned int *)((img.addr + (y * img.line_len) + (x * img.bpp
				/ 8))));
}

void	put_pixel_img(t_img img, int x, int y, int color)
{
	char	*dst;

	if (color == (int)0xFF000000)
		return ;
	if (x >= 0 && y >= 0 && x < img.width && y < img.height)
	{
		dst = img.addr + (y * img.line_len + x * (img.bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	texture_loop(t_cub *cub, int screen_x, int screen_y)
{
	int		tex_x;
	double	tex_y;
	double	tex_step;

	tex_step = (double)WALL_SIZE / cub->ray.line_height;
	tex_x = cub->ray.wall_x * WALL_SIZE;
	tex_y = (screen_y - HEIGHT / 2 + cub->ray.line_height / 2) * tex_step;
	while (screen_y < cub->ray.end_line)
	{
		tex_y += tex_step;
		if (cub->ray.side == 0)
		{
			if (cub->ray.dirx < 0)
				put_pixel(cub, screen_x, screen_y,
					get_pixel_img(cub->texture.wall_ea, tex_x, (int)tex_y));
			else
				put_pixel(cub, screen_x, screen_y,
					get_pixel_img(cub->texture.wall_we, tex_x, (int)tex_y));
		}
		else
		{
			if (cub->ray.diry < 0)
				put_pixel(cub, screen_x, screen_y,
					get_pixel_img(cub->texture.wall_so, tex_x, (int)tex_y));
			else
				put_pixel(cub, screen_x, screen_y,
					get_pixel_img(cub->texture.wall_no, tex_x, (int)tex_y));
		}
		screen_y++;
	}
}

void	minimap(t_cub *cub)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	while (i < cub->map.rows)
	{
		j = 0;
		while (j < (int)ft_strlen(cub->map.map[i]))
		{
			y = 0;
			while (y < 8)
			{
				x = 0;
				while (x < 8)
				{
					if (cub->map.map[i][j] == '1')
						put_pixel(cub, j * 8 + x, i * 8 + y, rgb(47, 0, 255));
					else if (cub->map.map[i][j] == '0' || is_player(cub, j, i))
						put_pixel(cub, j * 8 + x, i * 8 + y, rgb(158, 146,
								146));
					put_pixel(cub, cub->player_pos.posx * 8 + x,
						cub->player_pos.posy * 8 + y, rgb(255, 0, 0));
					x++;
				}
				y++;
			}
			j++;
		}
		i++;
	}
}

void	print_weapon(t_cub *cub)
{
	int	i;
	int	j;
	int	weapon_x;
	int	weapon_y;

	i = 0;
	while (i < 600)
	{
		j = 0;
		while (j < 600)
		{
			weapon_x = j * cub->texture.jagpistol.width / 600;
			weapon_y = i * cub->texture.jagpistol.height / 600;
			if ((get_pixel_img(cub->texture.jagpistol, weapon_x,
						weapon_y) & 0x00FFFFFF) != 0)
				put_pixel(cub, WIDTH / 2 - 300 + j, HEIGHT / 2 - 200
					+ i, get_pixel_img(cub->texture.jagpistol, weapon_x,
						weapon_y));
			j++;
		}
		i++;
	}
}

void	print_bar(t_cub *cub)
{
	int	i;
	int	j;
	int	bar_x;
	int	bar_y;

	i = 0;
	while (i < cub->texture.bar.height * 2)
	{
		j = 0;
		while (j < cub->texture.bar.width * 2)
		{
			bar_x = j * cub->texture.bar.width / (cub->texture.bar.width * 2);
			bar_y = i * cub->texture.bar.height / (cub->texture.bar.height * 2);
			put_pixel(cub, WIDTH / 2 - cub->texture.bar.width + j,
				HEIGHT / 2 + 450 - cub->texture.bar.height + i,
				get_pixel_img(cub->texture.bar, bar_x, bar_y));
			j++;
		}
		i++;
	}
}
