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
	double pos_x;
	double pos_y;	//x and y start position
	double dir_x; //initial direction vector
	double dir_y;
	double plane_x; //the 2d raycaster version of camera plane
	double plane_y;
	int w;
	int h;
	double camera_x; //x-coordinate in camera space
	double ray_dir_x;
	double ray_dir_y;
	//which box of the map we're in
	int map_x;
	int map_y;

	//length of ray from current position to next x or y-side
	double side_dist_x;
	double side_dist_y;

	 //length of ray from one x or y-side to next x or y-side
	double delta_dist_y;
	double delta_dist_x;
	double perp_wall_dist;

	//what direction to step in x or y-direction (either +1 or -1)
	int step_x;
	int step_y;

	int hit; //was there a wall hit?
	int side; //was a NS or a EW wall hit?

	double move_speed; //the constant value is in squares/second
	double rot_speed; //the constant value is in radians/second

	double time;
	double old_time;
}		t_ray;

typedef struct s_info
{
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

/*
	pixel.c
*/
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);

void			put_horizontal(t_data *data, int x, int y, int len, int color);

void			put_vertical(t_data *data, int x, int y, int len, int color);

void			put_rect(t_data *data, int x, int y, int xlen, int ylen, int color);

void			fill_rect(t_data *data, int x, int y, int xlen, int ylen, int color);

void	gradient_bg(t_all *all);

void	gradient_rect(t_all *all, int y_start, int color);

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
int	create_rgb(int r, int g, int b);

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

#endif