#ifndef CUB_H
# define CUB_H

#include "mlxopengl/mlx.h"
// #include "troep/minilibx_mms_20191025_beta/mlx.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <stdio.h>
#include "X11.h"
#include "../get_next_line/get_next_line.h"
#include "../libft/libft.h"

#define LEFT 123
#define RIGHT 124
#define UP 125
#define DOWN 126

typedef struct	s_data {
	void	*mlx;
	void	*img;
	void	*win;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_object {
	int	x;
	int y;
	int	width;
	int	height;

}				t_object;

typedef struct s_info
{
	int x_render_size;
	int y_render_size;
	char *n_path;
	char *s_path;
	char *w_path;
	char *e_path;
	char *spr_path;
	int floor_color;
	int ceiling_color;
}				t_info;

// parse.c
int		parse_map(int fd, t_info *info);


// pixel.c
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

void	put_horizontal(t_data *data, int x, int y, int len, int color);

void	put_vertical(t_data *data, int x, int y, int len, int color);

void	put_rect(t_data *data, int x, int y, int xlen, int ylen, int color);

void	fill_rect(t_data *data, int x, int y, int xlen, int ylen, int color);


// hook_action.c
int		key_release(int keycode, t_data *img);

int		key_press(int keycode, t_data *img);

int		destroy_window(t_data *img);

// move.c
int		move_rect(int keycode, int *x_pos, int *y_pos, t_data *img);

#endif