#include "cub.h"

int		main(int argc, char *argv[])
{
	t_data		img;
	t_info		info;

	if (argc != 2)
		printf("Invalid arguments\n");

	int fd = open(argv[1], O_RDONLY);

	int ret = parse_all(fd, &info);

	if (ret == 0)
	{
		int width = 960;
		int height = 540;


		img.mlx = mlx_init();
		img.win = mlx_new_window(img.mlx, width, height, "Maria's cub3d");
		img.img = mlx_new_image(img.mlx, width, height);

		// img.img = mlx_xpm_file_to_image(img.mlx, "./textures/sample.xpm", &width, &height);

		/*
		** After creating an image, we can call `mlx_get_data_addr`, we pass
		** `bits_per_pixel`, `line_length`, and `endian` by reference. These will
		// ** then be set accordingly for the *current* data address.
		// */
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
													&img.endian);


		// // add_shade(0xB0F0FB);

		// put ceiling
		fill_rect(&img, 0, 0, width, height / 2, 0xB0F0FB);

		// put floor
		fill_rect(&img, 0, height / 2, width, height / 2, 0x68BC13);

		// // put clouds
		fill_rect(&img, 250, 50, 200, 80, 0xFFFFFF);
		// // fill_rect(&img, 50, 50, 200, 80, 0xFFFFFF);
		// // fill_rect(&img, 300, 10, 200, 80, 0xFFFFFF);
		// // fill_rect(&img, 750, 60, 200, 80, 0xFFFFFF);

		// gen_darker_color(0xB0F0FB, 1/4);
		mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
		// mlx_put_image_to_window(img.mlx, img.win, img.img, 0, height);
		// mlx_put_image_to_window(img.mlx, img.win, img.img, width, 0);
		// mlx_put_image_to_window(img.mlx, img.win, img.img, width, height);
		mlx_hook(img.win, DestroyNotify, 0, destroy_window, &img);

		mlx_hook(img.win, KeyPress, 0, key_press, &img);
		// mlx_hook(img.win, 3, 0, key_release, &img);
		mlx_loop(img.mlx);
	}
}
