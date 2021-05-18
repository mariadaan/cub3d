#include "cub.h"

int	spawn_dir(t_all *all)
{
	double	radius;

	radius = 0;
	if (all->info.spawn_dir == 'N')
		return (0);
	else if (all->info.spawn_dir == 'E')
		radius = M_PI / 2;
	else if (all->info.spawn_dir == 'S')
		radius = M_PI;
	else if (all->info.spawn_dir == 'W')
		radius = 1.5 * M_PI;
	
	rotate(all, radius);
	return (0);
}

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

int	rotate(t_all *all, double radius)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = all->ray.dir_x;
	all->ray.dir_x = all->ray.dir_x * cos(radius)
		- all->ray.dir_y * sin(radius);
	all->ray.dir_y = old_dir_x * sin(radius) + all->ray.dir_y * cos(radius);
	old_plane_x = all->ray.plane_x;
	all->ray.plane_x = all->ray.plane_x * cos(radius)
		- all->ray.plane_y * sin(radius);
	all->ray.plane_y = old_plane_x * sin(radius)
		+ all->ray.plane_y * cos(radius);
	return (0);
}
