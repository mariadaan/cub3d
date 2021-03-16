#ifndef CUB_H
# define CUB_H

#include "mlxopengl/mlx.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <stdio.h>
#include "X11.h"
#include "gnl/get_next_line.h"
#include "libft/libft.h"

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

#endif