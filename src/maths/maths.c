/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:53:33 by doferet           #+#    #+#             */
/*   Updated: 2025/04/09 16:45:36 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	calcul(int x, t_cub *cub)
{
	cub->ray.cam_orientation = 2 * x / (double)WIDTH - 1;
	cub->ray.raydirx = cub->ray.dirx + cub->ray.planx * cub->ray.cam_orientation;
	cub->ray.raydiry = cub->ray.diry + cub->ray.plany * cub->ray.cam_orientation;
	if (cub->ray.raydirx == 0 || cub->ray.raydiry == 0)
	{
		fprintf(stderr, "Error: Division by zero in ray direction calculation.\n");
		exit(EXIT_FAILURE);
	}
	cub->ray.deltax = fabs(1 / cub->ray.raydirx);
	cub->ray.deltay = fabs(1 / cub->ray.raydiry);
}

static void	calcul_2(t_cub *cub)
{
	if (cub->ray.dirx < 0)
	{
		cub->ray.stepx = -1;
		cub->ray.sidex = (cub->ray.posx - cub->ray.mapx) * cub->ray.deltax;
	}
	else
	{
		cub->ray.stepx = 1;
		cub->ray.sidex = (cub->ray.mapx + 1.0 - cub->ray.posx) * cub->ray.deltax;
	}
	if (cub->ray.diry < 0)
	{
		cub->ray.stepy = -1;
		cub->ray.sidey = (cub->ray.posy - cub->ray.mapy) * cub->ray.deltay;
	}
	else
	{
		cub->ray.stepy = 1;
		cub->ray.sidey = (cub->ray.mapy + 1.0 - cub->ray.posy) * cub->ray.deltay;
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
		if (cub->ray.mapy < 0.25 || cub->ray.mapx < 0.25 || cub->ray.mapy > cub->map.rows - 0.25 || cub->ray.mapx > cub->map.columns - 1.25)
     		 break;
		else if (cub->map.map[cub->ray.mapx][cub->ray.mapy] > '0')
		{
			hit = 1;
		}
	}
}

static void	height_of_line(t_cub *cub)
{
	if (cub->ray.side == 0)
		cub->ray.wall_dist = cub->ray.sidex
			- cub->ray.deltax;
	else
		cub->ray.wall_dist = cub->ray.sidey
			- cub->ray.deltay;
	cub->ray.line_height = (int)(HEIGHT / cub->ray.wall_dist);
	cub->ray.start_line = -(cub->ray.line_height) / 2 + HEIGHT
		/ 2;
	if (cub->ray.start_line < 0)
		cub->ray.start_line = 0;
	cub->ray.end_line = cub->ray.line_height / 2 + HEIGHT / 2;
	if (cub->ray.end_line >= HEIGHT)
		cub->ray.end_line = HEIGHT - 1;
	if (cub->ray.side == 0)
		cub->ray.wall_x = cub->ray.posy
			+ cub->ray.wall_dist * cub->ray.diry;
	else
		cub->ray.wall_x = cub->ray.posx
			+ cub->ray.wall_dist * cub->ray.dirx;
	cub->ray.wall_x -= floor(cub->ray.wall_x);
}

void	texture_color(t_cub *cub, int x, int i, unsigned char *pixel)
{
	int	r;
	int	g;
	int	b;
	int	color;

	r = pixel[2];
	g = pixel[1];
	b = pixel[0];
	if (cub->ray.side == 1)
	{
		r /= 1.5;
		g /= 1.5;
		b /= 1.5;
	}
	color = rgb(r, g, b);
	put_pixel(cub, x, i, color);
}

void	texture_loop(t_cub *cub, int x)
{
	int				i;
	unsigned char	*pixel;

	if (cub->ray.side == 0 && cub->ray.dirx > 0)
		cub->ray.tex_x = cub->texture.wall_no.width - cub->ray.tex_x - 1;
	if (cub->ray.side == 1 && cub->ray.diry < 0)
		cub->ray.tex_x = cub->texture.wall_no.width - cub->ray.tex_x - 1;
	pixel = NULL;
	cub->ray.step = 1.0 * cub->texture.wall_no.height / cub->ray.line_height;
	i = cub->ray.start_line;
	cub->ray.tex_pos = (cub->ray.start_line - HEIGHT / 2 \
	+ cub->ray.line_height / 2) * cub->ray.step;
	while (i < cub->ray.end_line)
	{
		cub->ray.tex_y = (int)cub->ray.tex_pos & (cub->texture.wall_no.height \
		- 1);
		cub->ray.tex_pos += cub->ray.step;
		pixel = (unsigned char *)(cub->texture.wall_no.addr \
		+ cub->ray.tex_y * cub->texture.wall_no.line_len \
		+ cub->ray.tex_x * (cub->texture.wall_no.bpp / 8));
		texture_color(cub, x, i, pixel);
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
		//texture_loop(cub, x);
		x++;
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->image.img, 0, 0);
	mlx_destroy_image(cub->mlx_ptr, cub->image.img);
	cub->image.img = mlx_new_image(cub->mlx_ptr, WIDTH, HEIGHT);
	cub->image.addr = mlx_get_data_addr(cub->image.img, &cub->image.bpp,
			&cub->image.line_len, &cub->image.endian);
	return (0);
}
