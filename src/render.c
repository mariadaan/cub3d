#include "cub.h"

int	ver_line(t_all *all, int x)
{
	int	len;
	int i;

	len = all->rect.draw_end - all->rect.draw_start;
	i = 0;
	while (i < len)
	{
		put_pixel(&(all->img), x, all->rect.draw_start + i, all->rect.color);
		i++;
	}
	return (0);
}

int	tex2(t_all *all, t_img wall_img, int x)
{
	// t_img	wall_img;
	char	*dst;
	int		y_start;
	int		y_end;

	// if (all->ray.side == 0)
	// 	wall_img = all->tex.n_img;
	// else if (all->ray.side == 1)
	// 	wall_img = all->tex.n_img;

	//calculate value of wallX
	double wallX; //where exactly the wall was hit
	if(all->ray.side == 0)
		wallX = all->ray.pos_y + all->ray.perp_wall_dist * all->ray.ray_dir_y;
	else
		wallX = all->ray.pos_x + all->ray.perp_wall_dist * all->ray.ray_dir_x;
	wallX -= floor((wallX));

	// printfloat("wallX", wallX);
	//x coordinate on the texture
	int texX = (int)(wallX * (double)wall_img.width);
	if(all->ray.side == 0 && all->ray.ray_dir_x > 0)
		texX = wall_img.width - texX - 1;
	if(all->ray.side == 1 && all->ray.ray_dir_y < 0)
		texX = wall_img.width - texX - 1;

	// printnum("texX", texX);
	y_start = all->rect.draw_start;
	y_end = all->rect.draw_end;
	double y_tex;
	y_tex = 0;
	double y_tex_step;

	// printnum("line height", all->rect.line_height );
	y_tex_step = wall_img.height / (double)all->rect.line_height;
	if (all->rect.line_height > all->info.y_size)
		y_tex = (all->rect.line_height - all->info.y_size) * y_tex_step / 2;
	
	// 1 verticale lijn van boven naar beneden. 
	while (y_start < y_end)
	{
		dst = wall_img.addr + ((int)y_tex % (wall_img.height) * wall_img.line_length + ((int)texX) % wall_img.width * (wall_img.bits_per_pixel / 8));
		int color = *(unsigned int *)dst;
		if (all->ray.side == 0)
			color = darker_color(color);
			// color = gen_darker_color(color, 25);
		put_pixel(&(all->img), x, y_start, color);
		y_start++;
		y_tex += y_tex_step;
	}
	return (0);
}


int		tex3(t_all *all, t_img wall_img, int x)
{
	char	*dst;
	int		y_start;
	int		y_end;

	y_start = all->rect.draw_start;
	y_end = all->rect.draw_end;

	//calculate value of wallX
	double wallX; //where exactly the wall was hit
	if(all->ray.side == 0)
		wallX = all->ray.pos_y + all->ray.perp_wall_dist * all->ray.ray_dir_y;
	else
		wallX = all->ray.pos_x + all->ray.perp_wall_dist * all->ray.ray_dir_x;
	wallX -= floor((wallX));

	//x coordinate on the texture
	int texX = (int)(wallX * (double)(wall_img.width));
	if(all->ray.side == 0 && all->ray.ray_dir_x > 0)
		texX = wall_img.width - texX;
	if(all->ray.side == 1 && all->ray.ray_dir_y < 0)
		texX = wall_img.width - texX;

	// How much to increase the texture coordinate per screen pixel
	double step = wall_img.height / (double)all->rect.line_height;
	printfloat("step", step);
	// Starting texture coordinate
	double texPos = (all->rect.draw_start - all->info.y_size / 2 + all->rect.line_height / 2) * step;

	while (y_start < y_end)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		int texY = (int)texPos & (wall_img.height);
		texPos += step;
		dst = wall_img.addr + ((int)texY % (wall_img.bits_per_pixel) * wall_img.line_length + ((int)texX) * (wall_img.bits_per_pixel / 8));
		int color = *(unsigned int *)dst;
		// if (all->ray.side == 0)
		// 	color = gen_darker_color(color, 25);
		put_pixel(&(all->img), x, y_start, color);
		//  = texture[texNum][texHeight * texY + texX];
		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		// if(all->ray.side == 1)
		// 	color = (color >> 1) & 8355711;
		y_start++;
	}
	return (0);
}
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
	t_img wall_img;

	gradient_bg(all);
	x = 0;
	while (x < all->info.x_size)
	{
		set_ray_pos(all, x);
		set_ray_len(all);
		perform_dda(all);
		set_projection(all);
		wall_img = all->tex.n_img;
		printfloat("dir x ", all->ray.dir_x);
		printfloat("dir y ", all->ray.dir_y);
		printfloat("plane x ", all->ray.plane_x);
		printfloat("plane y ", all->ray.plane_y);
		printf("\n");

		if (all->ray.side == 0)
			wall_img = all->tex.n_img;
		else if (all->ray.side == 0  && all->ray.dir_y < 0)
			wall_img = all->tex.s_img;
		else if (all->ray.side == 1)
			wall_img = all->tex.e_img;
		else if (all->ray.side == 1  && all->ray.dir_y < 0)
			wall_img = all->tex.w_img;
		tex2(all, wall_img, x);
		x++;
	}
	return (0);
}



// vanaf hier skippen

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

// 	// How much to increase the texture coordinate per screen pixel
// 	double step = 1.0 * texHeight / all->rect.line_height;
// 	// Starting texture coordinate
// 	double texPos = (all->rect.draw_start - all->info.y_size / 2 + all->rect.line_height / 2) * step;
// 	for(int y = all->rect.draw_start; y < all->rect.draw_end; y++)
// 	{
// 		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
// 		int texY = (int)texPos & (texHeight - 1);
// 		texPos += step;
// 		unsigned int color = texture[texNum][texHeight * texY + texX];
// 		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
// 		if(all->ray.side == 1) color = (color >> 1) & 8355711;
// 		buffer[y][x] = color;
// 	}
// 	return (0);
// }