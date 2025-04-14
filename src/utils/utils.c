/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:02:56 by doferet           #+#    #+#             */
/*   Updated: 2025/04/14 19:47:43 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

int	key_event(int button, t_cub *cub)
{
	if (button == XK_Escape)
		mlx_loop_end(cub->mlx_ptr);
	if (button == XK_Left)
		cub->player_pos.rotate -= 1;
	if (button == XK_Right)
		cub->player_pos.rotate += 1;
	if (button == XK_w)
		cub->player_pos.move_y = 1;
	if (button == XK_d)
		cub->player_pos.move_x = 1;
	if (button == XK_s)
		cub->player_pos.move_y = -1;
	if (button == XK_a)
		cub->player_pos.move_x = -1;
	return (0);
}

int key_release(int button, t_cub *cub)
{
	if (button == XK_Escape)
		mlx_loop_end(cub->mlx_ptr);
	if (button == XK_w && cub->player_pos.move_y == 1)
		cub->player_pos.move_y = 0;
	if (button == XK_s && cub->player_pos.move_y == -1)
		cub->player_pos.move_y = 0;
	if (button == XK_d && cub->player_pos.move_x == 1)
		cub->player_pos.move_x += 1;
	if (button == XK_a && cub->player_pos.move_x == -1)
		cub->player_pos.move_x -= 1;
	if (button == XK_Left && cub->player_pos.rotate <= 1)
		cub->player_pos.rotate = 0;
	if (button == XK_Right && cub->player_pos.rotate >= -1)
		cub->player_pos.rotate = 0;
	return (0);
}
