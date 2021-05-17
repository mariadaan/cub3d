#include "cub.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	put_horizontal(t_img *data, int x, int y, int len, int color)
{
	int i;

	i = 0;
	while (i < len)
	{
		my_mlx_pixel_put(data, x + i, y, color);
		i++;
	}
}

void	put_vertical(t_img *data, int x, int y, int len, int color)
{
	int i;

	i = 0;
	while (i < len)
	{
		my_mlx_pixel_put(data, x, y + i, color);
		i++;
	}
}

void	put_rect(t_img *data, int x, int y, int xlen, int ylen, int color)
{
	put_horizontal(data, x, y, xlen, color);
	put_horizontal(data, x, y + ylen, xlen, color);
	put_vertical(data, x, y, ylen, color);
	put_vertical(data, x + xlen, y, ylen, color);
}

void	fill_rect(t_img *data, int x, int y, int xlen, int ylen, int color)
{
	int i;

	i = 0;
	while(i < ylen)
	{
		put_horizontal(data, x, y + i, xlen, color);
		i++;
	}
}

void	gradient_bg(t_all *all)
{
	int	y_start;

	y_start = 0;
	gradient_rect(all, 0, all->info.c_color);
	gradient_rect(all, all->info.y_size / 2, all->info.f_color);

}

void	gradient_rect(t_all *all, int y_start, int color)
{
	// print_components(color);
	int	i;

	if (y_start == 0)
	{
		i = 0;
		while (i < all->info.y_size / 2)
		{
			put_horizontal(&(all->img), 0, y_start + i, all->info.x_size, color);
			if (i % 2 == 0)
				color = gen_darker_color(color, 1);
			// printnum("color", color);
			// printnum("i", i);
			i++;
		}
	}
	else
	{
		i = 0;
		while (i < all->info.y_size / 2)
		{
			put_horizontal(&(all->img), 0, all->info.y_size - i - 1, all->info.x_size, color);
			// if (i % 2 == 0)
			// 	color = gen_darker_color(color, 1);
			// printnum("color", color);
			// printnum("i", i);
			i++;
		}
	}
	
}