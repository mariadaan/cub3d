#include "cub.h"

int	init_texture(t_all *all)
{
	int width;
	int height;

	all->tex.n_img.img = mlx_xpm_file_to_image(all->tex.n_img.mlx, "./bricks.xpm", &width, &height);

	printnum("width", width);
	printnum("height", height);
	all->tex.n_img.addr = mlx_get_data_addr(all->tex.n_img.mlx, &(all->tex.n_img.bits_per_pixel), &(all->tex.n_img.line_length), &(all->tex.n_img.endian));
	mlx_put_image_to_window(all->tex.n_img.mlx, all->img.win, all->tex.n_img.img, 0, 0);
	return (0);
}

int	init_raycaster(t_all *all)
{
	t_tex	tex;

	all->tex = tex;
	all->tex.n_img.mlx = mlx_init();
	all->tex.e_img.mlx = mlx_init();
	all->tex.s_img.mlx = mlx_init();
	all->tex.w_img.mlx = mlx_init();

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
	// init_texture(all);
	return (0);
}

int	init_mlx(t_all *all)
{
	// t_img newimg;
	// int width;
	// int height;

	// newimg.mlx = mlx_init();
	// newimg.img = mlx_xpm_file_to_image(newimg.addr, "./bricks.xpm", &width, &height);
	// printnum("width", width);
	// printnum("height", height);
	// newimg.win = mlx_new_window(newimg.mlx, width, height, "test");
	// newimg.addr = mlx_get_data_addr(newimg.img, &newimg.bits_per_pixel, &newimg.line_length,
	// 												&newimg.endian);
	// mlx_put_image_to_window(newimg.mlx, newimg.win, newimg.img, 0, 0);

	all->img.mlx = mlx_init();
	if (check_res(all))
		return (error_msg("Resolution too big for screen!\n"));
	success_msg("Parsed successfully!\n");
	all->img.win = mlx_new_window(all->img.mlx, all->info.x_size,
			all->info.y_size, "Maria's cub3d");
	printnum("all->info.x_size", all->info.x_size);
	printnum("all->info.y_size", all->info.y_size);
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
		return (error_msg("Invalid argument\n"));
	fd = open(cub_file, O_RDONLY);
	if (fd == -1)
		return (error_msg("Make sure cub file exists and path is correct\n"));
	if (parse_all(fd, &(all->info)))
		return (1);
	return (0);
}
