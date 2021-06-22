#include "cub.h"
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

/*
	Change the color of the full width of the main image. Used for drawing the
	background.
*/
void	put_hor_full(t_all *all, int y, int color)
{
	int	i;

	i = 0;
	while (i < all->info.x_size)
	{
		put_pixel((&all->img), i, y, color);
		i++;
	}
}

/*
	Checks whether a character is a valid part of the map borders
*/
int	is_notmap(char c)
{
	if (!c)
		return (1);
	if (c == ' ' || c == '\n')
		return (1);
	else
		return (0);
}

int	free_all(t_info *info, int stage)
{
	if (stage)
		free(info->full_file);
	free(info->no_path);
	free(info->so_path);
	free(info->we_path);
	free(info->ea_path);
	free_2darray(info->map);
	return (1);
}
