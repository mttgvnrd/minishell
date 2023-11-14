/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiovana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:47:51 by mgiovana          #+#    #+#             */
/*   Updated: 2022/10/07 12:01:45 by mgiovana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	i++;
	while (--i)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)(s + i));
	}
	if (s[0] == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}
