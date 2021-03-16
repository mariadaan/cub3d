#include "cub.h"

int	get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

int	get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

int	get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

unsigned int	create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

void	print_components(int color)
{
	int r;
	int g;
	int b;

	r = get_r(color);
	g = get_g(color);
	b = get_b(color);
	printf("r: %d\n", r);
	printf("g: %d\n", g);
	printf("b: %d\n", b);
	ft_putbasenbr(r, 2);
	ft_putchar('\n');
	ft_putbasenbr(g, 2);
	ft_putchar('\n');
	ft_putbasenbr(b, 2);
	ft_putchar('\n');
}

void	gen_darker_color(int color, int factor)
{
	ft_putbasenbr(color, 2);
	ft_putchar('\n');
	print_components(color);
}