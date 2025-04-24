/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:02:56 by doferet           #+#    #+#             */
/*   Updated: 2025/04/24 17:06:29 by doferet          ###   ########.fr       */
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
	if (button == XK_Control_L)
	{
		cub->player_pos.inverse = !cub->player_pos.inverse;
		if (!cub->player_pos.inverse)
			mlx_mouse_move(cub->mlx_ptr, cub->win_ptr, WIDTH / 2, HEIGHT / 2);
	}
	if (button == XK_p)
		cub->menu = !cub->menu;
	return (0);
}

int	key_release(int button, t_cub *cub)
{
	if (button == XK_Escape)
		mlx_loop_end(cub->mlx_ptr);
	if (button == XK_w && cub->player_pos.move_y == 1)
		cub->player_pos.move_y = 0;
	if (button == XK_s && cub->player_pos.move_y == -1)
		cub->player_pos.move_y = 0;
	if (button == XK_d && cub->player_pos.move_x == 1)
		cub->player_pos.move_x = 0;
	if (button == XK_a && cub->player_pos.move_x == -1)
		cub->player_pos.move_x = 0;
	if (button == XK_Left && cub->player_pos.rotate <= 1)
		cub->player_pos.rotate = 0;
	if (button == XK_Right && cub->player_pos.rotate >= -1)
		cub->player_pos.rotate = 0;
	return (0);
}

int	mouse_event(int x, t_cub *cub)
{
	int		dir_mouse_x;
	double	rotate;

	rotate = 0.025;
	dir_mouse_x = x - cub->player_pos.move_mouse_x;
	cub->player_pos.move_mouse_x = x;
	if (dir_mouse_x != 0)
	{
		if (cub->player_pos.move_mouse_x > WIDTH / 2)
			rotate_left_right(cub, rotate);
		else
			rotate_left_right(cub, -rotate);
	}
	if (!cub->player_pos.inverse)
		mlx_mouse_move(cub->mlx_ptr, cub->win_ptr, WIDTH / 2, HEIGHT / 2);
	return (0);
}
