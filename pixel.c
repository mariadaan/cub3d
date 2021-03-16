#include "cub.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	put_horizontal(t_data *data, int x, int y, int len, int color)
{
	int i;

	i = 0;
	while (i < len)
	{
		my_mlx_pixel_put(data, x + i, y, color);
		i++;
	}
}

void	put_vertical(t_data *data, int x, int y, int len, int color)
{
	int i;

	i = 0;
	while (i < len)
	{
		my_mlx_pixel_put(data, x, y + i, color);
		i++;
	}
}

void	put_rect(t_data *data, int x, int y, int xlen, int ylen, int color)
{

	put_horizontal(data, x, y, xlen, color);
	put_horizontal(data, x, y + ylen, xlen, color);
	put_vertical(data, x, y, ylen, color);
	put_vertical(data, x + xlen, y, ylen, color);
}

void	fill_rect(t_data *data, int x, int y, int xlen, int ylen, int color)
{
	int i;

	i = 0;
	while(i < ylen)
	{
		put_horizontal(data, x, y + i, xlen, color);
		i++;
	}
}