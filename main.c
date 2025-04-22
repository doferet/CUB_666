/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:55:33 by doferet           #+#    #+#             */
/*   Updated: 2025/04/21 02:07:37 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int	close_window(t_cub *f)
{
	mlx_loop_end(f->mlx_ptr);
	return (0);
}

int	menu(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT / 2 - 400)
	{
		j = -1;
		while (++j < WIDTH)
		{
			put_pixel(cub, j, i, rgb(255, 84, 84));
			
		}
		i++;
	}
	while (i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
		{
			put_pixel(cub, j, i, rgb(112, 0, 0));
		}
		i++;
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->image.img, 0, 0);
	mlx_destroy_image(cub->mlx_ptr, cub->image.img);
	cub->image.img = mlx_new_image(cub->mlx_ptr, WIDTH, HEIGHT);
	cub->image.addr = mlx_get_data_addr(cub->image.img, &cub->image.bpp,
			&cub->image.line_len, &cub->image.endian);
	return(0);
}


int	loop_handler(t_cub *cub)
{
	if (cub->menu)
		menu(cub);
	else
		raycasting(cub);
	return (0);
}

int	main(int ac, char **av)
{
	t_cub	cub;

	ft_bzero(&cub, sizeof(t_cub));
	cub.menu = false;
	if (parsing(&cub, ac, av) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	init_player_pos(&cub);
	init_mlx(&cub);
	mlx_loop_hook(cub.mlx_ptr, loop_handler, &cub);
	mlx_key_hook(cub.win_ptr, key_event, &cub);
	mlx_hook(cub.win_ptr, KeyPress, KeyPressMask, key_event, &cub);
	mlx_hook(cub.win_ptr, KeyRelease, KeyReleaseMask, key_release, &cub);
	mlx_hook(cub.win_ptr, DST_N, StructureNotifyMask, close_window, &cub);
	mlx_loop(cub.mlx_ptr);
	ft_free_all(&cub);
	return (0);
}

