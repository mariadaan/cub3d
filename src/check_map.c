#include "cub.h"

/*
	Find beginning of the map
*/
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
	Check first and last row of map
*/
int	check_firstlast(t_info *info)
{
	int	x;
	int	y;
	int	rowlen;

	x = 0;
	rowlen = ft_strlen(info->map[0]);
	while (x < rowlen)
	{
		if (ft_inset("0NESW", info->map[0][x]))
			return (1);
		x++;
	}
	x = 0;
	rowlen = ft_strlen(info->map[info->map_height - 1]);
	while (x < rowlen)
	{
		if (ft_inset("0NESW", info->map[info->map_height - 1][x]))
			return (1);
		x++;
	}

	y = 0;
	while (y < info->map_height)
	{
		rowlen = ft_strlen(info->map[y]);
		if (ft_inset("0NESW", info->map[y][0]) || ft_inset("0NESW", info->map[y][rowlen - 1]))
			return (1);
		y++;
	}
	return (0);
}

/*
	Check whether map is enclosed by walls
*/
int	check_map(t_info *info)
{
	int	x;
	int	y;
	int	rowlen;

	y = 1;
	while (y < info->map_height - 1)
	{
		x = 1;
		rowlen = ft_strlen(info->map[y]);
		while (x < rowlen - 1)
		{
			if (ft_inset("0NESW", info->map[y][x]) &&
				(is_notmap(info->map[y - 1][x]) ||
				is_notmap(info->map[y + 1][x]) ||
				is_notmap(info->map[y][x - 1]) ||
				is_notmap(info->map[y][x + 1]) ||
				is_notmap(info->map[y - 1][x - 1]) ||
				is_notmap(info->map[y + 1][x + 1]) ||
				is_notmap(info->map[y - 1][x + 1]) ||
				is_notmap(info->map[y + 1][x - 1])))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

/*
	Check whether map is valid
*/
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
