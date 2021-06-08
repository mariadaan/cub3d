#include "cub.h"

void	red(void)
{
	printf("\033[1;31m");
}

void	green(void)
{
	printf("\033[1;32m");
}

void	reset(void)
{
	printf("\033[0m");
}

int	error_msg(char *message)
{
	red();
	printf("\n%s\n\n", message);
	reset();
	return (1);
}

int	success_msg(char *message)
{
	green();
	printf("\n%s\n\n", message);
	reset();
	return (0);
}
