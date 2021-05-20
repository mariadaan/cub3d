#include "cub.h"


int	set_values(t_all *all, int x)
{
	//calculate ray position and direction
	all->ray.camera_x = 2 * x / (double)all->info.x_size - 1; //x-coordinate in camera space
	all->ray.ray_dir_x = all->ray.dir_x + all->ray.plane_x * all->ray.camera_x;
	all->ray.ray_dir_y = all->ray.dir_y + all->ray.plane_y * all->ray.camera_x;

	//which box of the map we're in
	all->ray.map_x = (int)all->ray.pos_x;
	all->ray.map_y = (int)all->ray.pos_y;

	//length of ray from one x or y-side to next x or y-side
	all->ray.delta_dist_y = fabs(1 / all->ray.ray_dir_x);
	all->ray.delta_dist_x = fabs(1 / all->ray.ray_dir_y);

	all->ray.hit = 0; //was there a wall hit?

	//calculate step and initial sideDist
	if (all->ray.ray_dir_x < 0)
	{
		all->ray.step_x = -1;
		all->ray.side_dist_x = (all->ray.pos_x - all->ray.map_x) * all->ray.delta_dist_y;
	}
	else
	{
		all->ray.step_x = 1;
		all->ray.side_dist_x = (all->ray.map_x + 1.0 - all->ray.pos_x) * all->ray.delta_dist_y;
	}
	if (all->ray.ray_dir_y < 0)
	{
		all->ray.step_y = -1;
		all->ray.side_dist_y = (all->ray.pos_y - all->ray.map_y) * all->ray.delta_dist_x;
	}
	else
	{
		all->ray.step_y = 1;
		all->ray.side_dist_y = (all->ray.map_y + 1.0 - all->ray.pos_y) * all->ray.delta_dist_x;
	}
	dda(all);
	//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
	if (all->ray.side == 0)
		all->ray.perp_wall_dist = (all->ray.map_x - all->ray.pos_x + (1 - all->ray.step_x) / 2) / all->ray.ray_dir_x;
	else
		all->ray.perp_wall_dist = (all->ray.map_y - all->ray.pos_y + (1 - all->ray.step_y) / 2) / all->ray.ray_dir_y;
	return (0);
}

int	dda_calc(t_all *all)
{

}
