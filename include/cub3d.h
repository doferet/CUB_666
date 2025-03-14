/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:27:30 by rbalazs           #+#    #+#             */
/*   Updated: 2025/03/14 16:55:25 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

////////////////////////////DEFINE//////////////////////////////

// TEXTURES
# define WALL "./textures/wall.xpm"
# define FLOOR "./textures/floor.xpm"
# define SQUARE_SIZE 60
# define WIDTH 1280
# define HEIGHT 720

// KEYS
# define W 119
# define A 97
# define S 115
# define D 100
# define UP 65362
# define LEFT 65361
# define DOWN 65364
# define RIGHT 65363
# define ESC 65307

# define KEYPRESS 2
# define DST_N 17

////////////////////////////INCLUDES//////////////////////////////

# include "../mlx/mlx.h"
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include "./structures.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <math.h>

////////////////////////////PROTOTYPES//////////////////////////////
// INIT
void	init_mlx(t_cub *cub);
void	init_texture_image(t_cub *cub, t_img *image, char *path);
void	put_img(t_img dst, t_img src, int x, int y);

// PARSING
char 	*ft_charjoin(char *str, char c, t_cub *cub);
int		parsing(t_cub *cub, int ac, char **av);
void	check_data(char *str, t_cub *cub);
void	check_color_floor(char *str, t_cub *cub);
void	check_color_ceiling(char *str, t_cub *cub);
void	check_color(t_cub *cub);
void    check_wrong_char_color(char *str, t_cub *cub);

// MATHS

// ERROR & FREE
void	ft_error(t_cub *cub, char *str);
void	free_matrix(char **matrix);
void	ft_free_all(t_cub *cub);

// DEBUG
void	print_tab(char **tab);

#endif