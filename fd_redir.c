/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiovana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:18:02 by mgiovana          #+#    #+#             */
/*   Updated: 2023/11/23 14:18:17 by mgiovana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_infile_fd(t_commands *cmd)
{
	cmd->input = 0;
	if (!cmd->from_file)
		return ;
	if (access(cmd->from_file, F_OK | R_OK))
	{
		if (access(cmd->from_file, F_OK))
			printf("minihell: %s: %s\n", strerror(errno), cmd->from_file);
	}
	else
		cmd->input = open(cmd->from_file, O_RDONLY);
}

//impostare correttamente il file descriptor di output per un comando
void	ft_outfile_fd(t_commands *cmd, char *to_file, int redirect)
{
	int	flag;

	flag = 0;
	cmd->output = STDOUT_FILENO;
	if (redirect & OUTPUT)
		flag |= O_TRUNC;
	else if (redirect & APPEND)
		flag |= O_APPEND;
	if (!access(to_file, F_OK | W_OK))
		cmd->output = open(to_file, O_WRONLY | flag);
	else if (!access(to_file, F_OK))
		printf("minihell: %s: %s\n", strerror(errno), to_file);
	else
		cmd->output = open(to_file, O_RDWR | O_CREAT | flag, 0666);
}

//agisce come coordinatore per le diverse fasi 
//di gestione della redirezione del comando
void	ft_execute_redirection(t_commands *cmd)
{
	int	count;

	count = -1;
	if ((cmd->redirect & INPUT))
		ft_infile_fd(cmd);
	if ((cmd->redirect & HEREDOC))
		while (cmd->hdocs_end[++count])
			ft_here_doc(&cmd->hdocs_end[count], cmd);
	if ((cmd->redirect & OUTPUT) || (cmd->redirect & APPEND))
	{
		count = -1;
		while (cmd->to_file[++count])
			ft_outfile_fd(cmd, cmd->to_file[count], cmd->redirect);
	}
}
