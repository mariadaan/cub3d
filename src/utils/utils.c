#include "../../cub.h"

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

/*
	Free the malloced strings. If stage == 1, the full file needs to be freed
	Paths and map always need to be freed.
*/
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
