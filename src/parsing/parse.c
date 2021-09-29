#include "../../cub.h"

/*
	Saves X and Y render size as ints
*/
int	parse_res(char *full_file, int *size, int pos)
{
	char	*line;
	char	**split;

	line = create_line(full_file, "R ");
	if (!line)
		return (error_msg("No resolution found"));
	split = ft_split(line, ' ');
	free(line);
	if (!(split[1]))
	{
		free_2darray(split);
		return (error_msg("Please provide both x and y render size"));
	}
	*size = ft_atoi(split[pos]);
	free_2darray(split);
	if (*size < 1 || *size < 1)
		return (error_msg("Invalid resolution"));
	return (0);
}

/*
	Saves rgb color as an unsigned int value
*/
int	parse_color(char *full_file, unsigned int *color, char *id)
{
	char	*line;
	char	**split;
	t_color	color_s;

	ft_bzero(&color_s, sizeof(t_color));
	line = create_line(full_file, id);
	if (!line)
		return (error_msg("No rgb value found"));
	split = ft_split(line, ',');
	if (check_rgb(split, &color_s))
	{
		free_2darray(split);
		free(line);
		return (1);
	}
	free_2darray(split);
	free(line);
	*color = create_rgb(color_s.r, color_s.g, color_s.b);
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
	if (start_index == -1)
		return (error_msg("Invalid map area"));
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
	if (check_spawn(info))
		return (error_msg("Make sure there is one spawn position in map!"));
	if (check_map(info))
		return (error_msg("Map must be closed/surrounded by walls!"));
	return (0);
}

/*
	Saves path to texture as a string
*/
int	parse_tex(t_info *info)
{
	info->no_path = create_line(info->full_file, "NO ");
	info->so_path = create_line(info->full_file, "SO ");
	info->we_path = create_line(info->full_file, "WE ");
	info->ea_path = create_line(info->full_file, "EA ");
	if (!(info->no_path) || !(info->so_path)
		|| !(info->we_path) || !(info->ea_path))
		return (error_msg("Enter path for every texture"));
	return (0);
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
	if (parse_res(info->full_file, &(info->x_size), 0)
		|| parse_res(info->full_file, &(info->y_size), 1)
		|| parse_color(info->full_file, &(info->f_color), "F ")
		|| parse_color(info->full_file, &(info->c_color), "C ")
		|| parse_map(info, info->full_file)
		|| get_spawn_pos(info)
		|| parse_tex(info))
		return (free_all(info, 1));
	free(info->full_file);
	success_msg("Parsing successful!");
	return (0);
}
