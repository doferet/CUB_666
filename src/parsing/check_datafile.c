#include "../../include/cub3d.h"

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

void	check_color_floor(char *str, t_cub *cub)
{
	char	*number;
	int		i;

	i = 0;
	number = malloc(sizeof(char) * 1);
	if (!number)
		ft_error(cub, "Malloc Error");
	number[0] = '\0';
	cub->datafile.b_floor = true;
	i++;
	while (str[i] == ' ')
		i++;
	// PREMIER NOMBRE POUR ROUGE
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = ft_charjoin(number, str[i], cub);
		i++;
	}
	cub->datafile.floor_red = ft_atoi(number);
	free(number);
	number = malloc(sizeof(char) * 1);
	if (!number)
		ft_error(cub, "Malloc Error");
	number[0] = '\0';
	// DEUXIEME NOMBRE POUR VERT
	while (str[i] == ' ' || str[i] == ',')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = ft_charjoin(number, str[i], cub);
		i++;
	}
	cub->datafile.floor_green = ft_atoi(number);
	free(number);
	number = malloc(sizeof(char) * 1);
	if (!number)
		ft_error(cub, "Malloc Error");
	number[0] = '\0';
	// TROISIEME NOMBRE POUR BLEU
	while (str[i] == ' ' || str[i] == ',')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = ft_charjoin(number, str[i], cub);
		i++;
	}
	if (number[0] == '\0')
	{
		free(number);
		ft_error(cub, "Missing value after comma");
	}
	cub->datafile.floor_blue = ft_atoi(number);
	free(number);
}

void	check_color_ceiling(char *str, t_cub *cub)
{
	char	*number;
	int		i;

	i = 0;
	number = malloc(sizeof(char) * 1);
	if (!number)
		ft_error(cub, "Malloc Error");
	number[0] = '\0';
	cub->datafile.b_ceiling = true;
	i++;
	while (str[i] == ' ')
		i++;
	// PREMIER NOMBRE POUR ROUGE
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = ft_charjoin(number, str[i], cub);
		i++;
	}
	cub->datafile.ceiling_red = ft_atoi(number);
	free(number);
	number = malloc(sizeof(char) * 1);
	if (!number)
		ft_error(cub, "Malloc Error");
	number[0] = '\0';
	// DEUXIEME NOMBRE POUR VERT
	while (str[i] == ' ' || str[i] == ',')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = ft_charjoin(number, str[i], cub);
		i++;
	}
	cub->datafile.ceiling_green = ft_atoi(number);
	free(number);
	number = malloc(sizeof(char) * 1);
	if (!number)
		ft_error(cub, "Malloc Error");
	number[0] = '\0';
	// TROISIEME NOMBRE POUR BLEU
	while (str[i] == ' ' || str[i] == ',')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = ft_charjoin(number, str[i], cub);
		i++;
	}
	if (number[0] == '\0')
	{
		free(number);
		ft_error(cub, "Missing value after comma");
	}
	cub->datafile.ceiling_blue = ft_atoi(number);
	free(number);
}



void	check_data(char *str, t_cub *cub)
{
	if (str[0] == 'N' && str[1] == 'O')
		check_texture_no(str, cub);
	else if (str[0] == 'S' && str[1] == 'O')
		check_texture_so(str, cub);
	else if (str[0] == 'W' && str[1] == 'E')
		check_texture_we(str, cub);
	else if (str[0] == 'E' && str[1] == 'A')
		check_texture_ea(str, cub);
	else if (str[0] == 'F')
	{
		if (cub->datafile.b_floor == true)
			ft_error(cub, "Floor color already set");
		check_wrong_char_color(str, cub);
		check_color_floor(str, cub);
	}
	else if (str[0] == 'C')
	{
		if (cub->datafile.b_ceiling == true)
			ft_error(cub, "Ceiling color already set");
		check_wrong_char_color(str, cub);
		check_color_ceiling(str, cub);
	}
	check_color(cub);
}
