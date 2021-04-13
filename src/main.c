#include "cub.h"

int		main(int argc, char *argv[])
{
	t_all		all;
	t_data		img;
	t_info		info;

	if (argc != 2)
		printf("Invalid arguments\n");

	int fd = open(argv[1], O_RDONLY);

	int ret = parse_all(fd, &info);

	if (ret == 0)
	{
		img.mlx = mlx_init();
		img.win = mlx_new_window(img.mlx, info.x_size, info.y_size, "Maria's cub3d");
		img.img = mlx_new_image(img.mlx, info.x_size, info.y_size);

		// img.img = mlx_xpm_file_to_image(img.mlx, "./textures/sample.xpm", &info.x_render_size, &info.y_render_size);

		/*
		** After creating an image, we can call `mlx_get_data_addr`, we pass
		** `bits_per_pixel`, `line_length`, and `endian` by reference. These will
		// ** then be set accordingly for the *current* data address.
		// */
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
													&img.endian);

		all.img = img;
		all.info = info;

		draw_bg(&img, &info);
		draw_wall(&img, &info);

		// // put clouds
		// fill_rect(&img, 250, 50, 200, 80, 0xFFFFFF);

		// gen_darker_color(0xB0F0FB, 1/4);
		mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
		// mlx_put_image_to_window(img.mlx, img.win, img.img, 0, info.y_render_size);
		// mlx_put_image_to_window(img.mlx, img.win, img.img, info.x_render_size, 0);
		// mlx_put_image_to_window(img.mlx, img.win, img.img, info.x_render_size, info.y_render_size);
		mlx_hook(img.win, DestroyNotify, 0, destroy_window, &img);

		mlx_hook(img.win, KeyPress, 0, key_press, &img);
		// mlx_loop_hook(img.mlx, render_frame, &img);
		mlx_loop(img.mlx);
	}
}
