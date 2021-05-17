#include "cub.h"

int	init_raycaster(t_all *all)
{
	all->ray.pos_x = all->info.y_spawn + 0.5;
	all->ray.pos_y = all->info.x_spawn + 0.5;
	all->ray.dir_x = -1;
	all->ray.dir_y = 0;
	all->ray.plane_x = 0;
	all->ray.plane_y = 0.66;
	all->ray.step_size = 0.3;
	all->ray.const_rad = 0.2;
	spawn_dir(all);
	draw_img(all);
	return (0);
}

int	init_mlx(t_all *all)
{
	all->img.mlx = mlx_init();
	if (check_res(all))
		return (error_msg("Resolution too big for screen!\n"));
	success_msg("Parsed successfully!\n");
	all->img.win = mlx_new_window(all->img.mlx, all->info.x_size,
			all->info.y_size, "Maria's cub3d");
	all->img.img = mlx_new_image(all->img.mlx, all->info.x_size,
			all->info.y_size);
	all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bits_per_pixel,
			&all->img.line_length, &all->img.endian);
	return (0);
}

int	check_input(t_all *all, int argc, char *cub_file)
{
	int	fd;

	if (argc != 2)
	{
		error_msg("Invalid arguments\n");
		return (1);
	}
	fd = open(cub_file, O_RDONLY);
	if (fd == -1)
	{
		perror("FAIL");
		error_msg("Make sure cub file exists and path is correct\n");
		return (1);
	}
	if (parse_all(fd, &(all->info)))
		return (1);
	return (0);
}
