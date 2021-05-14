#include "cub.h"

int verLine(t_data *img, int x, int drawStart, int drawEnd, int color)
{
	int len;

	len = drawEnd - drawStart;
	put_vertical(img, x, drawStart, len, color);
	return (0);
}

int render_screen(t_all *all)
{
	t_ray ray = all->ray;
	t_data img = all->img;
	t_info info = all->info;
	char **worldMap = info.map;

	gradient_bg(all);

	// Loop over vertical lines to be drawn in image
	for (int x = 0; x < info.x_size; x++)
	{
		//calculate ray position and direction
		ray.camera_x = 2 * x / (double)info.x_size - 1; //x-coordinate in camera space
		ray.ray_dir_x = ray.dir_x + ray.plane_x * ray.camera_x;
		ray.ray_dir_y = ray.dir_y + ray.plane_y * ray.camera_x;

		//which box of the map we're in
		ray.map_x = (int)ray.pos_x;
		ray.map_y = (int)ray.pos_y;

		//length of ray from one x or y-side to next x or y-side
		ray.delta_dist_y = fabs(1 / ray.ray_dir_x);
		ray.delta_dist_x = fabs(1 / ray.ray_dir_y);

		ray.hit = 0; //was there a wall hit?

		//calculate step and initial sideDist
		if (ray.ray_dir_x < 0)
		{
			ray.step_x = -1;
			ray.side_dist_x = (ray.pos_x - ray.map_x) * ray.delta_dist_y;
		}
		else
		{
			ray.step_x = 1;
			ray.side_dist_x = (ray.map_x + 1.0 - ray.pos_x) * ray.delta_dist_y;
		}
		if (ray.ray_dir_y < 0)
		{
			ray.step_y = -1;
			ray.side_dist_y = (ray.pos_y - ray.map_y) * ray.delta_dist_x;
		}
		else
		{
			ray.step_y = 1;
			ray.side_dist_y = (ray.map_y + 1.0 - ray.pos_y) * ray.delta_dist_x;
		}
		//perform DDA
		while (ray.hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (ray.side_dist_x < ray.side_dist_y)
			{
				ray.side_dist_x += ray.delta_dist_y;
				ray.map_x += ray.step_x;
				ray.side = 0;
				// if (ray.map_x < 0)
				// 	ray.map_x = 0;
			}
			else
			{
				ray.side_dist_y += ray.delta_dist_x;
				ray.map_y += ray.step_y;
				ray.side = 1;
				// if (ray.map_y < 0)
				// 	ray.map_y = 0;
			}
			// printnum("map_x", ray.map_x);
			// printnum("map_y", ray.map_y);

			//Check if ray has hit a wall
			if (worldMap[ray.map_x][ray.map_y] - '0' > 0)
				ray.hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (ray.side == 0)
			ray.perp_wall_dist = (ray.map_x - ray.pos_x + (1 - ray.step_x) / 2) / ray.ray_dir_x;
		else
			ray.perp_wall_dist = (ray.map_y - ray.pos_y + (1 - ray.step_y) / 2) / ray.ray_dir_y;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(info.y_size / ray.perp_wall_dist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + info.y_size / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + info.y_size / 2;
		if (drawEnd >= info.y_size)
			drawEnd = info.y_size - 1;

		//choose wall color

		int color = 0x9c9c9c;

		//give x and y sides different brightness
		if (ray.side == 1)
		{
			color = gen_darker_color(color, 50);
		}

		//draw the pixels of the stripe as a vertical line
		verLine(&img, x, drawStart, drawEnd, color);
	}
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	return (0);
}

int key_pressed(int keycode, t_all *all)
{
	t_ray ray = all->ray;
	t_info info = all->info;
	char **worldMap = info.map;

	if (keycode == 53)
		destroy_window(&(all->img));
	if (keycode == FORWARD)
	{
		printco("", ray.pos_x, ray.pos_y);
		printchar("", worldMap[(int)ray.pos_x][(int)ray.pos_y]);
		if (worldMap[(int)(ray.pos_x + ray.dir_x * ray.move_speed)][(int)(ray.pos_y)] - '0' == 0)
			ray.pos_x += ray.dir_x * ray.move_speed;
		if (worldMap[(int)(ray.pos_x)][(int)(ray.pos_y + ray.dir_y * ray.move_speed)] - '0' == 0)
			ray.pos_y += ray.dir_y * ray.move_speed;
	}
	//move backwards if no wall behind you
	if (keycode == BACKWARDS)
	{
				printco("", ray.pos_x, ray.pos_y);
		printchar("", worldMap[(int)ray.pos_x][(int)ray.pos_y]);
		if (worldMap[(int)(ray.pos_x - ray.dir_x * ray.move_speed)][(int)(ray.pos_y)] - '0' == 0)
			ray.pos_x -= ray.dir_x * ray.move_speed;
		if (worldMap[(int)(ray.pos_x)][(int)(ray.pos_y - ray.dir_y * ray.move_speed)] - '0' == 0)
			ray.pos_y -= ray.dir_y * ray.move_speed;
	}
	//move left if no wall
	if (keycode == LEFT)
	{
		if (worldMap[(int)(ray.pos_x - ray.plane_x * ray.move_speed)][(int)(ray.pos_y)] - '0' == 0)
			ray.pos_x -= ray.plane_x * ray.move_speed;
		if (worldMap[(int)(ray.pos_x)][(int)(ray.pos_y - ray.plane_y * ray.move_speed)] - '0' == 0)
			ray.pos_y -= ray.plane_y * ray.move_speed;
	}
	//move right if no wall
	if (keycode == RIGHT)
	{
		if (worldMap[(int)(ray.pos_x + ray.plane_x * ray.move_speed)][(int)(ray.pos_y)] - '0' == 0)
			ray.pos_x -= ray.plane_x * ray.move_speed;
		if (worldMap[(int)(ray.pos_x)][(int)(ray.pos_y + ray.plane_y * ray.move_speed)] - '0' == 0)
			ray.pos_y += ray.plane_y * ray.move_speed;
	}
	//rotate to the right
	if (keycode == RROTATE)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = ray.dir_x;
		ray.dir_x = ray.dir_x * cos(-ray.rot_speed) - ray.dir_y * sin(-ray.rot_speed);
		ray.dir_y = oldDirX * sin(-ray.rot_speed) + ray.dir_y * cos(-ray.rot_speed);
		double oldPlaneX = ray.plane_x;
		ray.plane_x = ray.plane_x * cos(-ray.rot_speed) - ray.plane_y * sin(-ray.rot_speed);
		ray.plane_y = oldPlaneX * sin(-ray.rot_speed) + ray.plane_y * cos(-ray.rot_speed);
	}
	//rotate to the left
	if (keycode == LROTATE)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = ray.dir_x;
		ray.dir_x = ray.dir_x * cos(ray.rot_speed) - ray.dir_y * sin(ray.rot_speed);
		ray.dir_y = oldDirX * sin(ray.rot_speed) + ray.dir_y * cos(ray.rot_speed);
		double oldPlaneX = ray.plane_x;
		ray.plane_x = ray.plane_x * cos(ray.rot_speed) - ray.plane_y * sin(ray.rot_speed);
		ray.plane_y = oldPlaneX * sin(ray.rot_speed) + ray.plane_y * cos(ray.rot_speed);
	}
	all->ray = ray;

	render_screen(all);
	return (keycode);
}

