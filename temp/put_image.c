static unsigned int	get_pixel_img(t_image img, int x, int y)
{
	return (*(unsigned int *)((img.addr + (y * img.size_line) + (x * img.bpp
				/ 8))));
}

static void	put_pixel_img(t_image img, int x, int y, int color)
{
	char	*dst;

	if (color == (int)0xFF000000)
		return ;
	if (x >= 0 && y >= 0 && x < img.w && y < img.h)
	{
		dst = img.addr + (y * img.size_line + x * (img.bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	put_img_to_img(t_image dst, t_image src, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < src.w)
	{
		j = 0;
		while (j < src.h)
		{
			put_pixel_img(dst, x + i, y + j, get_pixel_img(src, i, j));
			j++;
		}
		i++;
	}
}
