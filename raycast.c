#include "cub.h"

#define mapWidth 33
#define mapHeight 14
#define screenWidth 640
#define screenHeight 480

# define LEFT 123
# define RIGHT 124
# define UP 125
# define DOWN 126

int worldMap[mapWidth][mapHeight]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};



int verLine(t_data *img, int x, int drawStart, int drawEnd, int color)
{
	int len;

	len = drawEnd - drawStart;
	put_vertical(img, x, drawStart, len, color);
	// printf("verline");
	return (0);
}

int render_screen(t_all *all)
{
	t_ray ray = all->ray;
	t_data img = all->img;
	t_info info = all->info;
	// char **worldMap = info.map;

	fill_rect(&img, 0, 0, screenWidth, screenHeight / 2, 0x00B1DC);
	fill_rect(&img, 0, screenHeight / 2, screenWidth, screenHeight / 2, 0x103A44);

	for(int x = 0; x < screenWidth; x++)
	{
		//calculate ray position and direction
		ray.camera_x = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
		ray.ray_dir_x = ray.dir_x + ray.plane_x * ray.camera_x;
		ray.ray_dir_y = ray.dir_y + ray.plane_y * ray.camera_x;

		// printf("camera_x: %f\n", camera_x);
		// printf("plane_x:  %f\n", plane_x);
		// printf("plane_y:  %f\n", plane_y);
		// printf("ray_dir_x: %f\n", ray_dir_x);
		// printf("ray_dir_y: %f\n\n", ray_dir_y);
		//which box of the map we're in
		ray.map_x = (int)ray.pos_x;
		ray.map_y = (int)ray.pos_y;

		//length of ray from current position to next x or y-side
		// ray.side_dist_x;
		// ray.side_dist_y;

		 //length of ray from one x or y-side to next x or y-side
		ray.delta_dist_y = fabs(1 / ray.ray_dir_x); // fabs
		ray.delta_dist_x = fabs(1 / ray.ray_dir_y);
		// ray.perp_wall_dist;

		//what direction to step in x or y-direction (either +1 or -1)
		// ray.step_x;
		// ray.step_y;

		ray.hit = 0; //was there a wall hit?
		// ray.side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if(ray.ray_dir_x < 0)
		{
		ray.step_x = -1;
		ray.side_dist_x = (ray.pos_x - ray.map_x) * ray.delta_dist_y;
		}
		else
		{
			ray.step_x = 1;
			ray.side_dist_x = (ray.map_x + 1.0 - ray.pos_x) * ray.delta_dist_y;
		}
		if(ray.ray_dir_y < 0)
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
		if(ray.side_dist_x < ray.side_dist_y)
		{
			ray.side_dist_x += ray.delta_dist_y;
			ray.map_x += ray.step_x;
			ray.side = 0;
		}
		else
		{
			ray.side_dist_y += ray.delta_dist_x;
			ray.map_y += ray.step_y;
			ray.side = 1;
		}
		//Check if ray has hit a wall
		if(worldMap[ray.map_x][ray.map_y] > 0) ray.hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if(ray.side == 0) ray.perp_wall_dist = (ray.map_x - ray.pos_x + (1 - ray.step_x) / 2) / ray.ray_dir_x;
		else			ray.perp_wall_dist = (ray.map_y - ray.pos_y + (1 - ray.step_y) / 2) / ray.ray_dir_y;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(screenHeight / ray.perp_wall_dist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if(drawEnd >= screenHeight)drawEnd = screenHeight - 1;

		//choose wall color
		int color;
		
		color = 0xAB29E2;

		//give x and y sides different brightness
		if(ray.side == 1) {color = color / 2;}

		//draw the pixels of the stripe as a vertical line
		verLine(&img, x, drawStart, drawEnd, color);
	}
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	return (0);
}

int	key_pressed(int keycode, t_all *all)
{
	printnum("keycode", keycode);
	t_ray ray = all->ray;
	t_info info = all->info;
	// char **worldMap = info.map;

	if(keycode == DOWN)
	{
		printf("up\n");
		if(worldMap[(int)(ray.pos_x + ray.dir_x * ray.move_speed)][(int)(ray.pos_y)] == 0) ray.pos_x += ray.dir_x * ray.move_speed;
		if(worldMap[(int)(ray.pos_x)][(int)(ray.pos_y + ray.dir_y * ray.move_speed)] == 0) ray.pos_y += ray.dir_y * ray.move_speed;
	}
	//move backwards if no wall behind you
	if(keycode == UP)
	{
		printf("down\n");
		if(worldMap[(int)(ray.pos_x - ray.dir_x * ray.move_speed)][(int)(ray.pos_y)] == 0) ray.pos_x -= ray.dir_x * ray.move_speed;
		if(worldMap[(int)(ray.pos_x)][(int)(ray.pos_y - ray.dir_y * ray.move_speed)] == 0) ray.pos_y -= ray.dir_y * ray.move_speed;
	}
	//rotate to the right
	if(keycode == RIGHT)
	{
		printf("right\n");
		//both camera direction and camera plane must be rotated
		double oldDirX = ray.dir_x;
		ray.dir_x = ray.dir_x * cos(-ray.rot_speed) - ray.dir_y * sin(-ray.rot_speed);
		ray.dir_y = oldDirX * sin(-ray.rot_speed) + ray.dir_y * cos(-ray.rot_speed);
		double oldPlaneX = ray.plane_x;
		ray.plane_x = ray.plane_x * cos(-ray.rot_speed) - ray.plane_y * sin(-ray.rot_speed);
		ray.plane_y = oldPlaneX * sin(-ray.rot_speed) + ray.plane_y * cos(-ray.rot_speed);
	}
	//rotate to the left
	if(keycode == LEFT)
	{
		printf("left\n");
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
	if (keycode == 53)
		destroy_window(&(all->img));
	return (keycode);
}

int main(int argc, char *argv[])
{
	t_data		img;
	t_all		all;
	t_ray		ray;
	t_info		info;

	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, screenWidth, screenHeight, "Maria's cub3d");
	img.img = mlx_new_image(img.mlx, screenWidth, screenHeight);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
													&img.endian);

	if (argc != 2)
		printf("Invalid arguments\n");

	int fd = open(argv[1], O_RDONLY);

	int ret = parse_all(fd, &info);

	ray.pos_x = 10, ray.pos_y = 12;	//x and y start position
	ray.dir_x = -1, ray.dir_y = 0; //initial direction vector
	ray.plane_x = 0, ray.plane_y = 0.66; //the 2d raycaster version of camera plane 	
	ray.time = 0; //time of current frame
	ray.old_time = 0; //time of previous frame
	int w = screenWidth;
	int h = screenHeight;


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
	ray.rot_speed = 0.1; //the constant value is in radians/second 0.1
	// readKeys();

	all.img = img;
	all.ray = ray;
	render_screen(&all);
	mlx_hook(img.win, KeyPress, 0, key_pressed, &all);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	mlx_hook(img.win, DestroyNotify, 0, destroy_window, &all);
	mlx_loop(img.mlx);
}