int main(int argc, char *argv[])
{
	t_data img;
	t_all all;
	t_ray ray;
	t_info info;

	if (argc != 2)
		printf("Invalid arguments\n");

	int fd = open(argv[1], O_RDONLY);
	int ret = parse_all(fd, &info);
	if (ret)
		return (1);

	img.mlx = mlx_init();
	if (check_res(&img, &info))
	{
		red();
		printf("Resolution too big for screen!\n");
		reset();
		return (1);
	}
	green();
	printf("Parsed successfully!\n");
	reset();
	img.win = mlx_new_window(img.mlx, info.x_size, info.y_size, "Maria's cub3d");
	img.img = mlx_new_image(img.mlx, info.x_size, info.y_size);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								 &img.endian);

	// ray.pos_x = 11, ray.pos_y = 26;
	// HOE IS X Y EN ANDERSOM!!!
	ray.pos_x = info.y_spawn, ray.pos_y = info.x_spawn;		 //x and y start position
	ray.dir_x = -1, ray.dir_y = 0;		 //initial direction vector
	ray.plane_x = 0, ray.plane_y = 0.66; //the 2d raycaster version of camera plane
	ray.time = 0;						 //time of current frame
	ray.old_time = 0;					 //time of previous frame

	// mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	//timing for input and FPS counter
	// oldTime = time;
	// time = getTicks();
	// double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
	// print(1.0 / frameTime); //FPS counter
	// redraw();
	// cls();

	//speed modifiers
	ray.move_speed = 0.2; //the constant value is in squares/second 0.2
	ray.rot_speed = 0.1;  //the constant value is in radians/second 0.1
	// readKeys();

	all.img = img;
	all.ray = ray;
	all.info = info;

	render_screen(&all);
	mlx_hook(img.win, KeyPress, 0, key_pressed, &all);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	mlx_hook(img.win, DestroyNotify, 0, destroy_window, &all);
	mlx_loop(img.mlx);
}
