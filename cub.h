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

typedef struct s_rectangle {
	int				x;
	int				y;
	int				width;
	int				height;
	unsigned int	color;
}				t_rectangle;

typedef struct s_info
{
	int				x_render_size;
	int				y_render_size;
	char			*n_path;
	char			*s_path;
	char			*w_path;
	char			*e_path;
	char			*sprite_path;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	char			**map;
}				t_info;

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
int				get_t(int trgb);

int				get_r(int trgb);

int				get_g(int trgb);

int				get_b(int trgb);

unsigned int	create_trgb(int t, int r, int g, int b);

/*
	color_utils.c
*/
void			print_components(int color);

void			gen_darker_color(int color, int factor);

int	printnum(char * name, int num);
int	printstr(char *name, char *str);

#endif