#include "../../include/cub3d.h"

int rgb(int r, int g, int b)
{
	return (0 << 24 | r << 16 | g << 8 | b);
}

void put_pixel(t_cub *cub, int x, int y, int color)
{
	char *dst;

	dst = cub->image.addr + (y * cub->image.line_len + x * (cub->image.bpp / 8));
	*(unsigned int *)dst = color;
}

int random_range(int min, int max)
{
	return (rand() % (max - min + 1)) + min;
}

int fade_gray(int base, int step, int total)
{
	int shade = base - (step * (base / total));
	return (shade << 16) | (shade << 8) | shade;
}

void put_color_floor_ceiling(t_cub *cub)
{
	int i, j;
	int ceiling_color = rgb(cub->datafile.ceiling_red,
							cub->datafile.ceiling_green,
							cub->datafile.ceiling_blue);
	int floor_color = rgb(cub->datafile.floor_red,
						  cub->datafile.floor_green,
						  cub->datafile.floor_blue);

#define NUM_COMETS 3
	static float comet_x[NUM_COMETS];
	static float comet_y[NUM_COMETS];
	static float vx[NUM_COMETS];
	static float vy[NUM_COMETS];
	static int initialized = 0;

	if (!initialized)
	{
		for (int k = 0; k < NUM_COMETS; k++)
		{
			comet_x[k] = rand() % WIDTH;
			comet_y[k] = rand() % (HEIGHT / 2);
			vx[k] = 0.2 + (rand() % 30) / 100.0;
			vy[k] = 0.1 + (rand() % 20) / 100.0;
		}
		initialized = 1;
	}

	// ☁️ Fond ciel
	i = 0;
	while (i < HEIGHT / 2)
	{
		j = -1;
		while (++j < WIDTH)
			put_pixel(cub, j, i, ceiling_color);
		i++;
	}

	// 🌟 Étoiles scintillantes
	for (int s = 0; s < 80; s++)
	{
		int x = random_range(0, WIDTH - 1);
		int y = random_range(0, HEIGHT / 2 - 1);
		put_pixel(cub, x, y, 0xFFFFFF);
	}

	// 🌞 Soleil dans le ciel (halo jaune/orange)
	int sun_x = 1500; // position du soleil
	int sun_y = 80;
	int sun_radius = 35;
	for (int y = -sun_radius; y <= sun_radius; y++)
	{
		for (int x = -sun_radius; x <= sun_radius; x++)
		{
			int dist_sq = x * x + y * y;
			if (dist_sq <= sun_radius * sun_radius)
			{
				int draw_x = sun_x + x;
				int draw_y = sun_y + y;
				if (draw_x >= 0 && draw_x < WIDTH && draw_y >= 0 && draw_y < HEIGHT / 2)
				{
					int dist = sqrtf((float)dist_sq);
					int intensity = 255 - (dist * 5); // plus c’est loin, plus c’est doux
					if (intensity < 0)
						intensity = 0;

					int r = intensity;
					int g = intensity * 0.9;
					int b = intensity * 0.3;
					int color = (r << 16) | ((int)g << 8) | (int)b;
					put_pixel(cub, draw_x, draw_y, color);
				}
			}
		}
	}

	// ☄️ Comètes lentes + taille variable
	static int comet_size[NUM_COMETS];

	if (!initialized)
	{
		for (int k = 0; k < NUM_COMETS; k++)
		{
			comet_x[k] = rand() % WIDTH;
			comet_y[k] = rand() % (HEIGHT / 2);
			vx[k] = 0.2 + (rand() % 30) / 100.0;
			vy[k] = 0.1 + (rand() % 20) / 100.0;
			comet_size[k] = 3 + rand() % 4; // tailles de 3 à 6
		}
		initialized = 1;
	}

	for (int k = 0; k < NUM_COMETS; k++)
	{
		int trail_len = 12 + comet_size[k]; // plus grosse = plus de traînée
		for (int t = 0; t < trail_len; t++)
		{
			int x = (int)(comet_x[k] - t);
			int y = (int)(comet_y[k] - t / 2.0);
			if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT / 2)
			{
				int intensity = 200 - (t * 200 / trail_len);
				if (intensity < 0)
					intensity = 0;
				int color = (intensity << 16) | (intensity << 8) | intensity;
				for (int dx = -comet_size[k] / 2; dx <= comet_size[k] / 2; dx++)
				{
					for (int dy = -comet_size[k] / 2; dy <= comet_size[k] / 2; dy++)
					{
						int px = x + dx;
						int py = y + dy;
						if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT / 2)
							put_pixel(cub, px, py, color);
					}
				}
			}
		}
		comet_x[k] += vx[k];
		comet_y[k] += vy[k];
		if (comet_x[k] >= WIDTH || comet_y[k] >= HEIGHT / 2)
		{
			comet_x[k] = rand() % WIDTH;
			comet_y[k] = rand() % (HEIGHT / 2);
			vx[k] = 0.2 + (rand() % 30) / 100.0;
			vy[k] = 0.1 + (rand() % 20) / 100.0;
			comet_size[k] = 3 + rand() % 4;
		}

		// 🟫 Sol
		while (i < HEIGHT)
		{
			j = -1;
			while (++j < WIDTH)
				put_pixel(cub, j, i, floor_color);
			i++;
		}
	}
}
