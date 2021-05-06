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
		start_map = full_file + start_index;
		info->map = ft_split(start_map, '\n');
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

int	valid_map(t_info *info)
{
	int	x;
	int y;
	int	w;

	y = 0;
	x = 0;
	// map is invalid als er direct naast een spatie een 0 staat
	// of aan de zijkant een 0 staat
	while (y < info->map_height)
	{
		printnum("y", y);
		w = ft_strlen(info->map[y]);
		// while (x < w)
		// {
			while (info->map[y][x] == ' ')
				x++;
			printchar("naam char", info->map[y][x]);
			if (info->map[y][x] == '0')
			{
				printnum("ytest", y);
				return (1);
			}
			// x++;
		// }
		// OOK TUSSENDOOR CHECKEN OF ER NULLEN NAAST SPATIE STAAN
		x = w - 1 ;
		// while (x > 0)
		// {
			printnum("x", x);
			while (x > 0 && info->map[y][x] == ' ')
			{
				printnum("xxx", x);
				x--;
			}
			if (info->map[y][x] == '0')
			{
				printnum("ytest2", y);
				return (1);
			}
		// 	x--;
		// }
		x = 0;
		printnum("xxxxxxx", x);
		y++;
	}
	printnum("test", 1);
	return (0);
}