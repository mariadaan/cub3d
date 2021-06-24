#include "cub.h"

// Just some mlx functions, but better

/*
	Simplified version of mlx_put_image_to_window that always places the image
	in the upper left corner
*/
int	show_img(t_all *all)
{
	mlx_put_image_to_window(&(all->img.mlx), all->img.win, all->img.img, 0, 0);
	return (0);
}

/*
	Creates new img and saves xpm or png file into it
*/
int	file_to_img(t_img *img, char *filename)
{
	img->mlx = mlx_init();
	if (!(img->mlx))
		return (error_msg("Creating mlx pointer failed"));
	if (ft_strstr(filename, ".xpm"))
		img->img = mlx_xpm_file_to_image(img->mlx, filename, &(img->width),
				&(img->height));
	else if (ft_strstr(filename, ".png"))
		img->img = mlx_png_file_to_image(img->mlx, filename, &(img->width),
				&(img->height));
	if (!(img->img))
	{
		red();
		printf("\n\"%s\" does not exist.\n\n", filename);
		reset();
		return (1);
	}
	img->addr = mlx_get_data_addr(img->img, &(img->bits_per_pixel),
			&(img->line_length), &(img->endian));
	return (0);
}

/*
	Change the color of a pixel in an image on the given x and y location by
	altering the int color value on this location in img.addr
*/
void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
