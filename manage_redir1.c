/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redir1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiovana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 12:37:42 by mgiovana          #+#    #+#             */
/*   Updated: 2023/11/24 12:37:44 by mgiovana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_redirect(t_commands *cmd, char **cmd_table)
{
	int		count;
	int		len;
	int		redirect;
	int		old_redirect;

	count = -1;
	while (cmd_table && cmd_table[++count])
	{
		len = 0;
		if (ft_get_redirection(cmd_table[count]))
		{
			redirect = ft_get_redirection(cmd_table[count]);
			len ++;
			if ((redirect & HEREDOC) || (redirect & APPEND))
				len ++;
			old_redirect = cmd->redirect;
			cmd->redirect = redirect;
			if (ft_add_redirection(cmd_table, cmd, count, len))
				return (free(cmd_table), 1);
			cmd->redirect |= old_redirect;
			ft_arrange_table(cmd_table, count, len);
			count --;
		}
	}
	return (0);
}
