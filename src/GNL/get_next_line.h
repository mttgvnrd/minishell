/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiovana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:51:58 by mgiovana          #+#    #+#             */
/*   Updated: 2023/02/20 11:58:10 by mgiovana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
int		ft_strlen2(const char *str);
char	*ft_strjoin2(char *s1, char *s2);
void	ft_bzero2(void *s, size_t n);
void	*ft_calloc2(size_t nmemb, size_t size);
int		ft_check_eol(char *buff);

#endif
