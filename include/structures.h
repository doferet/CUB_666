/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:28:46 by rbalazs           #+#    #+#             */
/*   Updated: 2025/03/03 14:58:10 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "cub3d.h"

typedef struct s_maths
{
	int			x;
	int			y;
}				t_maths;

typedef struct s_map
{
	char		**map;
	int			rows;
	int			columns;
	int			player;
}				t_map;

typedef struct s_texture
{
	void		*wall;
	void		*floor;
	void		*player;
}				t_texture;

typedef struct s_cub
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_maths		player_pos;
	t_map		map;
	t_texture	texture;
}				t_cub;

#endif