/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_datafile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:07:55 by rbalazs           #+#    #+#             */
/*   Updated: 2025/03/28 18:46:30 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	read_textures(char *str, int i, t_cub *cub)
{
	if (str[i] == 'N' && str[i + 1] == 'O')
	{
		check_texture_no(str, i + 2, cub);
		return (true);
	}
	else if (str[i] == 'S' && str[i + 1] == 'O')
	{
		check_texture_so(str, i + 2, cub);
		return (true);
	}
	else if (str[i] == 'W' && str[i + 1] == 'E')
	{
		check_texture_we(str, i + 2, cub);
		return (true);
	}
	else if (str[i] == 'E' && str[i + 1] == 'A')
	{
		check_texture_ea(str, i + 2, cub);
		return (true);
	}
	return (false);
}

static bool	read_color(char *str, int i, t_cub *cub)
{
	if (str[i] == 'F')
	{
		if (cub->datafile.b_floor == true)
			ft_error(cub, "Floor color already set");
		cub->datafile.b_floor = true;
		check_wrong_char_color(str, i + 1, cub);
		check_color_floor(str, i + 1, cub);
		return (true);
	}
	else if (str[i] == 'C')
	{
		if (cub->datafile.b_ceiling == true)
			ft_error(cub, "Ceiling color already set");
		cub->datafile.b_ceiling = true;
		check_wrong_char_color(str, i + 1, cub);
		check_color_ceiling(str, i + 1, cub);
		return (true);
	}
	return (false);
}

void	check_data(char *str, t_cub *cub)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[0] != '\n' && !read_textures(str, i, cub) && !read_color(str, i,
			cub))
		ft_error(cub, "Invalid data");
	printf("FLOOR : %d %d %d\n", cub->datafile.floor_red,
		cub->datafile.floor_green, cub->datafile.floor_blue);
	printf("CEILING : %d %d %d\n", cub->datafile.ceiling_red,
		cub->datafile.ceiling_green, cub->datafile.ceiling_blue);
	check_color(cub);
	if (cub->datafile.b_no == true && cub->datafile.b_so == true
		&& cub->datafile.b_we == true && cub->datafile.b_ea == true
		&& cub->datafile.b_floor == true && cub->datafile.b_ceiling == true)
		cub->datafile.all_values = true;
}
