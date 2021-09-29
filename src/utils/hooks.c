#include "../../cub.h"

/*
	Closes window and frees map
*/
int	destroy_window(t_all *all)
{
	free_2darray(all->info.map);
	mlx_destroy_window(all->img.mlx, all->img.win);
	success_msg("Thanks for playing! :)");
	exit(0);
	return (1);
}

/*
	Executes player movement and rerenders image
*/
int	key_pressed(int keycode, t_all *all)
{
	if (keycode == ESC)
		destroy_window(all);
	else if (keycode == FORWARD)
		all->ray.forward = 1;
	else if (keycode == BACKWARDS)
		all->ray.backwards = 1;
	else if (keycode == LEFT)
		all->ray.left = 1;
	else if (keycode == RIGHT)
		all->ray.right = 1;
	else if (keycode == RROTATE)
		all->ray.rot_right = 1;
	else if (keycode == LROTATE)
		all->ray.rot_left = 1;
	else if (keycode == 25)
		rotate(all, -M_PI / 2);
	return (keycode);
}

/*
	Executes player movement and rerenders image
*/
int	key_released(int keycode, t_all *all)
{
	if (keycode == FORWARD)
		all->ray.forward = 0;
	else if (keycode == BACKWARDS)
		all->ray.backwards = 0;
	else if (keycode == LEFT)
		all->ray.left = 0;
	else if (keycode == RIGHT)
		all->ray.right = 0;
	else if (keycode == RROTATE)
		all->ray.rot_right = 0;
	else if (keycode == LROTATE)
		all->ray.rot_left = 0;
	return (keycode);
}
