#ifndef CUB_H
# define CUB_H

# include "mlx/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "keys.h"


typedef struct s_img {
	void			*mlx;
	void			*img;
	void			*win;
	char			*addr;
	int				bits_per_pixel;
	int				line_length; // in bytes (width / 4)
	int				endian;
	int				width; // in pixels
	int				height; // in pixels
}				t_img;

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

	double 			wallX; //where exactly the wall was hit
	int				x_tex; //x coordinate on the texture
	double			y_tex; //y coordinate on the texture
	double			y_tex_step;

	// double 			spriteX; //where exactly the sprite was hit
	// int				x_sprite; //x coordinate on the sprite
	// double			y_sprite; //y coordinate on the sprite
	// double			y_sprite_step;
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
	// char			*s_path;
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

/*
	init.c
*/
int				init_input(t_all *all, int argc, char *cub_file);

int				init_textures(t_all *all);

int				init_mlx(t_all *all);

int				init_raycaster(t_all *all);

/*
	parse.c NOG 1 FILE TEVEEL
*/

int				parse_all(int fd, t_info *info);

int				parse_int(char *line, int *size, int pos);

int				parse_path(char *full_file, char **path, char *id);

int				parse_color(char *line, unsigned int *color, char *id);

int				parse_map(t_info *info, char *full_file);

int				check_res(t_all *all);

/*
	check_map.c NOG 1 FILE TEVEEL
*/

int				find_map(char *str);

int				check_spawn(t_info *info);

int				get_spawn_pos(t_info *info);

int				check_firstlast(t_info *info);

int				check_map(t_info *info);

int				valid_map(t_info *info);

/*
	raycast.c
*/

void			set_ray_pos(t_all *all, int x);

void			set_ray_len(t_all *all);

void			perform_dda(t_all *all);

void			set_projection(t_all *all);

/*
	render.c
*/

int				draw_bg(t_all *all);

int				set_tex(t_all *all, t_img wall_img);

int				draw_tex(t_all *all, t_img wall_img, int spritelen);

int				draw_img(t_all *all);

/*
	hooks.c
*/

int				key_pressed(int keycode, t_all *all);

int				key_release(int keycode, t_all *all);

int				destroy_window(t_all *all);

/*
	move.c
*/

int				spawn_dir(t_all *all);

int				move_player(t_all *all, double x, double y);

int				rotate(t_all *all, double radius);


/*
	utils.c
*/

int				show_img(t_all *all);

int				file_to_img(t_img *img, char *filename);

void			put_pixel(t_img *img, int x, int y, int color);

void			put_hor_full(t_all *all, int y, int color);

int				is_notmap(char c);

void			print_info(t_info *info);

/*
	color.c
*/

int				create_rgb(int r, int g, int b);

int				get_r(int trgb);

int				get_g(int trgb);

int				get_b(int trgb);

/*
	color_utils.c
*/

void			print_components(int color);

int				gen_darker_color(int color, int factor);

int				darker_color(int color);

/*
	printvar.c
*/

int				printnum(char * name, int num);

int				printfloat(char *name, float num);

int				printstr(char *name, char *str);

int				printchar(char *name, char c);

int				printco(char *name, int x, int y);

int				printflco(char *name, double x, double y);

/*
	errors.c
*/

void			red(void);

void			green(void);

void			reset(void);

int				error_msg(char *message);

int				success_msg(char *message);

#endif
