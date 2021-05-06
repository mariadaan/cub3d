#ifndef CUB_H
# define CUB_H

# include "mlxopengl/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "keys.h"


typedef struct s_data {
	void			*mlx;
	void			*img;
	void			*win;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}				t_data;

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

	// what direction to step in x or y-direction (either +1 or -1, just to the next gridline)
	int step_x;
	int step_y;

	//was there a wall hit?
	int hit; 

	//was a NS or a EW wall hit? (0 = x wall hit, 1 = y wall hit)
	int side;

	double move_speed; //the constant value is in squares/second
	double rot_speed; //the constant value is in radians/second

	double time;
	double old_time;
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
	char			*s_path;
	unsigned int	f_color;
	unsigned int	c_color;
	char			**map;
	int				map_width;
	int				map_height;
	int				x_spawn;
	int				y_spawn;
	char			spawn_dir;
}				t_info;

typedef struct s_all {
	t_data img;
	t_ray ray;
	t_info info;
}			t_all;

typedef struct s_rect {
	int				x;
	int				y;
	int				width;
	int				height;
	unsigned int	color;
}				t_rect;

typedef struct s_position {
	int				x_pos;
	int				y_pos;
}				t_position;

typedef struct s_color {
	int				r;
	int				g;
	int				b;
	int				color;
}				t_color;

/*
	parse.c
*/
int				parse_all(int fd, t_info *info);

int				get_findex(char *str, char c);

int				get_lindex(char *str, char c);


/*
	pixel.c
*/
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);

void			put_horizontal(t_data *data, int x, int y, int len, int color);

void			put_vertical(t_data *data, int x, int y, int len, int color);

void			put_rect(t_data *data, int x, int y, int xlen, int ylen, int color);

void			fill_rect(t_data *data, int x, int y, int xlen, int ylen, int color);

void			gradient_bg(t_all *all);

void			gradient_rect(t_all *all, int y_start, int color);

/*
	hook_action.c
*/
int				key_release(int keycode, t_data *img);

int				key_press(int keycode, t_data *img);

int				destroy_window(t_data *img);

/*
	move.c
*/
int				move_rect(int keycode, int *x_pos, int *y_pos, t_data *img);

/*
	utils.c
*/
void			init_info(t_info *info);

void			print_info(t_info *info);

/*
	color.c
*/
// int				get_t(int trgb);

int				get_r(int trgb);

int				get_g(int trgb);

int				get_b(int trgb);

// unsigned int	create_trgb(int t, int r, int g, int b);
int				create_rgb(int r, int g, int b);

/*
	color_utils.c
*/
void			print_components(int color);

int				gen_darker_color(int color, int factor);

/*
	printvar.c
*/
int				printnum(char * name, int num);

int				printstr(char *name, char *str);

int				printchar(char *name, char c);

/*
	render.c
*/
int				draw_bg(t_data *img, t_info *info);

int				draw_wall(t_data *img, t_info *info);

/*
	check_map.c
*/
int				check_map(char *str);

int				parse_map(t_info *info, char *full_file);

int				valid_map(t_info *info);

#endif