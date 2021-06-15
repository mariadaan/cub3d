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
	Moves player position in map
*/
int	move_player(t_all *all, double x, double y)
{
	if (all->info.map[(int)(all->ray.pos_x + x * all->ray.step_size)]
		[(int)(all->ray.pos_y)] == '0')
		all->ray.pos_x += x * all->ray.step_size;
	if (all->info.map[(int)(all->ray.pos_x)][(int)
		(all->ray.pos_y + y * all->ray.step_size)] == '0')
		all->ray.pos_y += y * all->ray.step_size;
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
	return (0);
}
