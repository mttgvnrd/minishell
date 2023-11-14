/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiovana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:55:02 by mgiovana          #+#    #+#             */
/*   Updated: 2023/02/20 12:09:46 by mgiovana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexa(unsigned int num, const char ktm)
{
	int	len;

	len = 0;
	if (num == 0)
	{
		write (1, "0", 1);
		return (1);
	}
	if (ktm == 'x')
		len += ft_putnbr_base(num, "0123456789abcdef");
	else if (ktm == 'X')
		len += ft_putnbr_base(num, "0123456789ABCDEF");
	return (len);
}
