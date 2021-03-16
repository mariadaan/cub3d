#include "mlxopengl/mlx.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <stdio.h>


typedef struct	s_img {
	void	*mlx;
	void	*img;
	void	*win;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_param {
	void *img;


}				t_param;

void	my_pixel_put(t_img *img, int x, int y, unsigned int colour) {
	char	*dst;
	int		offset;
	offset = y * img->line_length + x * (img->bits_per_pixel / 8);
	dst = img->addr + offset;
	*(unsigned int *)dst = colour;
}

void	put_horizontal(t_img *img, int x, int y, int len, int color)
{
	int i;

	i = 0;
	while (i < len)
	{
		my_pixel_put(img, x + i, y, color);
		i++;
	}
}

int	destroy_window(t_img *img)
{
	mlx_destroy_window(img->mlx, img->win);
	exit(0);
	return (1);
}

int		main()
{
	// void	*mlx;
	// void	*mlx_win;
	t_img  img;

	int width = 800;
	int height = 480;


	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, width, height, "Hello world!");
	img.img = mlx_new_image(img.mlx, width, height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	printf("%d\n", img.line_length);
	printf("%d\n", img.bits_per_pixel);
	printf("%d\n", img.endian);

	// my_pixel_put(&img, width / 2, height / 2, 0xFFFFFF);
	put_horizontal(&img, 0, height / 2, width, 0xFFFFFF);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	mlx_hook(img.win, 17, 0, destroy_window, &img);
	mlx_loop(img.mlx);
}