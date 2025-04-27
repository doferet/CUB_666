/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:31:34 by doferet           #+#    #+#             */
/*   Updated: 2025/04/27 01:05:38 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_texture_image(t_cub *cub, t_img *image, char *path)
{
	if (!path)
		ft_error(cub, "Texture path is NULL");
	image->width = WALL_SIZE;
	image->height = WALL_SIZE;
	image->img = mlx_xpm_file_to_image(cub->mlx_ptr, path, &image->width,
			&image->height);
	if (!image->img)
		ft_error(cub, "Load Image Error");
	image->addr = mlx_get_data_addr(image->img, &image->bpp, &image->line_len,
			&image->endian);
	if (!image->addr)
		ft_error(cub, "Texture Address Fail");
}

void	init_texture_bar(t_cub *cub, t_img *image, char *path)
{
	if (!path)
		ft_error(cub, "Texture path is NULL");
	image->width = 600;
	image->height = 93;
	image->img = mlx_xpm_file_to_image(cub->mlx_ptr, path, &image->width,
			&image->height);
	if (!image->img)
		ft_error(cub, "Load Image Error");
	image->addr = mlx_get_data_addr(image->img, &image->bpp, &image->line_len,
			&image->endian);
	if (!image->addr)
		ft_error(cub, "Texture Address Fail");
}

void	init_textures(t_cub *cub)
{
	init_texture_image(cub, &cub->texture.wall_ea, cub->datafile.ea);
	init_texture_image(cub, &cub->texture.wall_no, cub->datafile.no);
	init_texture_image(cub, &cub->texture.wall_so, cub->datafile.so);
	init_texture_image(cub, &cub->texture.wall_we, cub->datafile.we);
	init_texture_image(cub, &cub->texture.jagpistol, PISTOL);
	init_texture_image(cub, &cub->texture.jagpistolred, PISTOLRED);
	init_texture_image(cub, &cub->texture.menu, MENU);
	init_texture_image(cub, &cub->texture.space, SPACE);
	init_texture_image(cub, &cub->texture.door, DOOR);
	init_texture_image(cub, &cub->texture.door1, DOOR1);
	init_texture_image(cub, &cub->texture.helmet, HELMET);
	init_texture_bar(cub, &cub->texture.bar, BAR);
}

void	init_mlx(t_cub *cub)
{
	cub->mlx_ptr = mlx_init();
	if (!cub->mlx_ptr)
		ft_error(cub, "MLX Init Error");
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, WIDTH, HEIGHT, "CUB_666");
	if (!cub->win_ptr)
		ft_error(cub, "MLX Window Error");
	cub->image.width = WIDTH;
	cub->image.height = HEIGHT;
	cub->image.img = mlx_new_image(cub->mlx_ptr, cub->image.width,
			cub->image.height);
	if (!cub->image.img)
		ft_error(cub, "New Image Error");
	cub->image.addr = mlx_get_data_addr(cub->image.img, &(cub->image.bpp),
			&(cub->image.line_len), &(cub->image.endian));
	if (!cub->image.addr)
		ft_error(cub, "Address Error");
	init_textures(cub);
}
