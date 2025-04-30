/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 01:15:16 by rbalazs           #+#    #+#             */
/*   Updated: 2025/04/30 11:18:37 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	minimap_color(int i, int j, int k, t_cub *cub)
{
	int	x;
	int	y;

	y = -1;
	while (++y < k)
	{
		x = -1;
		while (++x < k)
		{
			if (cub->map.map[i][j] == '1')
				put_pixel(cub, j * k + x, i * k + y, rgb(111, 122, 193));
			else if (cub->map.map[i][j] == '0' || is_player(cub, j, i))
				put_pixel(cub, j * k + x, i * k + y, rgb(95, 105, 165));
			put_pixel(cub, cub->player_pos.posx * k + x,
				cub->player_pos.posy * k + y, rgb(255, 0, 0));
		}
	}
}

void	minimap(t_cub *cub)
{
	int	i;
	int	j;
	int	scale;

	scale = fmin(WIDTH / cub->map.cols / 8, HEIGHT / cub->map.rows / 8);
	i = -1;
	while (++i < cub->map.rows)
	{
		j = -1;
		while (++j < (int)ft_strlen(cub->map.map[i]))
		{
			minimap_color(i, j, scale, cub);
		}
	}
}

void	animated_weapon(t_cub *cub, int i, int j, t_img img)
{
	int	weapon_x;
	int	weapon_y;

	while (i < 600)
	{
		j = 0;
		while (j < 600)
		{
			weapon_x = j * cub->texture.jagpistol.width / 600;
			weapon_y = i * cub->texture.jagpistol.height / 600;
			if ((get_pixel_img(cub->texture.jagpistol, weapon_x,
						weapon_y) & 0x00FFFFFF) != 0)
			{
				put_pixel(cub, WIDTH / 2 - 300 + j, HEIGHT / 2 - 250
					+ i, get_pixel_img(img, weapon_x, weapon_y));
			}
			j++;
		}
		i++;
	}
}

void	print_weapon(t_cub *cub)
{
	int	actual_time;

	actual_time = get_time();
	if (actual_time - cub->saved_time > 750)
	{
		animated_weapon(cub, 0, 0, cub->texture.jagpistolred);
		if (actual_time - cub->saved_time > 1500)
			cub->lock_time = false;
	}
	else
	{
		animated_weapon(cub, 0, 0, cub->texture.jagpistol);
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
				HEIGHT / 2 + 400 - cub->texture.bar.height + i,
				get_pixel_img(cub->texture.bar, bar_x, bar_y));
			j++;
		}
		i++;
	}
}
