#include "cub.h"

int	show_img(t_all *all)
{
	mlx_put_image_to_window(&(all->img.mlx), all->img.win, all->img.img, 0, 0);
	return (0);
}

int	ver_line(t_all *all, int x)
{
	int	len;

	len = all->rect.draw_end - all->rect.draw_start;
	put_vertical(&(all->img), x, all->rect.draw_start, len, all->rect.color);
	return (0);
}

#define texWidth 64
#define texHeight 64
#define screenWidth 640
#define screenHeight 480
unsigned int buffer[screenHeight][screenWidth];

int	textured(t_all *all, int x)
{
	//texturing calculations
	int texNum = all->info.map[all->ray.map_x][all->ray.map_x] - 1; //1 subtracted from it so that texture 0 can be used!

	//calculate value of wallX
	double wallX; //where exactly the wall was hit
	if(all->ray.side == 0) wallX = all->ray.pos_y + all->ray.perp_wall_dist * all->ray.ray_dir_y;
	else		wallX = all->ray.pos_x + all->ray.perp_wall_dist * all->ray.ray_dir_x;
	wallX -= floor((wallX));

	//x coordinate on the texture
	int texX = (int)(wallX * (double)(texWidth));
	if(all->ray.side == 0 && all->ray.ray_dir_x > 0) texX = texWidth - texX - 1;
	if(all->ray.side == 1 && all->ray.ray_dir_y < 0) texX = texWidth - texX - 1;

	// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
	// How much to increase the texture coordinate per screen pixel
	double step = 1.0 * texHeight / all->rect.line_height;
	// Starting texture coordinate
	double texPos = (all->rect.draw_start - all->info.y_size / 2 + all->rect.line_height / 2) * step;
	for(int y = all->rect.draw_start; y < all->rect.draw_end; y++)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		int texY = (int)texPos & (texHeight - 1);
		texPos += step;
		unsigned int color;
		//  = texture[texNum][texHeight * texY + texX];
		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		if(all->ray.side == 1) color = (color >> 1) & 8355711;
		buffer[y][x] = color;
	}
	return (0);
}

int	dda(t_all *all)
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
		if (all->info.map[all->ray.map_x][all->ray.map_y] > '0')
			all->ray.hit = 1;
	}
	return (0);
}

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

int	draw_img(t_all *all)
{
	int x;
	
	// ft_bzero(&rect, sizeof(&rect));
	gradient_bg(all);
	x = 0;
	// Loop over vertical lines to be drawn in image
	while (x < all->info.x_size)
	{
		set_values(all, x);
		//Calculate height of line to draw on screen
		all->rect.line_height = (int)(all->info.y_size / all->ray.perp_wall_dist);

		//calculate lowest and highest pixel to fill in current stripe
		all->rect.draw_start = -all->rect.line_height / 2 + all->info.y_size / 2;
		if (all->rect.draw_start < 0)
			all->rect.draw_start = 0;
		all->rect.draw_end = all->rect.line_height / 2 + all->info.y_size / 2;
		if (all->rect.draw_end >= all->info.y_size)
			all->rect.draw_end = all->info.y_size - 1;

		//choose wall color
		all->rect.color = 0x9c9c9c;

		//give x and y sides different brightness
		if (all->ray.side == 1)
		{
			all->rect.color = gen_darker_color(all->rect.color, 50);
		}
		// textured(all, x);
		// drawBuffer(buffer[0]);
		// for(int y = 0; y < h; y++) for(int x = 0; x < w; x++) buffer[y][x] = 0;
		//draw the pixels of the stripe as a vertical line
		ver_line(all, x);
		x++;
	}
	mlx_put_image_to_window(&(all->img.mlx), all->img.win, all->img.img, 0, 0);
	return (0);
}