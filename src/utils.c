#include "cub.h"

void	init_info(t_info *info)
{
	ft_bzero(info, sizeof(*info));
	// info->x_size = 0;
	// info->y_size = 0;
	// info->no_path = 0;
	// info->so_path = 0;
	// info->we_path = 0;
	// info->ea_path = 0;
	// info->s_path = 0;
	// info->f_color = 0;
	// info->map_width = 0;
	// info->map_height = 0;
	// info->x_spawn = 0;
	// info->y_spawn = 0;
}

void	print_info(t_info *info)
{
	printnum("size struct", sizeof(*info));
	printf("x_render_size:    %d\n", info->x_size);
	printf("y_render_size:    %d\n", info->y_size);
	printf("n_path:           %s\n", info->no_path);
	printf("s_path:           %s\n", info->so_path);
	printf("w_path:           %s\n", info->we_path);
	printf("e_path:           %s\n", info->ea_path);
	printf("sprite_path:      %s\n", info->s_path);
	printf("floor_color:      %d\n", info->f_color);
	printf("ceiling_color:    %d\n", info->c_color);
	printf("map: \n");
	ft_put2darray(info->map, info->map_height);
	printnum("mapwidth", info->map_width);
	printnum("mapheight", info->map_height);
	printnum("spawn x", info->x_spawn);
	printnum("spawn y", info->y_spawn);
	printchar("spawn direction", info->spawn_dir);
}