/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:48:46 by doferet           #+#    #+#             */
/*   Updated: 2025/04/24 03:22:46 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	destroy_texture(t_cub *cub)
{
	if (cub->image.img)
		mlx_destroy_image(cub->mlx_ptr, cub->image.img);
	if (cub->texture.wall_ea.img)
		mlx_destroy_image(cub->mlx_ptr, cub->texture.wall_ea.img);
	if (cub->texture.wall_no.img)
		mlx_destroy_image(cub->mlx_ptr, cub->texture.wall_no.img);
	if (cub->texture.wall_so.img)
		mlx_destroy_image(cub->mlx_ptr, cub->texture.wall_so.img);
	if (cub->texture.wall_we.img)
		mlx_destroy_image(cub->mlx_ptr, cub->texture.wall_we.img);
	if (cub->texture.jagpistol.img)
		mlx_destroy_image(cub->mlx_ptr, cub->texture.jagpistol.img);
	if (cub->texture.jagpistolred.img)
		mlx_destroy_image(cub->mlx_ptr, cub->texture.jagpistolred.img);
	if (cub->texture.bar.img)
		mlx_destroy_image(cub->mlx_ptr, cub->texture.bar.img);
	if (cub->texture.menu.img)
		mlx_destroy_image(cub->mlx_ptr, cub->texture.menu.img);
	if (cub->texture.door.img)
		mlx_destroy_image(cub->mlx_ptr, cub->texture.door.img);
	if (cub->texture.door_open.img)
		mlx_destroy_image(cub->mlx_ptr, cub->texture.door_open.img);
	if (cub->texture.space.img)
		mlx_destroy_image(cub->mlx_ptr, cub->texture.space.img);
	if (cub->texture.helmet.img)
		mlx_destroy_image(cub->mlx_ptr, cub->texture.helmet.img);
}

void	ft_error(t_cub *cub, char *str)
{
	write(2, "Error : ", 8);
	while (*str)
	{
		write(2, str, 1);
		str++;
	}
	write(2, "\n", 1);
	if (cub)
		ft_free_all(cub);
	exit(EXIT_FAILURE);
}

void	free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		ft_free((void **)&matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	ft_free((void **)&matrix);
}

void	free_datafile(t_cub *cub)
{
	if (cub->datafile.no)
		ft_free((void **)&cub->datafile.no);
	if (cub->datafile.so)
		ft_free((void **)&cub->datafile.so);
	if (cub->datafile.we)
		ft_free((void **)&cub->datafile.we);
	if (cub->datafile.ea)
		ft_free((void **)&cub->datafile.ea);
}

void	ft_free_all(t_cub *cub)
{
	if (!cub)
		return ;
	destroy_texture(cub);
	if (cub->win_ptr != NULL)
		mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
	if (cub->mlx_ptr != NULL)
	{
		mlx_loop_end(cub->mlx_ptr);
		mlx_destroy_display(cub->mlx_ptr);
		free(cub->mlx_ptr);
	}
	if (cub->map.map != NULL)
	{
		free_matrix(cub->map.map);
		cub->map.map = NULL;
	}
	if (cub->file.file != NULL)
		free_matrix(cub->file.file);
	free_datafile(cub);
}
