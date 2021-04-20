#include "cub.h"

int	parse_int(char *line, int *size, int pos)
{
	char	**split;

	if (!line)
		return (0);
	int linelen = ft_strlen(line);
	line = ft_strnstr(line, "R ", linelen);
	// ft_move_ptr(line, 'R');
	if (line[0] == 'R')
	{
		split = ft_split(line, ' ');
		*size = ft_atoi(split[pos]);
		free_2darray(split, 3);
		return (1);
	}
	return (0);
}

int	get_index(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != c)
		i++;
	return (i);
}

int	parse_path(char *line, char **path, char *compass)
{
	int		len;
	char	**split_line;
	char	*test;

	int linelen = ft_strlen(line);
	line = ft_strnstr(line, compass, linelen);
	int length = get_index(line, '\n');
	// error als length = 0
	test = ft_substr(line, 0, length);
	linelen = ft_strlen(line);
	len = ft_strlen(compass);
	if (!(ft_strncmp(line, compass, len)))
	{
		split_line = ft_split(test, ' ');
		*path = ft_strdup(split_line[1]);
		free_2darray(split_line, 2);
		free(test);
		return (1);
	}
	return (0);
}

int	parse_color(char *line, unsigned int *color, char *area)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	// line = ft_move_ptr(line, c);
	int linelen = ft_strlen(line);
	line = ft_strnstr(line, area, linelen);
	if (line[0] == *area)
	{
		line += 2;
		split = ft_split(line, ',');
		r = ft_atoi(split[0]);
		g = ft_atoi(split[1]);
		b = ft_atoi(split[2]);
		free_2darray(split, 3);
		*color = create_rgb(r, g, b);
		return (1);
	}
	return (0);
}

int	check_line(char *str)
{
	int check;
	int i;
	char **split;

	split = ft_split(str, '\n');

	// check = 1;
	i = 0;
	while (split[i])
	{
		check = 1;
		printstr("split plek", split[i]);
		int linelen = ft_strlen(split[i]);
		int j = 0;
		while (j < linelen)
		{
			if (!(ft_inset("102NEWS ", split[i][j])))
				check = 0;
			j++;
		}
		printnum("check", check);
		if (check == 1)
			return (i);
		i++;
	}
	return (0);
}

int	check_str(char *str)
{
	int check;
	int i;
	int index;

	i = 0;
	check = 1;
	while (str[i])
	{
		while (str[i] == '\n')
			i++;
		printchar("char", str[i]);
		if (!(ft_inset("102NEWS ", str[i])))
			check = 0;
		i++;
		if (str[i] == '\n' && check == 1)
			return (index);
		while (str[i] == '\n')
		{
			i++;
			printf("NEWLINE\n\n");
			check = 1;
			index = i;
		}
	}

		
	// 	int linelen = ft_strlend(str + i, '\n');
	// 	int j = 0;
	// 	while (j < linelen)
	// 	{
	// 		if (!(ft_inset("102NEWS ", (str + i)[j])))
	// 			check = 0;
	// 		j++;
	// 		all++;
	// 	}
	// 	printnum("check", check);
	// 	if (check == 1)
	// 		return (all);
	// 	all++;
	// 	i++;
	// }
	return (0);
}

int	parse_map(t_info *info, char *full_file)
{
	char	*start_map;
	int		map_check;
	char	**mappie;

	// begin map: geen ["NO", "SO", "WE", "EA", "S", "F", "C"] in line
	// alleen 1 0 2 N E W S of spatie in line
	map_check = check_str(full_file);
	printnum("mapcheck", map_check);
	if (map_check)
	{
		printstr("mappie", full_file + map_check);

		start_map = full_file + map_check;
		info->map = ft_split(start_map, '\n');
		return (1);
	}
	// start_map = ft_move_ptr(full_file, 'C');
	// start_map = ft_move_ptr(start_map, '\n') + 1;
	// info->map = ft_split(start_map, '\n');
	return (0);
}


// find N,S,E or W in map and save location as x and y value

int	get_spawn_pos(t_info *info)
{
	int	y_index;
	int x_index;

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
		return (1);
	}
	return (0);
}

// int	change_spawn(t_info *info)
// {
// 	info->map[info->y_spawn][info->x_spawn] = 0;
// }

int	parse_all(int fd, t_info *info)
{
	char	*full_file;
	char	**split;

	init_info(info);
	read_till_end(fd, &full_file);
	// split = ft_split(full_file, '\n');
	parse_int(full_file, &(info->x_size), 1);
	parse_int(full_file, &(info->y_size), 2);
	parse_path(full_file, &(info->no_path), "NO ");
	parse_path(full_file, &(info->so_path), "SO ");
	parse_path(full_file, &(info->we_path), "WE ");
	parse_path(full_file, &(info->ea_path), "EA ");
	parse_path(full_file, &(info->s_path), "S ");
	parse_color(full_file, &(info->f_color), "F ");
	parse_color(full_file, &(info->c_color), "C ");
	parse_map(info, full_file);
	get_spawn_pos(info);
	printchar("spawn", info->map[info->y_spawn][info->x_spawn]);
	info->map[info->y_spawn][info->x_spawn] = '0';
	// free_2darray(split, ft_count_rows(split));
	free(full_file);
	print_info(info);
	return (0);
}
