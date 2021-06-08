#include "cub.h"

/*
	RGB color related functions using bitshifting
*/

int	create_rgb(int r, int g, int b)
{
	return (0xFFFFFF & (r << 16 | g << 8 | b));
}

int	get_r(int rgb)
{
	return ((rgb & (0xFF << 16)) >> 16);
}

int	get_g(int rgb)
{
	return ((rgb & (0xFF << 8)) >> 8);
}

int	get_b(int rgb)
{
	return (rgb & 0xFF);
}

int	gen_darker_color(int color, int factor)
{
	int	r;
	int	g;
	int	b;

	r = get_r(color) - factor;
	if (r < 0)
		r = 0;
	g = get_g(color) - factor ;
	if (g < 0)
		g = 0;
	b = get_b(color) - factor;
	if (b < 0)
		b = 0;
	color = create_rgb(r, g, b);
	return (color);
}
