
# cub3D

## Usage
1. Clone this repository
   ```console
   git clone https://github.com/mariadaan/cub3d.git
   ```
2. Make the executable by running make
   ```console
   make
   ```
3. Execute **cub3D** with map of your choice
   ```console
   ./cub3D filename.cub
   ```

### Some example cub3D environments
Run one of the following commands to try different cub3D environments! 
- make jungle
- make jungle2
- make trip
- make map
- make map2

### Behavior in invalid map cases
- make invalid
- make invalid_res
- make wrongarg
- make non

## Variable explanation

### MLX variables 
	void	*mlx; *** // connection to the correct graphical system,holds the location of our  current MLX ***instance***
	void	*img; *** // address of image ***
	void	*win; *** // address of ***
	char	*addr; *** // array of colors (length is width in pixels * bpp) ***
	int	bits_per_pixel; *** // usually 4 bytes per pixel ***
	int	line_length; *** // in bytes (width * bpp) ***
	int	endian; *** // order of bytes ***
	int	width; *** // in pixels ***
	int	height; *** // in pixels ***

### Raycasting variables 
	*** // x and y exact player position ***
	double pos_x;
	double pos_y;

	*** // direction vector (point straight in front of player) ***
	double dir_x;
	double dir_y;

	*** // the 2d raycaster version of camera plane ***
	double plane_x;
	double plane_y;

	*** // x-coordinate in camera plane (factor to multiply plane coordinates with) ***
	double camera_x;

	*** // The ray position contains both info about in which square of the map we are, and  where in that square we are***
	double ray_dir_x;
	double ray_dir_y;

	*** // which box of the map we're in (just the coordinate of the square, not where in the  square)***
	int map_x;
	int map_y;

	*** // length of ray from current position to next x or y-side ***
	*** // x from pos to FIRST vertical line on the grid (after first hit, distance will remain  stable)***
	double side_dist_x;
	*** // y from pos to FIRST horizontal line on the grid ***
	double side_dist_y;

	*** // distance the ray has to travel to go from 1 x-side to the next x-side, or from 1  y-side to the next y-side.***
	*** // from side_dist_x till next vertical line ***
	double delta_dist_x;
	*** // from side_dist_y till next horizontal line ***
	double delta_dist_y;

	*** // length of full ray ***
	double perp_wall_dist;

	*** // what direction to step in x or y-direction (either +1 or -1, just to the next  gridline)***
	int step_x;
	int step_y;

	*** // was there a wall hit? ***
	int hit;

	*** // was a NS or a EW wall hit? (0 = x wall hit, 1 = y wall hit) ***
	int side;

	double step_size; *** // constant value in squares ***
	double const_rad; *** // constant value in radians ***

	int				line_height; *** // real wall height in pixels ***
	int				draw_start; *** // start y coordinate on image ***
	int				draw_end; *** // end y coordinate on image ***

	double 			wall_x; *** // where exactly the wall was hit ***
	int				x_tex; *** // x coordinate on the texture ***
	double			y_tex; *** // y coordinate on the texture ***
	double			y_tex_step; *** // y coordinate step size ***
