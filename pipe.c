/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiovana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:18:04 by mgiovana          #+#    #+#             */
/*   Updated: 2023/11/24 15:18:07 by mgiovana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//imposta l'input del processo figlio attraverso la pipe.
void	set_in_fd(t_exe *exec_data, int fd)
{
	exec_data->pipe2[READ] = fd;
	exec_data->pipe1[READ] = -1;
}

//Se pipe_shift è 0, inizializza pipe2; altrimenti, inizializza pipe1.
void	initiate_pipe(t_exe *exec_data)
{
	if (exec_data->pipe_shift == 0)
		pipe(exec_data->pipe2);
	else
		pipe(exec_data->pipe1);
}

//imposta l'output del processo figlio attraverso la pipe
void	set_out_fd(t_exe *exec_data, int fd)
{
	if (exec_data->pipe_shift == 0)
		exec_data->pipe2[WRITE] = fd;
	else
		exec_data->pipe1[WRITE] = fd;
}

// Ruota l'indicatore pipe_shift tra 0 e 1
void	rotator(t_exe *exec_data)
{
	if (exec_data->pipe_shift == 0)
		exec_data->pipe_shift = 1;
	else
		exec_data->pipe_shift = 0;
}
