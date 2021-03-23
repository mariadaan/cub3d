#include "cub.h"

// Put background ceiling and floor color into image

int	draw_bg(t_data *img, t_info *info)
{
	int	half_y_size;

	half_y_size = info->y_size / 2;
	fill_rect(img, 0, 0, info->x_size, half_y_size, info->c_color);
	fill_rect(img, 0, half_y_size, info->x_size, half_y_size, info->f_color);
	return (0);
}

int	get_distance(t_info *info)
{
	int	i;
	int	distance;

	// North facing spawn position
	if (info->spawn_dir == 'N')
	{
		// start looking for wall northwards from spawn position
		i = info->y_spawn;
		while (i > 0)
		{
			if (info->map[i][info->x_spawn] == '1')
			{
				printnum("first wall y pos", i);
				// wall found at y = i
				distance = info->y_spawn - i - 1;
				printnum("distance", distance);
				return (distance);
			}
			i--;
		}
	}
	return (0);
}

int	draw_wall(t_data *img, t_info *info)
{
	int	distance;
	// get distance to front facing wall
	distance = get_distance(info);

	// 
	return (0);
}