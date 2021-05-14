#include "cub.h"

int	find_map(char *full_file)
{
	int check;
	int i;

	i = ft_strlen(full_file) - 1;
	check = 1;
	while (full_file[i] && i > 0)
	{
		if (!(ft_inset("102NEWS \n", full_file[i])))
			check = 0;
		i--;
		if (full_file[i] == '\n' && full_file[i - 1] == '\n' && check == 1)
			return (i - 1);
	}
	return (-1);
}

int	parse_map(t_info *info, char *full_file)
{
	char	*start_map;
	int		start_index;
	int		i;
	int		width;

	i = 0;
	start_index = find_map(full_file);
	if (start_index != -1)
	{
		info->start = full_file + start_index;
		info->map = ft_split(info->start, '\n');
		while (info->map[info->map_height])
			info->map_height++;
		while (i < info->map_height)
		{
			width = ft_strlen(info->map[i]);
			if (width > info->map_width)
				info->map_width = width;
			i++;
		}
		return (0);
	}
	return (1);
}

int	is_notmap(char c)
{
	if (!c)
		return (1);
	if (c == ' ' || c == '\n')
		return (1);
	else
		return (0);
}

int	check_spawn(t_info *info)
{
	int	index;

	// check if no spawn position in map
	index = ft_setinset(info->start, "NESW");
	if (index == -1)
		return (1);
	// check if multiple spawn positions are in map
	index = ft_setinset(info->start + index + 1, "NESW");
	if (index != -1)
		return (1);
	return (0);
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
		if (ft_inset("02NESW", info->map[0][x]))
			return (1);
		x++;
	}
	x = 0;
	rowlen = ft_strlen(info->map[info->map_height - 1]);
	while (x < rowlen)
	{
		// check all chars in last row
		if (ft_inset("02NESW", info->map[info->map_height - 1][x]))
			return (1);
		x++;
	}

	y = 0;
	while (y < info->map_height)
	{
		// check first and last char of every row
		rowlen = ft_strlen(info->map[y]);
		if (ft_inset("02NESW", info->map[y][0]) || ft_inset("02NESW", info->map[y][rowlen - 1]))
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
			if (ft_inset("02NESW", info->map[y][x]) &&
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
		return (error_msg("Error encountered while parsing cub file: Make sure there is one spawn position in map!"));
	if (check_map(info) || check_firstlast(info))
		return (error_msg("Error encountered while parsing cub file: Map must be closed/surrounded by walls!"));
	return (0);
}