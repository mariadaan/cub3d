#include "cub.h"

int	parse_int(char *line, int *size, int pos)
{
	char **split;

	line = ft_move_ptr(line, 'R');
	if (line[0] == 'R')
	{
		split = ft_split(line, ' ');
		*size = ft_atoi(split[pos]);
		free2d_array(split, 3);
		return (1);
	}
	return (0);
}

int	parse_path(char *line, char **path, char *compass)
{
	int	len;
	char **split_line;

	line = ft_move_ptr(line, *compass);
	len = ft_strlen(compass);
	if (!(ft_strncmp(line, compass, len)))
	{
		split_line = ft_split(line, ' ');
		*path = ft_strdup(split_line[1]);
		free2d_array(split_line, 2);
		return (1);
	}
	printf("line: %s\n", line);
	return (0);
}

int	parse_color(char *line, unsigned int *color, char c)
{
	char **split;
	int	r;
	int	g;
	int	b;

	line = ft_move_ptr(line, c);
	if (line[0] == c)
	{
		line += 2;
		split = ft_split(line, ',');
		r = ft_atoi(split[0]);
		g = ft_atoi(split[1]);
		b = ft_atoi(split[2]);
		free2d_array(split, 3);
		*color = create_trgb(0, r, g, b);
		return (1);
	}
	printf("line: %s\n", line);
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

int	parse_all(int fd, t_info *info)
{
	char	*full_file;
	char	**split;

	init_info(info);
	read_till_end(fd, &full_file);
	split = ft_split(full_file, '\n');
	parse_int(split[0], &(info->x_render_size), 1);
	parse_int(split[0], &(info->y_render_size), 2);
	parse_path(split[1], &(info->n_path), "NO");
	parse_path(split[2], &(info->s_path), "SO");
	parse_path(split[3], &(info->w_path), "WE");
	parse_path(split[4], &(info->e_path), "EA");
	parse_path(split[5], &(info->sprite_path), "S");
	parse_color(split[6], &(info->floor_color), 'F');
	parse_color(split[7], &(info->ceiling_color), 'C');
	parse_map(info, full_file);
	free2d_array(split, ft_count_rows(split));
	free(full_file);
	print_info(info);
	return (1);
}