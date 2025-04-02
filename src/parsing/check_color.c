/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:27:35 by rbalazs           #+#    #+#             */
/*   Updated: 2025/04/02 12:28:05 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	verif_doublecomma(t_cub *cub, char *str)
{
	int		i;
	int		j;
	bool	is_double;

	i = 0;
	j = 0;
	is_double = false;
	while (str[i])
	{
		j = i;
		is_double = false;
		while (str[j] == ' ' || str[j] == ',' || str[j] == '\t'
			|| str[j] == '\r' || str[j] == '\v' || str[j] == '\f')
		{
			if (str[j] == ',' && is_double == true)
				ft_error(cub, "Multiple comma detected");
			if (str[j] == ',')
				is_double = true;
			j++;
		}
		i++;
	}
}

void	check_color(t_cub *cub)
{
	if (cub->datafile.floor_red < 0 || cub->datafile.floor_red > 255)
		ft_error(cub, "Color Error : Floor Red");
	if (cub->datafile.floor_green < 0 || cub->datafile.floor_green > 255)
		ft_error(cub, "Color Error : Floor Green");
	if (cub->datafile.floor_blue < 0 || cub->datafile.floor_blue > 255)
		ft_error(cub, "Color Error : Floor Blue");
	if (cub->datafile.ceiling_red < 0 || cub->datafile.ceiling_red > 255)
		ft_error(cub, "Color Error : Ceiling Red");
	if (cub->datafile.ceiling_green < 0 || cub->datafile.ceiling_green > 255)
		ft_error(cub, "Color Error : Ceiling Green");
	if (cub->datafile.ceiling_blue < 0 || cub->datafile.ceiling_blue > 255)
		ft_error(cub, "Color Error : Ceiling Blue");
}

char	*construct_number(char *str, int *i, t_cub *cub, bool start)
{
	char	*number;

	verif_doublecomma(cub, str);
	number = malloc(sizeof(char) * 1);
	if (!number)
		ft_error(cub, "Malloc Error");
	number[0] = '\0';
	while (str[*i] == ' ' || str[*i] == ',' || str[*i] == '\t'
		|| str[*i] == '\r' || str[*i] == '\v' || str[*i] == '\f')
	{
		if (str[*i] == ',' && start == true)
		{
			free(number);
			ft_error(cub, "No number before comma");
		}
		(*i)++;
	}
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		number = ft_charjoin(number, str[*i], cub);
		(*i)++;
	}
	return (number);
}

void	check_color_floor(char *str, int i, t_cub *cub)
{
	char	*number;

	cub->datafile.b_floor = true;
	number = construct_number(str, &i, cub, true);
	cub->datafile.floor_red = ft_atoi(number);
	free(number);
	number = construct_number(str, &i, cub, false);
	cub->datafile.floor_green = ft_atoi(number);
	free(number);
	number = construct_number(str, &i, cub, false);
	if (number[0] == '\0')
	{
		free(number);
		ft_error(cub, "Missing value after comma for the floor");
	}
	cub->datafile.floor_blue = ft_atoi(number);
	free(number);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\0'
			&& str[i] != '\r' && str[i] != '\v' && str[i] != '\f')
			ft_error(cub, "Invalid character after color");
		i++;
	}
}

void	check_color_ceiling(char *str, int i, t_cub *cub)
{
	char	*number;

	cub->datafile.b_ceiling = true;
	number = construct_number(str, &i, cub, true);
	cub->datafile.ceiling_red = ft_atoi(number);
	free(number);
	number = construct_number(str, &i, cub, false);
	cub->datafile.ceiling_green = ft_atoi(number);
	free(number);
	number = construct_number(str, &i, cub, false);
	if (number[0] == '\0')
	{
		free(number);
		ft_error(cub, "Missing value after comma");
	}
	cub->datafile.ceiling_blue = ft_atoi(number);
	free(number);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\0'
			&& str[i] != '\r' && str[i] != '\v' && str[i] != '\f')
			ft_error(cub, "Invalid character after color");
		i++;
	}
}
