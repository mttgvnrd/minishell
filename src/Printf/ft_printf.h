/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiovana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:54:06 by mgiovana          #+#    #+#             */
/*   Updated: 2023/02/20 12:12:01 by mgiovana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>

int		ft_printf(const char *ktm, ...);
int		ft_strlen3(const char *str);
int		ft_putchar(int c);
int		ft_putstrn(char *str);
int		ft_putptrn(uintptr_t ptr);
int		ft_putnbrn(int num);
char	*ft_itoa2(long int n);
int		ft_unsign(int num);
int		ft_hexa(unsigned int num, const char ktm);
int		ft_putnbr_base(unsigned int nbr, char *base);

#endif
