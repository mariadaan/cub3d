
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

## Some example cub3D environments
Run one of the following commands to try different cub3D environments! 
- make jungle
- make jungle2
- make trip
- make map
- make map2

## Behavior in invalid map cases
- make invalid
- make invalid_res
- make wrongarg
- make non


## MLX variables 
	void	*mlx; // 
	void	*img;
	void	*win;
	char	*addr;
	int		bits_per_pixel;
	int		line_length; // in bytes (width / 4)
	int		endian;
	int		width; // in pixels
	int		height; // in pixels

## Raycasting variables 
typedef struct s_ray {
	// x and y exact player position
	double pos_x;
	double pos_y;

	// direction vector (point straight in front of player)
	double dir_x;
	double dir_y;

	//the 2d raycaster version of camera plane
	double plane_x;
	double plane_y;

	//x-coordinate in camera plane (factor to multiply plane coordinates with)
	double camera_x;

	// The ray position contains both info about in which square of the map we are, and where in that square we are
	double ray_dir_x;
	double ray_dir_y;

	//which box of the map we're in (just the coordinate of the square, not where in the square)
	int map_x;
	int map_y;

	// length of ray from current position to next x or y-side
	// x vanaf pos tot EERSTE verticale lijn op grid (eenmalige kortere afstand, daarna altijd zelfde)
	double side_dist_x;
	// y vanaf pos tot EERSTE horizontale lijn op grid
	double side_dist_y;

	// distance the ray has to travel to go from 1 x-side to the next x-side, or from 1 y-side to the next y-side.
	// vanaf side_dist_x tot volgende verticale lijn
	double delta_dist_x;
	// vanaf side_dist_y tot volgende horizontale lijn
	double delta_dist_y;

	// lengte van de hele ray
	double perp_wall_dist;

	// lengte van de hele ray
	double perp_sprite_dist;

	// what direction to step in x or y-direction (either +1 or -1, just to the next gridline)
	int step_x;
	int step_y;

	//was there a wall hit?
	int hit;

	//was there a sprite hit?
	int hit_sprite;

	//was a NS or a EW wall hit? (0 = x wall hit, 1 = y wall hit)
	int side;

	double step_size; // constant value in squares
	double const_rad; // constant value in radians

	int				line_height; // real wall height in pixels
	int				draw_start; // start y coordinate on image
	int				draw_end; // end y coordinate on image

	double 			wall_x; //where exactly the wall was hit
	int				x_tex; //x coordinate on the texture
	double			y_tex; //y coordinate on the texture
	double			y_tex_step;
}		t_ray;

typedef struct s_info
{
	char			*full_file;
	int				x_size;
	int				y_size;
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	unsigned int	f_color;
	unsigned int	c_color;
	char			**map;
	int				map_width;
	int				map_height;
	int				x_spawn;
	int				y_spawn;
	char			spawn_dir;
	char			*start;
}				t_info;

typedef struct s_tex
{
	t_img			n_img;
	t_img			e_img;
	t_img			s_img;
	t_img			w_img;
	t_img			sprite_img;
}				t_tex;

typedef struct s_all {
	int				press_release;
	t_img			img;
	t_ray			ray;
	t_info			info;
	t_tex			tex;
}			t_all;

typedef struct s_color {
	int				r;
	int				g;
	int				b;
	int				color;
}				t_color;
