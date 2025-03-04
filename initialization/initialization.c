/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:31:34 by doferet           #+#    #+#             */
/*   Updated: 2025/03/04 15:20:27 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// static void	open_xpm(t_cub *cub)
// {
// 	int	img_size;

// 	img_size = SQUARE_SIZE;
// 	cub->texture.wall.img = mlx_xpm_file_to_image(cub->mlx_ptr, WALL,
// 			&img_size, &img_size);
// 	cub->texture.floor.img = mlx_xpm_file_to_image(cub->mlx_ptr, FLOOR,
// 			&img_size, &img_size);
// 	if (!cub->texture.wall.img || !cub->texture.floor.img)
// 		ft_error(cub, "XPM Error");
// }

static void	put_textures(t_cub *cub)
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
				put_img(cub->image, cub->texture.wall, SQUARE_SIZE * j, SQUARE_SIZE * i);
			if (cub->map.map[i][j] == '0')
				put_img(cub->image, cub->texture.floor, SQUARE_SIZE * j, SQUARE_SIZE * i);
		}
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->image.img, 0, 0);
}

static void	init_texture_image(t_cub *cub, t_img *image, char *path)
{
	image->width = 60;
	image->height = 60;
	image->img = mlx_xpm_file_to_image(cub->mlx_ptr, path, &image->width, &image->height);
	if (!image->img)
		ft_error(cub, "Load Image Error");
	image->addr = mlx_get_data_addr(image->img, &image->bpp, &image->line_len, &image->endian);
	if (!image->addr)
		ft_error(cub, "Texture Address Fail");
}

void	init_mlx(t_cub *cub)
{
	cub->mlx_ptr = mlx_init();
	if (!cub->mlx_ptr)
		ft_error(cub, "MLX Init Error");
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, cub->map.columns
			* SQUARE_SIZE, cub->map.rows * SQUARE_SIZE, "CUB_666");
	if (!cub->win_ptr)
		ft_error(cub, "MLX Window Error");
	cub->image.width = cub->map.columns * SQUARE_SIZE;
	cub->image.height = cub->map.rows * SQUARE_SIZE;
	cub->image.img = mlx_new_image(cub->mlx_ptr, cub->image.width, cub->image.height);
	if (!cub->image.img)
		ft_error(cub, "New Image Error");
	cub->image.addr = mlx_get_data_addr(cub->image.img, &(cub->image.bpp), &(cub->image.line_len), &(cub->image.endian));
	if (!cub->image.addr)
		ft_error(cub, "Address Error");
	//open_xpm(cub);
	init_texture_image(cub, &cub->texture.floor, FLOOR);
	init_texture_image(cub, &cub->texture.wall, WALL);
	put_textures(cub);
}

