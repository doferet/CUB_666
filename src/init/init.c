/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:31:34 by doferet           #+#    #+#             */
/*   Updated: 2025/04/10 18:33:59 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_texture_image(t_cub *cub, t_img *image, char *path)
{
	if (!path)
		ft_error(cub, "Texture path is NULL");
	image->width = SQUARE_SIZE;
	image->height = SQUARE_SIZE;
	image->img = mlx_xpm_file_to_image(cub->mlx_ptr, path, &image->width,
			&image->height);
	if (!image->img)
		ft_error(cub, "Load Image Error");
	image->addr = mlx_get_data_addr(image->img, &image->bpp, &image->line_len,
			&image->endian);
	if (!image->addr)
		ft_error(cub, "Texture Address Fail");
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
	init_texture_image(cub, &cub->texture.floor, FLOOR);
	init_texture_image(cub, &cub->texture.wall_ea, cub->datafile.ea);
	init_texture_image(cub, &cub->texture.wall_no, cub->datafile.no);
	init_texture_image(cub, &cub->texture.wall_so, cub->datafile.so);
	init_texture_image(cub, &cub->texture.wall_we, cub->datafile.we);
}

void	init_maths(t_maths *ray)
{
	ray->cam_orientation = 0;
	ray->dirx = 0;
	ray->diry = 0;
	ray->mapx = 0;
	ray->mapy = 0;
	ray->stepx = 0;
	ray->stepy = 0;
	ray->sidex = 0;
	ray->sidey = 0;
	ray->deltax = 0;
	ray->deltay = 0;
	ray->wall_dist = 0;
	ray->wall_x = 0;
	ray->side = 0;
	ray->line_height = 0;
	ray->start_line = 0;
	ray->end_line = 0;
	ray->move = 0;
	ray->move_x = 0;
	ray->move_y = 0;
}
