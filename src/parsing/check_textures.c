/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:07:59 by rbalazs           #+#    #+#             */
/*   Updated: 2025/04/30 12:47:39 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static char	*ft_strdup_texture(char *src)
{
	int		size;
	int		i;
	char	*dest;

	i = 0;
	size = 0;
	while (src[size] && src[size] != '\n')
		size++;
	size--;
	while (src[size] == ' ' || src[size] == '\t')
		size--;
	size++;
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	check_texture_no(char *str, int i, t_cub *cub)
{
	if (cub->datafile.b_no == true)
		ft_error(cub, "Texture NO already defined");
	cub->datafile.no = NULL;
	cub->datafile.b_no = true;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	cub->datafile.no = ft_strdup_texture(&str[i]);
}

void	check_texture_so(char *str, int i, t_cub *cub)
{
	if (cub->datafile.b_so == true)
		ft_error(cub, "Texture SO already defined");
	cub->datafile.so = NULL;
	cub->datafile.b_so = true;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	cub->datafile.so = ft_strdup_texture(&str[i]);
}

void	check_texture_we(char *str, int i, t_cub *cub)
{
	if (cub->datafile.b_we == true)
		ft_error(cub, "Texture WE already defined");
	cub->datafile.we = NULL;
	cub->datafile.b_we = true;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	cub->datafile.we = ft_strdup_texture(&str[i]);
}

void	check_texture_ea(char *str, int i, t_cub *cub)
{
	if (cub->datafile.b_ea == true)
		ft_error(cub, "Texture EA already defined");
	cub->datafile.ea = NULL;
	cub->datafile.b_ea = true;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	cub->datafile.ea = ft_strdup_texture(&str[i]);
	if (!cub->datafile.ea)
		ft_error(cub, "EA texture not found");
}
