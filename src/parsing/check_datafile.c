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
	if (str[0] == 'F')
	{
		if (cub->datafile.b_floor == true)
			ft_error(cub, "Floor color already set");
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
		cub->datafile.floor_blue = ft_atoi(number);
	}
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
	if (str[0] == 'C')
	{
		if (cub->datafile.b_ceiling == true)
			ft_error(cub, "Ceiling color already defined");
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
		cub->datafile.ceiling_blue = ft_atoi(number);
	}
	free(number);
}

void	check_texture_no(char *str, t_cub *cub)
{
	int	i;

	i = 0;
	
	if (cub->datafile.b_no == true)
		ft_error(cub, "Texture NO already defined");
	cub->datafile.b_no = true;
	i = 2;
	while (str[i] == ' ')
		i++;
	cub->datafile.no = ft_strdup(&str[i]);
}

void  check_texture_so(char *str, t_cub *cub)
{
	int i;

	i = 0;
	if (cub->datafile.b_so == true)
		ft_error(cub, "Texture SO already defined");
	cub->datafile.b_so = true;
	i = 2;
	while (str[i] == ' ')
		i++;
	cub->datafile.so = ft_strdup(&str[i]);
}

void  check_texture_we(char *str, t_cub *cub)
{
	int i;

	i = 0;
	if (cub->datafile.b_we == true)
		ft_error(cub, "Texture WE already defined");
	cub->datafile.b_we = true;
	i = 2;
	while (str[i] == ' ')
		i++;
	cub->datafile.we = ft_strdup(&str[i]);
}

void  check_texture_ea(char *str, t_cub *cub)
{
	int i;

	i = 0;
	if (cub->datafile.b_ea == true)
		ft_error(cub, "Texture EA already defined");
	cub->datafile.b_ea = true;
	i = 2;
	while (str[i] == ' ')
		i++;
	cub->datafile.ea = ft_strdup(&str[i]);
	if (!cub->datafile.ea)
		ft_error(cub, "EA texture not found");
	
}

void	check_data(char *str, t_cub *cub)
{
	if (str[0] == 'N' && str[1] == 'O')
		check_texture_no(str, cub);
	if (str[0] == 'S' && str[1] == 'O')
		check_texture_so(str, cub);
	if (str[0] == 'W' && str[1] == 'E')
		check_texture_we(str, cub);
	if (str[0] == 'E' && str[1] == 'A')
		check_texture_ea(str, cub);
	check_color_floor(str, cub);
	check_color_ceiling(str, cub);
	check_color(cub);
}