/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:26:43 by doferet           #+#    #+#             */
/*   Updated: 2025/04/17 13:29:34 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	rgb(int r, int g, int b)
{
	return (0 << 24 | r << 16 | g << 8 | b);
}

void	put_pixel(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	dst = cub->image.addr + (y * cub->image.line_len + x
			* (cub->image.bpp / 8));
	*(unsigned int *)dst = color;
}

void	put_color_floor_ceiling(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT / 2)
	{
		j = -1;
		while (++j < WIDTH)
		{
			put_pixel(cub, j, i, rgb(cub->datafile.ceiling_red,
					cub->datafile.ceiling_green, cub->datafile.ceiling_blue));
		}
		i++;
	}
	while (i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
		{
			put_pixel(cub, j, i, rgb(cub->datafile.floor_red,
					cub->datafile.floor_green, cub->datafile.floor_blue));
		}
		i++;
	}
}
