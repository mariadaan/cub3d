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