/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:27:43 by doferet           #+#    #+#             */
/*   Updated: 2025/04/22 01:47:14 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	read_data(t_cub *cub)
{
	int		i;
	bool	start;

	i = 0;
	start = false;
	while (cub->file.file[i])
	{
		if (is_line_map(cub->file.file[i]) == true && start == false)
		{
			start = true;
			cub->start_map = i;
		}
		if (is_line_map(cub->file.file[i]) == true && start == true)
			cub->end_map = i;
		i++;
	}
	i = 0;
	while (i < cub->start_map)
	{
		check_data(cub->file.file[i], cub);
		i++;
	}
	if (cub->datafile.all_values == false)
		ft_error(cub, "Missing values");
}

void	create_map(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	cub->map.map = malloc(sizeof(char *) * (cub->map.rows + 1));
	if (!cub->map.map)
		ft_error(cub, "Memory allocation error");
	while (cub->file.file[++i])
	{
		if (is_line_map(cub->file.file[i]) == true)
			cub->map.map[j++] = ft_strdup(cub->file.file[i]);
	}
	cub->map.map[j] = NULL;
	i = -1;
	while (++i < (cub->map.rows - 1))
	{
		if (cub->map.map[i] == NULL)
			ft_error(cub, "Map Error");
		cub->map.map[i][ft_strlen(cub->map.map[i]) - 1] = 0;
	}
	check_empty_line(cub);
}

void	add_to_file(t_file *file, char *line)
{
	char	**tmp;
	int		i;

	if (file->capacity == 0)
	{
		file->capacity = 20;
		file->index = 0;
		file->file = malloc(sizeof(char *) * file->capacity);
		if (!file->file)
			return ;
	}
	if (file->capacity == file->index)
	{
		tmp = malloc(sizeof(char *) * file->capacity * 2);
		if (!tmp)
			return ;
		i = -1;
		while (++i < file->index)
			tmp[i] = file->file[i];
		free(file->file);
		file->file = tmp;
		file->capacity *= 2;
	}
	file->file[file->index++] = ft_strdup(line);
}

void	stock_file_in_array(char *map_file, t_cub *cub)
{
	int		fd;
	char	*temp;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		ft_error(cub, "File not found");
	temp = get_next_line(fd);
	while (temp)
	{
		if (is_line_map(temp) == true)
			cub->map.rows++;
		add_to_file(&cub->file, temp);
		free(temp);
		temp = get_next_line(fd);
	}
	cub->file.file[cub->file.index] = NULL;
	if (cub->map.rows == 0)
		ft_error(cub, "Map is empty");
	if (cub->map.rows <= 2)
		ft_error(cub, "Map is too small");
	close(fd);
}

int	parsing(t_cub *cub, int ac, char **av)
{
	int	len;

	if (ac != 2)
		ft_error(cub, "Invalid arguments");
	len = ft_strlen(av[1]);
	if (len < 4 || ft_strncmp(&av[1][len - 4], ".cub", 4))
		ft_error(cub, "Invalid file extension");
	stock_file_in_array(av[1], cub);
	read_data(cub);
	create_map(cub);
	check_wall_player(cub);
	return (EXIT_SUCCESS);
}
