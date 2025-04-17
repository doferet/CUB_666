/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:53:33 by doferet           #+#    #+#             */
/*   Updated: 2025/04/17 14:00:44 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	calcul(int x, t_cub *cub)
{
	cub->ray.cam_orientation = 2 * x / (double)WIDTH - 1;
	cub->ray.dirx = cub->player_pos.dirx + cub->player_pos.planx
		* cub->ray.cam_orientation;
	cub->ray.diry = cub->player_pos.diry + cub->player_pos.plany
		* cub->ray.cam_orientation;
	cub->ray.mapx = (int)cub->player_pos.posx;
	cub->ray.mapy = (int)cub->player_pos.posy;
	cub->ray.deltax = fabs(1 / cub->ray.dirx);
	cub->ray.deltay = fabs(1 / cub->ray.diry);
}

static void	calcul_2(t_cub *cub)
{
	if (cub->ray.dirx < 0)
	{
		cub->ray.stepx = -1;
		cub->ray.sidex = (cub->player_pos.posx - cub->ray.mapx)
			* cub->ray.deltax;
	}
	else
	{
		cub->ray.stepx = 1;
		cub->ray.sidex = (cub->ray.mapx + 1.0 - cub->player_pos.posx)
			* cub->ray.deltax;
	}
	if (cub->ray.diry < 0)
	{
		cub->ray.stepy = -1;
		cub->ray.sidey = (cub->player_pos.posy - cub->ray.mapy)
			* cub->ray.deltay;
	}
	else
	{
		cub->ray.stepy = 1;
		cub->ray.sidey = (cub->ray.mapy + 1.0 - cub->player_pos.posy)
			* cub->ray.deltay;
	}
}

static void	dda_algo(t_cub *cub)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (cub->ray.sidex < cub->ray.sidey)
		{
			cub->ray.sidex += cub->ray.deltax;
			cub->ray.mapx += cub->ray.stepx;
			cub->ray.side = 0;
		}
		else
		{
			cub->ray.sidey += cub->ray.deltay;
			cub->ray.mapy += cub->ray.stepy;
			cub->ray.side = 1;
		}
      	if (cub->map.map[cub->ray.mapy][cub->ray.mapx] == '1') 
		{
			hit = 1;
		}
	}
}

static void	height_of_line(t_cub *cub)
{
	if (cub->ray.side == 0)
		cub->ray.wall_dist = cub->ray.sidex - cub->ray.deltax;
	else
		cub->ray.wall_dist = cub->ray.sidey - cub->ray.deltay;
	cub->ray.line_height = (int)(HEIGHT / cub->ray.wall_dist);
	cub->ray.start_line = -(cub->ray.line_height) / 2 + HEIGHT / 2;
	if (cub->ray.start_line < 0)
		cub->ray.start_line = 0;
	cub->ray.end_line = cub->ray.line_height / 2 + HEIGHT / 2;
	if (cub->ray.end_line >= HEIGHT)
		cub->ray.end_line = HEIGHT - 1;
	if (cub->ray.side == 0)
		cub->ray.wall_x = cub->player_pos.posy + cub->ray.wall_dist * cub->ray.diry;
	else
		cub->ray.wall_x = cub->player_pos.posx + cub->ray.wall_dist * cub->ray.dirx;
	cub->ray.wall_x -= floor(cub->ray.wall_x);
}


static unsigned int	get_pixel_img(t_img img, int x, int y)
{
	return (*(unsigned int *)((img.addr + (y * img.line_len) + (x * img.bpp
				/ 8))));
}

void texture_loop(t_cub *cub, int screen_x, int screen_y)
{
	int     tex_x;
    double  tex_y;
    double  tex_step;

	
    tex_step = (double)WALL_SIZE / cub->ray.line_height;
	tex_x = cub->ray.wall_x * WALL_SIZE;
    tex_y = (screen_y - HEIGHT / 2 + cub->ray.line_height / 2) * tex_step;
    while (screen_y < cub->ray.end_line)
    {
        tex_y += tex_step;
        if (cub->ray.side == 0)
        {
			if (cub->ray.dirx < 0)
				put_pixel(cub, screen_x, screen_y,
                	get_pixel_img(cub->texture.wall_ea, tex_x, (int)tex_y));
       		else
            	put_pixel(cub, screen_x, screen_y,
                	get_pixel_img(cub->texture.wall_we, tex_x, (int)tex_y));
		}
		else
		{
			if (cub->ray.diry < 0)
				put_pixel(cub, screen_x, screen_y,
                	get_pixel_img(cub->texture.wall_so, tex_x, (int)tex_y));
       		else
            	put_pixel(cub, screen_x, screen_y,
                	get_pixel_img(cub->texture.wall_no, tex_x, (int)tex_y));
		}
        screen_y++;
    }
}

void minimap(t_cub *cub)
{
	int i;
	int j;
	int x;
	int y;

	i = 0;
	while (i < cub->map.rows)
	{
		j = 0;
		while (j < (int)ft_strlen(cub->map.map[i]))
		{
			y = 0;
			while (y < 8)
			{
				x = 0;
				while (x < 8)
				{
					if (cub->map.map[i][j] == '1')
						put_pixel(cub, j * 8 + x, i * 8 + y, rgb(47, 0, 255));
					else if (cub->map.map[i][j] == '0' || is_player(cub, j, i))
						put_pixel(cub, j * 8 + x, i * 8 + y, rgb(158, 146, 146));
					put_pixel(cub, cub->player_pos.posx * 8 + x, cub->player_pos.posy * 8 + y, rgb(255, 0, 0));
					x++;
				}
				y++;
			}
			j++;
		}
		i++;
	}
}

void print_weapon(t_cub *cub)
{
	int i;
	int j;
	int weapon_x;
	int weapon_y;
	int screen_center_x = WIDTH / 2;
	int screen_center_y = HEIGHT / 2;

	i = 0;
	while (i < 600)
	{
		j = 0;
		while (j < 600)
		{
			weapon_x = j * cub->texture.jagpistol.width / 600;
			weapon_y = i * cub->texture.jagpistol.height / 600;
			if ((get_pixel_img(cub->texture.jagpistol, weapon_x, weapon_y) & 0x00FFFFFF) != 0)
				put_pixel(cub, screen_center_x - 300 + j, screen_center_y - 200 + i, get_pixel_img(cub->texture.jagpistol, weapon_x, weapon_y));
			j++;
		}
		i++;
	}
}

void print_bar(t_cub *cub)
{
	int i;
	int j;
	int bar_x;
	int bar_y;
	int screen_center_x = WIDTH / 2;
	int screen_center_y = HEIGHT / 2 + 450;

	i = 0;
	while (i < cub->texture.bar.height * 2)
	{
		j = 0;
		while (j < cub->texture.bar.width * 2)
		{
			bar_x = j * cub->texture.bar.width / (cub->texture.bar.width * 2);
			bar_y = i * cub->texture.bar.height / (cub->texture.bar.height * 2);
			put_pixel(cub, screen_center_x - cub->texture.bar.width + j, screen_center_y - cub->texture.bar.height + i, get_pixel_img(cub->texture.bar, bar_x, bar_y));
			j++;
		}
		i++;
	}
}


int	raycasting(t_cub *cub)
{
	int	x;

	x = 0;
	put_color_floor_ceiling(cub);
	while (x < WIDTH)
	{
		calcul(x, cub);
		calcul_2(cub);
		dda_algo(cub);
		height_of_line(cub);
		texture_loop(cub, x, cub->ray.start_line);
		x++;
	}
	minimap(cub);
	print_weapon(cub);
	print_bar(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->image.img, 0, 0);
	mlx_destroy_image(cub->mlx_ptr, cub->image.img);
	cub->image.img = mlx_new_image(cub->mlx_ptr, WIDTH, HEIGHT);
	cub->image.addr = mlx_get_data_addr(cub->image.img, &cub->image.bpp,
			&cub->image.line_len, &cub->image.endian);
	cub->player_pos.move = move_player(cub);
	return (0);
}
