/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiovana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:41:52 by mgiovana          #+#    #+#             */
/*   Updated: 2023/11/28 14:42:05 by mgiovana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup2_and_close(int from, int to)
{
	if (from > 2)
	{
		dup2(from, to);
		close(from);
	}
}

static void	execute_command(t_commands *cmd, t_env *env_list)
{
	if (!access(cmd->cmd, X_OK))
		execve(cmd->cmd, cmd->full_cmd,
			ft_create_env_array(env_list));
	else
		printf("%s: command not found\n", cmd->cmd);
}

// gestisce la duplicazione dei descrittori di file per implementare le pipe.
//Controlla pipe_shift per determinare quale parte della pipe deve essere duplicata.
static void	dup_pipe(t_exe *exec_data)
{
	if (exec_data->pipe_shift == 0)
	{
		dup2_and_close(exec_data->pipe1[READ], STDIN_FILENO);
		dup2_and_close(exec_data->pipe2[WRITE], STDOUT_FILENO);
		if (exec_data->pipe2[READ] > 2)
			close(exec_data->pipe2[READ]);
	}
	else
	{
		dup2_and_close(exec_data->pipe2[READ], STDIN_FILENO);
		dup2_and_close(exec_data->pipe1[WRITE], STDOUT_FILENO);
		if (exec_data->pipe1[READ] > 2)
			close(exec_data->pipe1[READ]);
	}
}

//chiude le pipe
static void	close_pipe(t_exe *exec_data)
{
	if (exec_data->pipe_shift == 0)
	{
		if (exec_data->pipe1[READ] != STDIN_FILENO)
			close(exec_data->pipe1[READ]);
		if (exec_data->pipe2[WRITE] != STDOUT_FILENO)
			close(exec_data->pipe2[WRITE]);
	}
	else
	{
		if (exec_data->pipe2[READ] != STDIN_FILENO)
			close(exec_data->pipe2[READ]);
		if (exec_data->pipe1[WRITE] != STDOUT_FILENO)
			close(exec_data->pipe1[WRITE]);
	}
}

//crea un nuovo processo tramite fork. Nel processo figlio, gestisce la duplicazione 
//dei descrittori di file per implementare le pipe e poi esegue il comando con execute_command. 
//Nel processo padre, chiude i descrittori di file associati alle pipe e restituisce il PID del processo figlio.
int	fork_process(t_commands	*cmd, t_exe *exec_data, t_env *env_list)
{
	int			pid;

	pid = fork();
	if (pid == 0)
	{
		dup_pipe(exec_data);
		execute_command(cmd, env_list);
		exit(127);
	}
	close_pipe(exec_data);
	return (pid);
}