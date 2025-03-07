/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:28:46 by rbalazs           #+#    #+#             */
/*   Updated: 2025/03/07 12:41:19 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "cub3d.h"

typedef struct s_maths
{
	int			x;
	int			y;
	int			start_orientation;
}				t_maths;

typedef struct s_map
{
	char		**map;
	int			rows;
	int			columns;
	int			player;
}				t_map;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_texture
{
	t_img		wall;
	t_img		floor;
	//void		*wall;
}				t_texture;

typedef struct s_cub
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_maths		player_pos;
	t_map		map;
	t_texture	texture;
	t_img		image;
}				t_cub;

#endif