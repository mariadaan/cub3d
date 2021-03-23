#include <stdio.h>

int	printnum(char *name, int num)
{
	int	ret;

	ret = 0;
	ret = printf("%-20s", name);
	ret += printf("%d\n", num);
	return (ret);
}

int	printstr(char *name, char *str)
{
	int	ret;

	ret = 0;
	ret = printf("%-20s", name);
	ret += printf("%s\n", str);
	return (ret);
}
