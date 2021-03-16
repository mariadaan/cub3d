#include "cub.h"

int		parse_map(int fd, t_info *info)
{
	char *line;
	char **split;

	while (get_next_line(fd, &line))
	{
		printf("%s\n", line);
		if (line[0] == 'R')
		{
			split = ft_split(line, ' ');
			info->x_render_size = ft_atoi(split[1]);
			info->y_render_size = ft_atoi(split[2]);
		}
			
	}
	printf("%s\n", line);
	return (1);
}