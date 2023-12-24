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

//esegue i comandi integrati
int	ft_execute_buildin(t_commands *cmd, t_env **env_list)
{
	if (!ft_strcmp(cmd->cmd, "export"))
		return (ft_export(cmd->args, env_list));
	else if (!ft_strcmp(cmd->cmd, "env"))
		return (ft_env(*env_list));
	else if (!ft_strcmp(cmd->cmd, "cd"))
		return (ft_cd(cmd->args, *env_list));
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(cmd->cmd, "unset"))
		return (ft_unset(cmd->args, env_list));
	else if (!ft_strcmp(cmd->cmd, "echo"))
		return (ft_echo(cmd->args));
	else if (!ft_strcmp(cmd->cmd, "exit"))
		ft_exit_minihell(cmd, *env_list);
	return (0);
}

int	ft_cmd_size(t_commands *cmd)
{
	int		count;

	count = 0;
	while (cmd)
	{
		cmd = cmd->next;
		count ++;
	}
	return (count);
}

char	**ft_create_env_array(t_env	*env_list)
{
	t_env	*tmp_list;
	char	*str;
	char	**env_array;
	int		index;

	index = -1;
	tmp_list = env_list;
	env_array = (char **)ft_calloc(1, sizeof(char *));
	while (tmp_list)
	{
		str = NULL;
		if (!tmp_list->custom)
		{
			str = ft_strjoin_free(ft_strdup(tmp_list->var), ft_strdup("="));
			str = ft_strjoin_free(str, ft_strdup(tmp_list->value));
			env_array[++index] = str;
			env_array = ft_double_realloc(env_array, index + 1, index + 2);
		}
		tmp_list = tmp_list->next;
	}
	return (env_array);
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
