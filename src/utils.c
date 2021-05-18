#include "cub.h"

/*
	Creates new img struct and saves xpm file into it
*/

int	xpm_to_img(t_img *img, char *filename)
{
	img->mlx = mlx_init();
	if (!(img->mlx))
		return (error_msg("Creating mlx pointer failed"));
	img->img = mlx_xpm_file_to_image(img->mlx, filename, &(img->width),
			&(img->height));
	if (!(img->img))
	{
		perror("FAIL");
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

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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

/*
	DELETE WHEN DONE
*/
void	print_info(t_info *info)
{
	// printnum("size struct", sizeof(*info));
	printf("x_render_size:    %d\n", info->x_size);
	printf("y_render_size:    %d\n", info->y_size);
	printf("n_path:           %s\n", info->no_path);
	printf("s_path:           %s\n", info->so_path);
	printf("w_path:           %s\n", info->we_path);
	printf("e_path:           %s\n", info->ea_path);
	printf("sprite_path:      %s\n", info->s_path);
	printf("floor_color:      %d\n", info->f_color);
	printf("ceiling_color:    %d\n", info->c_color);
	printf("map: \n");
	ft_put2darray(info->map, info->map_height);
	printnum("mapwidth", info->map_width);
	printnum("mapheight", info->map_height);
	printnum("spawn x", info->x_spawn);
	printnum("spawn y", info->y_spawn);
	printchar("spawn direction", info->spawn_dir);
}