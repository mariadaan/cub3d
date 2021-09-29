#include "cub.h"

/*
	Draw background
*/
int	draw_bg(t_all *all)
{
	int	y;
	int	color;

	y = 0;
	color = all->info.c_color;
	while (y < all->info.y_size / 2)
	{
		if (all->info.y_size / 200 == 0
			|| y % (all->info.y_size / 200) == 0)
			color = gen_darker_color(color, 1);
		put_hor_full(all, y, color);
		y++;
	}
	while (y < all->info.y_size)
	{
		put_hor_full(all, y, all->info.f_color);
		y++;
	}
	return (0);
}

/*
	Sets coordinates of texture image to use for wall
*/
int	set_tex(t_all *all, t_img wall_img)
{
	if (all->ray.side == 0)
		all->ray.wall_x = all->ray.pos_y + all->ray.perp_wall_dist
			* all->ray.ray_dir_y;
	else
		all->ray.wall_x = all->ray.pos_x + all->ray.perp_wall_dist
			* all->ray.ray_dir_x;
	all->ray.wall_x -= floor((all->ray.wall_x));
	all->ray.x_tex = (int)(all->ray.wall_x * (double)wall_img.width);
	if ((all->ray.side == 0 && all->ray.ray_dir_x > 0)
		|| (all->ray.side == 1 && all->ray.ray_dir_y < 0))
		all->ray.x_tex = wall_img.width - all->ray.x_tex;
	all->ray.y_tex = 0;
	all->ray.y_tex_step = wall_img.height / (double)all->ray.line_height;
	if (all->ray.line_height > all->info.y_size)
		all->ray.y_tex = (all->ray.line_height - all->info.y_size)
			* all->ray.y_tex_step / 2;
	return (0);
}

/*
	Places texture on vertical wall line
*/
int	draw_tex(t_all *all, t_img wall_img, int x)
{
	char	*dst;
	int		y_wall;
	int		color;

	set_tex(all, wall_img);
	y_wall = all->ray.draw_start;
	while (y_wall <= all->ray.draw_end)
	{
		dst = wall_img.addr + ((int)(all->ray.y_tex) % wall_img.height
				* wall_img.line_length + all->ray.x_tex % wall_img.width
				* (wall_img.bits_per_pixel / 8));
		color = *(unsigned int *)dst;
		put_pixel(&(all->img), x, y_wall, color);
		y_wall++;
		all->ray.y_tex += all->ray.y_tex_step;
	}
	return (0);
}

/*
	Loops over vertical lines to be drawn in image, does raycasting calculations
	for every line, and places the textures on the walls.
*/
int	draw_img(t_all *all)
{
	int	x;

	draw_bg(all);
	x = 0;
	while (x < all->info.x_size)
	{
		set_ray_pos(all, x);
		set_ray_len(&(all->ray));
		perform_dda(all);
		set_projection(&(all->ray), &(all->info));
		if (all->ray.side == 0 && all->ray.step_x == 1)
			draw_tex(all, all->tex.n_img, x);
		if (all->ray.side == 0 && all->ray.step_x == -1)
			draw_tex(all, all->tex.s_img, x);
		if (all->ray.side == 1 && all->ray.step_y == 1)
			draw_tex(all, all->tex.e_img, x);
		if (all->ray.side == 1 && all->ray.step_y == -1)
			draw_tex(all, all->tex.w_img, x);
		x++;
	}
	return (0);
}
