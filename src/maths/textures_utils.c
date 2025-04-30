/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 01:26:57 by rbalazs           #+#    #+#             */
/*   Updated: 2025/04/30 11:09:00 by rbalazs          ###   ########.fr       */
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

void	animation_time(t_cub *cub)
{
	if (cub->lock_time == false)
	{
		cub->saved_time = get_time();
		cub->lock_time = true;
	}
	if (cub->lock_time_anim == false)
	{
		cub->anim_time = get_time();
		cub->lock_time_anim = true;
	}
}

void	print_bonus(t_cub *cub)
{
	print_weapon(cub);
	print_bar(cub);
	minimap(cub);
}
