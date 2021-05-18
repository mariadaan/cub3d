#include "cub.h"
	
int main(void)
{
	t_img img;

	int img_width;
	int img_height;
	img.mlx = mlx_init();
	img.img = mlx_xpm_file_to_image(img.mlx, "./textures/wood.xpm", &img_width, &img_height);
	printnum("width",  img_width);
	printnum("height", img_height);
	img.win = mlx_new_window(img.mlx, img_width, img_height, "test");
	if (img.img == NULL)
	{
		printf("xpm = NULL\n");
		return (-1);
	}
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	mlx_loop(img.mlx);
	return (0);
}