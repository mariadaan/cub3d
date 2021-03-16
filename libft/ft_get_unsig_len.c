/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_get_unsig_len.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdaan <mdaan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/08 13:59:57 by mdaan         #+#    #+#                 */
/*   Updated: 2021/01/12 15:35:03 by mdaan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int			ft_get_unsig_len(unsigned int n)
{
	int len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		if (n > 0)
			n = n / 10;
		else
			n = n / -10;
		len++;
	}
	return (len);
}
