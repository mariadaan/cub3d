#include "../cub.h"

/*
	Checks whether resolution is valid and modifies it if necessary
*/

int	check_res(t_all *all)
{
	int	x;
	int	y;

	mlx_get_screen_size(&(all->img.mlx), &x, &y);
	if (x < all->info.x_size || y < all->info.y_size)
	{
		error_msg("Given resolution too big for screen . . .");
		all->info.x_size = x * 0.9;
		all->info.y_size = y * 0.9;
		success_msg("Resolution has been altered to screen size");
	}
	return (0);
}

/*
	Checks whether rgb color input is valid
*/

int	check_rgb(char **split, t_color *color_s)
{
	int i;

	if (!split)
		return (1);
	i = 0;
	while (split[i])
	{
		if (!(ft_has_digit(split[i])))
			return (error_msg("Please enter one r, g, and b value"));
		if (!(ft_onlydigits(split[i])))
			return (error_msg("Please enter rgb value with digits only"));
		i++;
	}
	if (i < 3)
		return (error_msg("Please enter one r, g, and b value"));
	color_s->r = ft_atoi(split[0]);
	color_s->g = ft_atoi(split[1]);
	color_s->b = ft_atoi(split[2]);
	if (color_s->r > 255 || color_s->g > 255 || color_s->b > 255
		|| color_s->r < 0 || color_s->g < 0 || color_s->b < 0)
		return (error_msg("Invalid rgb value"));
	return (0);
}