#include "cub.h"

int	check_res(t_all *all)
{
	int	x;
	int	y;

	mlx_get_screen_size(&(all->img), &x, &y);
	if (x < all->info.x_size || y < all->info.y_size)
	{
		printf("Error encountered while parsing cub file: Invalid resolution\n");
		return (1);
	}
	return (0);
}

int	parse_rendersize(t_info *info, char *full_file, char *id)
{
	char	**split;

	if (!full_file)
		return (0);
	full_file = ft_strstr(full_file, "R ");
	if (!(ft_strncmp(full_file, id, 2)))
	{
		split = ft_split(full_file, ' ');
		info->x_size = ft_atoi(split[0]);
		info->y_size = ft_atoi(split[1]);
		free_2darray(split, ft_count_rows(split));
		return (1);
	}
	return (0);
}

int	parse_int(char *line, int *size, int pos)
{
	char	**split;

	if (!line)
		return (0);
	line = ft_strstr(line, "R ");
	if (line[0] == 'R')
	{
		split = ft_split(line, ' ');
		*size = ft_atoi(split[pos]);
		free_2darray(split, 3);
		return (1);
	}
	return (0);
}

int	get_findex(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != c)
		i++;
	return (i);
}

int	get_lindex(char *str, char c)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (str && str[i] && str[i] != c)
		i--;
	return (i);
}

int	parse_path(char *full_file, char **path, char *id)
{
	int		id_len;
	int		path_len;
	char	*start;

	start = ft_strstr(full_file, id);
	start = ft_strstr(start, "./");
	path_len = get_findex(start, '\n');
	// error als path_len = 0
	*path = ft_substr(start, 0, path_len);
	return (0);
}

int	parse_color(char *line, unsigned int *color, char *id)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	line = ft_strstr(line, id);
	if (line[0] == *id)
	{
		line += 2;
		split = ft_split(line, ',');
		r = ft_atoi(split[0]);
		g = ft_atoi(split[1]);
		b = ft_atoi(split[2]);
		if (r > 255 || g > 255 || b > 255 || r < 0 || g < 0 || b < 0)
		{
			red();
			printf("Error encountered while parsing cub file: Invalid rgb values\n");
			reset();
			return (1);
		}
		free_2darray(split, 3);
		*color = create_rgb(r, g, b);
		return (0);
	}
	return (1);
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

int	parse_all(int fd, t_info *info)
{
	int ret;

	init_info(info);
	ret = read_till_end(fd, &(info->full_file));
	if (ret == -1)
		return (error_msg("Error encountered while reading cub file"));
	parse_int(info->full_file, &(info->x_size), 1);
	parse_int(info->full_file, &(info->y_size), 2);
	ret = parse_path(info->full_file, &(info->no_path), "NO ");
	ret += parse_path(info->full_file, &(info->so_path), "SO ");
	ret += parse_path(info->full_file, &(info->we_path), "WE ");
	ret += parse_path(info->full_file, &(info->ea_path), "EA ");
	ret += parse_path(info->full_file, &(info->s_path), "S ");
	if (ret)
		return (error_msg("Error encountered while parsing cub file: Invalid texture/sprite path"));
	ret = parse_color(info->full_file, &(info->f_color), "F ");
	ret += parse_color(info->full_file, &(info->c_color), "C ");
	if (ret)
		return (1);
	ret += parse_map(info, info->full_file);
	if (ret)
		return (error_msg("Error encountered while parsing cub file: Map is missing"));
	if (valid_map(info))
		return (1);
	get_spawn_pos(info);
	info->map[info->y_spawn][info->x_spawn] = '0';
	free(info->full_file);
	// print_info(info);
	return (0);
}
