/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiovana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:56:19 by mgiovana          #+#    #+#             */
/*   Updated: 2023/11/24 14:56:30 by mgiovana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//STUDIA TUTTO
void	add_pid_to_list(pid_t pid, t_pidNODE **pids)
{
	t_pidNODE	*new_node;
	t_pidNODE	*temp;

	new_node = malloc(sizeof(t_pidNODE));
	if (new_node == NULL)
	{
		perror("malloc");
		exit(1);
	}
	new_node->pid = pid;
	new_node->next = NULL;
	if (*pids == NULL)
		*pids = new_node;
	else
	{
		temp = *pids;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
}

void	execute_command(t_commands *current_cmd, t_exe *exec_data,
						t_env *env_list, t_pidNODE **pids)
{
	pid_t	pid;
	t_cmds	*cmd;

	if (exec_data->trigger == 0)
	{
		cmd = current_cmd;
		exec_data->trigger = 1;
	}
	if (current_cmd->next != NULL)
		initiate_pipe(exec_data);
	else
	{
		if (current_cmd->redirect & APPEND || current_cmd->redirect & OUTPUT)
			set_out_fd(exec_data, current_cmd->output);
		else
			set_out_fd(exec_data, cmd->output);
	}
	if (!check_or_exec_builtin(current_cmd, exec_data, env_list))
	{
		pid = fork_process(current_cmd, exec_data, env_list);
		add_pid_to_list(pid, pids);
	}
	rotator(exec_data);
}

//int	wait_for_child_processes(t_pidNODE	*pids, int	*exit_status)
{
	t_pidNODE	*temp;
	int			status;
	pid_t		terminated_pid;

	while (pids != NULL)
	{
		terminated_pid = waitpid(pids->pid, &status, 0);
		if (terminated_pid == -1)
		{
			perror("waitpid");
		}
		else
		{
			if (WIFEXITED(status))
				*exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				*exit_status = 128 + WTERMSIG(status);
			temp = pids;
			pids = pids->next;
			free(temp);
		}
	}
	return (*exit_status);
}

void	executor(t_commands *cmd, t_env *env_list)
{
	t_exec		exec_data;
	t_cmds		*current_command;
	t_pidNODE	*pids;
	int			exit_status;

	exit_status = 0;
	current_command = cmd;
	pids = NULL;
	exit_status = 0;
	exec_data.pipe_shift = 1;
	set_in_fd(&exec_data, cmd->input);
	exec_data.trigger = 0;
	while (current_command)
	{
		execute_command(current_command, &exec_data, env_list, &pids);
		current_command = current_command->next;
		env_list->exit_status = exit_status;
	}
	env_list->exit_status = wait_for_child_processes(pids, &exit_status);
}