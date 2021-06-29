#include "../cub.h"

/*
	The initialization functions are called from the main. If one of the init
	functions or the draw_img function returns 1, an error has occurred and the
	program will be exited. When all necessary values are set correctly, the
	first image is rendered and shown in the window. 

	If a key is pressed, mlx_hook calls the key_pressed function. This will move
	the player and modify the image that is shown in the window. The window
	stays the same throughout the entire program.
*/

int	main(int argc, char *argv[])
{
	t_all	all;

	ft_bzero(&all, sizeof(all));
	if (init_input(&all, argc, argv[1])
		|| init_textures(&all)
		|| init_mlx(&all)
		|| init_raycaster(&all)
		|| draw_img(&all)
		|| show_img(&all))
		return (1);
	mlx_hook(all.img.win, DESTROY, 0, &destroy_window, &all);
	mlx_hook(all.img.win, PRESS, 0, &key_pressed, &all);
	mlx_hook(all.img.win, RELEASE, 0, &key_released, &all);
	mlx_loop_hook(all.img.mlx, &check_move, &all);
	mlx_loop(all.img.mlx);
	return (0);
}
