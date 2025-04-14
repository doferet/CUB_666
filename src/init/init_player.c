/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 05:14:21 by rbalazs           #+#    #+#             */
/*   Updated: 2025/04/14 18:54:21 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"


static void	init_pos_north(t_cub *cub)
{
	cub->player_pos.dirx = 0.0;
	cub->player_pos.diry = -1.0;
	cub->player_pos.planx = 0.66;
	cub->player_pos.plany = 0;
}

static void	init_pos_south(t_cub *cub)
{
	cub->player_pos.dirx = 0;
	cub->player_pos.diry = 1.0;
	cub->player_pos.planx = -0.66;
	cub->player_pos.plany = 0.0;
}

static void	init_pos_east(t_cub *cub)
{
	cub->player_pos.dirx = 1;
	cub->player_pos.diry = 0;
	cub->player_pos.planx = 0;
	cub->player_pos.plany = 0.66;
}

static void	init_pos_west(t_cub *cub)
{
	cub->player_pos.dirx = -1;
	cub->player_pos.diry = 0;
	cub->player_pos.planx = 0;
	cub->player_pos.plany = -0.66;
}
void	init_player_pos(t_cub *cub)
{
	if (cub->player_pos.start_orientation == 'N')
		init_pos_north(cub);
	else if (cub->player_pos.start_orientation == 'S')
		init_pos_south(cub);
	else if (cub->player_pos.start_orientation == 'E')
		init_pos_east(cub);
	else if (cub->player_pos.start_orientation == 'W')
		init_pos_west(cub);
}