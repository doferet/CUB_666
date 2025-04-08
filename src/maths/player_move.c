/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:05:24 by doferet           #+#    #+#             */
/*   Updated: 2025/04/07 15:46:33 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	orientation(t_cub *cub)
{
	if (cub->player_pos.start_orientation == 'N')
	{
		cub->player_pos.dirx = -1.0;
		cub->player_pos.diry = 0.0;
		cub->player_pos.planx = 0.0;
		cub->player_pos.plany = 0.66;
	}
	else if (cub->player_pos.start_orientation == 'S')
	{
		cub->player_pos.dirx = 1.0;
		cub->player_pos.diry = 0.0;
		cub->player_pos.planx = 0.0;
		cub->player_pos.plany = -0.66;
	}
	else if (cub->player_pos.start_orientation == 'W')
	{
		cub->player_pos.dirx = 0.0;
		cub->player_pos.diry = -1.0;
		cub->player_pos.planx = -0.66;
		cub->player_pos.plany = 0.0;
	}
	else if (cub->player_pos.start_orientation == 'E')
	{
		cub->player_pos.dirx = 0.0;
		cub->player_pos.diry = 1.0;
		cub->player_pos.planx = 0.66;
		cub->player_pos.plany = 0.00;
	}
}
