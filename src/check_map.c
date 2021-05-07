#include "cub.h"

int	check_map(char *str)
{
	int check;
	int i;

	i = ft_strlen(str) - 1;
	check = 1;
	while (str[i])
	{
		if (!(ft_inset("102NEWS \n", str[i])))
			check = 0;
		i--;
		if (str[i] == '\n' && str[i - 1] == '\n' && check == 1)
			return (i - 1);
	}

	return (0);
}

int	parse_map(t_info *info, char *full_file)
{
	char	*start_map;
	int		start_index;
	int		i;
	int		width;

	i = 0;
	start_index = check_map(full_file);
	if (start_index)
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
		return (1);
	}
	return (0);
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

int	check_x(t_info *info)
{
	int map_len;
	int x;

	x = 1;
	map_len = ft_strlen(info->start);
	if (info->start[0] == '0' || info->start[map_len - 1] == '0')
		return (1);
	while (x < map_len - 1)
	{
		if (info->start[x] == '0' && (is_notmap(info->start[x - 1]) || is_notmap(info->start[x + 1])))
			return (1);
		x++;
	}
	return (0);
}

int	check_y(t_info *info)
{
	int x;
	int y;
	int rowlen;
	
	y = 1;
	while (y < info->map_height - 2)
	{
		x = 0;
		rowlen = ft_strlen(info->map[y]);
		while (x < rowlen)
		{
			if (info->map[y][x] == '0' && (is_notmap(info->map[y - 1][x]) || is_notmap(info->map[y + 1][x])))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	valid_map(t_info *info)
{
	if (check_x(info))
	{
		printf("Error encountered while parsing cub file: Invalid map!\n");
		return (1);
	}
	if (check_y(info))
	{
		printf("Error encountered while parsing cub file: Invalid map!\n");
		return (1);
	}
	return (0);
}