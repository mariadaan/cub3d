/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_abs.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdaan <mdaan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/08 14:14:17 by mdaan         #+#    #+#                 */
/*   Updated: 2021/01/08 14:14:19 by mdaan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

unsigned int		ft_abs(int num)
{
	if (num < 0)
		return ((unsigned int)num * -1);
	return ((unsigned int)num);
}
