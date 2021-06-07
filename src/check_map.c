#include "cub.h"

// CHECK WHETHER MAP IS VALID FUNCTIONS

int	find_map(char *full_file)
{
	int	check;
	int	i;

	i = ft_strlen(full_file) - 1;
	check = 1;
	while (full_file[i] && i > 0)
	{
		if (!(ft_inset("10NEWS \n", full_file[i])))
			check = 0;
		i--;
		if (full_file[i] == '\n' && full_file[i - 1] == '\n' && check == 1)
			return (i - 1);
	}
	return (-1);
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

int	check_firstlast(t_info *info)
{
	int x;
	int y;
	int rowlen;

	x = 0;
	rowlen = ft_strlen(info->map[0]);
	while (x < rowlen)
	{
		// check all chars in first row
		if (ft_inset("0NESW", info->map[0][x]))
			return (1);
		x++;
	}
	x = 0;
	rowlen = ft_strlen(info->map[info->map_height - 1]);
	while (x < rowlen)
	{
		// check all chars in last row
		if (ft_inset("0NESW", info->map[info->map_height - 1][x]))
			return (1);
		x++;
	}

	y = 0;
	while (y < info->map_height)
	{
		// check first and last char of every row
		rowlen = ft_strlen(info->map[y]);
		if (ft_inset("0NESW", info->map[y][0]) || ft_inset("0NESW", info->map[y][rowlen - 1]))
			return (1);
		y++;
	}
	return (0);
}

int	check_map(t_info *info)
{
	int x;
	int y;
	int rowlen;
	
	y = 1;
	while (y < info->map_height - 1)
	{
		x = 1;
		rowlen = ft_strlen(info->map[y]);
		while (x < rowlen - 1)
		{
			if (ft_inset("0NESW", info->map[y][x]) &&
				(is_notmap(info->map[y - 1][x]) || // onder
				is_notmap(info->map[y + 1][x]) || // boven
				is_notmap(info->map[y][x - 1]) || // links
				is_notmap(info->map[y][x + 1]) || // rechts
				is_notmap(info->map[y - 1][x - 1]) || // linksonder
				is_notmap(info->map[y + 1][x + 1]) || // rechtsboven
				is_notmap(info->map[y - 1][x + 1]) || // rechtsonder
				is_notmap(info->map[y + 1][x - 1]))) // rechtsboven
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	valid_map(t_info *info)
{
	if (check_spawn(info))
		return (error_msg("Error encountered while parsing cub file:"
			" Make sure there is one spawn position in map!"));
	if (check_map(info) || check_firstlast(info))
		return (error_msg("Error encountered while parsing cub file:"
			" Map must be closed/surrounded by walls!"));
	return (0);
}