/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdaan <mdaan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/04 12:59:32 by mdaan         #+#    #+#                 */
/*   Updated: 2021/03/09 16:59:27 by mdaan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 20

# include <stdlib.h>
# include <unistd.h>

int		get_next_line(int fd, char **line);
int		ft_modstr(char *s, char c);
int		ft_strlend(const char *s, char end);
void	ft_strcpy(char *dst, const char *src);

#endif
