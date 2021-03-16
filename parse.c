#include "cub.h"

int		parse_path(char **path, char **split, char *line, char *compass)
{
	int len;

	len = ft_strlen(compass);
	if (!(ft_strncmp(line, compass, len)))
	{
		split = ft_split(line, ' ');
		*path = ft_strdup(split[1]);
		free2d_array(split, 2);
		return (1);
	}
	return (0);
}

int		parse_int(int *size, char *line, int pos)
{
	char **split;

	if (line[0] == 'R')
	{
		split = ft_split(line, ' ');
		*size = ft_atoi(split[pos]);
		free2d_array(split, 3);
		return (1);
	}
	return (0);
}

int		parse_color(unsigned int *colour, char *line)
{
	char **split;

	
}

int		parse_map(int fd, t_info *info)
{
	char *line;
	char **split;

	while (get_next_line(fd, &line))
	{
		printf("%s\n", line);
		parse_int(&(info->x_render_size), line, 1);
		parse_int(&(info->y_render_size), line, 2);
		parse_path(&(info->n_path), split, line, "NO");
		parse_path(&(info->s_path), split, line, "SO");
		parse_path(&(info->w_path), split, line, "WE");
		parse_path(&(info->e_path), split, line, "EA");
		parse_path(&(info->sprite_path), split, line, "S");
		parse_color()

	}
	printf("%s\n", line);
	print_info(info);
	return (0);
}