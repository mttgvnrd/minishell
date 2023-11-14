/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiovana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:30:13 by mgiovana          #+#    #+#             */
/*   Updated: 2022/10/04 14:37:41 by mgiovana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<string.h>
#include<unistd.h>
#include<stdio.h>

void	*ft_memset(void *str, int c, size_t mod)
{
	unsigned char	*dest;
	size_t			i;

	i = 0;
	if (mod == 0)
		return (str);
	dest = str;
	while (i < mod)
	{
		dest[i] = (unsigned char)c;
		i++;
	}
	return (str);
}
/*
int	main(void)
{
	char	str[4] = "cane";

	puts(ft_memset(str, 'x', 4));
}*/
