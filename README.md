
# cub3D

## Usage
1. Clone this repository
   ```console
   git clone https://github.com/mariadaan/cub3d.git
   ```
2. Create the executable by running make
   ```console
   make
   ```
3. Execute **cub3D** with map of your choice
   ```console
   ./cub3D filename.cub
   ```

### Some example cub3D environments
Run one of the following commands to try different cub3D environments! 

- make residential
<p align="center">
<img src="/pics/trim.gif" alt="animated" />
</p>

- make trip
![Alt text](/pics/trip.png "Trip")

- make jungle
![Alt text](/pics/jungle.png "Jungle")

- make huisjes

- make jungle2

- make map

- make map2

### Behavior in invalid map cases
- make invalid
- make invalid_res
- make wrongarg
- make non

## How it works
When you run the cub3d program, the following functions are called from the main.

1. **init_input**: Checks user input. Has an argument with the name of the cub file been given?
	Does the file exist? If yes, the file will be parsed.
2. **parse_all**: Saves cub file in one long string and calls other functions (**parse_res**, 			**parse_color**, **parse_map**, **get_spawn_pos** and **parse_tex**) to parse all
	parts of the information in the cub file. This information is saved in the
	t_info info struct. 
2. **init_textures**: Creates an image structure for every texture and saves them in t_tex tex with 	**file_to_img**.
3. **init_mlx**: Create the window in which the cub3d project will be shown and create an
	image called img, that will be modified during the program. Also checks whether resolution is valid and modifies it if necessary in **check_res**. 
4. **init_raycaster**: Set the values that are used by the raycaster algorithm in render.c to the
	correct starting values. step_size can be modified to change walking speed.
	const_rad can be modified to change rotation speed. Depending on the spawn
	direction, player is rotated in the **spawn_dir** function.
5. **draw_img**: Draws background using **draw_bg**. Loops over vertical lines to be drawn in image, 	does raycasting calculations for every line (**set_ray_pos**, **set_ray_len**, **perform_dda** 		and **set_projection**), and places the textures on the walls (**draw_tex**).
6. **show_img**: Place the rendered image on the window so it can be shown. 

The hook functions that are called in main make sure that any key press or key release is constantly checked for. When a key has been pressed, **check_move** moves the player position in the map. After this, **draw_img** and **show_img** will be called again to update the image that is shown in the window. This keeps happening until the key is released. When the key is released, moving will stop and the image will not be updated until a key is pressed again. When the esc button or the red cross in the upper left corner is pressed, the program will free all allocated memory and quit the program.

## Variable explanation

### MLX variables 
	void	*mlx; // connection to the correct graphical system,holds the location of our current MLX instance
	void	*img; // address of image
	void	*win; // address of
	char	*addr; // array of colors (length is width in pixels * bpp)
	int	bits_per_pixel; // usually 4 bytes per pixel
	int	line_length; // in bytes (width * bpp)
	int	endian; // order of bytes
	int	width; // in pixels
	int	height; // in pixels

### Raycasting variables 
	// x and y exact player position
	double	pos_x;
	double	pos_y;

	// direction vector (point	straight in front of player)
	double	dir_x;
	double	dir_y;

	// the 2d raycaster version of camera plane
	double	plane_x;
	double	plane_y;

	// x-coordinate in camera plane (factor to multiply plane coordinates with)
	double	camera_x;

	// The ray position contains both info about in which square of the map we are, and where in that square we are
	double	ray_dir_x;
	double	ray_dir_y;

	// which box of the map we're in (just the coordinate of the square, not where in the square)
	int	map_x;
	int	map_y;

	// length of ray from current position to next x or y-side
	// x from pos to FIRST vertical line on the grid (after first hit, distance will remain stable)
	double	side_dist_x;
	// y from pos to FIRST horizontal line on the grid
	double	side_dist_y;

	// distance the ray has to travel to go from 1 x-side to the next x-side, or from 1 y-side to the next y-side.
	// from side_dist_x till next vertical line
	double	delta_dist_x;
	// from side_dist_y till next horizontal line
	double	delta_dist_y;

	// length of full ray
	double	perp_wall_dist;

	// what direction to step in x or y-direction (either +1 or -1, just to the next gridline)
	int	step_x;
	int	step_y;

	// was there a wall hit?
	int	hit;

	// was a NS or a EW wall hit? (0 = x wall hit, 1 = y wall hit)
	int	side;

	double	step_size; // constant value in squares
	double	const_rad; // constant value in radians

	int	line_height; // real wall height in pixels
	int	draw_start; // start y coordinate on image
	int	draw_end; // end y coordinate on image

	double	wall_x; // where exactly the wall was hit
	int	x_tex; // x coordinate on the texture
	double	y_tex; // y coordinate on the texture
	double	y_tex_step; // y coordinate step size

### Memleak check
```console
valgrind --log-file="memleak_logs" ./cub3D maps/jungle.cub
```