#include "cub.h"

/*
	Changes initial player direction if necessary
*/
int	spawn_dir(t_all *all)
{
	double	radians;

	radians = 0;
	if (all->info.spawn_dir == 'N')
		return (0);
	else if (all->info.spawn_dir == 'E')
		radians = M_PI / 2;
	else if (all->info.spawn_dir == 'S')
		radians = M_PI;
	else if (all->info.spawn_dir == 'W')
		radians = 1.5 * M_PI;
	rotate(all, radians);
	return (0);
}

/* 
	Checks if movement should be made
*/
int	check_move(t_all *all)
{
	if (all->ray.forward)
		move_player(all, all->ray.dir_x, all->ray.dir_y);
	if (all->ray.backwards)
		move_player(all, -all->ray.dir_x, -all->ray.dir_y);
	if (all->ray.left)
		move_player(all, -all->ray.plane_x, -all->ray.plane_y);
	if (all->ray.right)
		move_player(all, all->ray.plane_x, all->ray.plane_y);
	if (all->ray.rot_right)
		rotate(all, -all->ray.const_rad);
	if (all->ray.rot_left)
		rotate(all, all->ray.const_rad);
	return (1);
}


/*
	Moves player position in map
*/
int	move_player(t_all *all, double x, double y)
{
	if (all->info.map[(int)(all->ray.pos_x + x * all->ray.step_size)]
		[(int)(all->ray.pos_y)] == '0')
	{
		draw_img(all);
		show_img(all);
		all->ray.pos_x += x  * (all->ray.step_size - 0.01);
	}
	if (all->info.map[(int)(all->ray.pos_x)][(int)
		(all->ray.pos_y + y * all->ray.step_size)] == '0')
	{
		draw_img(all);
		show_img(all);
		all->ray.pos_y += y * (all->ray.step_size - 0.01);
	}
	return (0);
}

/*
	Rotates player by angle in radians
	(for example: 90° = π/2 rad)
*/
int	rotate(t_all *all, double radians)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = all->ray.dir_x;
	all->ray.dir_x = all->ray.dir_x * cos(radians)
		- all->ray.dir_y * sin(radians);
	all->ray.dir_y = old_dir_x * sin(radians) + all->ray.dir_y * cos(radians);
	old_plane_x = all->ray.plane_x;
	all->ray.plane_x = all->ray.plane_x * cos(radians)
		- all->ray.plane_y * sin(radians);
	all->ray.plane_y = old_plane_x * sin(radians)
		+ all->ray.plane_y * cos(radians);
	draw_img(all);
	show_img(all);
	return (0);
}
