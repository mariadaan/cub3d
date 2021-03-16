/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdaan <mdaan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/18 15:42:05 by mdaan         #+#    #+#                 */
/*   Updated: 2020/12/09 13:39:23 by mdaan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
**	Returns:
**	Amount of chars till the end char (either '\n' or '\0' in gnl)
*/

int			ft_strlend(const char *s, char end)
{
	int len;

	if (!s)
		return (0);
	len = 0;
	while (s[len] && s[len] != end)
		len++;
	return (len);
}

/*
**	Description:
**	Copies src string into dst if src exists.
*/

void		ft_strcpy(char *dst, const char *src)
{
	int i;

	if (!src)
		return ;
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

/*
**	Desciption:
**	Modifies string s to the part after char c. This happens by copying
**	the part after c to the beginning of the string. Pointer is not moved.
**
**	Returns:
**	1 if char c is in string
**	0 if char c is not in string
*/

int			ft_modstr(char *s, char c)
{
	int i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			ft_strcpy(s, s + i + 1);
			return (1);
		}
		i++;
	}
	s[0] = '\0';
	return (0);
}
