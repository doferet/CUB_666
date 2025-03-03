/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:28:46 by rbalazs           #+#    #+#             */
/*   Updated: 2024/06/21 16:02:19 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "solong.h"

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_map
{
	char		**map;
	int			rows;
	int			columns;
	int			collectibles;
	int			exit;
	int			player;
	int			moves;
}				t_map;

typedef struct s_square
{
	void		*wall;
	void		*floor;
	void		*player;
	void		*collectible;
	void		*exit;
}				t_square;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
}				t_mlx;

typedef struct s_data
{
	t_mlx		mlx;
	t_point		player_pos;
	t_map		map;
	t_square	square;
}				t_data;

#endif