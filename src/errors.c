#include "cub.h"

void	red(void)
{
	printf("\033[1;31m");
}

void	yellow(void)
{
	printf("\033[1;33m");
}

void	green(void)
{
	printf("\033[1;32m");
}

void	reset(void)
{
	printf("\033[0m");
}

int		error_msg(char *message)
{
	perror("FAIL");
	red();
	printf("\n%s\n\n", message);
	reset();
	return (1);
}

int		success_msg(char *message)
{
	green();
	printf("\n%s\n\n", message);
	reset();
	return (0);
}