#include "../cub.h"

int	main(int argc, char *argv[])
{
	t_all	all;
	t_data	img;
	t_ray	ray;
	t_info	info;
	t_rect	rect;

	// ft_bzero(&img, sizeof(t_data));
	// ft_bzero(&ray, sizeof(t_ray));
	// ft_bzero(&info, sizeof(t_info));
	// ft_bzero(&rect, sizeof(t_rect));
	all.img = img;
	all.ray = ray;
	all.info = info;
	all.rect = rect;
	if (check_input(&all, argc, argv[1]))
		return (1);
	init_mlx(&all);
	init_raycaster(&all);
	mlx_hook(all.img.win, KeyPress, 0, key_pressed, &all);
	mlx_hook(all.img.win, DestroyNotify, 0, destroy_window, &all);
	mlx_loop(all.img.mlx);
	return (0);
}