/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:05:24 by doferet           #+#    #+#             */
/*   Updated: 2025/04/02 11:56:45 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	orientation(t_cub *cub)
{
	if (cub->player_pos.start_orientation == 'N')
	{
		//! 1
	}
	else if (cub->player_pos.start_orientation == 'S')
	{
		//? -1
	}
	else if (cub->player_pos.start_orientation == 'W')
	{
		//? -1
	}
	else if (cub->player_pos.start_orientation == 'E')
	{
		//! 1
	}
}
