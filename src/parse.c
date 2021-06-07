#include "cub.h"

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

// DEZE WERKT NIET maar zou eigenlijk wel beter zijn dus ff fixen
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
		free_2darray(split);
		return (0);
	}
	return (1);
}

/*
	Saves X and Y render size as ints
*/

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
		free_2darray(split);
		if (*size < 1 || *size < 1)
			return (error_msg("Invalid resolution"));
		return (0);
	}
	return (1);
}

/*
	Saves path to texture and sprite as a string
*/

int	parse_path(char *full_file, char **path, char *id)
{
	int		path_len;
	char	*start;

	start = ft_strstr(full_file, id);
	start = ft_strstr(start, "./");
	path_len = get_findex(start, '\n');
	if (path_len == 0)
		return (error_msg("Invalid texture/sprite path"));
	*path = ft_substr(start, 0, path_len);
	return (0);
}

/*
	Saves rgb color as an unsigned int value
*/

int	parse_color(char *line, unsigned int *color, char *id)
{
	char	**split;
	int		rows;
	int		r;
	int		g;
	int		b;

	line = ft_strstr(line, id);
	if (line[0] == *id)
	{
		line += 2;
		split = ft_split(line, ',');
		rows = ft_count_rows(split);
		if (rows < 3)
			return (error_msg("Please enter one r, g, and b value"));
		r = ft_atoi(split[0]);
		g = ft_atoi(split[1]);
		b = ft_atoi(split[2]);
		if (r > 255 || g > 255 || b > 255 || r < 0 || g < 0 || b < 0)
			return (error_msg("Invalid rgb value"));
		free_2darray(split);
		*color = create_rgb(r, g, b);
	}
	return (0);
}

/*
	Save map in 2d array
*/
int	parse_map(t_info *info, char *full_file)
{
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
	return (error_msg("Invalid map"));
}

/*
	Saves cub file in one long string and calls other functions to parse all
	parts of the information in the cub file. This information is saved in the
	t_info info struct.
*/

int	parse_all(int fd, t_info *info)
{
	int	ret;

	ret = read_till_end(fd, &(info->full_file));
	if (ret == -1)
		return (error_msg("Error encountered while reading cub file"));
	if (parse_int(info->full_file, &(info->x_size), 1)
		|| parse_int(info->full_file, &(info->y_size), 2)
		|| parse_path(info->full_file, &(info->no_path), "NO ")
		|| parse_path(info->full_file, &(info->so_path), "SO ")
		|| parse_path(info->full_file, &(info->we_path), "WE ")
		|| parse_path(info->full_file, &(info->ea_path), "EA ")
		|| parse_color(info->full_file, &(info->f_color), "F ")
		|| parse_color(info->full_file, &(info->c_color), "C ")
		|| parse_map(info, info->full_file)
		|| valid_map(info)
		|| get_spawn_pos(info))
		return (1);
	free(info->full_file);
	success_msg("Parsing successful!");
	print_info(info);
	return (0);
}
