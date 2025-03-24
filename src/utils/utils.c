/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:02:56 by doferet           #+#    #+#             */
/*   Updated: 2025/03/18 15:52:00 by doferet          ###   ########.fr       */
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
	//fleches gauche droite + w s a d
	return (0);
}