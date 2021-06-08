#include "../libft.h"

char	*create_line(char *str, char *needle)
{
	char	*line;
	int		index;

	line = ft_strstr(str, needle);
	if (line)
	{
		line = ft_strdup(line + 2);
		if (!line)
			return (NULL);
		index = get_findex(line, '\n');
		line[index] = '\0';
		return (line);
	}
	return (NULL);
}
