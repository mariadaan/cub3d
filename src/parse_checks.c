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
	int	i;

	if (!split || !split[2])
		return (error_msg("Please enter one r, g, and b value"));
	i = 0;
	while (split[i])
	{
		if (!(ft_has_digit(split[i])))
			return (error_msg("Please enter one r, g, and b value"));
		if (!(ft_onlydigits(split[i])))
			return (error_msg("Please enter rgb value with digits only"));
		i++;
	}
	color_s->r = ft_atoi(split[0]);
	color_s->g = ft_atoi(split[1]);
	color_s->b = ft_atoi(split[2]);
	if (color_s->r > 255 || color_s->g > 255 || color_s->b > 255
		|| color_s->r < 0 || color_s->g < 0 || color_s->b < 0)
		return (error_msg("RGB values must be within 0 and 255"));
	return (0);
}

/*
	Check if no or multiple spawn position in map
*/

int	check_spawn(t_info *info)
{
	int	index;

	index = ft_setinset(info->start, "NESW");
	if (index == -1)
		return (1);
	index = ft_setinset(info->start + index + 1, "NESW");
	if (index != -1)
		return (1);
	return (0);
}

/*
	Finds N,S,E or W in map and save location as x and y value. Change the spawn
	position in map to a so it is seen as open space.
*/

int	get_spawn_pos(t_info *info)
{
	int	y_index;
	int	x_index;

	info->map_height = ft_count_rows(info->map);
	y_index = 0;
	while (y_index < info->map_height)
	{
		x_index = ft_setinset(info->map[y_index], "NSWE");
		if (x_index >= 0)
			break ;
		y_index++;
	}
	if (x_index >= 0)
	{
		info->x_spawn = x_index;
		info->y_spawn = y_index;
		info->spawn_dir = info->map[y_index][x_index];
		info->map[info->y_spawn][info->x_spawn] = '0';
		return (0);
	}
	return (error_msg("Error saving spawn position in map"));
}
