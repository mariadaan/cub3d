#include "cub.h"

void	set_ray_pos(t_all *all, int x)
{
	//calculate ray position and direction
	all->ray.camera_x = 2 * x / (double)all->info.x_size - 1; //x-coordinate in camera space
	all->ray.ray_dir_x = all->ray.dir_x + all->ray.plane_x * all->ray.camera_x;
	all->ray.ray_dir_y = all->ray.dir_y + all->ray.plane_y * all->ray.camera_x;

	//which box of the map we're in
	all->ray.map_x = (int)all->ray.pos_x;
	all->ray.map_y = (int)all->ray.pos_y;
}

void	set_ray_len(t_all *all)
{
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
}

void	perform_dda(t_all *all)
{
	//perform DDA
	while (all->ray.hit == 0)
	{
		//jump to next map square, OR in x-direction, OR in y-direction
		if (all->ray.side_dist_x < all->ray.side_dist_y)
		{
			all->ray.side_dist_x += all->ray.delta_dist_y;
			all->ray.map_x += all->ray.step_x;
			all->ray.side = 0;
		}
		else
		{
			all->ray.side_dist_y += all->ray.delta_dist_x;
			all->ray.map_y += all->ray.step_y;
			all->ray.side = 1;
		}

		//Check if ray has hit a wall
		if (all->info.map[all->ray.map_x][all->ray.map_y] == '1')
			all->ray.hit = 1;
	}
}

void	set_projection(t_all *all)
{
	//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
	if (all->ray.side == 0)
		all->ray.perp_wall_dist = (all->ray.map_x - all->ray.pos_x + (1 - all->ray.step_x) / 2) / all->ray.ray_dir_x;
	else
		all->ray.perp_wall_dist = (all->ray.map_y - all->ray.pos_y + (1 - all->ray.step_y) / 2) / all->ray.ray_dir_y;
	
	//Calculate height of line to draw on screen
	all->rect.line_height = (int)(all->info.y_size / all->ray.perp_wall_dist);

	//calculate lowest and highest pixel to fill in current stripe
	all->rect.draw_start = -all->rect.line_height / 2 + all->info.y_size / 2;
	if (all->rect.draw_start < 0)
		all->rect.draw_start = 0;
	all->rect.draw_end = all->rect.line_height / 2 + all->info.y_size / 2;
	if (all->rect.draw_end >= all->info.y_size)
		all->rect.draw_end = all->info.y_size - 1;

}
