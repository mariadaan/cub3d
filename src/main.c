#include "../cub.h"

int	main(int argc, char *argv[])
{
	t_all	all;
	t_img	img;
	t_ray	ray;
	t_info	info;
	t_rect	rect;

	if (0)
	{
		int width = 1080;
		int height = 720;
		int sizex;
		int sizey;
		img.mlx = mlx_init();
		img.win = mlx_new_window(img.mlx, width, height, "Maria's cub3d");
		// img.img = mlx_new_image(img.mlx, width, height);

		img.img = mlx_xpm_file_to_image(img.mlx, "./bricks.xpm", &sizex, &sizey);
		printnum("width", width);
		printnum("height", height);
		printnum("sizex", sizex);
		printnum("sizey", sizey);
		img.addr = mlx_get_data_addr(img.mlx, &img.bits_per_pixel, &img.line_length,
														&img.endian);
		printstr("test", img.addr);
		// fill_rect(&img, 250, 50, 200, 80, 0xFFFFFF);
		// mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
		return (1);
	}
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
	if (init_mlx(&all))
		return (1);
	if (init_raycaster(&all))
		return (1);
	mlx_hook(all.img.win, KeyPress, 0, key_pressed, &all);
	mlx_hook(all.img.win, DestroyNotify, 0, destroy_window, &all);
	mlx_loop(all.img.mlx);
	return (0);
}