#include "cub.h"

// INITIALIZATION FUNCTIONS

/*
	Checks user input. Has an argument with the name of the cub file been given?
	Does the file exist? If yes, the file is parsed and all information is saved
	in the info struct.
*/

int	init_input(t_all *all, int argc, char *cub_file)
{
	int		fd;
	t_info	info;

	if (argc != 2)
		return (error_msg("Invalid argument\n"));
	fd = open(cub_file, O_RDONLY);
	if (fd == -1)
		return (error_msg("Make sure cub file exists and path is correct\n"));
	ft_bzero(&info, sizeof(t_info));
	all->info = info;
	if (parse_all(fd, &(all->info)))
		return (1);
	return (0);
}

/*
	Creates an image structure for every texture and saves them in t_tex tex.
	In rect, information about the walls to be displayed will be saved later on.
*/

int	init_textures(t_all *all)
{
	t_tex	tex;

	ft_bzero(&tex, sizeof(t_tex));
	all->tex = tex;
	if (file_to_img(&(all->tex.n_img), all->info.no_path)
		|| file_to_img(&(all->tex.e_img), all->info.ea_path)
		|| file_to_img(&(all->tex.s_img), all->info.so_path)
		|| file_to_img(&(all->tex.w_img), all->info.we_path)
		|| file_to_img(&(all->tex.sprite_img), all->info.s_path))
		return (1);
	free(all->info.no_path);
	free(all->info.so_path);
	free(all->info.we_path);
	free(all->info.ea_path);
	free(all->info.s_path);
	return (0);
}

/*
	Create the window in which the cub3d project will be shown and create an
	image called img, that will be modified during the program.
*/

int	init_mlx(t_all *all)
{
	t_img	img;

	ft_bzero(&img, sizeof(t_img));
	all->img = img;
	all->img.mlx = mlx_init();
	if (!(all->img.mlx))
		return (error_msg("Creating mlx pointer failed"));
	if (check_res(all))
		return (error_msg("Resolution too big for screen!\n"));
	all->img.win = mlx_new_window(all->img.mlx, all->info.x_size,
			all->info.y_size, "Maria's cub3d");
	all->img.img = mlx_new_image(all->img.mlx, all->info.x_size,
			all->info.y_size);
	all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bits_per_pixel,
			&all->img.line_length, &all->img.endian);
	return (0);
}

/*
	Set the values that are used by the raycaster algorithm in render.c to the
	correct starting values. step_size can be modified to change walking speed.
	const_rad can be modified to change rotation speed. Depending on the spawn
	direction, player is rotated in the spawn_dir function.
*/

int	init_raycaster(t_all *all)
{
	t_ray	ray;

	ft_bzero(&ray, sizeof(t_ray));
	all->ray = ray;
	all->ray.pos_x = all->info.y_spawn + 0.5;
	all->ray.pos_y = all->info.x_spawn + 0.5;
	all->ray.dir_x = -1;
	all->ray.dir_y = 0;
	all->ray.plane_x = 0;
	all->ray.plane_y = 0.66;
	all->ray.step_size = 0.3;
	all->ray.const_rad = M_PI / 12;
	spawn_dir(all);
	return (0);
}
