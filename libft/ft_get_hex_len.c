/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_get_hex_len.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdaan <mdaan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/08 14:05:57 by mdaan         #+#    #+#                 */
/*   Updated: 2021/01/12 14:52:22 by mdaan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int			ft_get_hex_len(unsigned long long hex)
{
	int					base;
	unsigned long long	exp;
	int					len;

	base = 16;
	exp = 1;
	len = 1;
	while (hex / base / exp)
	{
		exp *= base;
		len++;
	}
	return (len);
}
