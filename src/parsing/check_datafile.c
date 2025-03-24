/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_datafile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:07:55 by rbalazs           #+#    #+#             */
/*   Updated: 2025/03/24 12:02:50 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	read_textures(char *str, t_cub *cub)
{
	if (str[0] == 'N' && str[1] == 'O')
		check_texture_no(str, cub);
	else if (str[0] == 'S' && str[1] == 'O')
		check_texture_so(str, cub);
	else if (str[0] == 'W' && str[1] == 'E')
		check_texture_we(str, cub);
	else if (str[0] == 'E' && str[1] == 'A')
		check_texture_ea(str, cub);
}

static void	read_color(char *str, t_cub *cub)
{
	if (str[0] == 'F')
	{
		if (cub->datafile.b_floor == true)
			ft_error(cub, "Floor color already set");
		cub->datafile.b_floor = true;
		check_wrong_char_color(str, cub);
		check_color_floor(str, cub);
	}
	else if (str[0] == 'C')
	{
		if (cub->datafile.b_ceiling == true)
			ft_error(cub, "Ceiling color already set");
		cub->datafile.b_ceiling = true;
		check_wrong_char_color(str, cub);
		check_color_ceiling(str, cub);
	}
}

void	check_data(char *str, t_cub *cub)
{
	if (str[0] != '\n' && str[0] != 'N' && str[0] != 'S'
		&& str[0] != 'E' && str[0] != 'W' && str[0] != 'F' && str[0] != 'C')
		ft_error(cub, "Invalid data");
	read_textures(str, cub);
	read_color(str, cub);
	check_color(cub);
	if (cub->datafile.b_no == true && cub->datafile.b_so == true
		&& cub->datafile.b_we == true && cub->datafile.b_ea == true
		&& cub->datafile.b_floor == true && cub->datafile.b_ceiling == true)
		cub->datafile.all_values = true;
}
