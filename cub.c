#include "cub.h"


int	get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

int	get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

int	get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

int	create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

// int main(void)
// {
// 	int r;
// 	int g;
// 	int b;

// 	// Red: 0x00FF0000;
// 	// Green: 0x0000FF00;
// 	// Blue: 0x000000FF;

// 	r = get_r(1683429);
// 	printf("%d\n", r);
// }

// int		main(void)
// {
// 	void	*mlx;
// 	void	*win;

// 	mlx = mlx_init();
// 	win = mlx_new_window(mlx, 960, 540, "Hello world!");
// 	mlx_loop(mlx);
// 	return (0);
// }



void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	put_horizontal(t_data *data, int x, int y, int len, int color)
{
	int i;

	i = 0;
	while (i < len)
	{
		my_mlx_pixel_put(data, x + i, y, color);
		i++;
	}
}

void	put_vertical(t_data *data, int x, int y, int len, int color)
{
	int i;

	i = 0;
	while (i < len)
	{
		my_mlx_pixel_put(data, x, y + i, color);
		i++;
	}
}

void	put_rect(t_data *data, int x, int y, int xlen, int ylen, int color)
{

	put_horizontal(data, x, y, xlen, color);
	put_horizontal(data, x, y + ylen, xlen, color);
	put_vertical(data, x, y, ylen, color);
	put_vertical(data, x + xlen, y, ylen, color);
}

void	fill_rect(t_data *data, int x, int y, int xlen, int ylen, int color)
{
	int i;

	i = 0;
	while(i < ylen)
	{
		put_horizontal(data, x, y + i, xlen, color);
		i++;
	}
}

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putbasenbr(unsigned int num, int base)
{
	char basestr[37] = "0123456789abcdefghijklmnopqrstuvwxyz";
	if (num >= (unsigned int)base)
		ft_putbasenbr(num / base, base);
	ft_putchar(basestr[num % base]);
}
void	print_components(int color)
{
	int r;
	int g;
	int b;

	r = get_r(color);
	g = get_g(color);
	b = get_b(color);
	printf("r: %d\n", r);
	printf("g: %d\n", g);
	printf("b: %d\n", b);
	ft_putbasenbr(r, 2);
	ft_putchar('\n');
	ft_putbasenbr(g, 2);
	ft_putchar('\n');
	ft_putbasenbr(b, 2);
	ft_putchar('\n');
}

int	destroy_window(t_data *img)
{
	mlx_destroy_window(img->mlx, img->win);
	exit(0);
	return (1);
}

int		move_rect(int keycode, int *x_pos, int *y_pos, t_data *img)
{
	if (keycode == LEFT)
		*x_pos -= 5;
	if (keycode == RIGHT)
		*x_pos += 5;
	if (keycode == UP)
		*y_pos += 5;
	if (keycode == DOWN)
		*y_pos -= 5;
	fill_rect(img, 0, 0, 960, 540 / 2, 0xB0F0FB);
	fill_rect(img, *x_pos, *y_pos, 200, 80, 0xFFFFFF);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	return (1);
}


int		key_release(int keycode, t_data *img)
{
	printf("keyrelease: %d\n", keycode);
	return (1);
}

int		key_press(int keycode, t_data *img)
{
	printf("keycode: %d\n", keycode);
	static int x_pos = 250;
	static int y_pos = 50;


	while (keycode >= 123 && keycode <= 126)
	{
		move_rect(keycode, &x_pos, &y_pos, img);
		if (mlx_hook(img->win, 3, 0, key_release, &img))
			break;
	}
	if (keycode == 53)
		destroy_window(img);
	// mlx_hook(img->win, 3, 0, exit_loop, &img);
	// mlx_loop(img->mlx);
	return (1);
}


void	gen_darker_color(int color, int factor)
{
	ft_putbasenbr(color, 2);
	ft_putchar('\n');
	print_components(color);
}

int		parse_map(int fd, t_info *info)
{
	char *line;
	char **split;

	while (get_next_line(fd, &line))
	{
		printf("%s\n", line);
		if (line[0] == 'R')
		{
			split = ft_split(line, ' ');
			info->x_render_size = ft_atoi(split[1]);
			info->y_render_size = ft_atoi(split[2]);
		}
			
	}
	printf("%s\n", line);
	return (1);
}

int		main(int argc, char *argv[])
{
	t_data		img;
	t_info		info;

	if (argc != 2)
		printf("Invalid arguments\n");

	int fd = open(argv[1], O_RDONLY);

	int ret = parse_map(fd, &info);

	if (ret == 0)
	{
		int width = 960;
		int height = 540;


		img.mlx = mlx_init();
		img.win = mlx_new_window(img.mlx, width, height, "Maria's cub3d");
		img.img = mlx_new_image(img.mlx, width, height);

		// img.img = mlx_xpm_file_to_image(img.mlx, "./textures/sample.xpm", &width, &height);

		/*
		** After creating an image, we can call `mlx_get_data_addr`, we pass
		** `bits_per_pixel`, `line_length`, and `endian` by reference. These will
		// ** then be set accordingly for the *current* data address.
		// */
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
													&img.endian);


		// // add_shade(0xB0F0FB);

		// put ceiling
		fill_rect(&img, 0, 0, width, height / 2, 0xB0F0FB);

		// put floor
		fill_rect(&img, 0, height / 2, width, height / 2, 0x68BC13);

		// // put clouds
		fill_rect(&img, 250, 50, 200, 80, 0xFFFFFF);
		// // fill_rect(&img, 50, 50, 200, 80, 0xFFFFFF);
		// // fill_rect(&img, 300, 10, 200, 80, 0xFFFFFF);
		// // fill_rect(&img, 750, 60, 200, 80, 0xFFFFFF);

		// gen_darker_color(0xB0F0FB, 1/4);
		mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
		// mlx_put_image_to_window(img.mlx, img.win, img.img, 0, height);
		// mlx_put_image_to_window(img.mlx, img.win, img.img, width, 0);
		// mlx_put_image_to_window(img.mlx, img.win, img.img, width, height);
		mlx_hook(img.win, DestroyNotify, 0, destroy_window, &img);

		mlx_hook(img.win, KeyPress, 0, key_press, &img);
		// mlx_hook(img.win, 3, 0, key_release, &img);
		mlx_loop(img.mlx);
	}
}
