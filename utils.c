#include "cub.h"

void	print_info(t_info *info)
{
	printf("x_render_size:    %d\n", info->x_render_size);
	printf("y_render_size:    %d\n", info->y_render_size);
	printf("n_path:           %s\n", info->n_path);
	printf("s_path:           %s\n", info->s_path);
	printf("w_path:           %s\n", info->w_path);
	printf("e_path:           %s\n", info->e_path);
	printf("sprite_path:      %s\n", info->sprite_path);
	printf("floor_color:      %d\n", info->floor_color);
	printf("ceiling_color:    %d\n", info->ceiling_color);
}