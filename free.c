/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiovana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:32:49 by mgiovana          #+#    #+#             */
/*   Updated: 2023/11/21 12:32:50 by mgiovana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_cmdlist(t_commands **cmd)
//libera la struttura t_commands
{
	t_commands	*cpy;

	cpy = *cmd;
	while (cpy)
	{
		*cmd = (*cmd)->next;
		if (cpy->cmd)
			free(cpy->cmd);
		if (cpy->args)
			ft_free_double_str(cpy->args);
		if (cpy->full_cmd)
			ft_free_double_str(cpy->full_cmd);
		if ((cpy->redirect & INPUT))
			free(cpy->from_file);
		if ((cpy->redirect & HEREDOC))
			ft_free_double_str(cpy->hdocs_end);
		if ((cpy->redirect & OUTPUT) || (cpy->redirect & APPEND))
			ft_free_double_str(cpy->to_file);
		free(cpy);
		cpy = *cmd;
	}
}
