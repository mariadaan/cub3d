#include "cub.h"

int	destroy_window(t_data *img)
{
	mlx_destroy_window(img->mlx, img->win);
	exit(0);
	return (1);
}

int	key_release(int keycode, t_data *img)
{
	printf("keyrelease: %d\n", keycode);
	return (1);
}

int	key_press(int keycode, t_data *img)
{
	static int	x_pos;
	static int	y_pos;

	x_pos = 250;
	y_pos = 50;
	while (keycode >= 123 && keycode <= 126)
	{
		move_rect(keycode, &x_pos, &y_pos, img);
		if (mlx_hook(img->win, KeyRelease, 0, key_release, &img))
			break ;
	}
	if (keycode == 53)
		destroy_window(img);
	return (1);
}
