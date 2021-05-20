#include "cub.h"

int	ver_line(t_all *all, int x)
{
	int	len;

	len = all->rect.draw_end - all->rect.draw_start;
	put_vertical(&(all->img), x, all->rect.draw_start, len, all->rect.color);
	return (0);
}

int	textured(t_all *all, int x)
{
	t_img	wall_img;
	char	*dst;
	int		color;
	int		y_start;
	int		y_end;
	int		i;
	int		wall_len;

	if (all->ray.side == 0)
		wall_img = all->tex.n_img;
	else if (all->ray.side == 1)
		wall_img = all->tex.n_img;

	i = 0;
	y_start = all->rect.draw_start;
	y_end = all->rect.draw_end;
	wall_len = y_end - y_start;
	// printnum("len", y_end - y_start);
	// printnum("height", all->rect.line_height);

	while (y_start < y_end)
	{
		int y_waarde = (i % (wall_img.height));
		dst = wall_img.addr + (y_waarde * wall_img.line_length + (x % wall_img.width) * (wall_img.bits_per_pixel / 8));
		color = *(unsigned int *)dst;
		if (all->ray.side == 0)
			color = gen_darker_color(color, 25);
		my_mlx_pixel_put(&(all->img), x, y_start, color);
		y_start++;
		i++;
	}
	return (0);
}


// #define texWidth 64
// #define texHeight 64
// #define screenWidth 640
// #define screenHeight 480
// unsigned int buffer[screenHeight][screenWidth];

// int	textured(t_all *all, int x)
// {
// 	//texturing calculations
// 	int texNum = all->info.map[all->ray.map_x][all->ray.map_x] - 1; //1 subtracted from it so that texture 0 can be used!

// 	//calculate value of wallX
// 	double wallX; //where exactly the wall was hit
// 	if(all->ray.side == 0) wallX = all->ray.pos_y + all->ray.perp_wall_dist * all->ray.ray_dir_y;
// 	else		wallX = all->ray.pos_x + all->ray.perp_wall_dist * all->ray.ray_dir_x;
// 	wallX -= floor((wallX));

// 	//x coordinate on the texture
// 	int texX = (int)(wallX * (double)(texWidth));
// 	if(all->ray.side == 0 && all->ray.ray_dir_x > 0) texX = texWidth - texX - 1;
// 	if(all->ray.side == 1 && all->ray.ray_dir_y < 0) texX = texWidth - texX - 1;

// 	// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
// 	// How much to increase the texture coordinate per screen pixel
// 	double step = 1.0 * texHeight / all->rect.line_height;
// 	// Starting texture coordinate
// 	double texPos = (all->rect.draw_start - all->info.y_size / 2 + all->rect.line_height / 2) * step;
// 	for(int y = all->rect.draw_start; y < all->rect.draw_end; y++)
// 	{
// 		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
// 		int texY = (int)texPos & (texHeight - 1);
// 		texPos += step;
// 		unsigned int color;
// 		//  = texture[texNum][texHeight * texY + texX];
// 		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
// 		if(all->ray.side == 1) color = (color >> 1) & 8355711;
// 		buffer[y][x] = color;
// 	}
// 	return (0);
// }

void	untextured(t_all *all, int x)
{
	//choose wall color
	all->rect.color = 0x9c9c9c;
	//give x and y sides different brightness
	if (all->ray.side == 1)
	{
		all->rect.color = gen_darker_color(all->rect.color, 50);
	}
	//draw the pixels of the stripe as a vertical line
	ver_line(all, x);
}

/*
	Loops over vertical lines to be drawn in image, does raycasting calculations
	for every line, and places the textures on the walls.
*/

int	draw_img(t_all *all)
{
	int x;

	gradient_bg(all);
	x = 0;
	// Loop over vertical lines to be drawn in image
	while (x < all->info.x_size)
	{
		set_ray_pos(all, x);
		set_ray_len(all);
		perform_dda(all);
		set_projection(all);
		textured(all, x);
		x++;
	}
	return (0);
}