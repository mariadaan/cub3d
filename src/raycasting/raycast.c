#include "cub.h"

/*
	- Calculate x-coordinate in camera space
	- Calculate ray position and direction
	- Save which box of the map we're in
*/
void	set_ray_pos(t_all *all, int x)
{
	all->ray.camera_x = 2 * x / (double)all->info.x_size - 1;
	all->ray.ray_dir_x = all->ray.dir_x + all->ray.plane_x * all->ray.camera_x;
	all->ray.ray_dir_y = all->ray.dir_y + all->ray.plane_y * all->ray.camera_x;
	all->ray.map_x = (int)all->ray.pos_x;
	all->ray.map_y = (int)all->ray.pos_y;
}

/*
	- Calculate length of ray from one x or y-side to next x or y-side
	- Calculate step and initial sideDist
*/
void	set_ray_len(t_ray *ray)
{
	ray->delta_dist_y = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_x = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_dist_y;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_dist_y;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_dist_x;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_dist_x;
	}
}

/*
	- Jump to next map square in x-direction OR in y-direction
	- Check if ray has hit a wall
*/
void	perform_dda(t_all *all)
{
	while (all->ray.hit == 0)
	{
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
		if (all->info.map[all->ray.map_x][all->ray.map_y] == '1')
			all->ray.hit = 1;
	}
}

/*
	- Calculate distance projected on camera direction
	- Calculate height of line to draw on screen
	- Calculate lowest and highest pixel to fill in current stripe
*/
void	set_projection(t_ray *ray, t_info *info)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - ray->pos_x
				+ (1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - ray->pos_y
				+ (1 - ray->step_y) / 2) / ray->ray_dir_y;
	ray->line_height = (int)(info->y_size / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + info->y_size / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + info->y_size / 2;
	if (ray->draw_end >= info->y_size)
		ray->draw_end = info->y_size - 1;
}
