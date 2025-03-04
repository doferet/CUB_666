/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:55:33 by doferet           #+#    #+#             */
/*   Updated: 2025/03/04 14:38:13 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

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
