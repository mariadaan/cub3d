#include <stdio.h>
#include "../libft.h"

int	printco(char *name, int x, int y)
{
	int	ret;

	ret = 0;
	if (ft_strlen(name) > 0)
		ret = printf("%-20s", name);
	ret = printf("( %d, %d )\n", x, y);
	return (ret);
}

int	printflco(char *name, double x, double y)
{
	int	ret;

	ret = 0;
	if (ft_strlen(name) > 0)
		ret = printf("%-20s", name);
	ret = printf("( %f, %f )\n", x, y);
	return (ret);
}
