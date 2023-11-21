/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiovana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:49:50 by mgiovana          #+#    #+#             */
/*   Updated: 2023/11/21 15:50:03 by mgiovana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cmd_analysis(t_commands *cmd, t_env **env_list)
//DA FINIRE
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