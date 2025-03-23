/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:07:59 by rbalazs           #+#    #+#             */
/*   Updated: 2025/03/18 10:09:22 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static char	*ft_strdup_texture(char *src)
{
	int		i;
	char	*dest;

	i = 0;
	while (src[i] && src[i] != '\n')
		i++;
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i] && src[i] != '\n')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	check_texture_no(char *str, t_cub *cub)
{
	int	i;

	i = 0;
	cub->datafile.no = NULL;
	if (cub->datafile.b_no == true)
		ft_error(cub, "Texture NO already defined");
	cub->datafile.b_no = true;
	i = 2;
	while (str[i] == ' ')
		i++;
	cub->datafile.no = ft_strdup_texture(&str[i]);
}

void	check_texture_so(char *str, t_cub *cub)
{
	int	i;

	i = 0;
	cub->datafile.so = NULL;
	if (cub->datafile.b_so == true)
		ft_error(cub, "Texture SO already defined");
	cub->datafile.b_so = true;
	i = 2;
	while (str[i] == ' ')
		i++;
	cub->datafile.so = ft_strdup_texture(&str[i]);
}

void	check_texture_we(char *str, t_cub *cub)
{
	int	i;

	i = 0;
	cub->datafile.we = NULL;
	if (cub->datafile.b_we == true)
		ft_error(cub, "Texture WE already defined");
	cub->datafile.b_we = true;
	i = 2;
	while (str[i] == ' ')
		i++;
	cub->datafile.we = ft_strdup_texture(&str[i]);
}

void	check_texture_ea(char *str, t_cub *cub)
{
	int	i;

	i = 0;
	cub->datafile.ea = NULL;
	if (cub->datafile.b_ea == true)
		ft_error(cub, "Texture EA already defined");
	cub->datafile.b_ea = true;
	i = 2;
	while (str[i] == ' ')
		i++;
	cub->datafile.ea = ft_strdup_texture(&str[i]);
	if (!cub->datafile.ea)
		ft_error(cub, "EA texture not found");
}
