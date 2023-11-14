/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiovana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:35:10 by mgiovana          #+#    #+#             */
/*   Updated: 2023/02/20 12:11:10 by mgiovana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_conv(va_list args, const char ktm)
{
	int	lenght;

	lenght = 0;
	if (ktm == 'c')
		lenght += ft_putchar(va_arg(args, int));
	else if (ktm == 's')
		lenght += ft_putstrn(va_arg(args, char *));
	else if (ktm == 'p')
		lenght += ft_putptrn(va_arg(args, uintptr_t));
	else if (ktm == 'd')
		lenght += ft_putnbrn(va_arg(args, int));
	else if (ktm == 'i')
		lenght += ft_putnbrn(va_arg(args, int));
	else if (ktm == 'u')
		lenght += ft_unsign(va_arg(args, int));
	else if (ktm == 'x')
		lenght += ft_hexa(va_arg(args, unsigned int), ktm);
	else if (ktm == 'X')
		lenght += ft_hexa(va_arg(args, unsigned int), ktm);
	return (lenght);
}

int	ft_printf(const char *ktm, ...)
{
	int		i;
	int		lenght;
	va_list	args;

	va_start(args, ktm);
	i = 0;
	lenght = 0;
	while (ktm[i])
	{
		if (ktm[i] == '%' && ktm[i + 1] == '%')
		{
			write(1, "%", 1);
			i++;
			lenght++;
		}
		else if (ktm[i] == '%')
			lenght += ft_print_conv(args, ktm[i++ + 1]);
		else
			lenght += ft_putchar(ktm[i]);
		i++;
	}
	va_end(args);
	return (lenght);
}
