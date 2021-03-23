#include "cub.h"

void	init_info(t_info *info)
{
	info->x_render_size = 0;
	info->y_render_size = 0;
	info->n_path = 0;
	info->s_path = 0;
	info->w_path = 0;
	info->e_path = 0;
	info->sprite_path = 0;
	info->floor_color = 0;
}

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
	// ft_putnbr_fd(info->floor_color, 1);
	// ft_putchar('=');
	// ft_putbasenbr(info->floor_color, 2);
	printf("ceiling_color:    %d\n", info->ceiling_color);
	printf("map: \n");
	ft_put2darray(info->map, ft_count_rows(info->map));
}