/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:59:10 by doferet           #+#    #+#             */
/*   Updated: 2025/04/24 17:03:56 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	print_bonus(t_cub *cub)
{
	minimap(cub);
	print_weapon(cub);
	print_bar(cub);
}

int	raycasting(t_cub *cub)
{
	int	x;
	int	y;

	x = -1;
	y = 0;
	put_color_floor_ceiling(cub);
	if (cub->lock_time == false)
	{
		cub->saved_time = get_time();
		cub->lock_time = true;
	}
	while (++x < WIDTH)
	{
		draw_ray(x, cub);
	}
	print_bonus(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->image.img, 0, 0);
	mlx_destroy_image(cub->mlx_ptr, cub->image.img);
	cub->image.img = mlx_new_image(cub->mlx_ptr, WIDTH, HEIGHT);
	cub->image.addr = mlx_get_data_addr(cub->image.img, &cub->image.bpp,
			&cub->image.line_len, &cub->image.endian);
	cub->player_pos.move = move_player(cub);
	mlx_mouse_get_pos(cub->mlx_ptr, cub->win_ptr, &x, &y);
	cub->player_pos.move_mouse_y = mouse_event(x, cub);
	return (0);
}
