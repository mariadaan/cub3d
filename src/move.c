#include "cub.h"

int		move_rect(int keycode, int *x_pos, int *y_pos, t_data *img)
{
	if (keycode == LEFT)
		*x_pos -= 5;
	if (keycode == RIGHT)
		*x_pos += 5;
	if (keycode == UP)
		*y_pos += 5;
	if (keycode == DOWN)
		*y_pos -= 5;
	fill_rect(img, 0, 0, 960, 540 / 2, 0xB0F0FB);
	fill_rect(img, *x_pos, *y_pos, 200, 80, 0xFFFFFF);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	return (1);
}