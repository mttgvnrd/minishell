/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiovana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:52:51 by mgiovana          #+#    #+#             */
/*   Updated: 2023/11/16 15:52:53 by mgiovana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//libera la struttura t_commands
void	ft_free_cmdlist(t_commands **cmd)
{
	t_commands	*tmp;

	tmp = *cmds;
	while (tmp)
	{
		*cmds = (*cmds)->next;
		if (tmp->cmd)
			free(tmp->cmd);
		if (tmp->args)
			ft_free_double_str(tmp->args);
		if (tmp->full_cmd)
			ft_free_double_str(tmp->full_cmd);
		if ((tmp->redirect & INPUT))
			free(tmp->from_file);
		if ((tmp->redirect & HEREDOC))
			ft_free_double_str(tmp->hdocs_end);
		if ((tmp->redirect & OUTPUT) || (tmp->redirect & APPEND))
			ft_free_double_str(tmp->to_file);
		free(tmp);
		tmp = *cmds;
	}
}