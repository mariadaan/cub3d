/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_count_numbers.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdaan <mdaan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/08 14:11:20 by mdaan         #+#    #+#                 */
/*   Updated: 2021/01/08 14:12:25 by mdaan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_count_numbers(char *s)
{
	int		digit_count;

	digit_count = 0;
	while (ft_isdigit(*s))
	{
		digit_count++;
		s++;
	}
	return (digit_count);
}
