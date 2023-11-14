/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiovana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:20:44 by mgiovana          #+#    #+#             */
/*   Updated: 2023/02/20 11:55:20 by mgiovana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_ncount(char *buff)
{
	int	i;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] && buff[i] == '\n')
		i++;
	return (i);
}

char	*ft_exline(char *buff)
{
	int		i;
	int		x;
	int		len;
	char	*ex;

	x = 0;
	i = ft_ncount(buff);
	if (!buff[i])
	{
		free(buff);
		return (NULL);
	}
	len = ft_strlen2(buff) - i + 1;
	ex = ft_calloc2(sizeof(char), len);
	if (!ex)
		return (NULL);
	while (buff[i])
		ex[x++] = buff[i++];
	free(buff);
	return (ex);
}

char	*ft_newline(char *buff)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!buff[i])
		return (NULL);
	i = ft_ncount(buff);
	tmp = ft_calloc2(sizeof(char), i + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	while (buff[i] && buff[i] != '\n')
	{
		tmp[i] = buff[i];
		i++;
	}
	if (buff[i] && buff[i] == '\n')
		tmp[i] = '\n';
	return (tmp);
}

char	*ft_read(int fd, int *flag)
{
	char		*tmp;
	int			check;

	tmp = ft_calloc2(sizeof(char), BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	check = read(fd, tmp, BUFFER_SIZE);
	*flag = check;
	if (check == -1)
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*line;
	int			flag;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0))
		return (NULL);
	if (!buff)
		buff = ft_calloc2(sizeof(char), 1);
	flag = 1;
	while (flag > 0)
	{
		tmp = ft_read(fd, &flag);
		buff = ft_strjoin2(buff, tmp);
		free(tmp);
		if (ft_check_eol(buff) == 1)
			break ;
	}
	line = ft_newline(buff);
	buff = ft_exline(buff);
	return (line);
}
