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
		if (y % (all->info.y_size / 200) == 0)
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
	//calculate value of wallX
	if(all->ray.side == 0)
		all->ray.wallX = all->ray.pos_y + all->ray.perp_wall_dist * all->ray.ray_dir_y;
	else
		all->ray.wallX = all->ray.pos_x + all->ray.perp_wall_dist * all->ray.ray_dir_x;
	all->ray.wallX -= floor((all->ray.wallX));

	//x coordinate on the texture
	all->ray.x_tex = (int)(all->ray.wallX * (double)wall_img.width);
	if((all->ray.side == 0 && all->ray.ray_dir_x > 0)
		|| (all->ray.side == 1 && all->ray.ray_dir_y < 0))
		all->ray.x_tex = wall_img.width - all->ray.x_tex;

	//y coordinate on the texture, step size
	all->ray.y_tex = 0;
	all->ray.y_tex_step = wall_img.height / (double)all->ray.line_height;
	if (all->ray.line_height > all->info.y_size)
		all->ray.y_tex = (all->ray.line_height - all->info.y_size) * all->ray.y_tex_step / 2;
	return (0);
}
/*
	Sets coordinates of texture image to use for wall
*/

int	set_sprite(t_all *all, t_img sprite_img)
{
	int spritelen = all->img.height / 2;
	//calculate value of spriteX
	if(all->ray.side == 0)
		all->ray.spriteX = all->ray.pos_y + all->ray.perp_sprite_dist * all->ray.ray_dir_y;
	else
		all->ray.spriteX = all->ray.pos_x + all->ray.perp_sprite_dist * all->ray.ray_dir_x;
	all->ray.spriteX -= floor((all->ray.spriteX));

	//x coordinate on the sprite
	all->ray.x_sprite = (int)(all->ray.spriteX * (double)sprite_img.width);
	if((all->ray.side == 0 && all->ray.ray_dir_x > 0)
		|| (all->ray.side == 1 && all->ray.ray_dir_y < 0))
		all->ray.x_sprite = sprite_img.width - all->ray.x_sprite;

	//y coordinate on the sprite, step size
	all->ray.y_sprite = 0;
	all->ray.y_sprite_step = all->tex.sprite_img.height / (double)spritelen;
	if (spritelen > all->tex.sprite_img.height )
		all->ray.y_sprite = (spritelen - all->tex.sprite_img.height ) * all->ray.y_sprite_step / 2;
	return (0);
}

int	draw_sprite(t_all *all, int x, int *new)
{
	char	*dst;
	int		y_img;
	int		color;
	// int		y_sprite;
	int		spritelen;

	new = 1;
	if (!all->ray.hit_sprite)
		return (0);
	if (all->ray.x_sprite >= all->tex.sprite_img.width)
		return (0);
	// set_sprite(all, all->tex.sprite_img);
	y_img = all->img.height / 4;
	// y_sprite = 0;

	spritelen = all->img.height / 2;

	all->ray.y_sprite = 0;
	all->ray.y_sprite_step = all->tex.sprite_img.height / (double)spritelen;
	if (spritelen > all->tex.sprite_img.height )
		all->ray.y_sprite = (spritelen - all->tex.sprite_img.height ) * all->ray.y_sprite_step / 2;

	// loop over vertical line on image
	while (y_img <= (all->img.height / 4 * 3) && all->ray.y_sprite < all->tex.sprite_img.height)
	{
		// printnum("y_img", y_img);
		// printnum("xsprite", all->ray.x_sprite % all->tex.sprite_img.width);
		// printnum("width", all->tex.sprite_img.width);
		// printnum("ysprite", (int)(y_sprite) % all->tex.sprite_img.height);
		// printnum("height", all->tex.sprite_img.height);
		dst = all->tex.sprite_img.addr + ((int)(all->ray.y_sprite) % all->tex.sprite_img.height * all->tex.sprite_img.line_length + all->ray.x_sprite % all->tex.sprite_img.width * (all->tex.sprite_img.bits_per_pixel / 8));
		color = *(unsigned int *)dst;
		// printnum("color", color);
		// printf("\n");
		put_pixel(&(all->img), x, y_img, color);
		y_img++;
		// y_sprite++;
		all->ray.y_sprite += all->ray.y_sprite_step;
	}
	// if (all->ray.hit_sprite == 1)
	// {
	// 	printf("yeah");
	// 	mlx_put_image_to_window(&(all->img.mlx), all->img.win, all->tex.sprite_img.img, 10, 80);
	// }
	return (1);
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
	// loop over vertical line 
	while (y_wall <= all->ray.draw_end)
	{
		dst = wall_img.addr + ((int)(all->ray.y_tex) % wall_img.height * wall_img.line_length + all->ray.x_tex % wall_img.width * (wall_img.bits_per_pixel / 8));
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
	int new;

	new = 0;

	draw_bg(all);
	x = 0;
	all->ray.x_sprite = 0;
	while (x < all->info.x_size)
	{
		set_ray_pos(all, x);
		set_ray_len(all);
		perform_dda(all);
		set_projection(all);
		if (all->ray.side == 0 && all->ray.step_x == 1)
			draw_tex(all, all->tex.n_img, x);
		if (all->ray.side == 0 && all->ray.step_x == -1)
			draw_tex(all, all->tex.s_img, x);
		if (all->ray.side == 1  && all->ray.step_y == 1)
			draw_tex(all, all->tex.e_img, x);
		if (all->ray.side == 1 && all->ray.step_y == -1)
			draw_tex(all, all->tex.w_img, x);
		if (all->ray.hit_sprite && new == 0)
		{
			draw_sprite(all, x, &new);
			all->ray.x_sprite++;
		}
		else
		{
			all->ray.x_sprite = 0;
		}
		
		x++;
	}
	return (0);
}
