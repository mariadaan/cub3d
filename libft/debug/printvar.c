#include <stdio.h>
#include "../libft.h"

int	printnum(char *name, int num)
{
	int	ret;

	ret = 0;
	if (ft_strlen(name) > 0)
		ret = printf("%-20s", name);
	ret += printf("%d\n", num);
	return (ret);
}

int	printfloat(char *name, float num)
{
	int	ret;

	ret = 0;
	if (ft_strlen(name) > 0)
		ret = printf("%-20s", name);
	ret += printf("%f\n", num);
	return (ret);
}

int	printstr(char *name, char *str)
{
	int	ret;

	ret = 0;
	if (ft_strlen(name) > 0)
		ret = printf("%-20s", name);
	ret += printf("%s\n", str);
	return (ret);
}

int	printchar(char *name, char c)
{
	int	ret;

	ret = 0;
	if (ft_strlen(name) > 0)
		ret = printf("%-20s", name);
	ret += printf("%c\n", c);
	return (ret);
}
