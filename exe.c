/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiovana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:49:50 by mgiovana          #+#    #+#             */
/*   Updated: 2023/11/23 12:10:14 by mgiovana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute_buildin(t_commands *cmd, t_env **env_list)
{
	if (!ft_strcmp(cmd->cmd, "export"))
		return (ft_export(cmd->args, env_list));//////////////////
	else if (!ft_strcmp(cmd->cmd, "env"))
		return (ft_env(*env_list));//////////////////
	else if (!ft_strcmp(cmd->cmd, "cd"))
		return (ft_cd(cmd->args, *env_list));//////////////////
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		return (ft_pwd());//////////////////
	else if (!ft_strcmp(cmd->cmd, "unset"))
		return (ft_unset(cmd->args, env_list));//////////////////
	else if (!ft_strcmp(cmd->cmd, "echo"))
		return (ft_echo(cmd->args));//////////////////
	else if (!ft_strcmp(cmd->cmd, "exit"))
		ft_exit_minihell(cmd, *env_list);//////////////////
	return (0);
}

//analisi dei comandi della lista di strutture t_commands
//ed inizio esecuzione
void	ft_init_exe(t_commands *cmd, t_env **env_list)
{
	t_commands	*tmp;

	cmd->input = STDIN_FILENO;
	cmd->output = STDOUT_FILENO;
	tmp = cmd;
	while (tmp)
	{
		ft_execute_redirection(tmp);
		tmp = tmp->next;
	}
	executor(cmd, *env_list);
	ft_free_cmdlist(&cmd);
}
