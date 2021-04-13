#include "cub.h"

int	parse_int(char *line, int *size, int pos)
{
	char	**split;

	if (!line)
		return (0);
	line = ft_move_ptr(line, 'R');
	if (line[0] == 'R')
	{
		split = ft_split(line, ' ');
		*size = ft_atoi(split[pos]);
		free_2darray(split, 3);
		return (1);
	}
	return (0);
}

int	parse_path(char *line, char **path, char *compass)
{
	int		len;
	char	**split_line;

	line = ft_move_ptr(line, *compass);
	len = ft_strlen(compass);
	if (!(ft_strncmp(line, compass, len)))
	{
		split_line = ft_split(line, ' ');
		*path = ft_strdup(split_line[1]);
		free_2darray(split_line, 2);
		return (1);
	}
	return (0);
}

int	parse_color(char *line, unsigned int *color, char c)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	line = ft_move_ptr(line, c);
	if (line[0] == c)
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

int	parse_map(t_info *info, char *full_file)
{
	char	*start_map;

	start_map = ft_move_ptr(full_file, 'C');
	start_map = ft_move_ptr(start_map, '\n') + 1;
	info->map = ft_split(start_map, '\n');
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
	split = ft_split(full_file, '\n');
	parse_int(split[0], &(info->x_size), 1);
	parse_int(split[0], &(info->y_size), 2);
	parse_path(split[1], &(info->no_path), "NO ");
	parse_path(split[2], &(info->so_path), "SO ");
	parse_path(split[3], &(info->we_path), "WE ");
	parse_path(split[4], &(info->ea_path), "EA ");
	parse_path(split[5], &(info->s_path), "S ");
	parse_color(split[6], &(info->f_color), 'F');
	parse_color(split[7], &(info->c_color), 'C');
	parse_map(info, full_file);
	get_spawn_pos(info);
	printchar("spawn", info->map[info->y_spawn][info->x_spawn]);
	info->map[info->y_spawn][info->x_spawn] = '0';
	free_2darray(split, ft_count_rows(split));
	free(full_file);
	print_info(info);
	return (0);
}
