/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:27:30 by rbalazs           #+#    #+#             */
/*   Updated: 2025/04/17 13:41:44 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

////////////////////////////DEFINE//////////////////////////////

// TEXTURES
# define WALL "./textures/wall.xpm"
# define PISTOL "./textures/jagpistol.xpm"
# define BAR "./textures/bar.xpm"

# define WALL_SIZE 64
# define WIDTH 1920
# define HEIGHT 1080

// MATHS
# define MOVESPEED 0.015
# define ROTSPEED 0.0125

// KEYS
# define DST_N 17

////////////////////////////INCLUDES//////////////////////////////

# include "../libft/get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "./structures.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

////////////////////////////PROTOTYPES//////////////////////////////
// INIT
void			init_mlx(t_cub *cub);
void			init_texture_image(t_cub *cub, t_img *image, char *path);
void			init_player_pos(t_cub *cub);

// PARSING
void			check_player(t_cub *cub);
bool			is_player(t_cub *cub, int x, int y);
char			**ft_double_strjoin(char **file, char *line);
char			*ft_charjoin(char *str, char c, t_cub *cub);
bool			is_line_map(char *str);
void			check_player(t_cub *cub);
int				parsing(t_cub *cub, int ac, char **av);
void			check_data(char *str, t_cub *cub);
void			check_wall(t_cub *cub);
void			check_empty_line(t_cub *cub);
void			check_color_floor(char *str, int i, t_cub *cub);
void			check_color_ceiling(char *str, int i, t_cub *cub);
void			check_color(t_cub *cub);
void			check_wrong_char_color(char *str, int i, t_cub *cub);
void			check_texture_no(char *str, int i, t_cub *cub);
void			check_texture_so(char *str, int i, t_cub *cub);
void			check_texture_we(char *str, int i, t_cub *cub);
void			check_texture_ea(char *str, int i, t_cub *cub);

// MATHS
int				raycasting(t_cub *cub);
void			draw_ray(int x, t_cub *cub);

// MOVE & ROTATE
bool			is_wall_collision(t_cub *cub, double x, double y);
bool			is_valid_pos(t_cub *cub, double x, double y);
int				valid_move(t_cub *cub, double new_x, double new_y);
int				move_player(t_cub *cub);
int				rotate_player(t_cub *cub, double rotdir);
int				rotate_left_right(t_cub *cub, double rotspeed);

// TEXTURES
void			put_color_floor_ceiling(t_cub *cub);
void			put_pixel(t_cub *cub, int x, int y, int color);
unsigned int	get_pixel_img(t_img img, int x, int y);
int				rgb(int r, int g, int b);
void			print_bar(t_cub *cub);
void			minimap(t_cub *cub);
void			print_weapon(t_cub *cub);
void			texture_loop(t_cub *cub, int screen_x, int screen_y);

//KEY & MOUSE EVENT
int				key_event(int button, t_cub *cub);
int				key_release(int button, t_cub *cub);
int				mouse_event(int x, t_cub *cub);

// ERROR & FREE
void			ft_error(t_cub *cub, char *str);
void			free_matrix(char **matrix);
void			ft_free_all(t_cub *cub);

// DEBUG
void			print_tab(char **tab);

#endif