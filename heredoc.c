/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiovana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:36:21 by mgiovana          #+#    #+#             */
/*   Updated: 2023/11/23 12:43:24 by mgiovana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*command <<DELIMITER
 * Text here
  ...
DELIMITER

Il blocco di testo tra <<DELIMITER e DELIMITER 
viene passato come input al comando specificato. 
Il "DELIMITER" è un token che indica dove inizia 
e finisce il blocco di testo.*/

int	ft_read_hdocs(char *hdocs_end)
{
	char	*str;
	char	*delimiter;
	int		fd;

	delimiter = ft_strjoin(hdocs_end, "\n");
	fd = open("minhell_tmp.txt", O_RDWR | O_CREAT | O_APPEND, 0666);
	write(1, "heredoc> ", 9);
	str = get_next_line(0);
	while (ft_strcmp(str, delimiter))
	{
		write(fd, str, ft_strlen(str));
		free(str);
		write(1, "heredoc> ", 9);
		str = get_next_line(0);
		if (!str)
			break ;
	}
	free(delimiter);
	free(str);
	return (fd);
}

int	ft_here_doc(char **hdocs_end, t_commands *cmd)
{
	int		fd;	

	if (!access("minhell_tmp.txt", F_OK))
		unlink("minhell_tmp.txt");
	fd = ft_read_hdocs(hdocs_end[0]);
	close(fd);
	if (hdocs_end[1])
		return (-1);
	cmd->input = open("minhell_tmp.txt", O_RDONLY);
	return (fd);
}
