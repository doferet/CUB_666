/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:55:33 by doferet           #+#    #+#             */
/*   Updated: 2025/03/17 15:34:04 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	close_window(t_cub *f)
{
	mlx_loop_end(f->mlx_ptr);
	return (0);
}

int	main(int ac, char **av)
{
	t_cub	cub;

	ft_bzero(&cub, sizeof(t_cub));
	cub.texture.wall_ea.img = NULL;
	cub.texture.wall_no.img = NULL;
	cub.texture.wall_we.img = NULL;
	cub.texture.wall_so.img = NULL;
	
	if (parsing(&cub, ac, av) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	init_mlx(&cub);
	mlx_hook(cub.win_ptr, DST_N, StructureNotifyMask, close_window, &cub);
	mlx_loop(cub.mlx_ptr);
	ft_free_all(&cub);
	return (EXIT_SUCCESS);
}
