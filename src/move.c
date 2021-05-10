#include "cub.h"

int		move_rect(int keycode, int *x_pos, int *y_pos, t_data *img)
{
	if (keycode == LROTATE)
		*x_pos -= 5;
	if (keycode == RROTATE)
		*x_pos += 5;
	if (keycode == FORWARD)
		*y_pos += 5;
	if (keycode == BACKWARDS)
		*y_pos -= 5;
	fill_rect(img, *x_pos, *y_pos, 200, 80, 0xFFBBFF);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	return (1);
}