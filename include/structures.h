/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:28:46 by rbalazs           #+#    #+#             */
/*   Updated: 2025/04/16 14:24:09 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "cub3d.h"
# include <stdbool.h>

typedef struct s_maths
{
	int			start_orientation;
	double		deltax;
	double		deltay;
	double		sidex;
	double		sidey;
	int			stepx;
	int			stepy;
	int			mapx;
	int			mapy;
	double		dirx;
	double		diry;
	double		planx;
	double		plany;
	double		cam_orientation;
	double		posx;
	double		posy;
	int			side;
	double		wall_dist;
	double		wall_x;
	int			line_height;
	int			start_line;
	int			end_line;
	double		step;
	int		move_x;
	int		move_y;
	int			rotate;
	int			move;
	double		tex_pos;
	int tex_x;
	int tex_y;
	char		test;
}				t_maths;

typedef struct s_map
{
	char		**map;
	int			rows;
	int			columns;
	int			player;
}				t_map;

typedef struct s_datafile
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;

	int			floor_red;
	int			floor_green;
	int			floor_blue;

	int			ceiling_red;
	int			ceiling_green;
	int			ceiling_blue;

	bool		b_no;
	bool		b_so;
	bool		b_we;
	bool		b_ea;
	bool		b_floor;
	bool		b_ceiling;
	bool		all_values;
}				t_datafile;

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
	t_img		wall_no;
	t_img		wall_so;
	t_img		wall_we;
	t_img		wall_ea;
	t_img		jagpistol;
	t_img       jagpistolred;
	t_img	    bar;
	int			type;
}				t_texture;

typedef struct s_cub
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_maths		player_pos;
	t_maths 	ray;
	t_datafile	datafile;
	t_map		map;
	t_texture	texture;
	t_img		image;
	char		**file;
	int			start_map;
	int			end_map;
	bool		menu;
}				t_cub;

#endif