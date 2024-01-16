/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiovana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:46:26 by mgiovana          #+#    #+#             */
/*   Updated: 2023/11/21 14:46:29 by mgiovana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_check_args(char *arg, char **cmd_args)
{
	if (!arg)
	{
		free(cmd_args);
		return (NULL);
	}
	return (cmd_args);
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

int	ft_count_lines(int fd)
{
	int		i;
	char	*line;

	if (fd < 0)
		return (-1);
	i = 1;
	line = get_next_line(fd);
	if (!line)
		return (0);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	return (i);
}

int	ft_go_home(int chdirrt, t_env *envp)
{
	const char	*home;

	home = getenv("HOME");
	if (home == NULL)
		return (perror("cd"), 1);
	chdirrt = chdir(home);
	if (chdirrt == -1)
		return (perror("cd"), 1);
	else
		ft_chdir_envp(envp);
	return (0);
}
