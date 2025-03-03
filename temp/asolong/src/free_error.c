/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:51:50 by rbalazs           #+#    #+#             */
/*   Updated: 2024/07/06 20:15:42 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/solong.h"

void	ft_error(t_data *data, char *str)
{
	write(2, "Error : ", 8);
	while (*str)
	{
		write(2, str, 1);
		str++;
	}
	write(2, "\n", 1);
	ft_free_all(data);
	exit(EXIT_FAILURE);
}

void	destroy_square(t_data *data)
{
	if (data->square.wall)
		mlx_destroy_image(data->mlx.mlx_ptr, data->square.wall);
	if (data->square.floor)
		mlx_destroy_image(data->mlx.mlx_ptr, data->square.floor);
	if (data->square.player)
		mlx_destroy_image(data->mlx.mlx_ptr, data->square.player);
	if (data->square.collectible)
		mlx_destroy_image(data->mlx.mlx_ptr, data->square.collectible);
	if (data->square.exit)
		mlx_destroy_image(data->mlx.mlx_ptr, data->square.exit);
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

void	ft_free_all(t_data *data)
{
	if (!data)
		return ;
	destroy_square(data);
	if (data->mlx.win_ptr != NULL)
		mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.win_ptr);
	if (data->mlx.mlx_ptr != NULL)
	{
		mlx_destroy_display(data->mlx.mlx_ptr);
		free(data->mlx.mlx_ptr);
	}
	if (data->map.map != NULL)
	{
		free_matrix(data->map.map);
		data->map.map = NULL;
	}
}

int	exit_game(t_data *data)
{
	ft_free_all(data);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
