/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:55:33 by doferet           #+#    #+#             */
/*   Updated: 2025/03/03 17:47:40 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

static void	open_xpm(t_cub *cub)
{
	int	img_size;

	img_size = SQUARE_SIZE;
	cub->texture.wall = mlx_xpm_file_to_image(cub->mlx_ptr, WALL,
			&img_size, &img_size);
	cub->texture.floor = mlx_xpm_file_to_image(cub->mlx_ptr, FLOOR,
			&img_size, &img_size);
	if (!cub->texture.wall || !cub->texture.floor)
		ft_error(cub, "XPM Error\n");
}

void	put_textures(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cub->map.rows)
	{
		j = -1;
		while (++j < cub->map.columns)
		{
			if (cub->map.map[i][j] == '1')
				mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr,
					cub->texture.wall, SQUARE_SIZE * j, SQUARE_SIZE * i);
			if (cub->map.map[i][j] == '0')
				mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr,
					cub->texture.floor, SQUARE_SIZE * j, SQUARE_SIZE * i);
		}
	}
}

void	init_mlx(t_cub *cub)
{
	cub->mlx_ptr = mlx_init();
	if (!cub->mlx_ptr)
		ft_error(cub, "MLX Init Error\n");
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, cub->map.columns
			* SQUARE_SIZE, cub->map.rows * SQUARE_SIZE, "CUB_666");
	if (!cub->win_ptr)
		ft_error(cub, "MLX Window Error\n");
	open_xpm(cub);
	put_textures(cub);
}

int	close_window(t_cub *f)
{
	mlx_loop_end(f->mlx_ptr);
	return (0);
}

int	main(int ac, char **av)
{
	t_cub	cub;

	ft_bzero(&cub, sizeof(t_cub));
	parsing(&cub, ac, av);
	init_mlx(&cub);
	print_tab(cub.map.map);
	mlx_hook(cub.win_ptr, DST_N, StructureNotifyMask, close_window, &cub);
	mlx_loop(cub.mlx_ptr);
	ft_free_all(&cub);
}
