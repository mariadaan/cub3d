#include "cub.h"

void	print_components(int color)
{
	int	r;
	int	g;
	int	b;

	r = get_r(color);
	g = get_g(color);
	b = get_b(color);
	printnum("color", color);
	printf("r: %d\n", r);
	printf("g: %d\n", g);
	printf("b: %d\n", b);
	// ft_putbasenbr(r, 2);
	// ft_putchar('\n');
	// ft_putbasenbr(g, 2);
	// ft_putchar('\n');
	// ft_putbasenbr(b, 2);
	ft_putchar('\n');
}

int		gen_darker_color(int color, int factor)
{
	// print_components(color);
	int r = get_r(color) - factor;
	if (r < 0)
		r = 0;
	int g = get_g(color) - factor ;
	if (g < 0)
		g = 0;
	int b = get_b(color) - factor;
	if (b < 0)
		b = 0;
	color = create_rgb(r, g, b);
	// print_components(color);
	return (color);
}

int		darker_color(int color)
{
	return ((color >> 1) & 8355711);
}

// int	add_shade(int rgb, double shading)
// {
// 	int		r;
// 	int		g;
// 	int		b;

// 	r = get_r(rgb) * shading;
// 	g = get_g(rgb) * shading;
// 	b = get_b(rgb) * shading;
// 	return (create_rgb(r, g, b));
// }
