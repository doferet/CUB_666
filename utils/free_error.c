/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:48:46 by doferet           #+#    #+#             */
/*   Updated: 2025/03/04 11:48:38 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	destroy_texture(t_cub *cub)
{
	if (cub->texture.wall.img)
		mlx_destroy_image(cub->mlx_ptr, cub->texture.wall.img);
	if (cub->texture.floor.img)
		mlx_destroy_image(cub->mlx_ptr, cub->texture.floor.img);
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
	ft_free_all(cub);
	exit(EXIT_FAILURE);
}

void	free_matrix(char **matrix)
{
	size_t	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
	matrix = NULL;
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
		mlx_destroy_display(cub->mlx_ptr);
		free(cub->mlx_ptr);
	}
	if (cub->map.map != NULL)
	{
		free_matrix(cub->map.map);
		cub->map.map = NULL;
	}
}
