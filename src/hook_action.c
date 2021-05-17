#include "cub.h"

int	destroy_window(t_img *img)
{
	mlx_destroy_window(img->mlx, img->win);
	exit(0);
	return (1);
}

int	key_pressed(int keycode, t_all *all)
{
	if (keycode == ESC)
		destroy_window(&(all->img));
	if (keycode == FORWARD)
		move_player(all, all->ray.dir_x, all->ray.dir_y);
	if (keycode == BACKWARDS)
		move_player(all, -all->ray.dir_x, -all->ray.dir_y);
	if (keycode == LEFT)
		move_player(all, -all->ray.plane_x, -all->ray.plane_y);
	if (keycode == RIGHT)
		move_player(all, all->ray.plane_x, all->ray.plane_y);
	if (keycode == RROTATE)
		rotate(all, -all->ray.const_rad);
	if (keycode == LROTATE)
		rotate(all, all->ray.const_rad);
	if (keycode == 25)
		rotate(all, -M_PI / 2);
	draw_img(all);
	return (keycode);
}