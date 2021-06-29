#ifndef CUB_H
# define CUB_H

# include "mlx/mlx.h"
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft/libft.h"

# define LROTATE 123
# define RROTATE 124
# define FORWARD 13
# define BACKWARDS 1
# define LEFT 0
# define RIGHT 2
# define ESC 53

# define PRESS 2
# define RELEASE 3
# define DESTROY 17

typedef struct s_img {
	void			*mlx;
	void			*img;
	void			*win;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
}				t_img;

typedef struct s_ray {
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	double			step_size;
	double			const_rad;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			wall_x;
	int				x_tex;
	double			y_tex;
	double			y_tex_step;
	int				forward;
	int				backwards;
	int				left;
	int				right;
	int				rot_left;
	int				rot_right;
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
	init.c			Initialization functions
*/
int				init_input(t_all *all, int argc, char *cub_file);
int				init_textures(t_all *all);
int				init_mlx(t_all *all);
int				init_raycaster(t_all *all);

/*
	parse.c			Parsing cub file functions
*/
int				parse_res(char *full_file, int *size, int pos);
int				parse_color(char *full_file, unsigned int *color, char *id);
int				parse_map(t_info *info, char *full_file);
int				parse_tex(t_info *info);
int				parse_all(int fd, t_info *info);

/*
	check_info.c	Check cub file information functions
*/
int				check_res(t_all *all);
int				check_rgb(char **split, t_color *color_s);
int				check_spawn(t_info *info);
int				get_spawn_pos(t_info *info);

/*
	check_map.c		Check whether map is valid functions
*/
int				find_map(char *str);
int				check_row(char **map, int y_pos);
int				check_firstlast(char **map, int height);
int				check_spots(char **map, int x, int y);
int				check_map(t_info *info);

/*
	raycast.c		Raycasting calculation functions
*/
void			set_ray_pos(t_all *all, int x);
void			set_ray_len(t_ray *ray);
void			perform_dda(t_all *all);
void			set_projection(t_ray *ray, t_info *info);

/*
	render.c		Rendering image to window
*/
int				draw_bg(t_all *all);
int				set_tex(t_all *all, t_img wall_img);
int				draw_tex(t_all *all, t_img wall_img, int spritelen);
int				draw_img(t_all *all);

/*
	hooks.c			Key hook functions
*/
int				key_pressed(int keycode, t_all *all);
int				key_released(int keycode, t_all *all);
int				destroy_window(t_all *all);

/*
	move.c			Move player functions
*/
int				spawn_dir(t_all *all);
int				check_move(t_all *all);
int				move_player(t_all *all, double x, double y);
int				rotate(t_all *all, double radius);

/*
	utils_mlx.c		MLX functions but better
*/
int				show_img(t_all *all);
int				file_to_img(t_img *img, char *filename);
void			put_pixel(t_img *img, int x, int y, int color);

/*
	utils.c			Basic utilities
*/
void			put_hor_full(t_all *all, int y, int color);
int				is_notmap(char c);
int				free_all(t_info *info, int stage);

/*
	color.c			RGB color related functions
*/
int				create_rgb(int r, int g, int b);
int				get_r(int trgb);
int				get_g(int trgb);
int				get_b(int trgb);
int				gen_darker_color(int color, int factor);

/*
	errors.c		Error message printing functions
*/
void			red(void);
void			green(void);
void			reset(void);
int				error_msg(char *message);
int				success_msg(char *message);
#endif
